#include "stdafx.h"

// This is some ghetto shit but leave it be
// They're all next to each other in memory so this is ez

struct GameWorldRef
{
	ClientWorld* GameWorld;
	GameAPI* Game;
	MasterServerConnection* g_masterServer;
	ServerThread* g_serverThread;
	float g_masterServerHeartbeatTimer;
	bool g_init;
	bool g_transitioning;
	bool g_watcherProcess;
	bool g_adminCharacter;
	GameServerConnection* g_gameServer;
};

GameWorldRef* gwr = NULL;

// Hooks go here

bool g_invisibility = false;

// I set this to 300 (/i 300) and sat on top of the chest to unlock bear flag
float g_invisoff = 200.f;

WorldVtbl WorldBackup;

typedef void(__thiscall* WorldTick_t)(World* pthis, float deltaTime);
typedef void(__thiscall* WorldChat_t)(World* pthis, Player*, std::string &);

// WEAPON HOOK IM SO SORRY THIS IS SO SLOPPY JESUS CHRIST

typedef bool(__thiscall* IsAutoFire_t)(IItem* pthis);

bool __fastcall new_IsAutoFire(IItem* pthis, void* _EDX) {
	return true;
}

void __fastcall new_WorldTick(World* pthis, void* _EDX, float deltaTime)
{
	// pre-server update
	bool updated = false;

	Vector3 originalPosition;

	if (g_invisibility && gwr->g_gameServer) {
		pthis->m_localPlayer->vfptr->GetPosition(pthis->m_localPlayer, &originalPosition);

		Vector3 pos = originalPosition;

		pos.z -= g_invisoff;

		pthis->m_localPlayer->vfptr->SetPosition(pthis->m_localPlayer, &pos);

		updated = true;
	}

	// Autopistol
	IPlayer* local = (IPlayer*)((ClientWorld*)pthis)->m_activePlayer.m_object;

	if (local) {
		IItem* currentWeapon = local->vfptr->GetCurrentItem(local);

		if (currentWeapon) {
			if ((DWORD)currentWeapon->vfptr->IsAutoFire != (DWORD)new_IsAutoFire) {
				MEMORY_BASIC_INFORMATION mbi;
				VirtualQuery((LPCVOID)currentWeapon->vfptr, &mbi, sizeof(mbi));
				VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);

				IItemVtbl table;

				memcpy(&table, currentWeapon->vfptr, sizeof(IItemVtbl));

				table.IsAutoFire = (IsAutoFire_t)new_IsAutoFire;

				memcpy(currentWeapon->vfptr, &table, sizeof(IItemVtbl));

				VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);
			}
		}
	}

	WorldBackup.Tick(pthis, deltaTime);

	// post-server update
	if (updated) {
		pthis->m_localPlayer->vfptr->SetPosition(pthis->m_localPlayer, &originalPosition);
	}
}

bool g_admin = false;

void __fastcall new_WorldChat(World* pthis, void* _EDX, Player* player, std::string &text) {
	if (!text.length())
		return; // wtf

	std::istringstream iss(text);

	std::vector<std::string> tokens
	{
		std::istream_iterator<std::string>{iss},
		std::istream_iterator<std::string>{}
	};

	if (tokens.size() == 0) {
		WorldBackup.Chat(pthis, player, text);
		return;
	}

	bool command = true;

	if (tokens[0].compare("/sws") == 0 && tokens.size() > 1) {
		player->m_walkingSpeed = atof(tokens[1].c_str());
	}
	else if (tokens[0].compare("/sjs") == 0 && tokens.size() > 1) {
		player->m_jumpSpeed = atoi(tokens[1].c_str());
	}
	else if (tokens[0].compare("/admin") == 0) {
		g_admin = !g_admin;
		player->m_admin = g_admin;
	}
	else if (tokens[0].compare("/i") == 0) {
		if (tokens.size() > 1) {
			g_invisibility = true;

			g_invisoff = atof(tokens[1].c_str());

			gwr->Game->vfptr->OnLog(gwr->Game, "Invisibility ON");
		}
		else {
			g_invisibility = false;

			gwr->Game->vfptr->OnLog(gwr->Game, "Invisibility OFF");
		}
	}
	else if (tokens[0].compare("/test") == 0) {
		std::string data = "Testing...?";

		WorldBackup.Chat(pthis, NULL, data);

		/*
		for (auto actor : gwr->GameWorld->m_actors) {
			if (!actor.m_object)
				continue;

			if (actor.m_object == (IActor*) player)
				continue;

			const char* name = actor.m_object->vfptr->GetDisplayName(actor.m_object);

			if (!name)
				continue;

			app.log("Actor: %s", name);

			if (!strcmp(name, "Golden Egg")) {
				gwr->GameWorld->vfptr->Activate(gwr->GameWorld, player, actor.m_object);
				//actor.m_object->vfptr->OnUse(actor.m_object, (IPlayer*) player);
			}
		}*/
	}
	else {
		command = false;
	}

	// Don't output
	if (command)
		return;

	WorldBackup.Chat(pthis, player, text);
}

//

DWORD WINAPI lpHackThread(LPVOID lpParam)
{
	HMODULE hGameLogic = NULL;

	while (hGameLogic == NULL) {
		hGameLogic = GetModuleHandle("GameLogic.dll");

		Sleep(100);
	}

	app.log("GameLogic.dll = 0x%X", hGameLogic);

	gwr = (GameWorldRef*)((DWORD)hGameLogic + 0x97D7C);

	app.log("gwr = 0x%X", gwr);

	if (gwr == NULL) {
		app.log("Unable to get GameWorldRef!");
		ExitProcess(0);
	}

	app.log("Waiting for game world...");

	while (gwr->GameWorld == NULL) {
		Sleep(100);
	}

	app.log("GameWorld: 0x%X", gwr->GameWorld);
	app.log("Game: 0x%X", gwr->Game);

	while (gwr->GameWorld == NULL || gwr->GameWorld->vfptr == NULL || gwr->GameWorld->vfptr->Chat == NULL)
		Sleep(100);

	ZeroMemory(&WorldBackup, sizeof(WorldVtbl));

	memcpy(&WorldBackup, gwr->GameWorld->vfptr, sizeof(WorldVtbl));

	MEMORY_BASIC_INFORMATION mbi;
	VirtualQuery((LPCVOID)gwr->GameWorld->vfptr, &mbi, sizeof(mbi));
	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_EXECUTE_READWRITE, &mbi.Protect);
	
	gwr->GameWorld->vfptr->Chat = (WorldChat_t) new_WorldChat;
	gwr->GameWorld->vfptr->Tick = (WorldTick_t) new_WorldTick;
	//gwr->GameWorld->vfptr->IsAuthority = (WorldIsAuthority_t) new_WorldIsAuthority;

	VirtualProtect(mbi.BaseAddress, mbi.RegionSize, mbi.Protect, &mbi.Protect);

	app.log("Hooked World...");

	return 0;
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if (dwReason == DLL_PROCESS_ATTACH) {
		app.module(hModule);
		app.log("Loaded!");

		CreateThread(0, 0, lpHackThread, 0, 0, 0);
	}

	return TRUE;
}

extern "C"
{
	__declspec(dllexport) void stub()
	{
		
	}
}
