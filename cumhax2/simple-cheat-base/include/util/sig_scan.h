#pragma once

#include <stdlib.h> //size_t
#include <windows.h>

void* scan_sig(DWORD dwAddress, DWORD dwLength, const char* szPattern);
void* scan_sig_module(const char* moduleName, const char* pattern);