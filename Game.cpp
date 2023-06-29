#pragma once
#include "Game.h"
#include "driver.h"
#include "offsets.h"
#include "imgui/imgui.h"

Game::Game() {
	this->mem = new MemTool();
	this->tool = new Tool();
	this->aimScope = 200;
	this->silkyNum = 9;
	this->aimXiong = FALSE;
	this->checkVisible = TRUE;
}

BOOLEAN can = FALSE;
bool Game::FindGameProc() {
	while (true)
	{
		Sleep(1000);
		this->pid = this->mem->GetPidByName("valorant-win64-shipping.exe");
		if (!this->pid)
		{
			continue;
		}
		
		can = TRUE;
		return TRUE;
	}
	return FALSE;
}


void Game::InitWindow() {
	this->gameLeft = 0;
	this->gameTop = 0;
	this->weight = 2560;
	this->hight = 1440;
	this->centerX = this->weight / 2;
	this->centerY = this->hight / 2;
}


DWORD Thread_KeyWatch(PVOID param) {
	Game* g = (Game*)param;
	while (true)
	{	
		if ((GetAsyncKeyState(VK_ADD) & 1) > 0)
		{
			g->aimScope += 20;
		}
		 else if ((GetAsyncKeyState(VK_SUBTRACT) & 1) > 0)
		{
			g->aimScope -= 20;
		}
		 else if ((GetAsyncKeyState(VK_DELETE) & 1) > 0)
		{
			g->aimScope = 200;
		}
		 else if ((GetAsyncKeyState(VK_END) & 1) > 0)
		{
			cleandraw();
			exit(0);
		}
		 else if ((GetAsyncKeyState(VK_F1) & 1) > 0)
		{
			g->aimXiong = TRUE;
		}
		 else if ((GetAsyncKeyState(VK_F2) & 1) > 0)
		{
			g->aimXiong = FALSE;
		}
		 else if ((GetAsyncKeyState(VK_F3) & 1) > 0)
		{
			g->checkVisible = TRUE;
		}
		 else if ((GetAsyncKeyState(VK_F4) & 1) > 0)
		{
			g->checkVisible = FALSE;
		}
		 else if ((GetAsyncKeyState(VK_F8) & 1) > 0)
		{
			g->region = 0;
			g->pid = 0;
			can = FALSE;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD0) & 1) > 0)
		{
			g->silkyNum = 0;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD1) & 1) > 0)
		{
			g->silkyNum = 1;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD2) & 1) > 0)
		{
			g->silkyNum = 2;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD3) & 1) > 0)
		{
			g->silkyNum = 3;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD4) & 1) > 0)
		{
			g->silkyNum = 4;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD5) & 1) > 0)
		{
			g->silkyNum = 5;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD6) & 1) > 0)
		{
			g->silkyNum = 6;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD7) & 1) > 0)
		{
			g->silkyNum = 7;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD8) & 1) > 0)
		{
			g->silkyNum = 8;
		}
		 else if ((GetAsyncKeyState(VK_NUMPAD9) & 1) > 0)
		{
			g->silkyNum = 9;
		}
	}

}
void Game::KeysWatch() {

	CreateThread(NULL, NULL, Thread_KeyWatch, this, NULL, NULL);
}

void Game::StartDraw() {
	while (can)
	{
		begindraw();
		DrawScope(this->centerX - this->aimScope / 2, this->centerY - this->aimScope / 2, this->aimScope, this->aimScope, 3);
		this->InitWindow();
		this->DrawBox();
		enddraw();
	}
}

int reint(int val, int sym) {
	if (sym != 0)
	{
		if (val > 0)
		{
			int ret = val / sym;
			return  ret > 1 ? ret : 1;
		}
		else
		{
			int ret = val / sym;
			return  ret < -1 ? ret : -1;
		}
	}
	return 0;
}

