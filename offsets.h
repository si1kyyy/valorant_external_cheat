#define _WORLDWIDE
namespace offsets {
#ifdef _WORLDWIDE
	//07.00.00.909577
	unsigned int worldKey = 0x9787480;
	unsigned int Gameinstance = 0x1a0;
	unsigned int Ulevel = 0x38;
	unsigned int LocalPlayers = 0x40;
	unsigned int PlayerController = 0x38;
	unsigned int PlayerCameraManager = 0x478;
	unsigned int MyHUD = 0x470;
	unsigned int AcknowledgedPawn = 0x460;
	unsigned int PlayerState = 0x3f0;
	unsigned int TeamComponent = 0x628;
	unsigned int TeamID = 0xf8;
	unsigned int UniqueID = 0x38;
	unsigned int FNameID = 0x18;
	unsigned int AActorArray = 0xa0;
	unsigned int RootComponent = 0x230;
	unsigned int RelativeLocation = 0x164;
	unsigned int MeshComponent = 0x430;
	unsigned int DamageHandler = 0xa20;
	unsigned int bIsDormant = 0x100;
	unsigned int Health = 0x1b0;
	unsigned int ComponentToWorld = 0x250;
	unsigned int BoneArray = 0x5D8;
	unsigned int BoneArrayCache = BoneArray + 0x10;
	unsigned int BoneCount = 0x5E0;
	unsigned int camera_fov = 0x1298;
	unsigned int team_component = 0x628;
	unsigned int team_id = 0xF8;
	unsigned int player_state = 0x3F0;
	unsigned int last_submit_time = 0x380;
	unsigned int last_render_time = 0x380 + 4;
	unsigned int is_visible = 0x501;
	unsigned int portrait_map = 0x1190;
	unsigned int character_map = portrait_map + 0x8;
#else
	//06.10.00.887325
	unsigned int worldKey = 0x70615C0;
	unsigned int Gameinstance = 0x1a0;
	unsigned int Ulevel = 0x38;
	unsigned int LocalPlayers = 0x40;
	unsigned int PlayerController = 0x38;
	unsigned int PlayerCameraManager = 0x478;
	unsigned int MyHUD = 0x470;//
	unsigned int AcknowledgedPawn = 0x460;
	unsigned int PlayerState = 0x3f0;
	unsigned int TeamComponent = 0x628;
	unsigned int TeamID = 0xf8;
	unsigned int UniqueID = 0x38;
	unsigned int FNameID = 0x18;//
	unsigned int AActorArray = 0xa0;
	unsigned int RootComponent = 0x230;
	unsigned int RelativeLocation = 0x164;//
	unsigned int MeshComponent = 0x430;
	unsigned int DamageHandler = 0xa10;
	unsigned int bIsDormant = 0x100;
	unsigned int Health = 0x1b0;
	unsigned int ComponentToWorld = 0x250;
	unsigned int BoneArray = 0x5D8;//
	unsigned int BoneArrayCache = BoneArray + 0x10;
	unsigned int BoneCount = 0x5E0;//
	unsigned int camera_fov = 0x1298;
	unsigned int team_component = 0x628;
	unsigned int team_id = 0xF8;
	unsigned int player_state = 0x3F0;
	unsigned int last_submit_time = 0x378;	//378
	unsigned int last_render_time = 0x378 + 4;
	unsigned int is_visible = 0x501;
	unsigned int portrait_map = 0x1170;
	unsigned int character_map = portrait_map + 0x8;
#endif
}


