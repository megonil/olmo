#ifndef olmo_token_h
#define olmo_token_h

#include <stdint.h>

// keywords
#define KEYWORDS                                                          \
	X (TFun, "fun")                                                       \
	X (TRet, "ret")                                                       \
	X (TIf, "if")                                                         \
	X (TElse, "else")                                                     \
	X (TFor, "for")                                                       \
	X (TWhile, "while")                                                   \
	X (TDo, "do")

#define SYMBOLS_2CHARD(M)                                                 \
	M (TRightShift, ">>", TGe, ">=")                                      \
	M (TLeftShift, "<<", TLe, "<=")

// 2 char symbols
#define SYMBOLS_2CHAR                                                     \
	X (TArrow, "->")                                                      \
	X (TStarStar, "**")                                                   \
	X (TEq, "==")                                                         \
	X (TNEq, "!=")

// these are being inserted to the keyword map
#define KEYWORDS_SPEC                                                     \
	X (TLiteral, "True")                                                  \
	X (TLiteral, "False")

#define SPECIAL_TOKENS                                                    \
	X (TType, "<type>")                                                   \
	X (TName, "<name>")                                                   \
	X (TLiteral, "<literal>")                                             \
	X (TEOF, "EOF")

#define M(Type1, Str1, Type2, Str2)                                       \
	X (Type1, Str1)                                                       \
	X (Type2, Str2)

#define TOKENS                                                            \
	KEYWORDS                                                              \
	SYMBOLS_2CHAR                                                         \
	SYMBOLS_2CHARD (M)                                                    \
	SPECIAL_TOKENS

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

typedef enum
{
	LitBool,
	LitChar,
	LitUint,
	LitInt,
	LitFloat,
	LitDouble,
	LitText,
	LitName,
} LiteralType;

typedef union
{
	double		d;
	uint64_t	i;
	const char* t;
} LiteralValue;

typedef struct
{
	LiteralType	 type;
	LiteralValue value;
} Literal;

typedef struct
{
	Literal	  lit; // optional
	TokenType type;
	int		  line;
} Token;

#define token(Type)                                                       \
	(Token)                                                               \
	{                                                                     \
		.type = Type                                                      \
	}
#define token_l(Field, Value, Type, Line)                                 \
	(Token)                                                               \
	{                                                                     \
		.lit  = {.value = {.Field = Value}, .type = Type},                \
		.type = TLiteral, .line = Line                                    \
	}

#define token_i(Value, Line) token_l (i, Value, LitInt, Line)
#define token_u(Value, Line) token_l (i, Value, LitUint, Line)
#define token_b(Value, Line) token_l (i, Value, LitBool, Line)
#define token_d(Value, Line) token_l (d, Value, LitDouble, Line)
#define token_f(Value, Line) token_l (d, Value, LitFloat, Line)
#define token_t(Value, Line) token_l (t, Value, LitText, Line)
#define token_n(Value, Line)                                              \
	(Token)                                                               \
	{                                                                     \
		.type = TName, .line = Line,                                      \
		.lit                                                              \
			= {.value = {.t = Value},                                     \
			   .type  = LitName }                                          \
	}
#define token_c(Value, Line) token_l (i, Value, LitChar, Line)

#endif // !olmo_token_h
