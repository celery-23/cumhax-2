#pragma once

// DECLARE_VFUNC macros define a virtual function's signature and index in one line.


// For example:
// DECLARE_VFUNC(ClientModeShared, CreateMove, 21, bool, float input_sample_frametime, CUserCmd* pCommand);

// Expands to:
// enum { ClientModeShared_CreateMove_index = 21};
// typedef bool (__fastcall* ClientModeShared_CreateMove_t) (ClientModeShared* ecx, int edx, float input_sample_frametime, CUserCmd* pCommand);


#define DECLARE_VFUNC(class_name, func_name, index, ret_type, ...)\
enum { class_name##_##func_name##_index = index };\
typedef ret_type (__fastcall* class_name##_##func_name##_t) (class_name* ecx, int edx, ##__VA_ARGS__)

#define DECLARE_VFUNC_EX(class_name, func_name, index, ret_type, calling_convention, ...)\
enum { class_name##_##func_name##_index = index };\
typedef ret_type (calling_convention* class_name##_##func_name##_t) (__VA_ARGS__)


// Passing in a pointer to an object to the following macros is equivalent to passing in a vtable_ptr_ptr,
// because the vtable pointer is the first data in the object.

#define GET_VFUNC(class_name, func_name, vtable_ptr_ptr) (*(class_name##_##func_name##_t**)vtable_ptr_ptr)[class_name##_##func_name##_index]

#define GET_VFUNC_INDEX(class_name, func_name) class_name##_##func_name##_index