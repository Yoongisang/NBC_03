#include "ItemBase.h"
#include <iostream>
using namespace std;

void ItemBase::PrintInfo() const
{
	cout << "[이름: " << name_ << ", 가격: " << price_ << "G]" << endl;
}
