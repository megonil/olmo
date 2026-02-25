#include "../lexer.h"

#include "../token.h"
#include "unity.h"

void
test_lexer ()
{
	Lexer lexer;
	LexerFromSource (&lexer, "1");

	Token token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_INT (1, token.lit.value.i);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	Token eof = LexerTokenize (&lexer);
	TEST_ASSERT_EQUAL_INT (TEOF, eof.type);

	LexerDestroy (&lexer);

	LexerFromSource (&lexer, "123.24");
	token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_FLOAT (123.24, token.lit.value.d);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	LexerDestroy (&lexer);
	LexerFromSource (&lexer, "1e-10");

	token = LexerTokenize (&lexer);

	TEST_ASSERT_EQUAL_FLOAT (1e-10, token.lit.value.d);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	LexerDestroy (&lexer);
}
