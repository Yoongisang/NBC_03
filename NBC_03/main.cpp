#include <iostream>
#include "Inventory.h"
#include "ItemBase.h"
#include "Weapon.h"
#include "Potion.h"
#include <string>

using namespace std;




int main()
{
    // 아이템 생성
    Weapon sword = { "Sword", 500 };
    Weapon axe = { "Axe", 300 };
    Potion hp = { "HpPotion", 100 };
    Potion mp = { "MpPotion", 200 };

    // 인벤토리 생성
    Inventory<ItemBase*> inven(5);

    // 아이템 추가
    cout << "=== 아이템 추가 ===" << endl;
    inven.AddItem(&sword);
    inven.AddItem(&axe);
    inven.AddItem(&hp);
    inven.AddItem(&mp);
    inven.PrintAllItems();
    cout << "Size: " << inven.GetSize() << ", Capacity: " << inven.GetCapacity() << endl;

    // 정렬 테스트
    cout << "\n=== 가격 오름차순 정렬 ===" << endl;
    inven.SortItems();
    inven.PrintAllItems();

    // 삭제 테스트
    cout << "\n=== 마지막 아이템 삭제 ===" << endl;
    inven.RemoveLastItem();
    inven.PrintAllItems();

    // 복사 생성자 테스트
    cout << "\n=== 복사 생성자 테스트 ===" << endl;
    {
        Inventory<ItemBase*> inven2(inven);
        cout << "inven2 Size: " << inven2.GetSize() << endl;
        inven2.PrintAllItems();
    }
    cout << "블록 종료 후 원본 확인:" << endl;
    inven.PrintAllItems();

    // Resize 테스트
    cout << "\n=== Resize 테스트 (용량 2로 축소) ===" << endl;
    inven.Resize(2);
    cout << "Size: " << inven.GetSize() << ", Capacity: " << inven.GetCapacity() << endl;
    inven.PrintAllItems();

    // 용량 초과 자동 확장 테스트
    cout << "\n=== 자동 확장 테스트 ===" << endl;
    inven.AddItem(&sword);
    inven.AddItem(&axe);
    inven.AddItem(&hp);
    cout << "Size: " << inven.GetSize() << ", Capacity: " << inven.GetCapacity() << endl;

    // Assign 테스트
    cout << "\n=== Assign 테스트 ===" << endl;
    Inventory<ItemBase*> inven3(3);
    inven3.AddItem(&mp);
    cout << "대입 전 inven3:" << endl;
    inven3.PrintAllItems();
    inven3.Assign(inven);
    cout << "대입 후 inven3:" << endl;
    inven3.PrintAllItems();

    cout << "\n=== 프로그램 종료 ===" << endl;

	return 0;
}