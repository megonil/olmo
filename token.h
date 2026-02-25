#ifndef olmo_token_h
#define olmo_token_h

#include "sourcemgr.h"

#include <stdint.h>

#define TOKENS                                                            \
	X (TFun, "fun")                                                       \
	X (TRet, "ret")                                                       \
	X (TIf, "if")                                                         \
	X (TElse, "else")                                                     \
	X (TWhile, "while")                                                   \
	X (TDo, "do")                                                         \
	X (TFor, "for")                                                       \
	X (TArrow, "->")                                                      \
	X (TType, "<type>")                                                   \
	X (TName, "<name>")                                                   \
	X (TInteger, "<integer>")                                             \
	X (TNumber, "<number>")                                               \
	X (TString, "<string>")

#define tokstart (UINT8_MAX + 1)

typedef enum : uint16_t
{
	// all ASCII symbols represented with their ASCII values
	TokensStart = tokstart,
#define X(Token, Str) Token,
	TOKENS
#undef X
} TokenType;

static const char* ttype_names[] = {
#define X(Token, Str) Str,
	TOKENS
#undef X
};

#define Tt2Str(tt) ttype_names[tt - tokstart]

typedef struct
{
	SmPos	  pos;
	TokenType type;
} Token;

#endif // !olmo_token_h
