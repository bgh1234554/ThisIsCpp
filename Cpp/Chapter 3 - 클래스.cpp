#include <string>
#include <iostream>

using namespace std;

//C++ ��Ÿ�� Ŭ���� ����� ��
class USERDATA {
public:
	int age = 20;
	char name[32] = "ȫ�浿"; //�̰� ���� ���� �����.
	//int age = 20;
	//char name[32] = "ȫ�浿"; //�̷������� �ʱ�ȭ �� �� ����.
	//USERDATA() {
	//	age = 20;
	//	strcpy_s(name, 32, "ȫ�浿"); �̰� ������ �� user���� ������ ���°���?
	//}
	void Print(void) {
		printf("%d, %s\n", age, name);
	}
};

class CTest {
public:
	CTest() {
		cout << "CTest ������ �Լ�" << endl;
		nData = 10;
	}
	//CTest() :nData(10) {}; //������ ����� ���ؼ� �ʱ�ȭ �ϴ� ���.
	int nData;
	void printdata() {
		cout << nData << endl;
	}
};
//Ŭ���� ���ʿ��� �Լ� ���� �ϰ� ���Ǵ� Ŭ���� �ٱ����� �ϴ� ����� �ִ�.
//void CTest::printdata(void) {
//	cout << nData << endl;
//}

//private, protected, public�� ���� Ű����� ����ڰ� Ư�� ��ҿ� �������� ���ϰ� ���Ƶ� �� ����.
class MyData {
	int data;
public:
	int GetData(void) { return data; }
	void SetData(int m) { data = m; } //���Ϳ� ���͸� ���ؼ� ������� ���� ������ �� ����. ���� ���� �Ҷ� 100�� �ѱ� �� ���� ��ó��.
	//private ������ ������ �Լ��� ����� �Ǽ��� ���� �ʾƾ� ��.
	MyData() {
		data = 245;
		cout << "Test Class generated" << endl;
	}
	~MyData() { //�Ҹ��� - Ŭ������ �Ҹ��Ҷ� ��µǴ� ����. ���� ������ ������ ������ �������, ���α׷��� ������ �������...
		cout << "Test Class deleted" << endl;
	}
};
//C++������ Ŭ���� �����ڰ� �����Լ� �ۿ� ������ �����Լ����� ���� ȣ���.
//�����ڴ� �������ǰ� ������. �Ҹ��ڴ� �ȵ�.

//MyData s; ���������� ����� class�� main �Լ����� ���� ������.

//�����ڵ� Ŭ������ ��� ������ ������ �� ����.
class RefTest {
	int& ndata;
public:
	RefTest(int& nParam) :ndata(nParam) {}; //�����ڸ� �����ڿ��� �ʱ�ȭ �Ҷ��� ������ ������ �ʱ�ȭ ����� �̿��� �ʱ�ȭ�ؾ���.
	int getdata(void) { return ndata; }
};

//������ ���� ����
class CMyData {
	int mdata;
public:
	CMyData():mdata(-1) {};
	CMyData(int n) { mdata = n; }
	CMyData(int x, int y) { mdata = x + y; }
	void SetData(int m) { mdata = m; }
	int GetData(void) const { return mdata; } //����� �޼��� - const Ű���带 ����ϸ�, ��� ������ �б�� ���������� ����� ����ϰ� ���� ���� �� ���.
	//�׷��� �� �޼ҵ� �ȿ��� mdata�� ���� ������ �� ����. ���ͷε� �ȵ�.
	//�޼ҵ嵵 �������ǰ� ������.
	//void SetData(double m) { mdata = 0; }//int ����� double ���� ���� �������ؼ� ���ϰ� ���� ���.
	//�ٸ� �̷��� �ϱ⺸�ٴ� double�� �Է��ϴ� ��츦 ������ ������ �� ����.
	void SetData(double m) = delete;
	//�̷��� double ���·� SetData�� ȣ���� ��� ������ ������ ��.
};

