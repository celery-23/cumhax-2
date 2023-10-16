#pragma once

#include <stdbool.h>

#include "util/vfunc_macros.h"

typedef void KeyValues;
typedef void KeyValuesSystem;

#define KEY_VALUES_SIZE 32U

typedef void* (__cdecl* KeyValuesSystem_factory_t)(void);
typedef bool (__fastcall* KeyValues_LoadFromBuffer_t)(KeyValues* ecx, int edx, const char* resourceName, char* pBuffer, void* pBaseFileSystem, char* pPathID);
typedef void* (__fastcall* KeyValues_ctor_t)(KeyValues* ecx, int edx, const char* name);

DECLARE_VFUNC(KeyValuesSystem, AllocKeyValuesMemory, 1, void*, int size);
DECLARE_VFUNC(KeyValuesSystem, FreeKeyValuesMemory, 2, void, void* pMem);