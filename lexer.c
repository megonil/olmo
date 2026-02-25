#include "lexer.h"

#include "sourcemgr.h"
#include "table.h"
#include "token.h"
#include "utils.h"

#include <assert.h>
#include <ctype.h>

#define cur lexer->c
#define next() cur++
#define peek(i) *(cur + i)

static table (KeywordTable, keywords);

void
LexerInit (Lexer* lexer, const char* filename)
{
	SourceMgrInit (&lexer->mgr, filename);
	KeywordTableInit (&keywords);
	lexer->c	= lexer->mgr.source;
	lexer->line = 1;
}

static int
isln (char* c)
{
#ifdef OLMO_UNIX
	return *c == '\n';
#elif defined(OLMO_WINDOWS)
	return *c == '\r' && *(c + 1) == '\n'
#endif
}

#define token(Type, Start, End)                                           \
	(Token)                                                               \
	{                                                                     \
		.pos = {.start = Start, .end = End}, .type = Type                 \
	}

static Token
number (Lexer* lexer)
{
	char* start	  = cur;
	int	  has_dot = 0;

	while (isdigit (*cur) || *cur == '.')
		{
			if (*cur == '.')
				{
					if (has_dot)
						{
							error ("two or more dots in number");
						}
					has_dot = 1;
				}
			next ();
		}

	Token result;
	char  temp = *cur;
	if (has_dot)
		{
			result = token (TNumber, start, cur);
		}
	else
		{
			result = token (TInteger, start, cur);
		}

	*cur = temp;
	return result;
}

static Token
string (Lexer* lexer)
{
}

static Token
ichar (Lexer* lexer)
{
}

static Token
ident (Lexer* lexer)
{
	char* start = cur;
	for (next (); isalpha (*cur); next ());

	char tmp = *cur;
	*cur	 = '\0';

	TokenType* type = KeywordTableGet (&keywords, start);
	Token	   result;
	if (type == 0)
		{
			result = token (*type, start, cur);
		}
	else
		{
			result = token (TName, start, cur);
		}

	*cur = tmp;
	return result;
}

static void
skip_comment (Lexer* lexer)
{
	while (!isln (lexer))
		{
			next ();
		}
}

#define doubletok(c, t, dc, dt)                                           \
	case c:                                                               \
		next ();                                                          \
		if (*cur == dc)                                                   \
			{                                                             \
				done (dt, cur - 1, cur);                                  \
			}                                                             \
		else                                                              \
			{                                                             \
				done (t, cur, cur);                                       \
			}                                                             \
		break;

#define done(t, start, end)                                               \
	result = token (t, start, end);                                       \
	goto known;

Token
LexerTokenize (Lexer* lexer)
{
	Token result;
	for (;;)
		{
			switch (*cur)
				{
					doubletok ('-', '-', '>', TArrow);

				case '"': return string (lexer);
				case '\'': return ichar (lexer);

				default:
					if (isspace (*cur))
						{
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
known:
	return result;
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
