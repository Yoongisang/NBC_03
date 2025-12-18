#pragma once
#include <string>

class ItemBase
{
protected:
	std::string name_;
	int price_;
public:
	// 생성과 동시에 아이템 이름, 가격 할당
	ItemBase(std::string name, int price) : name_(name), price_(price) {}
	// 아이템 정보 출력
	void PrintInfo() const;
	
	// 게터 함수(이름, 가격)
	std::string GetName() const { return name_; }
	int GetPrice() const { return price_; }
	// 기본 소멸자 상속 대비 virtual사용
	virtual ~ItemBase() = default;
};