FVector CameraLocation, CameraRotation;
float FovAngle;
ULONG64 lastPwn = -1;
FVector aimvec;
ULONG64 mtX = 0;
ULONG64 recoil = 0;
void Game::DrawBox() {
	DWORD juli = 9999999;
	DWORD aimpwn = -1;;
	float aimDistance = 0;
	srand(GetTickCount());
	//if (!this->region)
	//{
	//	ULONG64 temp = 0;
	//	this->mem->ExpSendGeneral(29, (ULONG64)&temp, 0, 0, 0, 0, 0, 0, 0);
	//	this->region = temp;
	//}
	//if (!this->region)
	//{
	//	return;
	//}
	//
	//ULONG64 worldPtr1 = this->GetWorld(this->region);

	ULONG64 base = 0;
	this->mem->ExpGetModuleBase(this->pid,"valorant-win64-shipping.exe",&base);
	//0x92df100

	ULONG64 key = this->mem->ReadQWord(this->pid, base + offsets::worldKey + 0x38);
	ULONG64 state[7] = { 0 };
	this->mem->ReadArr(this->pid, base + offsets::worldKey, state, 7 * 8);
	ULONG64 uworld_ptr = Decryption::Decrypt_UWorld(key, (uintptr_t*)state);
	ULONG64 worldPtr = this->mem->ReadQWord(this->pid, uworld_ptr);
	
	if (!worldPtr)
	{
		lastPwn = -1;
		return;
	}

	ULONG64 ULevelPtr = ReadGuardQword(worldPtr + offsets::Ulevel);
	ULONG64 UGameInstancePtr = this->mem->ReadQWord(this->pid, worldPtr + offsets::Gameinstance);
	ULONG64 ULocalPlayerPtrTemp = this->mem->ReadQWord(this->pid, UGameInstancePtr + offsets::LocalPlayers);
	ULONG64 ULocalPlayerPtr = this->mem->ReadQWord(this->pid, ULocalPlayerPtrTemp);



	ULONG64 APlayerControllerPtr = ReadGuardQword(ULocalPlayerPtr+ offsets::PlayerController);
	this->PlayerCameraManager = ReadGuardQword(APlayerControllerPtr + offsets::PlayerCameraManager);
	ULONG64 MyHUD = ReadGuardQword(APlayerControllerPtr + offsets::MyHUD);
	ULONG64 APawnPtr = ReadGuardQword(APlayerControllerPtr + offsets::AcknowledgedPawn);

	ULONG64 self_state = ReadGuardQword(APawnPtr + offsets::player_state);
	ULONG64 self_team_component = ReadGuardQword(self_state + offsets::team_component);
	ULONG64 self_team = this->mem->ReadQWord(this->pid, self_team_component + offsets::team_id);

	int MyUniqueID = 0;
	ULONG64 RootComponent = 0;
	FVector MyRelativeLocation;
	if (APawnPtr != 0)
	{
		MyUniqueID = this->mem->ReadDWord(this->pid, APawnPtr + offsets::UniqueID);
		RootComponent = this->mem->ReadQWord(this->pid, APawnPtr+ offsets::RootComponent);
		this->mem->ReadArr(this->pid, RootComponent+ offsets::RelativeLocation,&MyRelativeLocation,sizeof(FVector));
	}
	
	if (MyHUD != 0)
	{
		TArrayDrink PlayerArray;
		this->mem->ReadArr(this->pid, ULevelPtr + offsets::AActorArray, &PlayerArray, sizeof(TArrayDrink));
		aimvec = { 0,0,0 };
		
		for (uint32_t i = 0; i < PlayerArray.Count; ++i)
		{
			ULONG64 Pawns = ReadGuardQword((ULONG64)PlayerArray.Data + i * 8);
			if (Pawns != APawnPtr)
			{
				if (MyUniqueID == this->mem->ReadDWord(this->pid,Pawns + offsets::UniqueID))
				{
					ULONG64 player_state = ReadGuardQword(Pawns + offsets::player_state);
					ULONG64 team_component = ReadGuardQword(player_state + offsets::team_component);
					ULONG64 team = this->mem->ReadQWord(this->pid, team_component + offsets::team_id);

					if (team == self_team)
					{
						continue;
					}

					ULONG64 SkeletalMesh = ReadGuardQword(Pawns + offsets::MeshComponent);

					ULONG64 RootComponent = this->mem->ReadQWord(this->pid, Pawns + offsets::RootComponent);
					FVector RelativeLocation;
					this->mem->ReadArr(this->pid, RootComponent + offsets::RelativeLocation, &RelativeLocation, sizeof(FVector));
					FVector RelativeLocationProjected = this->ProjectWorldToScreen(RelativeLocation);
					FVector RelativePosition = RelativeLocation - CameraLocation;
					float RelativeDistance = RelativePosition.Length() / 10000 * 2;
					FVector HeadBone = this->GetEntityBone(SkeletalMesh, 8);
					FVector RootBone = this->GetEntityBone(SkeletalMesh, 0);
					float Distance = MyRelativeLocation.Distance(RelativeLocation);
					if (HeadBone.z == RootBone.z)
					{
						HeadBone.z += 183;
					}
					if (this->aimXiong)
					{
						HeadBone.z -= 50;
					}
					FVector HeadBoneProjected = this->ProjectWorldToScreen(HeadBone);
					FVector RootBoneProjected = this->ProjectWorldToScreen(RootBone);


					ULONG64 DamageHandler = ReadGuardQword(Pawns + offsets::DamageHandler);
					float Health = this->mem->ReadFloat(this->pid, DamageHandler + offsets::Health);
					if (Health <= 0) continue;

					BOOLEAN dormant = this->mem->ReadByte(this->pid, Pawns + offsets::bIsDormant);
					if (dormant)
					{

						float last_render_time = this->mem->ReadFloat(this->pid, SkeletalMesh + offsets::last_render_time);
						float last_submit_time = this->mem->ReadFloat(this->pid, SkeletalMesh + offsets::last_submit_time);
						//better
						bool is_visible = (last_render_time + 0.06F) >= last_submit_time;
						//shit
						//bool is_visible2 = this->mem->ReadByte(this->pid, Pawns + offsets::is_visible);
						ULONG64 shooter_character_minimap = this->mem->ReadQWord(this->pid, Pawns + offsets::character_map);
						//best
						bool is_visible3 = this->mem->ReadByte(this->pid, shooter_character_minimap + offsets::is_visible);
						bool visibleSign = this->checkVisible ? is_visible3 : is_visible;


						float h = RootBoneProjected.y - HeadBoneProjected.y;
						float w = h / 2;
						float x = RootBoneProjected.x - w / 2;
						float y = RootBoneProjected.y - h - 10;
						DrawNormalBox(x, y, w, h, 2, visibleSign?1:2);

						
						if (!visibleSign)
						{
							continue;
						}


						if ((int)HeadBoneProjected.x >= this->centerX-this->aimScope && (int)HeadBoneProjected.x<= this->centerX + this->aimScope)
						{
							if ((int)HeadBoneProjected.x >= this->centerX - this->aimScope*2 && (int)HeadBoneProjected.x <= this->centerX + this->aimScope * 2)
							{
								if ((int)HeadBoneProjected.y >= this->centerY - this->aimScope && (int)HeadBoneProjected.y <= this->centerY + this->aimScope)
								{
									int juliTemp = abs((int)HeadBoneProjected.x - this->centerX);
									if (lastPwn == i)
									{
										aimvec.x = HeadBoneProjected.x;
										aimvec.y = HeadBoneProjected.y;
										aimpwn = i;
										aimDistance = Distance;
										break;
									}
									if (juliTemp < juli)
									{
										aimvec.x = HeadBoneProjected.x;
										aimvec.y = HeadBoneProjected.y;
										aimpwn = i;
										aimDistance = Distance;
										juli = juliTemp;
									}
								}
							}
						}
					}
				}
			}
		}
		if ((GetAsyncKeyState(VK_RBUTTON) & 0x8000) > 0)
		{
			if (lastPwn == aimpwn || lastPwn == -1)
			{
				if (aimpwn != -1)
				{
					DWORD mx = (int)aimvec.x - this->centerX;
					DWORD my = (int)aimvec.y - this->centerY;
					if (juli * 4 > ((int)mx > 0 ? mx : mx * -1)) {
						if ((GetAsyncKeyState(VK_LBUTTON) & 0x8000) > 0)
						{
							recoil++;
						}
						else
						{
							recoil = 0;
						}
						lastPwn = aimpwn;
						char cmd[50] = { 0 };
						//sprintf(cmd, "km.move(%d,%d)\r\n", reint(mx, 2), reint(my, 2));
						sprintf(cmd, "km.move(%d,%d,5)\r\n", (int)mx/2, (int)my / 2+ (int)(recoil*aimDistance*0.005));
						this->myserial.write(cmd);
						//this->mem->ExpKmMouseMoveRelative((int)mx / 2, (int)my / 2 + (int)(recoil*aimDistance*0.005));
						if (this->silkyNum)
						{
							for (size_t i = 0; i < this->silkyNum * 200000; i++)
							{
								mtX = GetAsyncKeyState(VK_RBUTTON);//无意义代码，防止空循环编译时被优化掉
							}
						}
					}
				}
			}
			else
			{
				lastPwn = -1;
				Sleep(350);
			}
		}
		else
		{
			lastPwn = -1;
		}
		if (this->silkyNum)
		{
			this->mem->WriteDword(this->pid, 0, mtX);
		}
	}
}



