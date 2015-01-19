#pragma once

// Basic

struct IUE4Actor;
struct IActor;
struct Actor;
struct IActorFactory;
struct IPlayer;
struct Spawner;
struct AIZoneListener;
struct IItem;
struct AIZone;
struct IInventory;
struct IQuestState;
struct IQuest;
struct WriteStream;
struct GameAPI;

enum DamageType
{
	PhysicalDamage = 0x0,
	FireDamage = 0x1,
	ColdDamage = 0x2,
	ShockDamage = 0x3,
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Rotation
{
	float pitch;
	float yaw;
	float roll;
};

struct LocationAndRotation
{
	Vector3 location;
	Rotation rotation;
};

struct TimerSet
{
	struct TimerEvent
	{
		float timeLeft;
		float initialTime;
		bool recurring;
		bool withContext;
		std::function<void __cdecl(void)> callback;
		std::function<void __cdecl(Actor *)> contextCallback;
	};

	// fucked up
	unsigned char m_times[0x8];
};

//

struct GhettoObject
{
	template<typename T> __forceinline T Get(int offset) {
		return *(T*)((DWORD) this + offset);
	}

	template<typename T> __forceinline void Set(T data, int offset) {
		*(T*)((DWORD) this + offset) = data;
	}
};

template<typename T> struct ActorRef
{
	T* m_object;
};