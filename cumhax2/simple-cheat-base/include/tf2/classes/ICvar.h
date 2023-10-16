#pragma once

#include "util/vfunc_macros.h"

typedef void ICvar;

DECLARE_VFUNC_EX(ICvar, ConsolePrintf, 24, void, __cdecl, ICvar* ecx, const char* fmt, ...);


