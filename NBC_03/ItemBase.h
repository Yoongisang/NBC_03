#pragma once
#include <string>

class ItemBase
{
protected:
	std::string name_;
	int price_;
public:
	ItemBase(std::string name, int price) : name_(name), price_(price) {}
	void PrintInfo() const;
	

	std::string GetName() const { return name_; }
	int GetPrice() const { return price_; }

	virtual ~ItemBase() = default;
};
