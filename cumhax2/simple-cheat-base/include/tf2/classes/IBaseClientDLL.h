#pragma once

#include "util/vfunc_macros.h"
#include "tf2/classes/IClientClass.h"

typedef void IBaseClientDLL;

DECLARE_VFUNC(IBaseClientDLL, GetAllClasses, 8, IClientClass*);