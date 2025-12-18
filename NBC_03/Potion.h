#pragma once
#include "ItemBase.h"

class Potion : public ItemBase
{
public:
	Potion(std::string name, int price) : ItemBase(name, price) {}
	virtual ~Potion() = default;
};