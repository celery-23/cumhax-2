#pragma once

#include <stdbool.h>

#include "tf2/enums.h"

typedef void CRecvDecoder;
struct RecvTable;

typedef struct RecvProp
{

	const char* m_pVarName;
	SendPropType			m_RecvType;
	int						m_Flags;
	int						m_StringBufferSize;

	bool					m_bInsideArray;		// Set to true by the engine if this property sits inside an array.
												
	const void* m_pExtraData;					// Extra data that certain special property types bind to the property here.

	// If this is an array (DPT_Array).
	struct RecvProp* m_pArrayProp;
	void* /*ArrayLengthRecvProxyFn*/ m_ArrayLengthProxy;

	void* /*RecvVarProxyFn*/			m_ProxyFn;
	void* /*DataTableRecvVarProxyFn*/	m_DataTableProxyFn;	// For RDT_DataTable.

	struct RecvTable* m_pDataTable;					// For RDT_DataTable.
	int						m_Offset;

	int						m_ElementStride;
	int						m_nElements;

	// If it's one of the numbered "000", "001", etc properties in an array, then
	// these can be used to get its array property name for debugging.
	const char* m_pParentArrayPropName;
} RecvProp;


typedef struct RecvTable
{
	RecvProp* m_pProps;
	int m_nProps;
	CRecvDecoder* m_pDecoder;
	const char* m_pNetTableName;
	bool m_bInitialized;
	bool m_bInMainList;
} RecvTable;