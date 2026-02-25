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
	RUN_TEST (test_table);
	RUN_TEST (test_string_table);
	RUN_TEST (test_num_table);
	RUN_TEST (test_lexer);

	return UNITY_END ();
}
