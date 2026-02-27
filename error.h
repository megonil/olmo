#ifndef olmo_error_h
#define olmo_error_h
#include "array.h"

#include <stddef.h>
#define ln "\n"
#define at " at line %zu"

#define ERRORS                                                            \
	X (ErrUnfinishedTextLit, "unfinished text literal" at ln)             \
	X (ErrWrongCharLit, "wrong char literal" at ln)                       \
	X (ErrWrongEscapeSequence, "wrong escape sequence `%c`" at ln)        \
	X (ErrUnfinishedMultilineComment,                                     \
	   "unfinished multiline comment" at ln)                              \
	X (ErrExpectedNumber, "expected number" at ln)

typedef enum
{
#define X(Variant, Str) Variant,
	ERRORS
#undef X
} Err;

static const char* err_names[] = {
#define X(Variant, Str) Str,
	ERRORS
#undef X
};

extern Err* errors_produced;

#define Err2Str(err) (err_names[err])

#define error(E, ...)                                                     \
	fprintf (stderr, Err2Str (E), ##__VA_ARGS__);                         \
	ArrayPush (errors_produced, E)

#define errorr(E, ...)                                                    \
	error (E, ##__VA_ARGS__);                                             \
	return

#define lasterror() errors_produced[Len (errors_produced) - 1]

#undef ln
#endif // !olmo_error_h
