#pragma once

// Stores the information we need to hook a vtable and restore it later.
typedef struct
{
	void* object_ptr;
	void** original_vtable_ptr;
	void** new_vtable_ptr;

} VtableHook;

VtableHook vtable_hook_new(void* object_ptr);
void vtable_hook_delete(VtableHook vtable_hook);
void hook_vfunc(VtableHook vtable_hook, void* hook_func, int index);
void unhook_vfunc(VtableHook vtable_hook, int index);