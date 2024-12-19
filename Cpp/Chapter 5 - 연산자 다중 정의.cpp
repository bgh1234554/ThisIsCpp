#include <iostream>

using namespace std;

class CMyData5 {
private:
	int m_nData = 0;
public:
	//��ȯ ������
	CMyData5(int nparam) :m_nData(nparam) {
		cout << "CMyData5(int)" << endl;
	}
	//���� ������
	CMyData5(const CMyData5& rhs):m_nData(rhs.m_nData) {
		cout << "CMyData5(const CMyData&)" << endl;
	}
	//�̵� ������
	CMyData5(const CMyData5&& rhs) :m_nData(rhs.m_nData) {
		cout << "CMyData5(const CMyData&&)" << endl;
	}
	//�� ��ȯ
	operator int() {return m_nData;}
	//���� ����
	CMyData5 operator+(const CMyData5& rhs) {
		cout << "operator+" << endl;
		CMyData5 result(0);
		result.m_nData = this->m_nData + rhs.m_nData;
		return result;
	}
	//�ܼ� ���� ����
	CMyData5& operator=(const CMyData5& rhs) {
		cout << "operator=" << endl;
		m_nData = rhs.m_nData;
		return *this;
	}
	//5.6 ���� ���� ������
	//���� ���� ������
	int operator++() {
		cout << "operator++()" << endl;
		return ++m_nData; //�׳� ��� ���� �������Ѽ� ����ϸ� ��.
	}
	//���� ���� ������
	int operator++(int) {
		cout << "operator++(int)" << endl;
		//������ ���� ��ȯ�ϰ�, �� �ڿ� 1�� Ŀ���� �Ѵ�.
		int nData = m_nData; //���� �� ���
		m_nData++; //1 ������Ŵ
		return nData; //������ ���� �����ش�.
	}
};

class CMyData5ptr {
private:
	int* m_pnData = nullptr; //�����͸� �ʱ�ȭ �Ҷ� ���� NULL ������. C++11�� ���� �߰���.
public:
	explicit CMyData5ptr(int nParam) {
		cout << "CMyData5ptr(int)" << endl;
		m_pnData = new int(nParam); //new�� �ʱ�ȭ �ؾ���.
	}
	~CMyData5ptr() { delete m_pnData; }
	//���� ������
	CMyData5ptr(const CMyData5ptr& rhs) {
		cout << "CMyData5ptr(const CMyData5tpr &)" << endl;
	}
	operator int() { return *m_pnData; }
	//���� ������ ���� ����
	CMyData5ptr operator+(const CMyData5ptr& rhs) {
		cout << "operator+" << endl;
		return CMyData5ptr(*this->m_pnData + *rhs.m_pnData);
	}
	//�ܼ� ���� ������ ���� ����
	CMyData5ptr& operator=(const CMyData5ptr& rhs) {
		cout << "operator=" << endl;
		if (this == &rhs) { return *this; } //a=a�� ������ ����� �� �� if���� ������, �ٷ� ����� �ִ� �޸𸮸� �����ϱ� ������ ������ ���� ����.
		delete m_pnData;
		m_pnData = new int(*rhs.m_pnData);
		return *this; //��ȯ ������ Ŭ������ ������ ����: a=b=c�� ���� ������ �������� ��, void�� ��ȯ�ϰ� �Ǹ� void�� l-value�� �������� ���� �� ���� ����.
	}
	//���� ���� ������ ���� ���� (���� ����)
	CMyData5ptr& operator+=(const CMyData5ptr& rhs) {
		int* pResult = new int(*m_pnData);
		*pResult = *pResult + *rhs.m_pnData;
		//!!�����͸� ����ϱ� ������ ���� �޸𸮸� �����ϰ� ��ü�ϴ� ������ �� �ʿ���!!
		delete m_pnData;
		m_pnData = new int(*pResult);
		return *this; //��ȯ ������ Ŭ������ ������ ����: a=b=c�� ���� ������ �������� ��, void�� ��ȯ�ϰ� �Ǹ� void�� l-value�� �������� ���� �� ���� ����.
	}
	//�̵� ���� ������ ���� ���� (���� ����)
	CMyData5ptr& operator=(CMyData5ptr&& rhs) {
		cout << "operator=(Move)" << endl;
		this->m_pnData = rhs.m_pnData; // ������ ��� ���ϰ�, �׳� �ܼ� ������ : ���� ����
		rhs.m_pnData = nullptr;
		return *this; //��ȯ ������ Ŭ������ ������ ����: a=b=c�� ���� ������ �������� ��, void�� ��ȯ�ϰ� �Ǹ� void�� l-value�� �������� ���� �� ���� ����.
	}
	//���� �����ڴ� �������� �������� ����� ��ȯ�ؾ� �Ѵ�.
	void setData(int nParam) { *m_pnData = nParam; }
};

