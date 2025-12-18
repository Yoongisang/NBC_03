#include <iostream>
#include "Inventory.h"
#include <string>
using namespace std;

class ItemBase
{
protected:
	string name_;
	int price_;
public:
	ItemBase(string name, int price) : name_(name), price_(price) {}
	virtual void PrintInfo() const
	{
		cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
	}

	virtual ~ItemBase() = default;
};

class Weapon : public ItemBase
{
public:
	Weapon(string name, int price) : ItemBase(name, price) {}
	virtual void PrintInfo() const
	{
		cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
	}

	virtual ~Weapon() = default;
};

class Potion : public ItemBase
{
public:
	Potion(string name, int price) : ItemBase(name, price) {}
	virtual void PrintInfo() const
	{
		cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
	}

	virtual ~Potion() = default;
};


int main()
{
	Weapon W = { "Sword", 10 };
	Potion HP = { "HpPotion", 3 };
	Potion MP = { "MpPotion", 2 };

	Inventory<ItemBase*> I(15);
	cout << "1번 인벤토리 테스트" << '\n';
	cout << "*삭제" << '\n';
	I.RemoveLastItem();
	cout << "*추가 및 공간 체크" << '\n';
	I.AddItem(&W);
	I.AddItem(&HP);
	cout << "Capacity: " << I.GetCapacity() << " Size: " << I.GetSize() << '\n';
	I.AddItem(&MP);
	cout << "Capacity: " << I.GetCapacity() << " Size: " << I.GetSize() << '\n';
	cout << "*아이템 정보 출력" << '\n';
	I.PrintAllItems();
	cout << "*아이템 삭제 후 정보 출력" << '\n';
	I.RemoveLastItem();
	I.PrintAllItems();
	cout << "*인벤토리가 꽉 찼을때" << '\n';
	for (int i = 0; i < 14; i++)
	{
		// 꽉 찼을때 체크
		I.AddItem(&MP);
	}

	I.PrintAllItems();

	return 0;
}