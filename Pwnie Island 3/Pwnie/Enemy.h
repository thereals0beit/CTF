#pragma once

struct AIState;

struct AIStateVtbl
{
	void *(__thiscall *__vecDelDtor)(AIState *pthis, unsigned int);
	void(__thiscall *EnterState)(AIState *pthis, Actor *);
	void(__thiscall *LeaveState)(AIState *pthis);
	void(__thiscall *Tick)(AIState *pthis, float);
	void(__thiscall *OnAIMoveComplete)(AIState *pthis);
};

struct AIActor;

struct AIState
{
	AIStateVtbl *vfptr;
	AIActor *m_owner;
	TimerSet m_timers;
};

struct AIActor : Actor
{
	std::map<std::basic_string<char, std::char_traits<char>, std::allocator<char> >, AIState *, std::less<std::basic_string<char, std::char_traits<char>, std::allocator<char> > >, std::allocator<std::pair<std::basic_string<char, std::char_traits<char>, std::allocator<char> > const, AIState *> > > m_states;
	AIState *m_initialState;
	AIState *m_currentState;
	ActorRef<Actor> m_target;
};

struct LootEntry
{
	IItem *item;
	unsigned int minCount;
	unsigned int maxCount;
	float weight;
};

struct LootTable
{
	struct TableEntry
	{
		unsigned int value;
		float weight;
	};

	float m_dropChance;
	std::vector<LootTable::TableEntry, std::allocator<LootTable::TableEntry> > m_tiers;
	std::vector<LootTable::TableEntry, std::allocator<LootTable::TableEntry> > m_counts;
	float m_totalTierWeight;
	float m_totalCountWeight;
	std::vector<LootEntry, std::allocator<LootEntry> > m_additionalItems;
};

struct Enemy : public AIActor
{
	LootTable m_loot;
};

struct Magmarok : public Enemy
{
	bool m_healingActive;
	float m_healingTimeLeft;
	float m_advanceQuestTimer;
};

struct MagmarokFireball : public Projectile
{
	//
};

struct MagmarokSpawner : public Spawner
{
	//
};