#include "../lexer.h"

#include "../token.h"
#include "unity.h"

#define update() token = LexerTokenize (&lexer);
#define starttest(source)                                                 \
	LexerFromSource (&lexer, source);                                     \
	update ();
#define endtest() LexerDestroy (&lexer)

#define testh()                                                           \
	Lexer lexer;                                                          \
	Token token;

void
test_lexer_comments ()
{
	testh ();
	starttest ("# this is a comment");

	TEST_ASSERT_EQUAL_INT (TEOF, token.type);
	endtest ();
}
void
test_lexer_string ()
{
	testh ();
	starttest ("\"abc\n\x033\n\"");

	TEST_ASSERT_EQUAL_STRING ("abc\n\x033\n", token.lit.value.t);
	TEST_ASSERT_EQUAL_INT (LitText, token.lit.type);
	update ();

	TEST_ASSERT_EQUAL_INT (TEOF, token.type);
	endtest ();
}

void
test_lexer_char ()
{
	testh ();
	starttest ("'a'");

	TEST_ASSERT_EQUAL_INT ('a', token.lit.value.i);
	TEST_ASSERT_EQUAL_INT (LitChar, token.lit.type);
	update ();

	TEST_ASSERT_EQUAL_INT (TEOF, token.type);
	endtest ();

	starttest ("'\n' '\x033'");
	TEST_ASSERT_EQUAL_INT ('\n', token.lit.value.i);

	update ();
	TEST_ASSERT_EQUAL_INT ('\x033', token.lit.value.i);
	update ();
	TEST_ASSERT_EQUAL_INT (TEOF, token.type);
	endtest ();
}

void
test_lexer_ident ()
{
	testh ();
	starttest ("for");

	TEST_ASSERT_EQUAL_INT (TFor, token.type);
	endtest ();

	starttest ("abcdef");
	TEST_ASSERT_EQUAL_INT (TName, token.type);
	TEST_ASSERT_EQUAL_STRING ("abcdef", token.lit.value.t);
	endtest ();
}

void
test_lexer_generic ()
{
	testh ();

	starttest ("+ ) - *");

	TEST_ASSERT_EQUAL_INT ('+', token.type);
	update ();
	TEST_ASSERT_EQUAL_INT (')', token.type);

	update ();
	TEST_ASSERT_EQUAL_INT ('-', token.type);

	update ();
	TEST_ASSERT_EQUAL_INT ('*', token.type);

	endtest ();
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
	starttest ("-> >= >>")

		TEST_ASSERT_EQUAL_INT (TArrow, token.type);
	update ();
	TEST_ASSERT_EQUAL_INT (TGe, token.type);

	update ();
	TEST_ASSERT_EQUAL_INT (TRightShift, token.type);

	endtest ();
}
