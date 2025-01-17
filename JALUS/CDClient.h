#pragma once
#include "ZoneIDs.h"
#include "ComponentsRegistryEntry.h"
#include "StatsIndexInfo.h"
#include "CurrentMissionTasks.h"

class MissionNPCInfo
{
public:
	long missionID = -1;
	bool offersMission = false;
	bool acceptsMission = false;
};

class MissionRewards
{
public:
	long long universeScore = 0;
	long long currency = 0;
	long long reputation = 0;
	vector<long> itemLOTs = vector<long>();
	vector<long> itemCounts = vector<long>();
	vector<long> emotes = vector<long>();
	long maxImagination = -1;
	long maxHealth = -1;
	long maxInventory = -1;
};
	
enum ItemType
{
	ITEM_TYPE_BRICK = 1,
	ITEM_TYPE_HAT,
	ITEM_TYPE_HAIR,
	ITEM_TYPE_NECK,
	ITEM_TYPE_LEFT_HAND,
	ITEM_TYPE_RIGHT_HAND,
	ITEM_TYPE_LEGS,
	ITEM_TYPE_LEFT_TRINKET,
	ITEM_TYPE_RIGHT_TRINKET,
	ITEM_TYPE_BEHAVIOR,
	ITEM_TYPE_PROPERTY,
	ITEM_TYPE_MODEL,
	ITEM_TYPE_COLLECTABLE,
	ITEM_TYPE_CONSUMABLE,
	ITEM_TYPE_CHEST,
	ITEM_TYPE_EGG,
	ITEM_TYPE_PET_FOOD,
	ITEM_TYPE_QUEST_OBJECT,
	ITEM_TYPE_PET_INVENTORY_ITEM,
	ITEM_TYPE_PACKAGE,
	ITEM_TYPE_LOOT_MODEL,
	ITEM_TYPE_VEHICLE,
	ITEM_TYPE_CURRENCY,

	INVALID_ITEM_TYPE
};

class CDClient
{
public:
	static ItemType getItemType(long lot);
	static string getMinifigureName(long name_first, long name_middle, long name_last);
	static bool isActivityZone(ZoneID zoneID);
	static vector<ComponentsRegistryEntry> getComponentsRegistryEntries(long lot);
	static vector<long> getInventoryIndexInfo(long lot);
	static StatsIndexInfo getStatsIndexInfo(long componentID);
	static vector<MissionNPCInfo> getMissionNPCIndexInfo(long lot);
	static vector<long> getPrereqMissionIDs(long missionID);
	static vector<MissionTask> getMissionTasks(long missionID);
	static MissionRewards getMissionRewards(long missionID);
	static bool isMission(long missionID);
	static vector<long> getAchievements(long prereqMissionID = -1);
	static long lookUpLevel(long long universeScore);
};