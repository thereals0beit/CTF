#pragma once

struct PlayerQuestState
{
	IQuestState *state;
	unsigned int count;
};

struct IFastTravel
{
	//
};

struct IAchievement
{
	//
};

struct IPlayerVtbl
{
	IActor *(__thiscall *GetActorInterface)(IPlayer *pthis);
	bool(__thiscall *IsLocalPlayer)(IPlayer *pthis);
	ILocalPlayer *(__thiscall *GetLocalPlayer)(IPlayer *pthis);
	const char *(__thiscall *GetPlayerName)(IPlayer *pthis);
	const char *(__thiscall *GetTeamName)(IPlayer *pthis);
	char(__thiscall *GetAvatarIndex)(IPlayer *pthis);
	const unsigned int *(__thiscall *GetColors)(IPlayer *pthis);
	bool(__thiscall *IsPvPDesired)(IPlayer *pthis);
	void(__thiscall *SetPvPDesired)(IPlayer *pthis, bool);
	IInventory *(__thiscall *GetInventory)(IPlayer *pthis);
	unsigned int(__thiscall *GetItemCount)(IPlayer *pthis, IItem *);
	unsigned int(__thiscall *GetLoadedAmmo)(IPlayer *pthis, IItem *);
	bool(__thiscall *AddItem)(IPlayer *pthis, IItem *, unsigned int, bool);
	bool(__thiscall *RemoveItem)(IPlayer *pthis, IItem *, unsigned int);
	bool(__thiscall *AddLoadedAmmo)(IPlayer *pthis, IItem *, IItem *, unsigned int);
	bool(__thiscall *RemoveLoadedAmmo)(IPlayer *pthis, IItem *, unsigned int);
	IItem *(__thiscall *GetItemForSlot)(IPlayer *pthis, unsigned int);
	void(__thiscall *EquipItem)(IPlayer *pthis, unsigned int, IItem *);
	unsigned int(__thiscall *GetCurrentSlot)(IPlayer *pthis);
	void(__thiscall *SetCurrentSlot)(IPlayer *pthis, unsigned int);
	IItem *(__thiscall *GetCurrentItem)(IPlayer *pthis);
	int(__thiscall *GetMana)(IPlayer *pthis);
	bool(__thiscall *UseMana)(IPlayer *pthis, int);
	void(__thiscall *SetItemCooldown)(IPlayer *pthis, IItem *, float, bool);
	bool(__thiscall *IsItemOnCooldown)(IPlayer *pthis, IItem *);
	float(__thiscall *GetItemCooldown)(IPlayer *pthis, IItem *);
	bool(__thiscall *HasPickedUp)(IPlayer *pthis, const char *);
	void(__thiscall *MarkAsPickedUp)(IPlayer *pthis, const char *);
	IQuest **(__thiscall *GetQuestList)(IPlayer *pthis, unsigned int *);
	void(__thiscall *FreeQuestList)(IPlayer *pthis, IQuest **);
	IQuest *(__thiscall *GetCurrentQuest)(IPlayer *pthis);
	void(__thiscall *SetCurrentQuest)(IPlayer *pthis, IQuest *);
	PlayerQuestState (__thiscall *GetStateForQuest)(IPlayer *pthis, IQuest *);
	void(__thiscall *StartQuest)(IPlayer *pthis, IQuest *);
	void(__thiscall *AdvanceQuestToState)(IPlayer *pthis, IQuest *, IQuestState *);
	void(__thiscall *CompleteQuest)(IPlayer *pthis, IQuest *);
	bool(__thiscall *IsQuestStarted)(IPlayer *pthis, IQuest *);
	bool(__thiscall *IsQuestCompleted)(IPlayer *pthis, IQuest *);
	void(__thiscall *EnterAIZone)(IPlayer *pthis, const char *);
	void(__thiscall *ExitAIZone)(IPlayer *pthis, const char *);
	void(__thiscall *UpdateCountdown)(IPlayer *pthis, int);
	bool(__thiscall *CanReload)(IPlayer *pthis);
	void(__thiscall *RequestReload)(IPlayer *pthis);
	float(__thiscall *GetWalkingSpeed)(IPlayer *pthis);
	float(__thiscall *GetSprintMultiplier)(IPlayer *pthis);
	float(__thiscall *GetJumpSpeed)(IPlayer *pthis);
	float(__thiscall *GetJumpHoldTime)(IPlayer *pthis);
	bool(__thiscall *CanJump)(IPlayer *pthis);
	void(__thiscall *SetJumpState)(IPlayer *pthis, bool);
	void(__thiscall *SetSprintState)(IPlayer *pthis, bool);
	void(__thiscall *SetFireRequestState)(IPlayer *pthis, bool);
	void(__thiscall *TransitionToNPCState)(IPlayer *pthis, const char *);
	void(__thiscall *BuyItem)(IPlayer *pthis, IActor *, IItem *, unsigned int);
	void(__thiscall *SellItem)(IPlayer *pthis, IActor *, IItem *, unsigned int);
	void(__thiscall *EnterRegion)(IPlayer *pthis, const char *);
	void(__thiscall *Respawn)(IPlayer *pthis);
	void(__thiscall *Teleport)(IPlayer *pthis, const char *);
	void(__thiscall *Chat)(IPlayer *pthis, const char *);
	IFastTravel *(__thiscall *GetFastTravelDestinations)(IPlayer *pthis, const char *);
	void(__thiscall *FastTravel)(IPlayer *pthis, const char *, const char *);
	void(__thiscall *MarkAsAchieved)(IPlayer *pthis, IAchievement *);
	bool(__thiscall *HasAchieved)(IPlayer *pthis, IAchievement *);
	void(__thiscall *SubmitDLCKey)(IPlayer *pthis, const char *);
	unsigned int(__thiscall *GetCircuitInputs)(IPlayer *pthis, const char *);
	void(__thiscall *SetCircuitInputs)(IPlayer *pthis, const char *, unsigned int);
	void(__thiscall *GetCircuitOutputs)(IPlayer *pthis, const char *, bool *, unsigned int);
};

