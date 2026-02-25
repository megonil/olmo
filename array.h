#ifndef olmo_Array_h
#define olmo_Array_h

#include <stddef.h>

typedef void (PrintFunction (void*));

typedef struct
{
	size_t len;
	size_t cap;
	size_t itemsize;
} ArrayHeader;

#define CAP_INITIAL 8

#define Array(T) (T*) ArrayInit (sizeof (T), CAP_INITIAL)
#define Arrayc(T, cap) (T*) ArrayInit (sizeof (T), cap)
#define ArrayH(arr) ((ArrayHeader*) (arr) - 1)
#define Cap(arr) ArrayH (arr)->cap
#define Len(arr) ArrayH (arr)->len
#define ArrayItemsize(arr) ArrayH (arr)->itemsize
#define ArrayEmpty(arr) (Len (arr) == 0)
#define ArrayReserve(arr, items) arr = ArrayResize (arr, items)
#define ArrayJpush(arr, val) arr[Len (arr)++] = val
#define ArrayInc(arr) Len (arr)++
#define ArrayPush(arr, val)                                               \
	ArrayReserve (arr, 1);                                                \
	ArrayJpush (arr, val)

#define ArrayPop(arr, T) (T) arr[Len (arr)--]
#define foreach(arr, name) for (int name = 0; name < Len (arr); ++name)

#define String() Array (char)
#define StringClear(arr)                                                  \
	arr[0]	  = '\0';                                                     \
	Len (arr) = 0;

/// Init Array
void*
ArrayInit (size_t itemsize, size_t capacity);

/// Resize Array if needed so it can fit another n elements
void*
ArrayResize (void* array, size_t n);

void
ArrayFree (void* array);

/// for each element in array call PrintFunction
void
ArrayPrint (void* array, PrintFunction fn);

#endif // !olmo_Array_h
