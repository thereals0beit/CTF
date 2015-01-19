#pragma once

struct ItemAndCount
{
	IItem *item;
	unsigned int count;
	unsigned int loadedAmmo;
};

struct ItemPickup
{
	Actor baseclass_0;
	IItem *m_item;
	std::basic_string<char, std::char_traits<char>, std::allocator<char> > m_pickupName;
};

enum ItemRarity
{
	ResourceItem = 0x0,
	NormalItem = 0x1,
	RareItem = 0x2,
	LegendaryItem = 0x3,
	LeetItem = 0x4,
};

struct IItemVtbl
{
	void *(__thiscall *__vecDelDtor)(IItem *pthis, unsigned int);
	const char *(__thiscall *GetName)(IItem *pthis);
	const char *(__thiscall *GetDisplayName)(IItem *pthis);
	const char *(__thiscall *GetItemTypeName)(IItem *pthis);
	const char *(__thiscall *GetDescription)(IItem *pthis);
	const char *(__thiscall *GetFlavorText)(IItem *pthis);
	bool(__thiscall *CanEquip)(IItem *pthis);
	unsigned int(__thiscall *GetMaximumCount)(IItem *pthis);
	bool(__thiscall *CanActivate)(IItem *pthis, IPlayer *);
	bool(__thiscall *CanActivateInInventory)(IItem *pthis);
	void(__thiscall *Activate)(IItem *pthis, IPlayer *);
	bool(__thiscall *ShowInInventory)(IItem *pthis);
	bool(__thiscall *ShowEventOnPickup)(IItem *pthis);
	bool(__thiscall *ShowEventOnDuplicatePickup)(IItem *pthis);
	bool(__thiscall *ShowNotificationOnPickup)(IItem *pthis);
	float(__thiscall *GetCooldownTime)(IItem *pthis);
	ItemRarity(__thiscall *GetItemRarity)(IItem *pthis);
	IItem *(__thiscall *GetAmmoType)(IItem *pthis);
	unsigned int(__thiscall *GetClipSize)(IItem *pthis);
	int(__thiscall *GetDamage)(IItem *pthis);
	int(__thiscall *GetDamagePerSecond)(IItem *pthis);
	DamageType(__thiscall *GetDamageType)(IItem *pthis);
	int(__thiscall *GetManaCost)(IItem *pthis);
	const char *(__thiscall *GetCustomCostDescription)(IItem *pthis);
	bool(__thiscall *IsAutoFire)(IItem *pthis);
	unsigned int(__thiscall *GetNumberOfProjectiles)(IItem *pthis);
	float(__thiscall *GetReloadTime)(IItem *pthis, int);
	bool(__thiscall *HasPartialReload)(IItem *pthis);
	float(__thiscall *GetRange)(IItem *pthis);
	int(__thiscall *GetTradeValue)(IItem *pthis);
	bool(__thiscall *IsDynamic)(IItem *pthis);
	bool(__thiscall *IsUpdating)(IItem *pthis);
};


struct IItem
{
	IItemVtbl *vfptr;
};

struct Item
{
	IItem baseclass_0;
};

struct ZeroCool
{
	Item baseclass_0;
};

struct GoldenEgg
{
	Item baseclass_0;
};