struct IPlayer
{
	IPlayerVtbl *vfptr;
};

struct Player
{
	Actor baseclass_0;
	IPlayer baseclass_70;
	unsigned int m_characterId;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_playerName;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_teamName;
	char m_avatarIndex;
	unsigned int m_colors[4];
	std::map<IItem *, ItemAndCount, std::less<IItem *>, std::allocator<std::pair<IItem * const, ItemAndCount> > > m_inventory;
	std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > m_pickups;
	std::map<IItem *, float, std::less<IItem *>, std::allocator<std::pair<IItem * const, float> > > m_cooldowns;
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, unsigned int, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, unsigned int> > > m_circuitInputs;
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::vector<bool, std::allocator<bool> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, std::vector<bool, std::allocator<bool> > > > > m_circuitOutputs;
	bool m_admin;
	bool m_pvpEnabled;
	bool m_pvpDesired;
	float m_pvpChangeTimer;
	int m_pvpChangeReportedTimer;
	bool m_changingServerRegion;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_currentRegion;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_changeRegionDestination;
	std::set<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::basic_string<char, std::char_traits<char>, std::allocator<char> > > > m_aiZones;
	int m_mana;
	float m_manaRegenTimer;
	float m_healthRegenCooldown;
	float m_healthRegenTimer;
	int m_countdown;
	Vector3 m_remoteLookPosition;
	Rotation m_remoteLookRotation;
	IItem *m_equipped[10];
	unsigned int m_currentSlot;
	std::map<IQuest *, PlayerQuestState, std::less<IQuest *>, std::allocator<std::pair<IQuest * const, PlayerQuestState> > > m_questStates;
	IQuest *m_currentQuest;
	float m_walkingSpeed;
	float m_jumpSpeed;
	float m_jumpHoldTime;
	ActorRef<NPC> m_currentNPC;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_currentNPCState;
	ILocalPlayer *m_localPlayer;
	WriteStream *m_eventsToSend;
	bool m_itemsUpdated;
	float m_itemSyncTimer;
	unsigned int m_chatMessageCounter;
	float m_chatFloodDecayTimer;
	IItem *m_lastHitByItem;
	float m_lastHitItemTimeLeft;
	float m_circuitStateCooldownTimer;
};
