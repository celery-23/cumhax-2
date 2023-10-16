#pragma once

#include <stdbool.h>

#include "util/vfunc_macros.h"
#include "tf2/enums.h"

typedef void IMatRenderContext;

DECLARE_VFUNC(IMatRenderContext, DepthRange, 11, void, float zNear, float zFar);
DECLARE_VFUNC(IMatRenderContext, ClearBuffers, 12, void, bool bClearColor, bool bClearDepth, bool bClearStencil);
DECLARE_VFUNC(IMatRenderContext, SetStencilEnable, 117, void, bool onoff);
DECLARE_VFUNC(IMatRenderContext, SetStencilFailOperation, 118, void, StencilOperation_t op);
DECLARE_VFUNC(IMatRenderContext, SetStencilZFailOperation, 119, void, StencilOperation_t op);
DECLARE_VFUNC(IMatRenderContext, SetStencilPassOperation, 120, void, StencilOperation_t op);
DECLARE_VFUNC(IMatRenderContext, SetStencilCompareFunction, 121, void, StencilComparisonFunction_t cmpfn);
DECLARE_VFUNC(IMatRenderContext, SetStencilReferenceValue, 122, void, int ref);
DECLARE_VFUNC(IMatRenderContext, SetStencilTestMask, 123, void, unsigned int msk);
DECLARE_VFUNC(IMatRenderContext, SetStencilWriteMask, 124, void, unsigned int msk);

/*

	virtual void SetStencilEnable(bool onoff) = 0; // 117
	virtual void SetStencilFailOperation(StencilOperation_t op) = 0; // 118
	virtual void SetStencilZFailOperation(StencilOperation_t op) = 0; // 119
	virtual void SetStencilPassOperation(StencilOperation_t op) = 0; // 120
	virtual void SetStencilCompareFunction(StencilComparisonFunction_t cmpfn) = 0; //121
	virtual void SetStencilReferenceValue(int ref) = 0; //122
	virtual void SetStencilTestMask(uint32_t msk) = 0; //123
	virtual void SetStencilWriteMask(uint32_t msk) = 0; //124
	
	*/