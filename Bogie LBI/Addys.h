enum RType
{
	TNIL = 0,
	TBOOLEAN = 1,
	TNUMBER = 4,
	TSTRING = 5,
	TFUNCTION = 8,
	TUSERDATA = 6,
	TTABLE = 7
};

int Identity1 = 24;
int Identity2 = 108;

unsigned int ADDRESS_RetcheckJMP = 0x2AF57B0;
unsigned int ADDRESS_Index2Adr = 0x1459FA0;

unsigned int ADDRESS_deserialize = 0x1465A50;
unsigned int ADDRESS_lua_type = 0x145C3E0;
unsigned int ADDRESS_lua_tonumber = 0x145C060;
unsigned int ADDRESS_lua_newthread = 0x145AA70;
unsigned int ADDRESS_lua_pushcclosure = 0x145ADF0;
unsigned int ADDRESS_lua_getfield = 0x145A570;
unsigned int ADDRESS_lua_setfield = 0x145BA20;
unsigned int ADDRESS_lua_pushstring = 0x145B100;
unsigned int ADDRESS_lua_pcall = 0x145ACE0;
unsigned int ADDRESS_lua_pushvalue = 0x145B2B0;
unsigned int ADDRESS_lua_pushnumber = 0x145B0A0;
unsigned int ADDRESS_luaL_checktype = 0x145C900;
unsigned int ADDRESS_lua_pushlstring = 0x145AFE0;
unsigned int ADDRESS_lua_gettop = 0x145A740;

typedef int(__cdecl* deserialize_DEF)(uint32_t RState, const char* Name, const char* Bytecode, int Size);
typedef void(__cdecl* pushlstring_DEF)(uint32_t RState, const char* String, int Size);
typedef void(__cdecl* getfield_DEF)(uint32_t RState, int Index, const char* Name);
typedef void(__cdecl* settop_DEF)(uint32_t RState, int Index);
typedef void(__cdecl* setfield_DEF)(uint32_t RState, signed int Index, const char* Content);
typedef void(__cdecl* pushcclosure_DEF)(uint32_t RState, uint32_t Address, int a2, int Upvalues, int a4);
typedef void(__cdecl* pushvalue_DEF)(uint32_t RState, int Index);
typedef int(__cdecl* gettop_DEF)(uint32_t RState);
typedef bool(__cdecl* iscfunction_DEF)(uint32_t RState, int Index);
typedef void(__cdecl* pushboolean_DEF)(uint32_t RState, bool Bool);
typedef int(__cdecl* type_DEF)(uint32_t RState, int Index);
typedef int(__cdecl* L_error_DEF)(uint32_t RState, const char* ErrorMSG);
typedef char* (__cdecl* tolstring_DEF)(uint32_t RState, int Index, size_t* Size);
typedef void(__cdecl* createtable_DEF)(uint32_t RState, int a1, int a2);
typedef bool(__cdecl* pcall_DEF)(uint32_t RState, int a1, int a2, int a3);
typedef int(__cdecl* getmetatable_DEF)(uint32_t RState, int Index);
typedef void(__cdecl* setreadonly_DEF)(uint32_t RState, uint32_t Index, bool Value);
typedef void(__cdecl* rawseti_DEF)(uint32_t RState, uint32_t a1, uint32_t a2);
typedef bool(__cdecl* toboolean_DEF)(uint32_t RState, int Index);
typedef uintptr_t(__cdecl* newthread_DEF)(uintptr_t RState);
typedef void(__cdecl* setmetatable_DEF)(uintptr_t RState, int Index);
typedef void(__cdecl* call_DEF)(uint32_t RState, int a1, int a2);
typedef void(__cdecl* pushstring_DEF)(uint32_t RState, const char* String);
typedef uintptr_t (__cdecl* index2adr_DEF) (uintptr_t RState, int Index);
typedef double(__cdecl* DEF_r_lua_tonumber)(unsigned int RState, int Index);

DEF_r_lua_tonumber r_lua_tonumber;
deserialize_DEF r_deserialize;
pushlstring_DEF r_lua_pushlstring;
getfield_DEF r_lua_getfield;
setfield_DEF r_lua_setfield;
pushcclosure_DEF r_lua_pushcclosure;
pushvalue_DEF r_lua_pushvalue;
gettop_DEF r_lua_gettop;
type_DEF r_lua_type;
pcall_DEF r_lua_pcall;
toboolean_DEF r_lua_toboolean;
newthread_DEF r_lua_newthread;
pushstring_DEF r_lua_pushstring;
index2adr_DEF r_index2adr;

void r_spawn(unsigned int RLS) {
	r_lua_getfield(RLS, -10002, "spawn");
	r_lua_pushvalue(RLS, -2);
	r_lua_pcall(RLS, 1, 0, 0);
}

unsigned int Rebase(unsigned int Address)
{
	return (Address - 0x400000 + reinterpret_cast<unsigned int>(GetModuleHandleA(0)));
}

unsigned int* GetLevelLoc(unsigned int RState)
{
	return reinterpret_cast<unsigned int*>(*reinterpret_cast<unsigned int*>(RState + Identity2) + Identity1);
}

unsigned int GetRState()
{
	return EyeStep::util::debug_r32(Rebase(ADDRESS_Index2Adr) + 3, EyeStep::R32_EBP, 8, 1)[0];
}

uint32_t CreateCall(uint32_t addy, int ArgCount)
{
	return EyeStep::util::createRoutine(Rebase(addy), ArgCount);
}

bool SetupAddys()
{
	r_deserialize = reinterpret_cast<deserialize_DEF>(CreateCall(ADDRESS_deserialize, 4));
	r_lua_newthread = reinterpret_cast<newthread_DEF>(CreateCall(ADDRESS_lua_newthread, 1));
	r_lua_pushlstring = reinterpret_cast<pushlstring_DEF>(CreateCall(ADDRESS_lua_pushlstring, 3));
	r_lua_getfield = reinterpret_cast<getfield_DEF>(CreateCall(ADDRESS_lua_getfield, 3));
	r_lua_setfield = reinterpret_cast<setfield_DEF>(CreateCall(ADDRESS_lua_setfield, 3));
	r_lua_pushcclosure = reinterpret_cast<pushcclosure_DEF>(CreateCall(ADDRESS_lua_pushcclosure, 5));
	r_lua_pushvalue = reinterpret_cast<pushvalue_DEF>(CreateCall(ADDRESS_lua_pushvalue, 2));
	r_lua_gettop = reinterpret_cast<gettop_DEF>(CreateCall(ADDRESS_lua_gettop, 1));
	r_lua_type = reinterpret_cast<type_DEF>(CreateCall(ADDRESS_lua_type, 2));
	r_lua_pcall = reinterpret_cast<pcall_DEF>(CreateCall(ADDRESS_lua_pcall, 4));
	r_lua_pushstring = reinterpret_cast<pushstring_DEF>(CreateCall(ADDRESS_lua_pushstring, 2));
	r_index2adr = reinterpret_cast<index2adr_DEF>(CreateCall(ADDRESS_Index2Adr, 2));
	r_lua_tonumber = reinterpret_cast<DEF_r_lua_tonumber>(CreateCall(ADDRESS_lua_tonumber, 2));
	return true;
}