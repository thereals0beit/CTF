#pragma once

struct CharacterInfo
{
	int id;
	const char *name;
	const char *location;
	char avatar;
	unsigned int colors[4];
	unsigned int flags;
};

struct GameAPIVtbl
{
	bool(__thiscall *SpawnActor)(GameAPI *pthis, IActor *, Vector3 *, Rotation *, bool);
	bool(__thiscall *SpawnActorAtNamedLocation)(GameAPI *pthis, IActor *, const char *);
	bool(__thiscall *SpawnRemotePlayer)(GameAPI *pthis, IPlayer *, Vector3 *, Rotation *);
	void(__thiscall *DamageInRadius)(GameAPI *pthis, IActor *, IItem *, Vector3 *, float, int, DamageType);
	unsigned int(__thiscall *GetNamedLocationPoints)(GameAPI *pthis, const char *, LocationAndRotation **);
	void(__thiscall *FreeNamedLocationPoints)(GameAPI *pthis, LocationAndRotation *);
	Vector3 *(__thiscall *GetDirectionFromRotation)(GameAPI *pthis, Vector3 *result, Rotation *);
	Rotation *(__thiscall *GetRotationFromDirection)(GameAPI *pthis, Rotation *result, Vector3 *);
	void(__thiscall *OnWeaponFired)(GameAPI *pthis, IItem *, Vector3 *, Vector3 *);
	void(__thiscall *OnBulletHitActor)(GameAPI *pthis, IItem *, IActor *, Vector3 *, Vector3 *);
	void(__thiscall *OnBulletHitWorld)(GameAPI *pthis, IItem *, Vector3 *, Vector3 *);
	void(__thiscall *OnLog)(GameAPI *pthis, const char *);
	void(__thiscall *OnMasterServerConnected)(GameAPI *pthis, bool, const char *, const char *);
	void(__thiscall *OnLoginComplete)(GameAPI *pthis, bool, const char *, bool, CharacterInfo *, unsigned int);
	void(__thiscall *OnRegisterComplete)(GameAPI *pthis, bool, const char *, const char *, bool);
	void(__thiscall *OnCreateCharacterComplete)(GameAPI *pthis, bool, const char *, int);
	void(__thiscall *OnDeleteCharacterComplete)(GameAPI *pthis, bool, int);
	void(__thiscall *OnJoinGameServerComplete)(GameAPI *pthis, bool, const char *, bool, const char *, unsigned __int16, const char *);
	void(__thiscall *OnGameServerConnected)(GameAPI *pthis, bool, const char *, Vector3 *, Rotation *);
	void(__thiscall *OnTransitionToNewServer)(GameAPI *pthis);
	void(__thiscall *OnSubmitAnswerComplete)(GameAPI *pthis, bool, const char *);
	void(__thiscall *OnTeammatesListed)(GameAPI *pthis, const char **, const char **, unsigned int);
	unsigned int(__thiscall *GetDefaultCircuitInputs)(GameAPI *pthis, const char *);
	unsigned int(__thiscall *GetCircuitOutputCount)(GameAPI *pthis, const char *);
	void(__thiscall *GetCircuitOutputs)(GameAPI *pthis, const char *, unsigned int, bool *, unsigned int, bool *);
};

struct GameAPI
{
	GameAPIVtbl *vfptr;
};