ULONG64 Game::GetWorld(ULONG64 p) {
	ULONG64 uworld_addr = this->mem->ReadQWord(this->pid,p + 0x50);
	for (size_t i = 0; i < 0x2000; i++)
	{
		ULONG64 temp = this->mem->ReadQWord(this->pid, p + i*4);
		if (temp)
		{
			Sleep(1);
		}
	}
	unsigned long long uworld_offset;

	if (uworld_addr > 0x10000000000)
	{
		uworld_offset = uworld_addr - 0x10000000000;
	}
	else {
		uworld_offset = uworld_addr - 0x8000000000;
	}

	return p + uworld_offset;
}


ULONG64 Game::ReadGuardQword(ULONG64 dst) {
	ULONG64 temp = this->mem->ReadQWord(this->pid, dst);
	ULONG64 sign = 0xFFFFFFF000000000 & temp;
	if (sign == 0x8000000000 || sign == 0x10000000000)
	{
		ULONG64 temp = this->mem->ReadQWord(this->pid, dst);
		return temp & 0xFFFFFF + this->region;
	}
	else
	{
		return temp;
	}
}




#define M_PI 3.14159265358979323846264338327950288419716939937510

D3DXMATRIX Matrix(FVector rot, FVector origin)
{
	float radPitch = (rot.x * float(M_PI) / 180.f);
	float radYaw = (rot.y * float(M_PI) / 180.f);
	float radRoll = (rot.z * float(M_PI) / 180.f);

	float SP = sinf(radPitch);
	float CP = cosf(radPitch);
	float SY = sinf(radYaw);
	float CY = cosf(radYaw);
	float SR = sinf(radRoll);
	float CR = cosf(radRoll);

	D3DMATRIX matrix;
	matrix.m[0][0] = CP * CY;
	matrix.m[0][1] = CP * SY;
	matrix.m[0][2] = SP;
	matrix.m[0][3] = 0.f;

	matrix.m[1][0] = SR * SP * CY - CR * SY;
	matrix.m[1][1] = SR * SP * SY + CR * CY;
	matrix.m[1][2] = -SR * CP;
	matrix.m[1][3] = 0.f;

	matrix.m[2][0] = -(CR * SP * CY + SR * SY);
	matrix.m[2][1] = CY * SR - CR * SP * SY;
	matrix.m[2][2] = CR * CP;
	matrix.m[2][3] = 0.f;

	matrix.m[3][0] = origin.x;
	matrix.m[3][1] = origin.y;
	matrix.m[3][2] = origin.z;
	matrix.m[3][3] = 1.f;

	return matrix;
}


