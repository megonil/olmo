#include "../table.h"

#include "unity.h"

void
setUp (void)
{
}
void
tearDown (void)
{
}

void
test_table (void)
{
	Table table;
	TableInit (&table);

	TableInsert (&table, "key1", 100);
	TableInsert (&table, "key2", 200);

	int* v1 = TableGet (&table, "key1");
	TEST_ASSERT_NOT_NULL (v1);
	TEST_ASSERT_EQUAL_INT (100, *v1);

	TEST_ASSERT_TRUE (TableContains (&table, "key2"));

	TableRemove (&table, "key1");
	TEST_ASSERT_FALSE (TableContains (&table, "key1"));

	TableFree (&table);
}

void
test_string_table (void)
{
	StringTable table;
	StringTableInit (&table);

	StringTableInsert (&table, "user", "admin");
	StringTableInsert (&table, "mode", "debug");

	const char** val = StringTableGet (&table, "user");
	TEST_ASSERT_NOT_NULL (val);
	TEST_ASSERT_EQUAL_STRING ("admin", *val);

	TEST_ASSERT_TRUE (StringTableContains (&table, "mode"));

	StringTableFree (&table);
}

void
test_num_table (void)
{
	NumTable table;
	NumTableInit (&table);

	NumTableInsert (&table, 42, 1337);
	NumTableInsert (&table, 7, 777);

	int* val = NumTableGet (&table, 42);
	TEST_ASSERT_NOT_NULL (val);
	TEST_ASSERT_EQUAL_INT (1337, *val);

	TEST_ASSERT_TRUE (NumTableContains (&table, 7));

	NumTableRemove (&table, 42);
	TEST_ASSERT_FALSE (NumTableContains (&table, 42));

	NumTableFree (&table);
}

int
main (void)
{
	UNITY_BEGIN ();
	RUN_TEST (test_table);
	RUN_TEST (test_string_table);
	RUN_TEST (test_num_table);
	return UNITY_END ();
}
