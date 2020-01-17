#pragma once
#include <stdio.h>
#include <Windows.h>
#include <tlhelp32.h>
// Technique 1: CreateRemoteThread
DWORD demoCreateRemoteThreadW(PCWSTR pszLibFile, DWORD dwProcessId);