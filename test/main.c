#include "lexer.c"
#include "table.c"
#include "unity.h"
#include "unity_internals.h"

void
setUp (void)
{
}
void
tearDown (void)
{
}

int
main (void)
{
	UNITY_BEGIN ();
	// utilities testing
	RUN_TEST (test_table);
	RUN_TEST (test_string_table);
	RUN_TEST (test_num_table);

	// actual language
	RUN_TEST (test_lexer_generic);
	RUN_TEST (test_lexer_ident);
	RUN_TEST (test_lexer_string);
	RUN_TEST (test_lexer_char);
	RUN_TEST (test_lexer_comments);

	return UNITY_END ();
}