//������ ���� ���Ǵ� ���� ���� ���鿡�� ������ �ֱ� ������, ������ ������ �ٸ� �����ڸ� �θ� �� �ִ� ����� �߰���.
//������ �ʱ�ȭ ��Ͽ��� ��� ������� ����.
class MyPoint {
	int mx=0;
	int my=0;
public:
	MyPoint(int x) {
		if (x >= 100) { mx = 100; }
		else { mx = x; }
	}
	MyPoint(int x, int y): MyPoint(x) { //x������ �̹� ���������ϱ�.
		if (y >= 100) { my = 100; }
		else { my = y; }
	}
	void print() {
		cout << "x = " << mx << endl;
		cout << "y = " << my << endl;
	}
};

//����� ����Ʈ ������.
class DefaultTest {
int m_nData = 5;
int mutable nData = 10;
public:
	DefaultTest(void) = default; //����� ����Ʈ ������. ������ ���Ǹ� ������� �ʾƵ� ����� ���ǰ� �и���.
	//DefaultTest(void) = delete; ����Ʈ �����ڸ� ���� �� ����� �� ����.
	int GetData() const {
		nData = 20;
		return m_nData, nData; //mutable Ű���带 ����� ������ ������ ��� �޼ҵ� �ȿ����� ���Ⱑ ������.
	}
};

//const_cast<�ڷ���>(���) ����
void TestFunc(const int& param) {
	//����� ������ ����������, const_cast<�ڷ���>(���) ������ ���ؼ� ������ ���� �� �� �ִ�. ������ �����ؾ��� ��쿡 ����Ѵ�.
	//���� ����ϴ� ���� �ٶ������� �ʴ�. ����� �ݵ�� ��ȣ�� ����� �Ѵ�!
	int& nNewParam = const_cast<int&>(param);
	nNewParam = 20;
}

//static ���� ���ؼ� �ν��Ͻ��� �������� �ʰ� Ŭ������ �μ��� ���� ȣ���� �� ����.
//��ü���� ���α׷��ֿ����� ���������� ���.
class StaticTest {
	int mData;
	static int mCount; //static ���� ����
public:
	StaticTest(int nparam) :mData(nparam) { mCount++; }
	int GetData() const { return mData; }
	void ResetCount() { mCount = 0; }
	static int GetCount() { return mCount; } //static �޼ҵ�. mCount�� static int�ϱ�.
	//���� ����� ��ǻ� �����Լ�, ���������� ���� ������ this �����͸� ����� �� ����.
};
int StaticTest::mCount = 0; //static ���� ���� (�ۿ��� �ؾ���)

//57��° �ٿ� ����.
int main3() {
	USERDATA user = { 19, "ö��"}; //������ ���� �ʱ�ȭ �ϴ� ��. C ����ü ��Ÿ��.
	user.Print();
	USERDATA u;
	u.Print();

	CTest t;
	t.printdata();
	cout << "start" << endl;

	//Ŭ������ �翬�� new �����ڿ� delete �����ڷ� �������� ���� ����.
	MyData* pnew = new MyData;
	MyData x;
	delete pnew; //�̶� �Ҹ��� ������ ����.
	cout << "end" << endl;

	int a = 10;
	RefTest ref(a);
	cout << ref.getdata() << endl;
	a = 20;
	cout << ref.getdata() << endl; //�����ڵ� �ᱹ���� �����ͱ� ������ ������ �ٲ�����ϱ� Ŭ���� �� ������ ����� ���� �ٲ�.

	CMyData first;
	CMyData b(3);
	CMyData c(4, 5);
	cout << first.GetData() << endl;
	cout << b.GetData() << endl;
	cout << c.GetData() << endl;

	MyPoint start(102);
	start.print();
	MyPoint end(52, 200);
	end.print();

	int nData = 10;
	TestFunc(nData);
	cout << nData << endl;

	//static test
	StaticTest d(10);
	StaticTest e(20);
	cout << StaticTest::GetCount() << endl;
	e.ResetCount();
	cout << StaticTest::GetCount() << endl;
	//��ü ���� ���α׷��ֿ��� ���������� �Լ��� �����ϸ� ��ü����� ������� �ڵ�� ������ �� �ֱ� ������ ���� ����� ����ϴ� ���� ����.
	return 0;
}
//�����Լ��� �� ���� �ڿ� MyData Ŭ���� 2���� �����.