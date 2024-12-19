#include <iostream>

using namespace std;

class CMyData7 {
protected:
	int m_nData = 10;
public:
	virtual ~CMyData7(){
	}
	virtual void PrintData() {
		cout << "CMyData7: " << m_nData << endl;
	}
	void TestFunc() {
		cout << "***TestFunc()***" << endl;
		PrintData(); //PrintData가 virtual 메서드이기 때문에 과거의 코드가 미래의 코드를 부르는 형식이 된다!
		//!!가상 함수는 재정의된 미래의 코드를 호출한다!!
		cout << "****************" << endl;
	}
	void SetData(int nparam) { m_nData = nparam; }
	int GetData() const { return m_nData; }
};

class CMyData7Ex :public CMyData7 {
public:
	//가상함수 멤버 재정의: 기존 정의는 override되어 무시됨.
	virtual void PrintData() {
		cout << "CMyData7Ex: " << m_nData*2 << endl;
	}
	void SetData(int nparam) {
		if (nparam > 10) nparam = 10;
		CMyData7::SetData(nparam);
	}
	void PrintData2() {//7.4에 쓸 용도
		cout << "CMyData7Ex: " << GetData() << endl;
	}
};

class CMyDataptr {
private:
	char* m_pszData;
public:
	CMyDataptr() { m_pszData = new char[32]; }
	//소멸자를 가상 함수로 선언하기
	virtual ~CMyDataptr() {
		cout << "~CMyDataptr()" << endl;
		delete m_pszData;
	}
};

class CMyDataptrEx : public CMyDataptr {
private:
	int* m_pnData;
public:
	CMyDataptrEx() { m_pnData = new int; }
	~CMyDataptrEx() {
		cout << "~CMyDataptrEx()" << endl;
		delete m_pnData;
	}
};

class vtable {
public:
	vtable() {
		cout << "vtable()" << endl;
	}
	virtual ~vtable() {}
	virtual void TestFunc1() {}
	virtual void TestFunc2() {}
};

class vtableEx : public vtable {
public:
	vtableEx() {
		cout << "vtableEx()" << endl;
	}
	virtual ~vtableEx() {}
	virtual void TestFunc1() {}
	virtual void TestFunc2() { cout << "TestFunc2()" << endl; }
};

void bindTest1(int nParam){}
void bindTest2(int nParam){}

class CMyInterface {
public:
	CMyInterface() {
		cout << "CMyInterface()" << endl;
	}
	//선언만 있고 정의는 없는 순수가상함수.
	virtual int GetData() const = 0;
	virtual void SetData(int nparam) = 0;
};

class CMyInterfaceEx : public CMyInterface {
private:
	int m_nData = 0;
public:
	CMyInterfaceEx() {
		cout << "CMyInterfaceEx()" << endl;
	}
	//자식 클래스는 부모 순수 가상 클래스의 순수 가상 함수를 반드시 정의해야함.
	virtual int GetData() const {
		return m_nData;
	}
	virtual void SetData(int nparam) {
		m_nData = nparam;
	}
};
//초기 제작자의 코드
class CMyObject {
public:
	CMyObject(){}
	virtual ~CMyObject(){}
	virtual int GetDeviceID() = 0;//나중에 모든 파생 클래스가 이 메서드를 가질 것임을 확정할 수 있음.

protected:
	int m_nDeviceID=NULL;
};

void PrintID(CMyObject* pObj) {//어떤 장치일지는 모르지만, 제품 ID는 일관되게 출력할 수 있음. 순수 가상 클래스덕분에.
	//상속된 클래스도 다 이용할 수 있게, 일부러 CMyObject*로 매개변수를 선언함.
	//virtual 함수로 정의되어 있기 때문에 어차피 실형식을 따름.
	cout << "Device ID: " << pObj->GetDeviceID() << endl;
}

//후기 제작자의 코드
class CMyTV :public CMyObject {
public:
	CMyTV(int nID) { m_nDeviceID = nID; }
	virtual int GetDeviceID() {
		cout << "CMyTV::GetDeviceID()" << endl;
		return m_nDeviceID;
	}
};

class CMyPhone :public CMyObject {
public:
	CMyPhone(int nID) { m_nDeviceID = nID; }
	virtual int GetDeviceID() {
		cout << "CMyPhone::GetDeviceID()" << endl;
		return m_nDeviceID;
	}
};
//이렇게 어떤 기기 class를 만들든 PrintID 메서드를 실행할 수 있도록 만들 수 있음.

