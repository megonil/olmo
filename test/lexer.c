#include "../lexer.h"

#include "../token.h"
#include "unity.h"

#define update() token = LexerTokenize (&lexer);
#define starttest(source)                                                 \
	LexerFromSource (&lexer, source);                                     \
	update ();
#define endtest() LexerDestroy (&lexer)

void
test_lexer ()
{
	Lexer lexer;
	Token token;
	starttest ("1");

	TEST_ASSERT_EQUAL_INT (1, token.lit.value.i);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	update ();
	TEST_ASSERT_EQUAL_INT (TEOF, token.type);

	endtest ();
	starttest ("123.24");

	TEST_ASSERT_EQUAL_FLOAT (123.24, token.lit.value.d);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	endtest ();
	starttest ("1e-10");

	TEST_ASSERT_EQUAL_FLOAT (1e-10, token.lit.value.d);
	TEST_ASSERT_EQUAL_INT (TLiteral, token.type);

	endtest ();
	starttest ("'a'");

	TEST_ASSERT_EQUAL_INT ('a', token.lit.value.i);
	TEST_ASSERT_EQUAL_INT (LitChar, token.lit.type);

	endtest ();
	starttest ("\"abc\"");

	TEST_ASSERT_EQUAL_STRING ("abc", token.lit.value.t);
	TEST_ASSERT_EQUAL_INT (LitText, token.lit.type);

	endtest ();
	starttest ("\"abc\" '1' 1");

	TEST_ASSERT_EQUAL_STRING ("abc", token.lit.value.t);
	TEST_ASSERT_EQUAL_INT (LitText, token.lit.type);

	update ();

	TEST_ASSERT_EQUAL_INT ('1', token.lit.value.i);

	update ();

	TEST_ASSERT_EQUAL_INT (1, token.lit.value.i);
	endtest ();
	starttest ("for");

	TEST_ASSERT_EQUAL_INT (TFor, token.type);
	endtest ();

	starttest ("abcdef");

	TEST_ASSERT_EQUAL_INT (TName, token.type);
	TEST_ASSERT_EQUAL_STRING ("abcdef", token.lit.value.t);

	endtest ();
}
