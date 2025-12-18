#pragma once
#include <iostream>
#include <algorithm>
#include "ItemBase.h"
using namespace std;

// 포인터용 비교 함수
bool compareItemsByPrice(ItemBase* a, ItemBase* b) {
	return a->GetPrice() < b->GetPrice();
}

template <typename T>
class Inventory
{
private:
	T* pItems_ = nullptr;
	int capacity_;
	int size_;
public:
	// 생성자 소멸자
	Inventory(int capacity = 10);
	//복사 생성자
	Inventory(const Inventory<T>& other);
	~Inventory();
	// 외부에서 인벤토리 객체를 조작하는 기능
	void AddItem(const T& item);
	void RemoveLastItem();
	void Resize(int newCapacity);
	void SortItems();
	// 대입 함수(이미 존재하는 객체에 값을 덮어쓸 때
	void Assign(const Inventory<T>& other);
	// Getter
	int GetSize() const { return size_; }
	int GetCapacity() const { return capacity_;	}
	// 아이템 정보 출력
	void PrintAllItems() const;
};


template<typename T>
inline Inventory<T>::Inventory(int capacity) : capacity_(capacity), size_(0)
{
	// 0 이하의 입력이 들어오면 기본 용량 1 할당
	if (capacity <= 0)
	{
		capacity_ = 1;
	}
	// 받은 용량대로 아이템 동적배열
	pItems_ = new T[capacity_];
}

template<typename T>
inline Inventory<T>::Inventory(const Inventory<T>& other)
{
	capacity_ = other.capacity_;
	size_ = other.size_;
	pItems_ = new T[capacity_];
	for (int i = 0; i < size_; ++i)
	{
		pItems_[i] = other.pItems_[i];
	}
	cout << "인벤토리 복사 완료" << '\n';
}

template<typename T>
inline Inventory<T>::~Inventory()
{
	// 소멸자에서 배열 해제 및 nullptr 입력(nullptr이 아니라면)
	if (pItems_ != nullptr)
	{
		delete[] pItems_;
		pItems_ = nullptr;
	}

	cout << "소멸자 호출" << '\n';
}

template<typename T>
inline void Inventory<T>::AddItem(const T& item)
{
	// 인벤토리 공간 체크
	if (size_ >= capacity_)
	{
		cout << "인벤토리가 꽉 차서 확장합니다." << '\n';
		int newCapacity = capacity_ * 2;
		T* temp = new T[newCapacity];

		for (int i = 0; i < size_; i++)
		{
			temp[i] = pItems_[i];
		}
		delete[] pItems_;

		pItems_ = temp;
		capacity_ = newCapacity;
	}

	pItems_[size_] = item;
	size_++;
}

template<typename T>
inline void Inventory<T>::RemoveLastItem()
{
	// 인벤토리 공간 체크
	if (size_ == 0)
	{
		cout << "인벤토리가 비어있습니다." << '\n';
		return;
	}

	pItems_[size_-1] = T();
	size_--;
}

template<typename T>
inline void Inventory<T>::Resize(int newCapacity)
{
	if (newCapacity <= 0)
	{
		newCapacity = 1;
	}

	T* temp = new T[newCapacity];
	// 용량과 기존 size_중 작은 값만큼 복사
	int copySize = min(newCapacity, size_);

	for (int i = 0; i < copySize; i++)
	{
		temp[i] = pItems_[i];
	}

	delete[] pItems_;
	pItems_ = temp;
	capacity_ = newCapacity;
	size_ = copySize;
}

template<typename T>
inline void Inventory<T>::SortItems()
{
	if (size_ <= 1)
	{
		return;
	}

	sort(pItems_, pItems_ + size_, compareItemsByPrice);
	
}

template<typename T>
inline void Inventory<T>::Assign(const Inventory<T>& other)
{
	if (this == &other)
	{
		return;
	}
	delete[] pItems_;

	capacity_ = other.capacity_;
	size_ = other.size_;
	pItems_ = new T[capacity_];

	for (int i = 0; i < size_; ++i) {
		pItems_[i] = other.pItems_[i];
	}

	cout << "인벤토리 복사 완료" << endl;
}

template<typename T>
inline void Inventory<T>::PrintAllItems() const
{
	if (size_ == 0)
	{
		cout << "(비어있음)" << '\n';
		return;
	}

	for (int i = 0; i < size_; i++)
	{
		pItems_[i]->PrintInfo();
	}
}
