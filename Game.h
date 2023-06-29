#pragma once
#include "global.hpp"
#include "MemTool.h"
#include "Tool.h"
#include "Render.h"


class Game
{
public:
	MemTool* mem;
	Tool* tool;
	_com myserial;

	DWORD pid;  //ÓÎÏ·½ø³ÌID

	ULONG64 region = 0;
	ULONG64 PlayerCameraManager = 0;

	LONG gameLeft;
	LONG gameTop;
	LONG weight;
	LONG hight;
	LONG centerX;
	LONG centerY;
	

	void DrawBox();
	void StartDraw();

public:
	DWORD silkyNum;
	DWORD aimScope;
	BOOLEAN aimXiong;
	BOOLEAN checkVisible;


	Game();
	
	bool FindGameProc();
	void InitWindow();
	void KeysWatch();
	ULONG64 GetWorld(ULONG64 p);
	ULONG64 ReadGuardQword(ULONG64 dst);
	FVector ProjectWorldToScreen(FVector WorldLocation);
	FVector GetEntityBone(ULONG64 mesh, int id);
};

