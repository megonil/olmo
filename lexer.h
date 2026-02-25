#ifndef olmo_lexer_h
#define olmo_lexer_h

#include "token.h"

#include <stddef.h>

typedef struct
{
	SourceMgr mgr;
	size_t	  line;
	char*	  c;
} Lexer;

void
LexerInit (Lexer* lexer, const char* filename);

Token
LexerTokenize (Lexer* lexer);

/// print the token
void
LexerDislex (Lexer* lexer, Token* token);

#endif // !olmo_lexer_h
