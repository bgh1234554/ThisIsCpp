#include <iostream>

using namespace std;

void ExceptTest1() {
	int nInput;
	cout << "1~10 양의 정수를 입력하세요: ";
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
		cout << "정상적으로 소멸함" << endl;
	}
};

int main10() {
	cout << "====10.1 try, throw, catch 문====" << endl;
	cout << "-----10.1.1 기본 활용 방법-----" << endl;
	//if-else가 너무 많으면 예외처리 코드가 분산되어 있어 보기 어려움.
	//int a(100), int b;
	//cout << "Input Number: ";
	//cin >> b;
	//try {
	//	//예외 검사
	//	if (b == 0) throw b; //값을 던짐
	//	else
	//		cout << a / b << endl;
	//}
	//catch (int nExp) {
	//	cout << "ERROR: Can't divide by " << b << endl;
	//}
	cout << "-----10.1.2 catch 다중화-----" << endl;
	//catch를 자료형에 따라 여러개를 만들 수 있음.
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
	//if-else문이 중첩이 가능한 것처럼, try-catch문도 당연히 가능하다.
	//어떤 형식의 예외든 받아들이는 catch문을 만들고 싶다면, catch(...)라는 구문을 사용할 수 있다.
	cout << "-----10.1.3 예외 클래스-----" << endl;
	//당연히 catch의 인수로 클래스도 받을 수 있다. 사용자 정의 예외 클래스도 만들 수 있다는 것.
	//try {
	//	int nInput = 0;
	//	cout << "양의 정수를 입력하세요: ";
	//	cin >> nInput;
	//	if (nInput < 0) {
	//		CMyException exp(10, "양의 정수를 입력해야 합니다");
	//		throw exp;
	//	}
	//}
	//catch(CMyException &exp){
	//	cout << "ERROR CODE [" << exp.GetErrorCode() << "] " << exp.GetMessage() << endl;
	//}
	cout << endl;

	cout << "====10.2 스택 풀기(stack unwinding)====" << endl;
	//호출 스택에 함수 A(), B(), C()가 호출됐을때, C함수에서 예외가 발생한 경우, A가 호출되기 전으로 되돌려야 하는 경우가 있다.
	//문제는 C를 호출한 A와 B가 모두 반환되도록 작성해야 한다는 것인데, 구조화된 예외 처리를 이용하면 그럴 필요가 없이 알아서 해준다.
	try {
		TestFunc3();
	}
	catch (...) {
		cout << "Exception happend!" << endl;
	}
	//스택 풀기를 하려면 예외 처리 코드가 복잡해질 수 있기 때문에, 다음과 같은 코드를 잘 기억해두어야함.
	cout << endl;

	cout << "====10.3 메모리 예외 처리====" << endl;
	//너무 큰 메모리를 할당 시 에러가 발생하는데 이때 메모리를 할당해주는 함수나 연산자는 NULL을 반환한다.
	//==NULL과 같은 연산을 통해 메모리를 비교할 수도 있지만, 구조화된 예외처리를 이용할 수 있다.
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
	//생성자 함수는 반환형식이 없기 때문에 인스턴스를 선언하는 곳에서 오류를 확인하기 힘들다. 
	// 이때 catch(bad_alloc &exp)을 사용하면 자연스럽게 코드의 흐름이 catch문으로 넘어온다.
	//bad_alloc - exception 클래스의 파생 클래스. .what() 메서드를 통해 이유를 알 수 있다.
	return 0;
}