#ifndef crit_sourcemgr_h
#define crit_sourcemgr_h

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

#endif // !crit_sourcemgr_h
