#include "util/vtable.h"
#include "globals.h"
#include "tf2/classes/ClientModeShared.h"
#include "features/bhop.h"

VtableHook ClientModeShared_hook;

bool __fastcall CreateMove_hook(ClientModeShared* ecx, int edx, float input_sample_frametime, CUserCmd* pCommand)
{
	bool ret = GET_VFUNC(ClientModeShared, CreateMove, &ClientModeShared_hook.original_vtable_ptr)
							(client_mode_shared, edx, input_sample_frametime, pCommand);

	bhop(pCommand);
	return ret;
}