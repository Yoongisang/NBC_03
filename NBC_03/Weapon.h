#pragma once
#include "ItemBase.h"

class Weapon : public ItemBase
{
public:
	Weapon(std::string name, int price) : ItemBase(name, price) {}
	virtual ~Weapon() = default;
};