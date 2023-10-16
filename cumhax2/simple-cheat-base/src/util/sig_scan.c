
// THIS IS ALL PASTED


#include <stdio.h> //sscanf

#include "util/sig_scan.h"

#define INRANGE(x,a,b)    (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

void* scan_sig(DWORD dwAddress, DWORD dwLength, const char* szPattern)
{
	const char* pat = szPattern;
	DWORD firstMatch = (DWORD)NULL;
	for (DWORD pCur = dwAddress; pCur < dwLength; pCur++)
	{
		if (!*pat) return (void*)firstMatch;
		if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
			if (!firstMatch) firstMatch = pCur;
			if (!pat[2]) return (void*)firstMatch;
			if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
			else pat += 2;
		}
		else {
			pat = szPattern;
			firstMatch = 0;
		}
	}
	return NULL;
}

void* scan_sig_module(const char* moduleName, const char* pattern)
{
	HMODULE hmModule = GetModuleHandleA(moduleName);
	if (hmModule == NULL) return NULL;

	PIMAGE_DOS_HEADER pDOSHeader = (PIMAGE_DOS_HEADER)hmModule;
	PIMAGE_NT_HEADERS pNTHeaders = (PIMAGE_NT_HEADERS)(((DWORD)hmModule) + pDOSHeader->e_lfanew);

	return scan_sig((DWORD)((DWORD)hmModule + pNTHeaders->OptionalHeader.BaseOfCode), (size_t)(((DWORD)hmModule) + pNTHeaders->OptionalHeader.SizeOfCode), pattern);
}