class COperatorTest {
protected:
	int m_nData = 0;
public:
	COperatorTest(int nParam):m_nData(nParam){}
	COperatorTest operator+(const COperatorTest& rhs) {
		return COperatorTest(m_nData + rhs.m_nData);
	}
	COperatorTest& operator=(const COperatorTest& rhs) {
		m_nData = rhs.m_nData;
		return *this;
	}
	operator int() { return m_nData; }
};

class COperatorTestEx :public COperatorTest {
public:
	COperatorTestEx(int nParam):COperatorTest(nParam){}
	//해결 방법 1.
	//COperatorTestEx operator+(const COperatorTestEx& rhs) {
	//	//형변환 사용가능
	//	return COperatorTestEx(static_cast<int>(COperatorTest::operator+(rhs)));
	//}
	//해결 방법 2
	using COperatorTest::operator+;
	using COperatorTest::operator=;
};

class CMyObject2 {
public:
	CMyObject2() {
		cout << "CMyObject()" << endl;
	}
	virtual ~CMyObject2(){}
};

class CMyImage:virtual public CMyObject2 {
protected:
	int m_nHeight;
	int m_nWidth;
public:
	CMyImage(int nHeight, int nWidth) :m_nHeight(nHeight), m_nWidth(nWidth) {
		cout << "CMyImage(int,int)" << endl;
	}
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }
	int GetSize() const { return m_nHeight* m_nWidth; }
};

class CMyShape: virtual public CMyObject2{
protected:
	int m_nType;
public:
	CMyShape(int nType) :m_nType(nType) {
		cout << "CMyShape(int)" << endl;
	}
	int GetType() const { return m_nType; }
	int GetSize() const { return 1; }
};

class CMyPicture : public CMyImage, public CMyShape {
public:
	CMyPicture() :CMyImage(10, 20), CMyShape(1) {
		cout << "CMyPicture()" << endl;
	}
};

class CMyUSB {
public:
	virtual int GetUSBVersion() = 0;
	virtual int GetTransferRate() = 0;
};

class CMySerial {
public:
	virtual int GetSerial() = 0;
	virtual int GetRate() = 0;
};

class CMyDevice : public CMyUSB, public CMySerial {
public:
	virtual int GetUSBVersion() { return 45; }
	virtual int GetTransferRate() { return 2; }
	virtual int GetSerial() { return 12312322; }
	virtual int GetRate() { return 9; }
};

