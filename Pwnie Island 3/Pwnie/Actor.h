#pragma once

struct IUE4ActorVtbl
{
	void *(__thiscall *GetUE4Actor)(IUE4Actor *pthis);
	void(__thiscall *RemoveFromWorld)(IUE4Actor *pthis);
	Vector3 *(__thiscall *GetPosition)(IUE4Actor *pthis, Vector3 *result);
	Rotation *(__thiscall *GetRotation)(IUE4Actor *pthis, Rotation *result);
	Vector3 *(__thiscall *GetProjectilePosition)(IUE4Actor *pthis, Vector3 *result);
	Vector3 *(__thiscall *GetCharacterVelocity)(IUE4Actor *pthis, Vector3 *result);
	void(__thiscall *SetPosition)(IUE4Actor *pthis, Vector3 *);
	void(__thiscall *SetRotation)(IUE4Actor *pthis, Rotation *);
	void(__thiscall *SetCharacterVelocity)(IUE4Actor *pthis, Vector3 *);
	void(__thiscall *SetForwardAndStrafeMovement)(IUE4Actor *pthis, float, float);
	void(__thiscall *InterpolatePositionAndRotation)(IUE4Actor *pthis, Vector3 *, Rotation *, float, float);
	bool(__thiscall *MoveToLocation)(IUE4Actor *pthis, Vector3 *);
	bool(__thiscall *MoveToRandomLocationInRadius)(IUE4Actor *pthis, float);
	bool(__thiscall *MoveToActor)(IUE4Actor *pthis, IActor *);
	void(__thiscall *OnUpdateState)(IUE4Actor *pthis, const char *, bool);
	void(__thiscall *OnTriggerEvent)(IUE4Actor *pthis, const char *, IActor *);
	void(__thiscall *OnUpdatePvPEnabled)(IUE4Actor *pthis, bool);
	IActor *(__thiscall *LineTraceTo)(IUE4Actor *pthis, Vector3 *);
	void(__thiscall *FireBullets)(IUE4Actor *pthis, IItem *, int, DamageType, Vector3 *, unsigned int, float);
	void(__thiscall *LocalRespawn)(IUE4Actor *pthis, Vector3 *, Rotation *);
	bool(__thiscall *IsOnGround)(IUE4Actor *pthis);
	void(__thiscall *OnReload)(IUE4Actor *pthis, unsigned int);
};

struct IUE4Actor
{
	IUE4ActorVtbl *vfptr;
};

struct ILocalPlayer : public IUE4Actor
{
	//
};

struct IActorFactoryVtbl
{
	Actor *(__thiscall *CreateActor)(IActorFactory *pthis);
};

struct IActorFactory
{
	IActorFactoryVtbl *vfptr;
};

struct IActorVtbl
{
	void *(__thiscall *__vecDelDtor)(IActor *pthis, unsigned int);
	void *(__thiscall *GetUE4Actor)(IActor *pthis);
	bool(__thiscall *IsNPC)(IActor *pthis);
	bool(__thiscall *IsPlayer)(IActor *pthis);
	IPlayer *(__thiscall *GetPlayerInterface)(IActor *pthis);
	void(__thiscall *AddRef)(IActor *pthis);
	void(__thiscall *Release)(IActor *pthis);
	void(__thiscall *OnSpawnActor)(IActor *pthis, IUE4Actor *);
	void(__thiscall *OnDestroyActor)(IActor *pthis);
	const char *(__thiscall *GetBlueprintName)(IActor *pthis);
	bool(__thiscall *IsCharacter)(IActor *pthis);
	bool(__thiscall *CanBeDamaged)(IActor *pthis, IActor *);
	int(__thiscall *GetHealth)(IActor *pthis);
	int(__thiscall *GetMaxHealth)(IActor *pthis);
	void(__thiscall *Damage)(IActor *pthis, IActor *, IItem *, int, DamageType);
	void(__thiscall *Tick)(IActor *pthis, float);
	bool(__thiscall *CanUse)(IActor *pthis, IPlayer *);
	void(__thiscall *OnUse)(IActor *pthis, IPlayer *);
	void(__thiscall *OnHit)(IActor *pthis, IActor *, Vector3 *, Vector3 *);
	void(__thiscall *OnAIMoveComplete)(IActor *pthis);
	const char *(__thiscall *GetDisplayName)(IActor *pthis);
	bool(__thiscall *IsElite)(IActor *pthis);
	bool(__thiscall *IsPvPEnabled)(IActor *pthis);
	IItem **(__thiscall *GetShopItems)(IActor *pthis, unsigned int *);
	void(__thiscall *FreeShopItems)(IActor *pthis, IItem **);
	int(__thiscall *GetBuyPriceForItem)(IActor *pthis, IItem *);
	int(__thiscall *GetSellPriceForItem)(IActor *pthis, IItem *);
	Vector3 *(__thiscall *GetLookPosition)(IActor *pthis, Vector3 *result);
	Rotation *(__thiscall *GetLookRotation)(IActor *pthis, Rotation *result);
	IActor *(__thiscall *GetOwner)(IActor *pthis);
};

struct IActor
{
	IActorVtbl *vfptr;
};

struct Actor
{
	IActor baseclass_0;
	unsigned int m_refs;
	unsigned int m_id;
	IUE4Actor *m_target;
	TimerSet *m_timers;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_blueprintName;
	ActorRef<IActor> m_owner;
	int m_health;
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, bool, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, bool> > > m_states;
	float m_forwardMovementFraction;
	float m_strafeMovementFraction;
	Vector3 m_remotePosition;
	Vector3 m_remoteVelocity;
	Rotation m_remoteRotation;
	float m_remoteLocationBlendFactor;
	Spawner *m_spawner;
};

struct AIZoneListenerVtbl
{
	void *(__thiscall *__vecDelDtor)(AIZoneListener *pthis, unsigned int);
	void(__thiscall *OnAIZoneActivated)(AIZoneListener *pthis);
	void(__thiscall *OnAIZoneDeactivated)(AIZoneListener *pthis);
};

struct AIZoneListener
{
	AIZoneListenerVtbl *vfptr;
	AIZone *m_zone;
};

struct Spawner
{
	AIZoneListener baseclass_0;
	std::vector<ActorRef<Actor>, std::allocator<ActorRef<Actor> > > m_actors;
	Vector3 m_position;
	Rotation m_rotation;
	unsigned int m_maxActors;
	float m_maxSpawnTimer;
	float m_currentSpawnTimer;
};
