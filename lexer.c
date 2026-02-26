#include "lexer.h"

#include "array.h"
#include "sourcemgr.h"
#include "table.h"
#include "token.h"
#include "utils.h"

#include <assert.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

#define cur lexer->c
#define next() cur++

static void
save (Lexer* lexer)
{
	ArrayPush (lexer->buffer, *lexer->c);
	next ();
}

#define peek(i) *(cur + i)

extern KeywordTable keywords;

void
LexerInit (Lexer* lexer, const char* filename)
{
	SourceMgrInit (&lexer->mgr, filename);

	lexer->c	  = lexer->mgr.source;
	lexer->line	  = 1;
	lexer->buffer = String ();
}

void
LexerFromSource (Lexer* lexer, char* source)
{
	lexer->c	  = source;
	lexer->line	  = 1;
	lexer->buffer = String ();
}
static void
readhex (Lexer* lexer)
{
	next ();
	int value = 0;

	for (int i = 0; i < 2; ++i)
		{
			int digit = 0;
			if (isdigit (*cur))
				{
					digit = *cur - '0';
				}
			else if (*cur >= 'a' && *cur <= 'f')
				{
					digit = *cur - 'a' + 10;
				}
			else if (*cur >= 'A' && *cur <= 'F')
				{
					digit = *cur - 'A' + 10;
				}

			value = (value << 4) | digit;
			ArrayPush (lexer->buffer, (char) value);
			return;
		}
}

static void
save_escape (Lexer* lexer)
{
	char c;
	if (*cur == '\\')
		{
			next ();
			switch (*cur)
				{
				case 'n': c = '\n'; break;
				case 'r': c = '\r'; break;
				case 'b': c = '\b'; break;
				case 'a': c = '\a'; break;
				case 't': c = '\t'; break;
				case 'v': c = '\v'; break;
				case 'f': c = '\f'; break;
				case '0': c = '\0'; break;
				case '\'': c = '\''; break;
				case '"': c = '"'; break;
				case 'x': readhex (lexer); return;
				case 'u': unimplemented ("wait");
				}
		}
	else
		{
			c = *cur;
		}

	next ();
	ArrayPush (lexer->buffer, c);
}

static bool
isln (char* c)
{
#ifdef OLMO_UNIX
	return *c == '\n';
#elif defined(OLMO_WINDOWS)
	return *c == '\r' && *(c + 1) == '\n'
#endif
}

#define flowerror()                                                       \
	note ("value overflow/underflow at line %zu", lexer->line);

static Token
number (Lexer* lexer)
{
	char* start = cur;

	double number = parse_double (start, &cur);

	switch (*cur)
		{
		case 'd': return token_d (number, lexer->line);
		case 'f':
			if (number > FLT_MAX || number < FLT_MIN)
				{
					flowerror ();
				}
			return token_f ((float) number, lexer->line);
		case 'u':
			if (number > UINT32_MAX)
				{
					flowerror ();
				}
		default:
			if (fractpart (number) != 0)
				{
					return token_d (number, lexer->line);
				}
			if (number > INT32_MAX || number < INT32_MIN)
				{
					flowerror ();
				}

			return token_i ((int32_t) number, lexer->line);
		}
}

/// string that this function produces
/// for now is just pointer to lexer buffer
static Token
text (Lexer* lexer)
{
	next (); // skip "

	// just save to buffer
	for (; *cur != '"' && *cur != '\0'; save_escape (lexer));

	if (*cur == '\0')
		{
			error ("unfinished string");
		}

	next (); // skip "

	return token_t (lexer->buffer, lexer->line);
}

static Token
ichar (Lexer* lexer)
{
	next (); // skip '

	save_escape (lexer);

	if (*cur != '\'')
		{
			error ("too many characters in char literal");
		}
	else if (*cur == '\0')
		{
			error ("unfinished char literal");
		}

	next ();
	return token_c (lexer->buffer[0], lexer->line);
}

/// same warning as for the text() function
static Token
ident (Lexer* lexer)
{
	while (isalpha (*cur) || *cur == '_')
		{
			save (lexer);
		}

	TokenType* type = KeywordTableGet (&keywords, lexer->buffer);
	if (type != NULL)
		{
			return token (*type);
		}
	else
		{
			return token_n (lexer->buffer, lexer->line);
		}
}

static void
skip_comment (Lexer* lexer)
{
	while (!isln (cur))
		{
			next ();
		}
}

#define doubletok(c, t, dc, dt)                                           \
	if (*cur == c)                                                        \
		{                                                                 \
			next ();                                                      \
			if (*cur == dc)                                               \
				{                                                         \
					next ();                                              \
					return token (dt);                                    \
				}                                                         \
			return token (t);                                             \
		}

#define ddoubletok(T1, Str1, T2, Str2)                                    \
	if (*cur == Str1[0])                                                  \
		{                                                                 \
			next ();                                                      \
			if (*cur == Str1[1])                                          \
				{                                                         \
					next ();                                              \
					return token (T1);                                    \
				}                                                         \
			if (*cur == Str2[1])                                          \
				{                                                         \
					next ();                                              \
					return token (T2);                                    \
				}                                                         \
			return token (Str1[0]);                                       \
		}

static Token
symbol_2char (Lexer* lexer)
{
#define X(Type, Str) doubletok (Str[0], Str[0], Str[1], Type)
	SYMBOLS_2CHAR
#undef X
	SYMBOLS_2CHARD (ddoubletok);

	next ();
	return token (peek (-1));
}

static void
skip_multilinecomment (Lexer* lexer)
{
	// skip start of the multiline comment
	next ();
	next ();

	while (*cur != '#' && peek (1) != '/' && *cur != '\0')
		{
			next ();
		}

	if (*cur == '\0')
		{
			error ("unfinished multiline comment");
		}

	// skip end of the multiline comment
	next ();
	next ();
}

Token
LexerTokenize (Lexer* lexer)
{
	StringClear (lexer->buffer);
	for (;;)
		{
			switch (*cur)
				{

				case '#': skip_comment (lexer); continue;
				case '\0': return token (TEOF);
				case '"': return text (lexer);
				case '\'': return ichar (lexer);
				case '\\':
					if (peek (1) == '#')
						{
							skip_multilinecomment (lexer);
							continue;
						}

				default:
					if (isspace (*cur))
						{
							next ();
							continue;
						}
					else if (isln (cur))
						{
							lexer->line++;
							continue;
						}

					if (isdigit (*cur))
						{
							return number (lexer);
						}
					if (isalpha (*cur))
						{
							return ident (lexer);
						}

					return symbol_2char (lexer);
				}
		}
}

static int lastline = 1;

void
LexerDislex (Lexer* lexer, Token* token)
{
	if (lexer->line > lastline)
		{
			printf ("\n");
			return;
		}

	if (token->type < TokensStart)
		{
			printf ("%c ", token->type);
		}
	else
		{
			printf ("%s ", Tt2Str (token->type));
		}
}

void
LexerDestroy (Lexer* lexer)
{
	ArrayFree (lexer->buffer);
}

#undef literal
