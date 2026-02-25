// these functions needed to free and init some things

#include "table.h"

#include <unistd.h>

KeywordTable keywords;

// at the start of main
void __attribute__ ((constructor))
init_keywords ()
{
#define X(Type, Str) {Str, Type},
	TableInitList (Keyword, &keywords, KEYWORDS);
#undef X
}

// at the end of program(exit or return in main)
void __attribute__ ((destructor))
clean_keywords ()
{
	KeywordTableFree (&keywords);
}
