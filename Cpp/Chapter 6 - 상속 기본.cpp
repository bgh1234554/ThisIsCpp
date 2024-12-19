#include <iostream>

using namespace std;

//초기 개발자의 클래스
class CMyData6 {
private:
	int m_nData = 0;
protected: //파생 클래스에서만 접근 가능
	void PrintData() { cout << "CMyData::PrintData()" << endl; }
public:
	//생성자 다중 정의
	CMyData6() { cout << "CMyData6()" << endl; }
	CMyData6(int nParam) :m_nData(nParam) { cout << "CMyData6(int)" << endl; }
	CMyData6(double dParam) :m_nData(dParam) { cout << "CMyData6(double)" << endl; }
	//게터, 세터 메서드
	int GetData() const { return m_nData; }
	void SetData(int nparam) { m_nData = nparam; }
};

//후기 개발자의 클래스
//상속의 기본적인 문법 : 접근제어 지시자 부모클래스 이름.
class CMyData6Ex : public CMyData6 {
public:
	using CMyData6::CMyData6; //생성자 상속
	//CMyData6Ex() { cout << "CMyData6Ex()" << endl; }
	////기본 클래스의 3가지 생성자 중 int를 선택함
	//CMyData6Ex(int nParam) :CMyData6(nParam) { cout << "CMyData6Ex(int)" << endl; }
	////double 입력하면 기본 생성자 호출하기로 결정.
	//CMyData6Ex(double dParam) :CMyData6() { cout << "CMyData6Ex(double)" << endl; }
	void TestFunc() {
		CMyData6::PrintData();
		CMyData6::SetData(5);
		cout << CMyData6::GetData() << endl; //부모 클래스의 메소드에 접근
	}
	void SetData(int nparam) { //값을 보정하는 기능을 추가. 
		//기존 메서드와 새 메서드를 묶어 작동하게 하려는 의도. 상속과 재정의의 가장 보편적인 목적.
		if (nparam < 0) { CMyData6::SetData(0); } //파생 클래스에서 기본 형식의 동일한 메서드를 호출하려고 하면 소속 클래스를 명시해야함.
		if (nparam > 10) { CMyData6::SetData(10); }
	}
};

class CMyDataA {
protected:
	char* m_pszData;
public:
	CMyDataA() {
		cout << "CMyDataA()" << endl;
		m_pszData = new char[32];
	}
	~CMyDataA() {
		cout << "~CMyDataA()" << endl;
		delete m_pszData;
	}
};

class CMyDataB: public CMyDataA {
public:
	CMyDataB() {
		cout << "CMyDataB()" << endl;
	}
	~CMyDataB() {
		cout << "~CMyDataB()" << endl;
	}
};

class CMyDataC : public CMyDataB {
public:
	CMyDataC() {
		cout << "CMyDataC()" << endl;
	}
	~CMyDataC() {
		cout << "~CMyDataC()" << endl;
		//delete m_pszData; //파생 클래스에서 부모 클래스 멤버 메모리를 해제함 -> 오류 발생!!
	}
};

int main6() {
	cout << "====6.1 상속이란?====" << endl;
	cout << "-----6.1.1 기본 문법-----" << endl;
	//파생 클래스의 인스턴스가 생성될 때 기본 클래스의 생성자도 호출된다.
	//파생 클래스는 기본 클래스의 멤버에 접근할 수 있다. 단, private 접근 제어 지시자로 선언된 멤버에 대해서는 안됨.
	//파생 클래스의 인스턴스를 통해 기본 클래스 메서드를 호출할 수 있다.
	CMyData6Ex data;
	//기본 클래스 접근
	data.SetData(10);
	cout << data.GetData() << endl;
	//파생 클래스 접근
	data.TestFunc();
	//파생 클래스의 생성자가 먼저 호출되지만, 생성되기 전에 부모 클래스의 생성자를 호출하고 실행한 뒤 반환한다.
	cout << endl;

	cout << "====6.2 메서드 재정의====" << endl;
	cout << "-----6.2.1 기본 문법 및 특징-----" << endl;
	//재정의(override) - 매서드를 재정의하면 기존의 것이 무시됨. 기존의 것도 공존하지만, 별다른 말이 없을 경우 새로운 것이 대체함.
	CMyData6 a;
	a.SetData(-10);
	cout << a.GetData() << endl;
	CMyData6Ex b;
	b.SetData(15);
	cout << b.GetData() << endl;
	b.CMyData6::SetData(-11); //명시적 호출을 통해 부모 클래스의 메서드를 사용 가능. 단, public인 경우에만.
	cout << endl;
	cout << "-----6.2.2 참조 형식과 실 형식-----" << endl;
	CMyData6Ex c;
	CMyData6& rData = c; //파생형식을 기본 형식으로 참조하는 것은 매우 자연스러운 일. 파생 형식도 기본 형식의 한 종류니까.
	rData.SetData(15); // c - 실제 형식, rData - 참조 형식
	cout << rData.GetData() << endl; //실 형식과 참조 형식이 다른 경우에는 참조 형식의 메서드로 호출됨.
	//참조 형식 - 포인터 버전
	CMyData6* pData = new CMyData6Ex;
	pData->SetData(15);
	delete pData;//CMyData::SetData가 호출되며, 사실 이 코드는 메모리 누수 문제가 있으나 추후에 다룰 예정임.\
	//CMyData6Ex 클래스가 호출되지 않기 때문.
	cout << endl;

	cout << "====6.3 상속에서의 생성자와 소멸자====" << endl;
	cout << "-----6.3.1 호출 순서-----" << endl;
	//C가 B를 상속받았고, B는 A의 상속클래스라고 할 때,
	//가장 먼저 호출되는 생성자는 C-B-A순이지만, 실행되는 순은 A-B-C이다.
	//파생 클래스가 기본 클래스의 생성자를 선택하고 호출한다.
	//생성자가 다중 정의되어있어도 하나만 선택하고 호출한다.
	cout << "BEGIN" << endl;
	CMyDataC data2;
	cout << "END" << endl;
	//파생 클래스는 부모 클래스의 멤버 변수에 "직접 쓰기" 연산을 하지 않는 것이 정답이다.
	//파생 클래스 생성자에서 부모 클래스 멤버 변수를 초기화 하지 않는다.
	//생성자와 소멸자는 객체 자신의 초기화 및 해제만 생각하는 것이 옳다.
	cout << endl;
	cout << "-----6.3.2 생성자 선택-----" << endl;
	//파생 클래스의 생성자는 자신이 호출된 후 기본 클래스의 생성자 중 어떤 것이 호출될지 선택할 수 있음.
	//여기서 선택이란 생성자 초기화 목록에 상위 클래스 생성자를 호출하듯이 기술할 수 있다는 거임.
	CMyData6Ex aa;
	CMyData6Ex bb(5);
	CMyData6Ex cc(3.14);
	//생성자 상속 - 파생 클래스를 만들 때, 다중 정의된 상위 클래스의 메서드를 그대로 가져오는 문법.
	//using CMyData::CMyData; 와 같은 방식으로 가능. C++11에 추가되었으며, VS2015부터 가능함.
	return 0;
}