int main7() {
	cout << "====7.1 가상함수====" << endl;
	cout << "-----7.1.1 기본 문법-----" << endl;
	//가상 함수: virtual 키워드 사용. 파생 형식에서 메서드를 재정의하면 과거의 정의가 완전히 무시됨.
	CMyData7Ex a;
	a.PrintData();
	CMyData7& b = a;
	b.PrintData(); //virtual 메서드라서 실 형식에 정의되어있는 PrintData 함수를 호출한다.
	a.TestFunc(); //TestFunc안에 있는 PrintData를 CMyData7Ex::PrintData()로 호출한다.
	//일반 메서드는 참조 형식을 따르고, 가상 메서드는 실 형식을 따른다.
	//파생 클래스에서 가상 함수를 재정의하지 못하게
	//virtual void PrintData() final;
	//과 같이 final 키워드를 사용해서 재정의를 방지할 수 있음.
	cout << endl;
	cout << "-----7.1.3 소멸자 가상화-----" << endl;
	CMyDataptr* pData = new CMyDataptrEx; //가능함
	delete pData; //참조 형식의 소멸자만 호출되고, 실 형식의 소멸자가 호출되지 않아 내부적인 메모리 누수 오류가 발생함.
	//간단하게 해결 - 소멸자의 가상화.
	//부모 클래스의 소멸자가 가상화되면, 자식 클래스는 가상 함수 선언을 하지 않아도 자동으로 가상화가 된다.
	cout << endl;

	cout << "====7.2 가상 함수 테이블====" << endl;
	//vtable - 함수 포인터 배열
	vtable* vp = new vtableEx;
	vp->TestFunc2();
	delete vp;
	//각 생성자에 브레이크 포인트 걸고 디버깅하면 VS2022 화면 하단에 있는 로컬에 __vfptr라는 것이 나옴.
	//가상 함수의 주소가 들어있는 배열. 가상함수로 선언된 멤버 함수들의 주소에 배열 형태로 접근할 수 있음.
	//가상 함수를 멤버로 갖는 모든 클래스는 각자 자신만의 고유한 가상함수 테이블을 갖는데, 이 테이블을 __vfptr로 가리키는 것.
	//바인딩 - 함수나 변수의 주소가 결정되는 것.
	//이른 바인딩 - 컴파일 타임에 결정되는 것.
	//늦은 바인딩 - 프로그램이 실행되는 도중에 결정되는 것. 가상함수도 이에 해당함. -> 동적 바인딩이라고도 부름.
	bindTest1(10); //디버그 후 디스어셈블리창을 켜보면 call bindTest1(주소값) 이렇게 나와있음. 이른 바인딩.
	int nInput = 0;
	//cin >> nInput;
	void(*pfTest)(int) = NULL;
	if (nInput > 10) { pfTest = bindTest1; }
	else { pfTest = bindTest2; }
	pfTest(10); //디스어셈블리창을 켜보면 call qword ptr[pfTest]로 값이 확정되어 있지 않음. 늦은 바인딩.
	cout << endl;

	cout << "====7.3 순수 가상 클래스====" << endl;
	//JAVA의 interface와 거의 동일한 것 같음.
	//순수 가상함수를 멤버로 가진 클래스
	//선언만 미리 해놓고 구현은 나중에 하는것. JAVA의 추상 메서드와 동일.
	//문법: virtual int GetData() const = 0; 뒤에 =0이 붙음.
	//CMyInterface i; //순수 가상 클래스는 인스턴스를 선언 및 정의할 수 없음.
	CMyInterfaceEx ie;
	ie.SetData(5);
	cout << ie.GetData() << endl;
	cout << endl;
	cout << "-----7.3.1 인터페이스 상속-----" << endl;
	//순수 가상 클래스를 사용하는 이유 : 다른 장치들과 상호작용할 때, 어디서든지 사용할 수 있도록 보편적인 인터페이스를 선택할 수 있음.
	//CMyObject 관련 클래스 예제 참조.
	CMyTV tv(12);
	CMyPhone phone(15);
	PrintID(&tv);
	PrintID(&phone);
	cout << endl;
	cout << "-----7.3.2 추상 자료형의 사용 예-----" << endl;
	//빠른 연산이 필요한 순간에 switch-case 문이나 다중 if문을 사용하는 것은 비효율적임.
	//여유로울때 미리 연산해두면, 빠르게 처리해야 할 때 유용함. -> 사용자 입력을 받을 때.
	//switch-case문 같은 경우에는 사용자 입력 시점에 수행하는 것이 좋음.
	// 
	cout << "AdtSample.cpp 코드 참조." << endl;
	//CalcFare()함수가 가상 함수이기 때문에 상속 받아도 실 형식의 함수가 호출됨. switch-case문을 사용하지 않고도, 효과적인 성능을 기대할 수 있음.
	//순수 가상 클래스의 경우에는 new 연산을 사용할 수 없음!
	//추상 자료형을 이용하면 경우의 수가 아무리 늘어나도, 병렬적이라 똑한은 부하 수준으로 대응이 가능함.
	cout << endl;

	cout << "====7.4 상속과 형변환====" << endl;
	//C언어에서는 강제 형변환 연산자 단 하나만 제공하지만, C++에는 매우 다양한 방법이 존재함.
	//const_cast<int> - 이미 배웠음. 상수형 포인터/참조자의 const를 없앨때 사용됨.
	int num=6;
	cout << "num: " << num << endl;
	const int& nparam = num;
	int& nNewparam = const_cast<int&>(nparam); //상수형 참조여도 이제 쓰기가 가능해짐.
	nNewparam = 7;
	cout << "num: " << num << endl;
	cout << endl;
	cout << "-----7.4.1 static_cast-----" << endl;
	//상속 관계일때 기본 형식을 부모의 형식으로 포인팅 할 수 있는데,
	//기본 형식 포인터가 가리키는 대상을 다시 파생 형식 포인터로 형변환하는 하향 변환은 상속관계에서만 가능함.
	CMyData7* ppData = new CMyData7Ex; //자식에서 부모로 묵시적으로 형변환
	CMyData7Ex* pNewData = NULL;
	ppData->SetData(15);
	pNewData = static_cast<CMyData7Ex*>(ppData); //부모 클래스에서 자식 클래스로 형변환이 가능
	pNewData->PrintData2();
	delete ppData;
	//근데 230번 줄에서 CMyData7Ex를 CMyData7로 바꿔도 static_cast 연산이 오류없이 수행됨.
	//자식 클래스가 부모 클래스 이외의 멤버 변수를 가지고 있거나, 부모 클래스의 멤버 데이터를 호출하지는 않고 있기 때문.
	cout << endl;
	cout << "-----7.4.2 dynamic_cast-----" << endl;
	//동적으로 생성된 객체를 가리키는 포인터가 기본 형식일 경우, 구체적으로 어떤 인스턴스인지 확인할때 사용함.
	//다만 성능저하의 원인이 되기 때문에 코드가 잘못 진행되고 있다는 신호라고 볼 수 있음.
	//dynamic_cast는 형변환에 실패하면 NULL을 반환하는데, 이를 통해 NULL인지 아닌지 조건문으로 확인하면서 바른 변환인지 아닌지 확인할 수 있음.
	//이와 같은 방법을 RTTI라고 함.
	//다만, 대부분의 경우에 switch-case문과 RTTI는 가상 함수와 추상 자료형을 사용하는 방법으로 전환할 수 있기 때문에 사용하지 않는 것이 바람직함.
	//reinterpret_cast - C언어에서 사용되는 강제변환과 같기 때문에 굳이 쓸 필요 없이, 꼭 필요하다면 C언어 스타일로 해도 됨.
	cout << endl;

	cout << "====7.5 상속과 연산자 다중 정의====" << endl;
	//파생 클래스에서 기본 클래스가 가진 생성자를 그대로 쓰고 싶으면 using 기본클래스::기본클래스 를 사용하면 가능함.
	//기본적으로 모든 연산자는 파생 형식에 자동적으로 종속되지만, 단순 대입 연산자는 예외임.
	COperatorTest aa(3), bb(4);
	cout << aa + bb << endl;
	COperatorTestEx cc(33), dd(44), ee(0);
	ee = cc + dd; //일반적으로는 오류 발생. 단순 대입은 상속이 안되기 때문. 근데 덧셈 연산을 해도 형식이 안맞아서 대입이 안됨.
	//해결 방법 1. 수동으로 연산자를 만든다. COperatorTestEx operator+(const COperatorTestEx& rhs)
	//해결 방법 2. 알맹이는 그대로고 형식만 바꿀 경우에는 using 키워드를 사용할 수 있다.
	cout << ee << endl;
	cout << endl;

	cout << "====7.6 다중 상속====" << endl;
	cout << "-----7.6.1 다중 상속과 모호성-----" << endl;
	//JAVA는 추상클래스나 클래스의 다중상속이 안되지만, C++은 허용함.
	//다만, 자바에서 설명하듯이 모호성과 불확실성을 증가시키기 때문에 인터페이스 다중상속 외에는 권장하지 않음.
	//다중상속은 두 클래스의 모든 것을 온전히 상속함.
	CMyPicture pic;
	cout << "Width: " << pic.GetWidth() << endl;
	cout << "Height: " << pic.GetHeight() << endl;
	cout << "Type: " << pic.GetType() << endl;
	//두 상위 클래스 메서드 모두에 접근이 가능하다.
	//두 상위 클래스 모두에 GetSize()메서드가 있는데, 이때는 둘 중 어느 것인지 특정해주면 사용할 수 있다.
	cout << "Size: " << pic.CMyImage::GetSize() << endl;
	cout << endl;
	cout << "-----7.6.2 가상 상속-----" << endl;
	//만약 CMyImage와 CMyShape가 공통된 부모클래스 CMyObject를 가지고 있다면
	//CMyPicture 클래스를 생성할때 CMyObject 클래스 생성자가 2개가 된다.
	//가상 상속을 사용하면 해결할 수 있다. 상속 코드를 작성할 때 파생 형식 클래스에 virtual 키워드를 작성하면 된다.
	//다만 두 부모 클래스에서 각각 최상위 클래스의 멤버값을 수정하고 이런 상황이 되면 점점 복잡해지므로, 다중 상속은 사용하지 않는 것이 좋다.
	//굳이 써야하면 이 뒤로 더 이상이 파생 클래스가 나오지 않을 때에 써야하나, 추천하지는 않는다.
	cout << endl;
	cout << "-----7.6.3 인터페이스 다중 상속-----" << endl;
	//다중 상속이 좋은 유일한 경우.
	//자바에서 인터페이스가 ~~able로 이름이 지어진 뒤, 여러 곳에서 활용하듯이, C++에서도 알맹이는 하나인데 활용방법이 여러가지인 경우에 사용함.
	//자바의 인터페이스가 추상 메서드만 가지는 것처럼, C++에서도 인터페이스를 구현할때는 순수 가상 클래스로 구현함.
	//CMyUSB, CMyDevice, CMySerial 클래스 참조
	CMyDevice dev; //dev는 두 클래스가 가진 인터페이스/기능을 모두 제공함.
	//인터페이스들을 활용해 더 쉽게 자신의 환경에 맞는 방향으로 객체를 구현할 수 있음.
	return 0;
}
