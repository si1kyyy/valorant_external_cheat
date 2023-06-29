#pragma once
#include "global.hpp"


//自定义枚举进程参数
typedef struct
{
	HWND	hwnd;
	DWORD	processId;
}WindowsArg;

class MemTool
{

	HMODULE handle;


public:
	MemTool();
	ULONG64 GetProcModuleBase(DWORD pid, const char* mName);
	ULONG64 ReadQWord(DWORD pid, ULONG64 base);
	DWORD ReadDWord(DWORD pid, ULONG64 base);
	float ReadFloat(DWORD pid, ULONG64 base);
	UWORD ReadWWord(DWORD pid, ULONG64 base);
	UCHAR ReadByte(DWORD pid, ULONG64 base);
	void ReadArr(DWORD pid, ULONG64 dst, PVOID arr, ULONG64 size);

	void WriteDword(DWORD pid, ULONG64 base, DWORD data);
	void WriteFloat(DWORD pid, ULONG64 base, float val);
	void WriteByte(DWORD pid, ULONG64 base, UCHAR data);
	void WriteArr(DWORD pid, ULONG64 base, PVOID arr, ULONG64 size);
	void WriteWword(DWORD pid, ULONG64 base, short val);
	BOOLEAN FarCall(DWORD pid, PUCHAR code, ULONG64 size);

	DWORD GetPidByName(const char* name);
	HWND  GetHwndByProcessId(DWORD processId);






	gExpLoadDriver ExpLoadDriver;
	gExpGetPidByName ExpGetPidByName;
	gExpGetModuleBase ExpGetModuleBase;
	gExpReadProcMemory ExpReadProcMemory;
	gExpWriteProcMemory ExpWriteProcMemory;
	gExpHideProcessByPid ExpHideProcessByPid;

	gExpKmInstall ExpKmInstall;
	gExpKmKeyDown ExpKmKeyDown;
	gExpKmKeyUp ExpKmKeyUp;
	gExpKmMouseLeftDown ExpKmMouseLeftDown;
	gExpKmMouseLeftUp ExpKmMouseLeftUp;
	gExpKmMouseRightDown ExpKmMouseRightDown;
	gExpKmMouseRightUp ExpKmMouseRightUp;
	gExpKmMouseMoveRelative ExpKmMouseMoveRelative;
	gExpKmMouseMoveTo ExpKmMouseMoveTo;

	gExpSendGeneral ExpSendGeneral;

	gExpDeleteFileForce ExpDeleteFileForce;
};

