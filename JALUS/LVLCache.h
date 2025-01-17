#pragma once
#include "Common.h"

class ObjectProperty
{
public:
	string key = "";
	string value = "";
	char type = -1;
};

class ObjectPropertyContainer
{
public:
	long long objectID = -1;
	vector<ObjectProperty> properties = vector<ObjectProperty>();
};

class LVLCache
{
private:
	static vector<ObjectPropertyContainer> containers;
public:
	static void loadObjects();
	static vector<ObjectProperty> getObjectProperties(long long objectID);
	static ObjectProperty getObjectProperty(string key, long long objectID);
};