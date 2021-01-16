
/* Written by am0y @ v3rmillion.net
Init will add a vectored exception handler that we'll use to retrieve the correct address corresponding to the int3 breakpoint.
The idea is to call GenerateSafeAddress and pass our c function's address in it so it returns the location of a int3 breakpoint in .text range corresponding to our c function, therefore
bypassing callcheck.
*/


#include <windows.h>
#include <vector>
#include <limits.h>
#include <exception>
#include <iostream>
#include <unordered_map>

typedef std::unordered_map<unsigned int, unsigned int> ccMap; /* A typedef of our unordered map*/
ccMap ccCache; /* Our unordered map (cache) first->int3bp | second->cfunc */

const unsigned int exists(unsigned int addr) { /* A function we will use to determine if there's already our function cached */
    /* Iterate our map and check if we can find our c func at it->second */
    for (ccMap::const_iterator it = ccCache.begin(); it != ccCache.end(); ++it) {
        /* Found */
        if (it->second == addr) return it->first;
    }
    /* Not found */
    return 0;
}

LONG __stdcall ccVEH(PEXCEPTION_POINTERS code) { /* Our VEH */
    /* Check if the ExceptionCode is the one we're looking for */
    if (code->ExceptionRecord->ExceptionCode == 0x80000003L)
    {
        /* Set our Eip to our c func address */
        code->ContextRecord->Eip = ccCache.at(code->ContextRecord->Eip);
        /* Resume */
        return -1;
    }
}

unsigned int currentInt3PbIteration = 0; /* Iteration start value */

unsigned int GenerateSafeAddress(unsigned int addr) /* Get a int3 breakpoint address corresponding to our c function address. */
{
    /* Check if our c func isn't already listed, return the correct int3bp if it is */
    const unsigned int e0 = exists(addr);
    if (e0 != 0) return e0;

    /* Scan start address */
    static const unsigned int startAddr = reinterpret_cast<unsigned int>(GetModuleHandleA(NULL));

    /* A sample of the byte signature we're looking for */
    static const byte int3bpSignature[8] = { 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC, 0xCC };

    /* A variable to keep track of our scanning status*/
    unsigned int fndInt3BpAddr = 0x0;

    /* Scan until we reach INT_MAX-1 or until we find a int3 breakpoint address*/
    while (currentInt3PbIteration < (INT_MAX - 1)) {
        /* Compare the signature with current iteration */
        ++currentInt3PbIteration;
        if (memcmp((void*)(startAddr + currentInt3PbIteration), int3bpSignature, sizeof(int3bpSignature)) == 0) {
            /* Insert a ccMap::value_type in our map, with the int3 breakpoint we found and its maching c function*/
            ccCache.insert(ccMap::value_type(startAddr + currentInt3PbIteration, addr));
            /* Save our int3 breakpoint address */
            fndInt3BpAddr = startAddr + currentInt3PbIteration;
            break;
        }
    }

    /* Return our matching address. If return is 0x0 then we failed to find a int3 breakpoint.*/
    return fndInt3BpAddr;
}

namespace Callcheck
{
    void Init()
    {
        AddVectoredExceptionHandler(1, ccVEH);
    }
    void secure_register(uintptr_t RLS, int Function(uintptr_t), const char* name) {
        r_lua_pushcclosure(RLS, GenerateSafeAddress((uintptr_t)Function), NULL, NULL, NULL);
        r_lua_setfield(RLS, -10002, name);
    }
}
