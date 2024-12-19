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
	//���� ���� �������� ���� ���� ���� ���� ����
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
		//����Ʈ�� ��� �����͸� ��� ����ϰ� ����
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
		pNode->pNext = m_HeadNode.pNext; //�� �ڿ� ����ϱ�, ���� ���� ����Ű����, ���ο� ���� ����Ű�� �ϰ�,
		m_HeadNode.pNext = pNode;//���� �ִ� ���� ���� �ָ� ���� ������� ����Ų��.
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
	CMyList m_list; //UI Ŭ���� ���ο� �ڷᱸ���� ���Խ�Ų��.
	CMyList& m_list2; //aggregation ���� - ���ο� �ڷᱸ���� ���� ������ �ְ�, �����δ� ���� ������.
public:
	//���� ������ �ݵ�� ������ �ʱ�ȭ ������� �ʱ�ȭ�ؾ���.
	CMyUI(CMyList&rList):m_list2(rList){}
	//�޴� ��� �� ����� �Է� Ȯ��
	int PrintMenu() {
		system("cls");
		cout << "[1]add\t" << "[2]Print\t" << "[0]Exit\t" << endl;
		cout.flush();
		int nInput = 0;
		cin >> nInput;
		return nInput;
	}
	//���������� �޴��� ����ϴ� ���� �̺�Ʈ �ݺ���
	void Run() {
		char szName[32];
		int nInput = 0;
		int nCount = 0;
		while ((nInput = PrintMenu()) > 0) {
			switch (nInput) {
			case 1:
				cout << "�̸� ";
				cout.flush();
				cin >> szName;
				m_list.AddNewNode(szName);
				nCount++;
				break;
			case 2:
				cout << "������� ����� �����Դϴ�.\n";
				m_list.Print();
				Sleep(500*nCount);
				break;
			}
		}
	}
};
int main8() {
	cout << "====8.1 friend====" << endl;
	cout << "-----8.1.1 friend �Լ�-----" << endl;
	//friend Ű���� - ���� ���� ������(public, protected, private)�� ������ ���� ����.
	//friend �Լ��� private ��� ������ "��� ���� �����ڸ� ���� ���� ������ ���"�ȴ�.
	CMyData8 a(5);
	PrintData(a);
	//���� ������ ��ü��� �ϴ��� ������ ��ٸ� ��������ֱ� ���� friend Ű���带 ����� �� ����.
	//������ - �� ����� ���� C ��� ���α׷��� C++�� �ű涧 friend Ű���带 ����� �� ����.
	cout << endl;
	cout << "-----8.1.3 friend Ŭ����-----" << endl;
	//�� �״�� ���� ���� �������� ������ ���� �ʾ�, ��� �޼��忡 ������ ���Ǵ� Ŭ����.
	//�ַ� �ڷ�� �� �ڷḦ �����ϴ� Ŭ���� ���̿� ���δ�. ��ǥ������ Node�� Linked List���� ����.
	//CMyList list;
	//list.AddNewNode("ö��");
	//list.AddNewNode("����");
	//list.AddNewNode("�浿");
	cout << endl;

	cout << "====8.2 ���� ����====" << endl;
	//���հ��� - ���� Ŭ���� �ν��Ͻ����� �� �ϳ��� �̷�� ����
	cout << "-----8.2.1 composition ����-----" << endl;
	//Composition���� 
	//�ڵ����� ����/�ڵ�/���ӱ� ���� ������ �����ϸ� �Ǹ�, �ڵ��� �ν��Ͻ��� �Ҹ�ɰ�� �����ִ� �ٸ� ���赵 ��� �Ҹ���.
	//�𿩼� �� �� ���� �� ����� �̷��.
	//Aggregation����
	//��ǻ�Ϳ� �����/��ü/Ű���� ���� ������ �����ϸ� �Ǹ�, ��� �� �ϳ��� �ý����� �̷�����, ���� ���������� ��뵵 ������.
	//���� �������� �͵��� �𿩼� ������� �и� ���� ����ü.
	//CMyUI ui;
	//ui.Run();
	//�߿��Ѱ� CMyUI�� ���涧 ��� ������ �ִ� CMyList�� ���� �����Ǹ�, �Ҹ��Ҷ��� ���� �Ҹ��Ѵٴ� ��
	//�������� Composition ����.
	//main()�Լ��� �������� -> ��ü ���� ���α׷����� ����.
	//���� ��� ������ �����ͳ� �������ٸ� Composition�� �ƴ϶� Aggregation���谡 ��.
	//UI�� ������ٰ� �ص� List�� ���� �����ֱ� ����.
	cout << "-----8.2.2 aggregation ����-----" << endl;
	CMyList list;
	CMyUI ui(list);
	ui.Run();
	//aggregation ����� ���� ���, �ڷ� ���� ��ü�� ���� ������.
	//���踦 �Ҷ��� �ڷᱸ���� ����� �������̽��� ���� �����ϴ� ���� ����.
	//���α׷��� ���� �ý���, ����� �������̽�, ���� �����ʹ� ���� �и��Ǵ� ���� ��Ģ��.
	// UI, DATA, CTRL�� ���� �и��Ǿ� �־����.
	return 0;
}


