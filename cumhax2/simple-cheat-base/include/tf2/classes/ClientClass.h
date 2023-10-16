#pragma once

#include "tf2/classes/RecvTable.h"

typedef struct ClientClass
{
	void* /*CreateClientClassFn*/ m_pCreateFn;
	void* /*CreateEventFn*/ m_pCreateEventFn;
	const char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	struct ClientClass* m_pNext;
	int	m_ClassID;
} ClientClass;