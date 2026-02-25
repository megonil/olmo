#ifndef olmo_sourcemgr_h
#define olmo_sourcemgr_h

typedef struct
{
	const char* filename;
	char*		source;
} SourceMgr;

/// init, set source pointer. (uses SourceMgrNewFile)
void
SourceMgrInit (SourceMgr* mgr, const char* filename);

/// change filename and set source pointer
void
SourceMgrNewFile (SourceMgr* mgr, const char* filename);

typedef struct
{
	char* start;
	char* end;
} SmPos;

#endif // !olmo_sourcemgr_h
