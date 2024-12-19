#include <iostream>
#include <windows.h>

using namespace std;

class CMyData8 {
private:
	int m_nData = 0;
public:
	CMyData8(int nParam) : m_nData(nParam) {}
	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }\
	friend void PrintData(const CMyData8&);
};
void PrintData(const CMyData8& rData)
{
	//접근 제어 지시자의 영향 없이 직접 접근 가능
	cout << "PrintData(): " << rData.m_nData << endl;
}

class CNode {
	friend class CMyList;
private:
	char m_szName[32];
	CNode* pNext = nullptr;
public:
	explicit CNode(const char* pszParam) {
		strcpy_s(m_szName, sizeof(m_szName), pszParam);
	}
};

class CMyList {
private:
	CNode m_HeadNode;
public:
	CMyList() : m_HeadNode("DummyHead") {}
	~CMyList() {
		//리스트에 담긴 데이터를 모두 출력하고 삭제
		CNode* pNode = m_HeadNode.pNext;
		CNode* pDelete = nullptr;
		while (pNode) {
			pDelete = pNode;
			pNode = pNode->pNext;
			cout << pDelete->m_szName << endl;
			delete pDelete;
		}
		m_HeadNode.pNext = nullptr;
	}
	void AddNewNode(const char* pszParam) {
		CNode* pNode = new CNode(pszParam);
		pNode->pNext = m_HeadNode.pNext; //맨 뒤에 끼우니까, 원래 놈이 가리키던걸, 새로운 놈이 가리키게 하고,
		m_HeadNode.pNext = pNode;//기존 애는 새로 들어온 애를 다음 사람으로 가리킨다.
	}

	void Print() {
		CNode* pNode = m_HeadNode.pNext;
		while (pNode) {
			cout << pNode->m_szName << endl;
			pNode = pNode->pNext;
		}
	}
};

class CMyUI {
private:
	CMyList m_list; //UI 클래스 내부에 자료구조를 포함시킨다.
	CMyList& m_list2; //aggregation 관계 - 내부에 자료구조에 대한 참조만 있고, 실제로는 따로 존재함.
public:
	//참조 변수는 반드시 생성자 초기화 목록으로 초기화해아함.
	CMyUI(CMyList&rList):m_list2(rList){}
	//메뉴 출력 및 사용자 입력 확인
	int PrintMenu() {
		system("cls");
		cout << "[1]add\t" << "[2]Print\t" << "[0]Exit\t" << endl;
		cout.flush();
		int nInput = 0;
		cin >> nInput;
		return nInput;
	}
	//지속적으로 메뉴를 출력하는 메인 이벤트 반복문
	void Run() {
		char szName[32];
		int nInput = 0;
		int nCount = 0;
		while ((nInput = PrintMenu()) > 0) {
			switch (nInput) {
			case 1:
				cout << "이름 ";
				cout.flush();
				cin >> szName;
				m_list.AddNewNode(szName);
				nCount++;
				break;
			case 2:
				cout << "현재까지 저장된 내용입니다.\n";
				m_list.Print();
				Sleep(500*nCount);
				break;
			}
		}
	}
};
int main8() {
	cout << "====8.1 friend====" << endl;
	cout << "-----8.1.1 friend 함수-----" << endl;
	//friend 키워드 - 접근 제어 지시자(public, protected, private)의 영향을 받지 않음.
	//friend 함수는 private 멤버 변수에 "멤버 접근 연산자를 통한 직접 접근이 허용"된다.
	CMyData8 a(5);
	PrintData(a);
	//따로 떨어진 객체라고 하더라도 관련이 깊다면 연결시켜주기 위해 friend 키워드를 사용할 수 있음.
	//응집성 - 한 덩어리로 만든 C 기반 프로그램을 C++로 옮길때 friend 키워드를 사용할 수 있음.
	cout << endl;
	cout << "-----8.1.3 friend 클래스-----" << endl;
	//말 그대로 접근 제어 지시자의 영향을 받지 않아, 모든 메서드에 접근이 허용되는 클래스.
	//주로 자료와 그 자료를 관리하는 클래스 사이에 쓰인다. 대표적으로 Node와 Linked List간의 관계.
	//CMyList list;
	//list.AddNewNode("철수");
	//list.AddNewNode("영희");
	//list.AddNewNode("길동");
	cout << endl;

	cout << "====8.2 집합 관계====" << endl;
	//집합관계 - 여러 클래스 인스턴스들이 모여 하나를 이루는 관계
	cout << "-----8.2.1 composition 관계-----" << endl;
	//Composition관계 
	//자동차와 엔진/핸들/변속기 간의 관계라고 생각하면 되며, 자동차 인스턴스가 소멸될경우 엮여있는 다른 관계도 모두 소멸함.
	//모여서 뗄 수 없는 한 덩어리를 이룬다.
	//Aggregation관계
	//컴퓨터와 모니터/본체/키보드 간의 관계라고 생각하면 되며, 모두 모여 하나의 시스템을 이루지만, 각각 개별적으로 사용도 가능함.
	//각자 독립적인 것들이 모여서 만들어진 분리 가능 집합체.
	//CMyUI ui;
	//ui.Run();
	//중요한건 CMyUI가 생길때 멤버 변수로 있는 CMyList도 같이 생성되며, 소멸할때도 같이 소멸한다는 것
	//전형적인 Composition 관계.
	//main()함수가 간단해짐 -> 객체 지향 프로그래밍의 장점.
	//만약 멤버 변수가 포인터나 참조였다면 Composition이 아니라 Aggregation관계가 됨.
	//UI가 사라진다고 해도 List는 따로 남아있기 때문.
	cout << "-----8.2.2 aggregation 관계-----" << endl;
	CMyList list;
	CMyUI ui(list);
	ui.Run();
	//aggregation 관계로 적을 경우, 자료 구조 객체가 따로 존재함.
	//설계를 할때는 자료구조와 사용자 인터페이스는 따로 존재하는 것이 좋음.
	//프로그램의 제어 시스템, 사용자 인터페이스, 원본 데이터는 서로 분리되는 것이 원칙임.
	// UI, DATA, CTRL은 서로 분리되어 있어야함.
	return 0;
}


