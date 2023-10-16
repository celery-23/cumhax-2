#include <stddef.h> // NULL
#include <string.h> // memcpy
#include <stdlib.h> // malloc

#include "util/vtable.h"

VtableHook vtable_hook_new(void* object_ptr)
{

	void*** vtable_ptr_ptr = (void***)object_ptr; // Points to the object's vtable pointer.
												  // Since it's always(?) the first data stored in the object we can just do a simple cast.
												  // If it wasn't the first data in the object we'd need to add an offset here.

												  // vtable_ptr_ptr -> vtable_ptr (first 4 bytes in object) -> vtable == { void* vfunc1, void* vfunc2 ... }


	int n;
	for (n = 0; (*vtable_ptr_ptr)[n] != NULL; n++); // The vtable is guaranteed to be terminated by a null pointer.
													// So we just increment n until we hit a null pointer in the vtable.
							
	
	VtableHook ret = { 0 };
	ret.object_ptr = object_ptr;
	ret.original_vtable_ptr = *vtable_ptr_ptr;

	ret.new_vtable_ptr = malloc((n + 1) * sizeof(void*)); // Add 1 for the NULL pointer at the end. I've never checked if this is actually necessary.
	memcpy(ret.new_vtable_ptr, ret.original_vtable_ptr, n * sizeof(void*));
	ret.new_vtable_ptr[n] = NULL;

	*vtable_ptr_ptr = ret.new_vtable_ptr;

	return ret;
}


void vtable_hook_delete(VtableHook vtable_hook)
{
	if (vtable_hook.object_ptr != NULL)
		*(void***)vtable_hook.object_ptr = vtable_hook.original_vtable_ptr; // Make the object's vtable_ptr point to the original vtable.
																			
	free(vtable_hook.new_vtable_ptr);
}

void hook_vfunc(VtableHook vtable, void* hook_func, int index)
{
	vtable.new_vtable_ptr[index] = hook_func;
}

void unhook_vfunc(VtableHook vtable, int index)
{
	vtable.new_vtable_ptr[index] = vtable.original_vtable_ptr[index];
}