#include <iostream>

using namespace std;

void ExceptTest1() {
	int nInput;
	cout << "1~10 ���� ������ �Է��ϼ���: ";
	cin >> nInput;
	if (nInput < 1 || nInput>10) throw nInput;
}

void ExceptTest2() {
	char ch;
	cout << "Menu: [A]dd\t[D]elete\t[E]xit:";
	cin >> ch;
	if (ch != 'A' && ch != 'D' && ch != 'E') throw ch;
}

class CMyException {
private:
	int m_nErrorcode;
	char m_szMsg[128];
public:
	CMyException(int nCode, const char* pszMsg) {
		m_nErrorcode = nCode;
		strcpy_s(m_szMsg, sizeof(m_szMsg), pszMsg);
	}
	int GetErrorCode() const { return m_nErrorcode; }
	const char* GetMessage() const { return m_szMsg; }
};

void TestFunc1() {
	cout << "TestFunc1 start" << endl;
	throw 0;
	cout << "TestFunc1 end" << endl;
}

void TestFunc2() {
	cout << "TestFunc2 start" << endl;
	TestFunc1();
	cout << "TestFunc2 end" << endl;
}

void TestFunc3() {
	cout << "TestFunc3 start" << endl;
	TestFunc2();
	cout << "TestFunc3 end" << endl;
}

class CTest10 {
private:
	char* m_pszData;
public:
	CTest10(int nSize) {
		m_pszData = new char[nSize];
	}
	~CTest10() {
		delete[] m_pszData;
		cout << "���������� �Ҹ���" << endl;
	}
};

int main10() {
	cout << "====10.1 try, throw, catch ��====" << endl;
	cout << "-----10.1.1 �⺻ Ȱ�� ���-----" << endl;
	//if-else�� �ʹ� ������ ����ó�� �ڵ尡 �л�Ǿ� �־� ���� �����.
	//int a(100), int b;
	//cout << "Input Number: ";
	//cin >> b;
	//try {
	//	//���� �˻�
	//	if (b == 0) throw b; //���� ����
	//	else
	//		cout << a / b << endl;
	//}
	//catch (int nExp) {
	//	cout << "ERROR: Can't divide by " << b << endl;
	//}
	cout << "-----10.1.2 catch ����ȭ-----" << endl;
	//catch�� �ڷ����� ���� �������� ���� �� ����.
	//try {
	//	ExceptTest1();
	//	ExceptTest2();
	//}
	//catch(int nExp){
	//	cout << nExp << " is out of range";
	//}
	//catch (char ch) {
	//	cout << ch << " is a wrong input";
	//}
	//if-else���� ��ø�� ������ ��ó��, try-catch���� �翬�� �����ϴ�.
	//� ������ ���ܵ� �޾Ƶ��̴� catch���� ����� �ʹٸ�, catch(...)��� ������ ����� �� �ִ�.
	cout << "-----10.1.3 ���� Ŭ����-----" << endl;
	//�翬�� catch�� �μ��� Ŭ������ ���� �� �ִ�. ����� ���� ���� Ŭ������ ���� �� �ִٴ� ��.
	//try {
	//	int nInput = 0;
	//	cout << "���� ������ �Է��ϼ���: ";
	//	cin >> nInput;
	//	if (nInput < 0) {
	//		CMyException exp(10, "���� ������ �Է��ؾ� �մϴ�");
	//		throw exp;
	//	}
	//}
	//catch(CMyException &exp){
	//	cout << "ERROR CODE [" << exp.GetErrorCode() << "] " << exp.GetMessage() << endl;
	//}
	cout << endl;

	cout << "====10.2 ���� Ǯ��(stack unwinding)====" << endl;
	//ȣ�� ���ÿ� �Լ� A(), B(), C()�� ȣ�������, C�Լ����� ���ܰ� �߻��� ���, A�� ȣ��Ǳ� ������ �ǵ����� �ϴ� ��찡 �ִ�.
	//������ C�� ȣ���� A�� B�� ��� ��ȯ�ǵ��� �ۼ��ؾ� �Ѵٴ� ���ε�, ����ȭ�� ���� ó���� �̿��ϸ� �׷� �ʿ䰡 ���� �˾Ƽ� ���ش�.
	try {
		TestFunc3();
	}
	catch (...) {
		cout << "Exception happend!" << endl;
	}
	//���� Ǯ�⸦ �Ϸ��� ���� ó�� �ڵ尡 �������� �� �ֱ� ������, ������ ���� �ڵ带 �� ����صξ����.
	cout << endl;

	cout << "====10.3 �޸� ���� ó��====" << endl;
	//�ʹ� ū �޸𸮸� �Ҵ� �� ������ �߻��ϴµ� �̶� �޸𸮸� �Ҵ����ִ� �Լ��� �����ڴ� NULL�� ��ȯ�Ѵ�.
	//==NULL�� ���� ������ ���� �޸𸮸� ���� ���� ������, ����ȭ�� ����ó���� �̿��� �� �ִ�.
	try {
		int nSize;
		cout << "Input Size ";
		cin >> nSize;
		CTest10 test(nSize);
	}
	catch (bad_alloc& exp) {
		cout << exp.what() << endl;
		cout << "ERROR: CTest10()" << endl;
	}
	//������ �Լ��� ��ȯ������ ���� ������ �ν��Ͻ��� �����ϴ� ������ ������ Ȯ���ϱ� �����. 
	// �̶� catch(bad_alloc &exp)�� ����ϸ� �ڿ������� �ڵ��� �帧�� catch������ �Ѿ�´�.
	//bad_alloc - exception Ŭ������ �Ļ� Ŭ����. .what() �޼��带 ���� ������ �� �� �ִ�.
	return 0;
}