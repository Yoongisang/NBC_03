#pragma once
#include <iostream>

using namespace std;

template <typename T>
class Inventory
{
private:
	T* pItem_ = nullptr;
	int capacity_;
	int size_;
public:
	// 생성자 소멸자
	Inventory(int capacity = 10);
	~Inventory();
	// 외부에서 인벤토리 객체를 조작하는 기능
	void AddItem(const T& item);
	void RemoveLastItem();
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
	pItem_ = new T[capacity_];
}

template<typename T>
inline Inventory<T>::~Inventory()
{
	// 소멸자에서 배열 해제 및 nullptr 입력(nullptr이 아니라면)
	if (pItem_ != nullptr)
	{
		delete[] pItem_;
		pItem_ = nullptr;
	}

	cout << "소멸자 호출" << '\n';
}

template<typename T>
inline void Inventory<T>::AddItem(const T& item)
{
	// 인벤토리 공간 체크
	if (size_ >= capacity_)
	{
		cout << "인벤토리가 꽉 찼습니다." << '\n';
		return;
	}

	pItem_[size_] = item;
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

	pItem_[size_-1] = T();
	size_--;
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
		pItem_[i]->PrintInfo();
	}
}
