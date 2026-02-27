// these functions needed to free and init some things
#include "array.h"
#include "error.h"
#include "table.h"
#include "token.h"

#include <unistd.h>

KeywordTable keywords;
Err*		 errors_produced;

// at the start of main
void __attribute__ ((constructor))
app_init ()
{
#define X(Type, Str) {Str, Type},
	TableInitList (Keyword, &keywords, KEYWORDS_SPEC KEYWORDS);
#undef X

	errors_produced = Array (Err);
}

// at the end of program(exit or return in main)
void __attribute__ ((destructor))
app_clean ()
{
	KeywordTableFree (&keywords);
	ArrayFree (errors_produced);
}
