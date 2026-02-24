#ifndef olmo_array_h
#define olmo_array_h

#include <stddef.h>

typedef void (PrintFunction (void*));

typedef struct
{
	size_t len;
	size_t cap;
	size_t itemsize;
} ArrayHeader;

#define error(fmt, ...)                                                   \
	printf ("error: " fmt "\n", ##__VA_ARGS__);                           \
	exit (1)

#define cast(v, T) (T) (v)

#define CAP_INITIAL 8

#define array(T) (T*) array_init (sizeof (T), CAP_INITIAL)
#define arrayc(T, cap) (T*) array_init (sizeof (T), cap)
#define array_header(arr) ((ArrayHeader*) (arr) - 1)
#define cap(arr) array_header (arr)->cap
#define len(arr) array_header (arr)->len
#define array_itemsize(arr) array_header (arr)->itemsize
#define array_empty(arr) (len (arr) == 0)
#define array_reserve(arr, items) arr = array_resize (arr, items)
#define array_jpush(arr, val) arr[len (arr)++] = val
#define array_inc(arr) len (arr)++
#define array_push(arr, val)                                              \
	array_reserve (arr, 1);                                               \
	array_jpush (arr, val)

#define array_pop(arr, T) (T) arr[len (arr)--]
#define foreach(arr, name) for (int name = 0; name < len (arr); ++name)

/// Init array
void*
array_init (size_t itemsize, size_t capacity);

/// Resize array if needed so it can fit another n elements
void*
array_resize (void* array, size_t n);

void
array_free (void* array);

void
array_print (void* array, PrintFunction fn);

#endif // !olmo_array_h
