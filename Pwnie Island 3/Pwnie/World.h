#pragma once

struct World;
struct Player;
struct ILocalPlayer;
struct Actor;
struct IItem;
struct IQuest;
struct IQuestState;
struct AIZone;

struct WorldVtbl
{
	void *(__thiscall *__vecDelDtor)(World *pthis, unsigned int);
	void(__thiscall *Tick)(World *pthis, float);
	bool(__thiscall *HasLocalPlayer)(World *pthis);
	bool(__thiscall *IsAuthority)(World *pthis);
	void(__thiscall *AddLocalPlayer)(World *pthis, Player *, ILocalPlayer *);
	void(__thiscall *AddRemotePlayer)(World *pthis, Player *);
	void(__thiscall *AddRemotePlayerWithId)(World *pthis, unsigned int, Player *);
	void(__thiscall *RemovePlayer)(World *pthis, Player *);
	void(__thiscall *Use)(World *pthis, Player *, Actor *);
	void(__thiscall *Activate)(World *pthis, Player *, IItem *);
	void(__thiscall *Reload)(World *pthis, Player *);
	void(__thiscall *Jump)(World *pthis, bool);
	void(__thiscall *Sprint)(World *pthis, bool);
	void(__thiscall *FireRequest)(World *pthis, bool);
	void(__thiscall *TransitionToNPCState)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *BuyItem)(World *pthis, Player *, Actor *, IItem *, unsigned int);
	void(__thiscall *SellItem)(World *pthis, Player *, Actor *, IItem *, unsigned int);
	void(__thiscall *Respawn)(World *pthis, Player *);
	void(__thiscall *Teleport)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *Chat)(World *pthis, Player *, std::string &text);
	void(__thiscall *FastTravel)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *SetPvPDesired)(World *pthis, Player *, bool);
	void(__thiscall *SubmitDLCKey)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *SetCircuitInputs)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, unsigned int);
	void(__thiscall *SendAddItemEvent)(World *pthis, Player *, IItem *, unsigned int);
	void(__thiscall *SendRemoveItemEvent)(World *pthis, Player *, IItem *, unsigned int);
	void(__thiscall *SendLoadedAmmoEvent)(World *pthis, Player *, IItem *, unsigned int);
	void(__thiscall *SendPickedUpEvent)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *EquipItem)(World *pthis, Player *, char, IItem *);
	void(__thiscall *SetCurrentSlot)(World *pthis, Player *, char);
	void(__thiscall *SendEquipItemEvent)(World *pthis, Player *, char, IItem *);
	void(__thiscall *SendCurrentSlotEvent)(World *pthis, Player *, char);
	void(__thiscall *SetCurrentQuest)(World *pthis, Player *, IQuest *);
	void(__thiscall *SendSetCurrentQuestEvent)(World *pthis, Player *, IQuest *);
	void(__thiscall *SendStartQuestEvent)(World *pthis, Player *, IQuest *);
	void(__thiscall *SendAdvanceQuestToStateEvent)(World *pthis, Player *, IQuest *, IQuestState *);
	void(__thiscall *SendCompleteQuestEvent)(World *pthis, Player *, IQuest *);
	void(__thiscall *SendHealthUpdateEvent)(World *pthis, Actor *, int);
	void(__thiscall *SendManaUpdateEvent)(World *pthis, Player *, int);
	void(__thiscall *SendCountdownUpdateEvent)(World *pthis, Player *, int);
	void(__thiscall *SendPvPCountdownUpdateEvent)(World *pthis, Player *, bool, int);
	void(__thiscall *SendPvPEnableEvent)(World *pthis, Player *, bool);
	void(__thiscall *SendStateEvent)(World *pthis, Actor *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, bool);
	void(__thiscall *SendTriggerEvent)(World *pthis, Actor *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, Actor *, bool);
	void(__thiscall *SendFireBulletsEvent)(World *pthis, Actor *, IItem *, Vector3 *, unsigned int, float);
	void(__thiscall *SendDisplayEvent)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *SendNPCConversationStateEvent)(World *pthis, Player *, Actor *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *SendNPCConversationEndEvent)(World *pthis, Player *);
	void(__thiscall *SendNPCShopEvent)(World *pthis, Player *, Actor *);
	void(__thiscall *SendRespawnEvent)(World *pthis, Player *, Vector3 *, Rotation *);
	void(__thiscall *SendTeleportEvent)(World *pthis, Actor *, Vector3 *, Rotation *);
	void(__thiscall *SendRelativeTeleportEvent)(World *pthis, Actor *, Vector3 *);
	void(__thiscall *SendReloadEvent)(World *pthis, Player *, IItem *, IItem *, unsigned int);
	void(__thiscall *SendPlayerJoinedEvent)(World *pthis, Player *);
	void(__thiscall *SendPlayerLeftEvent)(World *pthis, Player *);
	void(__thiscall *SendPlayerItemEvent)(World *pthis, Player *);
	void(__thiscall *SendActorSpawnEvent)(World *pthis, Actor *);
	void(__thiscall *SendActorDestroyEvent)(World *pthis, Actor *);
	void(__thiscall *SendExistingPlayerEvent)(World *pthis, Player *, Player *);
	void(__thiscall *SendExistingActorEvent)(World *pthis, Player *, Actor *);
	void(__thiscall *SendChatEvent)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *SendKillEvent)(World *pthis, Player *, Actor *, IItem *);
	void(__thiscall *SendCircuitOutputEvent)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *, unsigned int, std::vector<bool, std::allocator<bool> > *);
	void(__thiscall *SendActorPositionEvents)(World *pthis, Player *);
	void(__thiscall *SendRegionChangeEvent)(World *pthis, Player *, std::basic_string<char, std::char_traits<char>, std::allocator<char> > *);
	void(__thiscall *SendLastHitByItemEvent)(World *pthis, Player *, IItem *);
};

struct World
{
	WorldVtbl *vfptr;
	std::set<ActorRef<IPlayer>, std::less<ActorRef<IPlayer> >, std::allocator<ActorRef<IPlayer> > > m_players;
	std::set<ActorRef<IActor>, std::less<ActorRef<IActor> >, std::allocator<ActorRef<IActor> > > m_actors;
	std::map<unsigned int, ActorRef<IActor>, std::less<unsigned int>, std::allocator<std::pair<unsigned int const, ActorRef<IActor> > > > m_actorsById;
	ILocalPlayer *m_localPlayer;
	unsigned int m_nextId;
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, AIZone *, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, AIZone *> > > m_aiZones;
};

struct ClientWorld : public World
{
	ActorRef<IPlayer> m_activePlayer;
	float m_timeUntilNextNetTick;
};