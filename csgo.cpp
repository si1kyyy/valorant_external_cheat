#pragma once
#include "global.hpp"
#include "Game.h"
#include "Render.h"





Game* game = NULL;
int WinMain(HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow)
//int main() 
{
	game = new Game();
	
	LONG ret = game->mem->ExpLoadDriver("replace with your driver key");
	//Silky读写键鼠绘制注入 四合一驱动 974884781
	//云端每分钟变更一次特征，两次特征相似度不超过40%，上市至今从未被特征
	//针对个人作者、上市作者推出点数、时长双制度收费，不花冤枉钱
	if (ret != 0x66666666)
	{
		game->tool->Log( "驱动加载失败！", ret);
		return -1;
	}
	
	//ret = game->mem->ExpKmInstall();
	//if (ret != 0)
	//{
	//	game->tool->Log("键鼠加载失败！", ret);
	//	return -1;
	//}

	game->KeysWatch();
	//game->Bhop();
	//game->QuickStop();
	//game->WebRadar();
	//game->SkinChanger();
	//game->FakeLag();
	//game->AntiRecoil();
	//game->TriggerBot();
	game->tool->Log("******", 0);
	if (!game->myserial.open(3, 115200))
	{
		game->tool->Log("COM3打开失败！", 1);
		return -1;
	}

	//CHAR* selfPath = game->tool->GetSelfPhyPath();
	//ret = game->mem->ExpDeleteFileForce(selfPath);
	//ret = game->mem->ExpHideProcessByPid(GetCurrentProcessId(), 0, TRUE);
	setup_window();
	init_wndparams();
RETRY:
	if (!game->FindGameProc())
	{
		game->tool->Log( "failed", 1);
		return -1;
	}
	game->myserial.open(3, 115200);
	game->StartDraw();
	
	goto RETRY;
	
	return 0;
}
