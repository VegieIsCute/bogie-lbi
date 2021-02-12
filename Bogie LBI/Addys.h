int Identity1 = 24;
int Identity2 = 108;

unsigned int ADDRESS_deserialize = 0;
unsigned int ADDRESS_lua_newthread = 0;
unsigned int ADDRESS_lua_pushcclosure = 0;
unsigned int ADDRESS_lua_getfield = 0;
unsigned int ADDRESS_lua_setfield = 0;
unsigned int ADDRESS_lua_pushstring = 0;
unsigned int ADDRESS_lua_pcall = 0;
unsigned int ADDRESS_lua_pushvalue = 0;
unsigned int ADDRESS_lua_pushlstring = 0;

typedef int(__cdecl* deserialize_DEF)(unsigned int RState, const char* Name, const char* Bytecode, int Size);
typedef unsigned int(__cdecl* newthread_DEF)(unsigned int RState);
typedef void(__cdecl* pushcclosure_DEF)(unsigned int RState, unsigned int Address, int a2, int Upvalues, int a4);
typedef void(__cdecl* getfield_DEF)(unsigned int RState, int Index, const char* Name);
typedef void(__cdecl* setfield_DEF)(unsigned int RState, signed int Index, const char* Content);
typedef void(__cdecl* pushstring_DEF)(unsigned int RState, const char* String);
typedef bool(__cdecl* pcall_DEF)(unsigned int RState, int Args, int Result, int a3);
typedef void(__cdecl* pushvalue_DEF)(unsigned int RState, int Index);
typedef void(__cdecl* pushlstring_DEF)(unsigned int RState, const char* String, int Size);

deserialize_DEF r_deserialize;
newthread_DEF r_lua_newthread;
pushcclosure_DEF r_lua_pushcclosure;
getfield_DEF r_lua_getfield;
setfield_DEF r_lua_setfield;
pushstring_DEF r_lua_pushstring;
pcall_DEF r_lua_pcall;
pushvalue_DEF r_lua_pushvalue;
pushlstring_DEF r_lua_pushlstring;

void r_spawn(unsigned int RLS) {
	r_lua_getfield(RLS, -10002, "spawn");
	r_lua_pushvalue(RLS, -2);
	r_lua_pcall(RLS, 1, 0, 0);
}

uintptr_t Rebase(uintptr_t addy) {
	return (addy - 0x400000 + reinterpret_cast<uintptr_t>(GetModuleHandleA(NULL)));
}
unsigned int* GetLevelLoc(unsigned int RState)
{
	return reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(RState + Identity2) + Identity1);
}

unsigned int GetRState()
{
	return EyeStep::util::debug_r32(ADDRESS_lua_newthread + 3, EyeStep::R32_EBP, 8, 1)[0];
}

unsigned int CreateCall(unsigned int addy, int ArgCount)
{
	return EyeStep::util::createRoutine(unprotect(addy), ArgCount);
}

bool FindAddys()
{
	std::vector<unsigned int> __index = EyeStep::scanner::scan_xrefs("__index");
	std::vector<unsigned int> A1_CALLS = EyeStep::util::getCalls(EyeStep::util::getPrologue(EyeStep::scanner::scan_xrefs("*** Could not evaluate expression *** Error: %s")[0]));
	std::vector<unsigned int> MT_CALLS = EyeStep::util::getCalls(EyeStep::util::getPrologue(__index[0]));
	std::vector<unsigned int> NEWMT_CALLS = EyeStep::util::getCalls(EyeStep::util::getPrologue(MT_CALLS[0]));
	
	ADDRESS_deserialize = EyeStep::util::getPrologue(EyeStep::scanner::scan_xrefs(": bytecode version mismatch")[0]);
	ADDRESS_lua_pushlstring = EyeStep::util::getPrologue(EyeStep::util::getCalls(EyeStep::util::getPrologue(__index[2]))[4]);
	ADDRESS_lua_pushstring = EyeStep::util::getPrologue(EyeStep::util::getCalls(ADDRESS_deserialize).rbegin()[2]);
	ADDRESS_lua_getfield = EyeStep::util::getPrologue(NEWMT_CALLS[0]);
	ADDRESS_lua_setfield = EyeStep::util::getPrologue(NEWMT_CALLS.rbegin()[0]);
	ADDRESS_lua_pushvalue = EyeStep::util::getPrologue(NEWMT_CALLS.rbegin()[1]);
	ADDRESS_lua_pushcclosure = EyeStep::util::getPrologue(MT_CALLS.rbegin()[3]);
	ADDRESS_lua_newthread = EyeStep::util::getPrologue(A1_CALLS[1]);
	ADDRESS_lua_pcall = EyeStep::util::getPrologue(A1_CALLS[7]);

	return true;
}

bool SetAddys()
{
	r_deserialize = reinterpret_cast<deserialize_DEF>(CreateCall(ADDRESS_deserialize, 4));
	r_lua_newthread = reinterpret_cast<newthread_DEF>(CreateCall(ADDRESS_lua_newthread, 1));
	r_lua_pushlstring = reinterpret_cast<pushlstring_DEF>(CreateCall(ADDRESS_lua_pushlstring, 3));
	r_lua_getfield = reinterpret_cast<getfield_DEF>(CreateCall(ADDRESS_lua_getfield, 3));
	r_lua_setfield = reinterpret_cast<setfield_DEF>(CreateCall(ADDRESS_lua_setfield, 3));
	r_lua_pushcclosure = reinterpret_cast<pushcclosure_DEF>(CreateCall(ADDRESS_lua_pushcclosure, 5));
	r_lua_pushvalue = reinterpret_cast<pushvalue_DEF>(CreateCall(ADDRESS_lua_pushvalue, 2));
	r_lua_pcall = reinterpret_cast<pcall_DEF>(CreateCall(ADDRESS_lua_pcall, 4));
	r_lua_pushstring = reinterpret_cast<pushstring_DEF>(CreateCall(ADDRESS_lua_pushstring, 2));
	return true;
}
