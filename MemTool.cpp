#pragma once
#include "MemTool.h"
#include <tlhelp32.h>



MemTool::MemTool() {
	this->handle = LoadLibraryA("silky.dll");
	this->ExpGetModuleBase = (gExpGetModuleBase)GetProcAddress(this->handle, "ExpGetModuleBase");
	this->ExpLoadDriver = (gExpLoadDriver)GetProcAddress(this->handle, "ExpLoadDriver");
	this->ExpGetPidByName = (gExpGetPidByName)GetProcAddress(this->handle, "ExpGetPidByName");
	this->ExpReadProcMemory = (gExpReadProcMemory)GetProcAddress(this->handle, "ExpReadProcMemory");
	this->ExpWriteProcMemory = (gExpWriteProcMemory)GetProcAddress(this->handle, "ExpWriteProcMemory");

	this->ExpKmInstall = (gExpKmInstall)GetProcAddress(this->handle, "ExpKmInstall");
	this->ExpKmKeyDown = (gExpKmKeyDown)GetProcAddress(this->handle, "ExpKmKeyDown");
	this->ExpKmKeyUp = (gExpKmKeyUp)GetProcAddress(this->handle, "ExpKmKeyUp");
	this->ExpKmMouseLeftDown = (gExpKmMouseLeftDown)GetProcAddress(this->handle, "ExpKmMouseLeftDown");
	this->ExpKmMouseLeftUp = (gExpKmMouseLeftUp)GetProcAddress(this->handle, "ExpKmMouseLeftUp");
	this->ExpKmMouseRightDown = (gExpKmMouseRightDown)GetProcAddress(this->handle, "ExpKmMouseRightDown");
	this->ExpKmMouseRightUp = (gExpKmMouseRightUp)GetProcAddress(this->handle, "ExpKmMouseRightUp");
	this->ExpKmMouseMoveRelative = (gExpKmMouseMoveRelative)GetProcAddress(this->handle, "ExpKmMouseMoveRelative");
	this->ExpKmMouseMoveTo = (gExpKmMouseMoveTo)GetProcAddress(this->handle, "ExpKmMouseMoveTo");
	this->ExpDeleteFileForce = (gExpDeleteFileForce)GetProcAddress(this->handle, "ExpDeleteFileForce");

	this->ExpHideProcessByPid = (gExpHideProcessByPid)GetProcAddress(this->handle, "ExpHideProcessByPid");

	this->ExpSendGeneral = (gExpSendGeneral)GetProcAddress(this->handle, "ExpSendGeneral");
}


//#define _APICOPY
#ifdef _APICOPY
ULONG64 way = 257378;
#else // APICOPY
ULONG64 way = 0;
#endif


ULONG64 MemTool::GetProcModuleBase(DWORD pid, const char* mName) {
	ULONG64 base = 0;
	LONG ret = this->ExpGetModuleBase(pid,(char*)mName,&base);
	return base;
}

ULONG64 MemTool::ReadQWord(DWORD pid, ULONG64 base) {
	ULONG64 val = 0;
	this->ExpReadProcMemory(pid,base,(ULONG64)&val,8, way);
	return val;
}
float MemTool::ReadFloat(DWORD pid, ULONG64 base) {
	DWORD val = 0;
	this->ExpReadProcMemory(pid, base, (ULONG64)&val, 4, way);
	float t = *(float*)(&val);
	return t;
}
DWORD MemTool::ReadDWord(DWORD pid, ULONG64 base) {
	DWORD val = 0;
	this->ExpReadProcMemory(pid, base, (ULONG64)&val, 4, way);
	return val;
}
UWORD MemTool::ReadWWord(DWORD pid, ULONG64 base) {
	UWORD val = 0;
	this->ExpReadProcMemory(pid, base, (ULONG64)&val, 2, way);
	return val;
}
UCHAR MemTool::ReadByte(DWORD pid, ULONG64 base) {
	UCHAR val = 0;
	this->ExpReadProcMemory(pid, base, (ULONG64)&val, 1, way);
	return val;
}
void MemTool::ReadArr(DWORD pid, ULONG64 dst, PVOID arr, ULONG64 size) {
	this->ExpReadProcMemory(pid,dst,(ULONG64)arr,size,0);
}
void MemTool::WriteDword(DWORD pid, ULONG64 base, DWORD data) {
	DWORD buf = data;
	LONG ret = this->ExpWriteProcMemory(pid,base,(ULONG64)&buf,4, way);
}
void MemTool::WriteFloat(DWORD pid, ULONG64 base,float val) {
	float val1 = val;
	LONG ret = this->ExpWriteProcMemory(pid, base, (ULONG64)&val1, 4, way);
}
void MemTool::WriteWword(DWORD pid, ULONG64 base, short val) {
	short val1 = val;
	LONG ret = this->ExpWriteProcMemory(pid, base, (ULONG64)&val1, 2, way);
}

void MemTool::WriteArr(DWORD pid, ULONG64 base, PVOID arr,ULONG64 size) {
	this->ExpWriteProcMemory(pid, base, (ULONG64)arr, size, way);
}
void MemTool::WriteByte(DWORD pid, ULONG64 base, UCHAR data) {
	UCHAR buf = data;
	LONG ret = this->ExpWriteProcMemory(pid, base, (ULONG64)&buf, 1, way);
}


DWORD MemTool::GetPidByName(const char* name) {
	ULONG64 pid = 0;
	LONG ret = this->ExpGetPidByName((char*)name,(ULONG64)&pid);
	return pid;
}

