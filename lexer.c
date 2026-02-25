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
	for (; *cur != '"' && *cur != '\0'; save (lexer));

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

	char val = *cur;
	next ();

	if (*cur != '\'')
		{
			error ("too many characters in char literal");
		}
	else if (*cur == '\0')
		{
			error ("unfinished char literal");
		}

	next ();
	return token_c (val, lexer->line);
}

static Token
ident (Lexer* lexer)
{
	unimplemented ("keywords lexing");
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
	case c:                                                               \
		next ();                                                          \
		if (*cur == dc)                                                   \
			{                                                             \
				return token (dt);                                        \
			}                                                             \
		else                                                              \
			{                                                             \
				return token (t);                                         \
			}

Token
LexerTokenize (Lexer* lexer)
{
	StringClear (lexer->buffer);
	for (;;)
		{
			switch (*cur)
				{
					doubletok ('-', '-', '>', TArrow);

				case '#': skip_comment (lexer); continue;
				case '\0': return token (TEOF);
				case '"': return text (lexer);
				case '\'': return ichar (lexer);

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
					else if (isalpha (*cur))
						{
							return ident (lexer);
						}
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
