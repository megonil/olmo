#ifndef olmo_table_h
#define olmo_table_h

// open addressing
// linear probing
// hashmap

#include <stdint.h>

typedef uint32_t hash_t;

#define TABLE_INITIAL_CAP 16
#define TABLE_MAX_LOAD 0.75

#define default_name

#define define_tableitemstr(Name, K, V)                                   \
	typedef struct Name##TableItem                                        \
	{                                                                     \
		K	   key;                                                       \
		V	   value;                                                     \
		hash_t hash;                                                      \
	} Name##TableItem

#define define_tableitem(Name, K, V)                                      \
	typedef struct Name##TableItem                                        \
	{                                                                     \
		K key;                                                            \
		V value;                                                          \
	} Name##TableItem

#define define_tablestruct(Name)                                          \
	typedef struct Name##Table                                            \
	{                                                                     \
		Name##TableItem* entries;                                         \
		uint32_t		 cap;                                             \
		uint32_t		 size;                                            \
	} Name##Table

#define define_tablemethods(Name, K, V)                                   \
	void Name##TableInit (Name##Table* table);                            \
	void Name##TableFree (Name##Table* table);                            \
	int	 Name##TableInsert (Name##Table* table, K key, V value);          \
	V*	 Name##TableGet (Name##Table* table, K key);                      \
	int	 Name##TableContains (Name##Table* table, K key);                 \
	void Name##TableRemove (Name##Table* table, K key)

#define define_tablestr(Name, K, V)                                       \
	define_tableitemstr (Name, K, V);                                     \
	define_tablestruct (Name);                                            \
	define_tablemethods (Name, K, V)

#define define_table(Name, K, V)                                          \
	define_tableitem (Name, K, V);                                        \
	define_tablestruct (Name);                                            \
	define_tablemethods (Name, K, V)

define_tablestr (default_name, const char*, int);
define_tablestr (String, const char*, const char*);

define_table (Num, int, int);

#endif // !olmo_table_h