FVector Game::ProjectWorldToScreen(FVector WorldLocation)
{
	FVector Screenlocation = FVector(0, 0, 0);
	
	FMinimalViewInfo ViewInfo;
	this->mem->ReadArr(this->pid, this->PlayerCameraManager + offsets::camera_fov-0x18, &ViewInfo, sizeof(FMinimalViewInfo));
	
	CameraLocation = ViewInfo.Location;
	CameraRotation = ViewInfo.Rotation;
	
	
	D3DMATRIX tempMatrix = Matrix(CameraRotation, FVector(0, 0, 0));
	
	FVector vAxisX = FVector(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]),
		vAxisY = FVector(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]),
		vAxisZ = FVector(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);
	
	FVector vDelta = WorldLocation - CameraLocation;
	FVector vTransformed = FVector(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));
	
	if (vTransformed.z < 1.f) vTransformed.z = 1.f;
	
	FovAngle = ViewInfo.FOV;
	
	float ScreenCenterX = 2560.0f / 2.0f;
	float ScreenCenterY = 1440.0f / 2.0f;
	
	Screenlocation.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	Screenlocation.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
	
	return Screenlocation;
}


D3DMATRIX MatrixMultiplication(D3DMATRIX pM1, D3DMATRIX pM2)
{
	D3DMATRIX pOut;
	pOut._11 = pM1._11 * pM2._11 + pM1._12 * pM2._21 + pM1._13 * pM2._31 + pM1._14 * pM2._41;
	pOut._12 = pM1._11 * pM2._12 + pM1._12 * pM2._22 + pM1._13 * pM2._32 + pM1._14 * pM2._42;
	pOut._13 = pM1._11 * pM2._13 + pM1._12 * pM2._23 + pM1._13 * pM2._33 + pM1._14 * pM2._43;
	pOut._14 = pM1._11 * pM2._14 + pM1._12 * pM2._24 + pM1._13 * pM2._34 + pM1._14 * pM2._44;
	pOut._21 = pM1._21 * pM2._11 + pM1._22 * pM2._21 + pM1._23 * pM2._31 + pM1._24 * pM2._41;
	pOut._22 = pM1._21 * pM2._12 + pM1._22 * pM2._22 + pM1._23 * pM2._32 + pM1._24 * pM2._42;
	pOut._23 = pM1._21 * pM2._13 + pM1._22 * pM2._23 + pM1._23 * pM2._33 + pM1._24 * pM2._43;
	pOut._24 = pM1._21 * pM2._14 + pM1._22 * pM2._24 + pM1._23 * pM2._34 + pM1._24 * pM2._44;
	pOut._31 = pM1._31 * pM2._11 + pM1._32 * pM2._21 + pM1._33 * pM2._31 + pM1._34 * pM2._41;
	pOut._32 = pM1._31 * pM2._12 + pM1._32 * pM2._22 + pM1._33 * pM2._32 + pM1._34 * pM2._42;
	pOut._33 = pM1._31 * pM2._13 + pM1._32 * pM2._23 + pM1._33 * pM2._33 + pM1._34 * pM2._43;
	pOut._34 = pM1._31 * pM2._14 + pM1._32 * pM2._24 + pM1._33 * pM2._34 + pM1._34 * pM2._44;
	pOut._41 = pM1._41 * pM2._11 + pM1._42 * pM2._21 + pM1._43 * pM2._31 + pM1._44 * pM2._41;
	pOut._42 = pM1._41 * pM2._12 + pM1._42 * pM2._22 + pM1._43 * pM2._32 + pM1._44 * pM2._42;
	pOut._43 = pM1._41 * pM2._13 + pM1._42 * pM2._23 + pM1._43 * pM2._33 + pM1._44 * pM2._43;
	pOut._44 = pM1._41 * pM2._14 + pM1._42 * pM2._24 + pM1._43 * pM2._34 + pM1._44 * pM2._44;

	return pOut;
}
FVector Game::GetEntityBone(ULONG64 mesh, int id)
{
	ULONG64 array = this->mem->ReadQWord(this->pid, mesh + offsets::BoneArray);
	if (array == NULL)
		array = this->mem->ReadQWord(this->pid, mesh + offsets::BoneArrayCache);

	FTransform bone;
	this->mem->ReadArr(this->pid, array + (id * sizeof(FTransform)), &bone, sizeof(FTransform));

	FTransform ComponentToWorld;
	this->mem->ReadArr(this->pid, mesh + offsets::ComponentToWorld, &ComponentToWorld, sizeof(FTransform));
	D3DMATRIX Matrix;

	Matrix = MatrixMultiplication(bone.ToMatrixWithScale(), ComponentToWorld.ToMatrixWithScale());

	return FVector(Matrix._41, Matrix._42, Matrix._43);
}












