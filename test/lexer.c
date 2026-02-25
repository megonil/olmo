#include "../lexer.h"

#include "../token.h"
#include "unity.h"

#define starttest(source) LexerFromSource (&lexer, source)
#define endtest() LexerDestroy (&lexer)

void
test_lexer ()
{
	Lexer lexer;
	starttest ("1");

	Token token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_INT (1, token.lit.value.i);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	Token eof = LexerTokenize (&lexer);
	TEST_ASSERT_EQUAL_INT (TEOF, eof.type);

	endtest ();
	starttest ("123.24");

	token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_FLOAT (123.24, token.lit.value.d);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	endtest ();
	starttest ("1e-10");

	token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_FLOAT (1e-10, token.lit.value.d);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	endtest ();
	starttest ("'a'");
	token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_INT ('a', token.lit.value.i);
	TEST_ASSERT_EQUAL_INT (LitChar, token.lit.type);
}