//�޸� ������ ������ int �迭.
class CIntArray {
private:
	int* m_pnData; //�迭 �޸�
	int m_nSize; //�迭 ����� ����
public:
	CIntArray(int nSize) {
		m_nSize = nSize;
		m_pnData = new int[nSize];
		memset(m_pnData, 0, sizeof(int)*nSize); //memset(�迭, ��, �뷮(����Ʈ))
	}
	~CIntArray() { delete m_pnData; }
	int& operator[](int nIndex) {
		cout << "operator[]" << endl;
		return m_pnData[nIndex];
	}
	int operator[](int nIndex) const {
		cout << "operator[] const" << endl;
		return m_pnData[nIndex];
	}
};

void TestFunc(const CIntArray& arParam) {
	cout << "TestFunc()" << endl;
	cout << arParam[3] << endl;
}
int main5() {
	cout << "====5.1 ������ �Լ���?====" << endl;
	//�����ڸ� �̿��ϵ� ȣ���� �� �ִ� �޼���. ����� ������ �߻��ؼ� �ȵ�.
	//����� �ڵ��ʿ����� �������� Ȯ���ϱ� �� ����� �� ������, �ξ� ������.
	//����� �� �����ڸ� ���������ؼ��� �ȵ�.
	cout << "====5.2 ��� ������====" << endl;
	//operator int(), CMyData5 operator=(const CMyData &rhs), CMyData5& operator+(const CMyData &rhs)
	//�� ��ȯ, �ܼ� ����, ���� ������ ��������
	cout << "BEGIN" << endl;
	CMyData5 a(0), b(4), c(5);
	//b+c ������ �����ϸ� �ӽ� ��ü ����, �� ��ü�� a�� ���Ե�.
	a = b + c;
	cout << a << endl;
	cout << "END" << endl;
	cout << endl;

	cout << "====5.3 �ܼ� ���� ������====" << endl;
	//���� ���綧���� ���� ���ǰ� �ʿ��� ������.
	CMyData5ptr aa(0), bb(2), cc(3);
	aa = bb = cc; //����� 3��.
	cout << aa << endl;
	cout << endl;
	cout << "-----5.3.1 ���� ���� ������-----" << endl;
	//�̹� �ǽ� �������� �غ� �͵��� operator+=���� ��. �ٸ� �����͸� ����� ��� �� ��ٷο� �� ����. �ڵ� ����.
	aa.setData(50), bb.setData(20), cc.setData(33);
	aa += bb;
	aa += cc;
	cout << aa << endl;
	cout << endl;
	cout << "-----5.3.2 �̵� ���� ������-----" << endl;
	//�̸� ���� �ӽ� ��ü�� �����ϱ� ���� �̵� ���� �����ڵ� ������.
	aa.setData(0), bb.setData(3), cc.setData(4);
	aa = bb + cc; //���⼭ �̵� ���� �����ڰ� ����ȴ�.
	cout << aa << endl;
	aa = bb;
	cout << aa << endl;
	//bb+cc ������ operator+ �����ڷ� ������ �ڿ� ������ �ӽ� ��ü�� r-value ��Ƽ� �ٷ� �ܼ� ���� ������ ������ ��, �̵� ���� �����ڰ� ȣ��ȴ�.
	//�Ϲ� ���� �����ڴ� ���� ���縦, �̵� ���� �����ڴ� ���� ���縦 ������. ���� �����ڿ� �̵� ������ó��.
	cout << endl;

	cout << "====5.4 �迭 ������====" << endl;
	//�迭 �������� �Ű������� int �ϳ�. index������ ����.
	//int& operator[] (int index) -> �Ϲ����� �迭 ����. l-value, r-value ��η� ��� ����.
	//int operator[] (int index) const -> ����� ������ ���ؼ��� ȣ���� �� �ְ�, r-value�θ� ��� ����.
	CIntArray arr(5);
	for (int i=0; i < 5; i++) {
		arr[i] = i* 10;
	}
	TestFunc(arr);
	cout << endl;

	cout << "====5.5 ���� ������====" << endl;
	//���� ������ : ���, �ε� �����ڿ� �� �����ڸ� ���� ���� �����ڶ�� ��.
	//int���� ��ȯ�ϸ� ���̸� 1, �����̸� 0�� ��ȯ��.
	//�迭 ���� ���� ���� ���� ���� ���ڿ��� -> ���ô� CMystring ���Ͽ��� Ȯ���� ��.
	cout << endl;

	cout << "====5.6 ���� ���� ������====" << endl;
	//for������ ���� �� �� �ִ� ++�� --�����ڸ� ����.
	//�տ� ������ ������, �ڿ� ������ ������.
	//int operator++() : ������, int operator++(int) : ������
	CMyData5 x(10);
	cout << ++x << endl;
	cout << x++ << endl;
	cout << x << endl;
	return 0;
}