#pragma once
#include <iostream>
#include <algorithm>
#include "ItemBase.h"
using namespace std;

// 포인터용 비교 함수: pItems_가 포인터 배열이므로 매개변수도 포인터로 받음
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
	// 받은 용량만큼 배열 동적 할당
	pItems_ = new T[capacity_];
}

template<typename T>
inline Inventory<T>::Inventory(const Inventory<T>& other)
{
	// 복사생성자로 다른 객체의 값들을 복사하기위해 capacity, size값 복사 new T[capacity]로 동적 할당 
	capacity_ = other.capacity_;
	size_ = other.size_;
	pItems_ = new T[capacity_];
	//other의 pItems_의 값들을 복사(깊은복사)
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
		// 확장하기 위해 새 공간을 기존 공간 * 2로 설정 그 크기만큼 동적할당한 임시포인터 생성
		int newCapacity = capacity_ * 2;
		T* temp = new T[newCapacity];
		// 임시 포인터에 기존의 값들을 복사
		for (int i = 0; i < size_; i++)
		{
			temp[i] = pItems_[i];
		}
		// 기존 포인터 해제
		delete[] pItems_;
		// 기존 포인터에 임시 포인터 주소 대입, capacity_도 새 크기로 갱신
		pItems_ = temp;
		capacity_ = newCapacity;
	}
	// 추가하려던 새 item을 추가 후 size++
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
	// 배열의 마지막 item 삭제, size--
	pItems_[size_-1] = T();
	size_--;
}

template<typename T>
inline void Inventory<T>::Resize(int newCapacity)
{
	// 새로 설정하는 공간이 0보다 작다면 생성자 규칙과 같게 1로 설정
	if (newCapacity <= 0)
	{
		newCapacity = 1;
	}
	// 재설정된 capacity 크기만큼 동적 할당
	T* temp = new T[newCapacity];
	// 새로 설정된 용량과 기존 size_중 작은 값만큼 copySize로 설정한 다음 아이템 데이터 복사(깊은 복사)
	int copySize = min(newCapacity, size_);
	for (int i = 0; i < copySize; i++)
	{
		temp[i] = pItems_[i];
	}
	// 기존 포인터 해제 및 임시포인터의 주소를 가리키도록 설정 capcity_, size_ 값 재설정
	delete[] pItems_;
	pItems_ = temp;
	capacity_ = newCapacity;
	size_ = copySize;
}

template<typename T>
inline void Inventory<T>::SortItems()
{
	// 아이템이 1개 이하면 정렬 필요 X
	if (size_ <= 1)
	{
		return;
	}
	// sort(시작, 끝): 끝은 마지막 요소 다음을 가리킴
	// pItems_ + size_ = 배열 끝 다음 위치	
	sort(pItems_, pItems_ + size_, compareItemsByPrice);
	
}

template<typename T>
inline void Inventory<T>::Assign(const Inventory<T>& other)
{
	// 자기 자신에게 대입하는 경우 무시
	if (this == &other)
	{
		return;
	}
	// 기존 포인터 해제
	delete[] pItems_;
	// capacity_, size_ 재설정 포인터 새로 동적할당
	capacity_ = other.capacity_;
	size_ = other.size_;
	pItems_ = new T[capacity_];
	// 아이템 데이터 깊은복사 
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
		// pItems_가 담고있는 클래스 객체의 PrintInfo()함수 호출
		pItems_[i]->PrintInfo();
	}
}
