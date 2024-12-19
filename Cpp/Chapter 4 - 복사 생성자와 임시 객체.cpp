#include <iostream>

using namespace std;
class CMyData4{
	int m_nData = 0;
public:
	CMyData4() { cout << "CMyData4()" << endl; }
	CMyData4(int nParam):m_nData(nParam){ cout << "CMyData4(int)" << endl; }
	//복사 생성자: 객체의 복사본을 생성할때 호출되는 생성자.
	//클래스 내부에서 메모리를 동적으로 할당하고 해제하고, 이를 포인터 변수로 관리할 때에는 만들어줘야함.
	CMyData4(const CMyData4& rhs) 
	//:m_nData(rhs.m_nData)
	{
		this->m_nData = rhs.m_nData; //구분하기 편하게 this 사용.
		cout << "CMyData4(const CMyData4&)" << endl;
	}
	void SetData(int param) { m_nData=param; }
	int GetData() const { return m_nData; }
};
//복사 생성자가 호출되는 경우
//1. 명시적으로 객체의 복사본을 생성. (CTest a;)
//2. 함수 형태로 호출 (TestFunc(a))
//2-1. 클래스가 매개변수로 활용됨. 2-2. 반환 형식으로 사용됨. -> 성능 문제가 있기 때문에 중요함. (특히 return 값일 때)

void TestFunc(CMyData4 param) {
	cout << "TestFunc()" << endl;
	param.SetData(20);
}

void TestFunc2(CMyData4 &param) {
	cout << "TestFunc()" << endl;
	param.SetData(20); //const CMyData4 &param이었으면 이 줄은 제대로 작동하지 않음.
}

class ShallowCopy {
	int* m_pnData = nullptr;
public:
	ShallowCopy(int nParam) {
		m_pnData = new int;
		*m_pnData = nParam;
	}
	~ShallowCopy() { //소멸시 동적으로 메모리 해제
		delete m_pnData;
	}
	ShallowCopy(const ShallowCopy& rhs) {
		cout << "ShallowCopy(const ShallowCopy&)" << endl;
		m_pnData = new int; //메모리 할당 후
		*m_pnData = *rhs.m_pnData; //포인터가 가리키는 값을 복사해야 깊은 복사가 완성됨.
	}
	ShallowCopy& operator=(const ShallowCopy& rhs) {
		*m_pnData = *rhs.m_pnData;
		return *this; //무조건 *this를 return 해야함.
	}
	int GetData() {
		if (m_pnData != NULL) {
			return *m_pnData;
		}
		return 0;
	}
};

class ConversionTest {
	int m_nData = 0;
public:
	//변환 생성자. 묵시적 변환 생성을 막기 위해 explicit 키워드 사용.
	explicit ConversionTest(int nParam) :m_nData(nParam) {
		cout << "ConversionTest(int)" << endl;
	}
	operator int(void) { return m_nData; } //클래스를 int로 변환하는 방법 제공.
	ConversionTest(const ConversionTest& rhs) :m_nData(rhs.m_nData) {
		cout << "ConversionTest(const ConversionTest&)" << endl;
	}
	void SetData(int param) { m_nData = param; }
	int GetData() const { return m_nData; }
};

void TestConversion(ConversionTest param) {
	cout << "TestConversion(): " << param.GetData() << endl;
}

void TestConversion2(const ConversionTest &param) {
	cout << "TestConversion(): " << param.GetData() << endl;
}

class CTestData {
private:
	int m_nData;
	const char* m_pszName = nullptr;
public:
	CTestData(int nParam, const char* pszName) : m_nData(nParam), m_pszName(pszName) {
		cout << "CTestData(int): " << m_pszName << endl;
	}
	~CTestData() {
		cout << "~CTestData(): " << m_pszName << endl;
	}
	CTestData(const CTestData& rhs) : m_nData(rhs.m_nData), m_pszName(rhs.m_pszName) {
		cout << "CTestData(const CTestData&): " << m_pszName << endl; //const 까먹지 말기
	}
	CTestData& operator=(const CTestData& rhs) {
		cout << "operator=" << endl;
		//값만 변경, 이름은 그대로.
		m_nData = rhs.m_nData;
		return *this;
	}
	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};
//코드 관련: char* m_pszName을 const char* m_pszName으로 바꾸면 잘 작동한다.
//문자열 상수를 저장할때는 꼭 앞에 const를 붙여야함.

CTestData TestFunc3(int nParam) {
	//testa는 지역변수이기 때문에 함수가 반환되면 소멸됨.
	CTestData testa(nParam, "testa");
	return testa;
}

void rvalueTestFunc(int& rParam) {
	cout << "TestFunc(int &)" << endl;
}

void rvalueTestFuncFixed(int&& rParam) {
	cout << "TestFunc(int &)" << endl;
}

class MoveSemantics {
	int m_nData = 0;
public:
	MoveSemantics(){ cout << "MoveSemantics()" << endl; }
	~MoveSemantics(){ cout << "~MoveSemantics()" << endl; }
	//복사 생성자
	MoveSemantics(const MoveSemantics& rhs):m_nData(rhs.m_nData){ cout << "MoveSemantics(const MoveSemantics&)" << endl; }
	//이동 생성자 (const 안사용함. rvalue 참조니까.)
	MoveSemantics(MoveSemantics&& rhs):m_nData(rhs.m_nData){ cout << "MoveSemantics(MoveSemantics&&)" << endl; }
	MoveSemantics& operator=(const MoveSemantics&) = default;
	int GetData() const { return m_nData; }
	void SetData(int nparam) { m_nData = nparam; }
};

MoveSemantics TestSemantics(int nParam) {
	cout << "TestSemantics(): Begin" << endl;
	MoveSemantics a;
	a.SetData(nParam);
	cout << "TestSemantics(): End" << endl;
	return a;
}

int main4() {
	cout << "====4.1 복사 생성자====!" << endl;
	CMyData4 a;
	a.SetData(10);
	CMyData4 b(a); //복사 생성자 호출
	cout << b.GetData() << endl;
	cout << endl;
	cout << "-----4.1.1 함수 호출과 복사 생성자-----" << endl;
	CMyData4 x(10);
	TestFunc(x); //실행 시켜보면 TestFunc를 실행할 때 복사 생성자가 호출됨. param은 a를 원본으로 한 복사본임. -> 프로그램 성능 저하.
	//참조자를 이용하면 복사 생성자의 생성을 막을 수 있음.
	cout << "x: " << x.GetData() << endl;
	CMyData4 y(10);
	TestFunc2(y); //복사 생성자 실행 안됨.
	cout << "y: " << y.GetData() << endl;
	//다만 저 46번 줄을 봤을때 함수가 참조에 의한 호출을 하는지, 값에 의한 호출을 하는지 알 수 없음.
	//알아야 하는 이유 -> 함수의 실인수로 기술한 변수가 함수 호출로 인해 값이 변할 수 있기 때문. 그래서 일단 클래스 형식인 매개변수면 상수형 참조로 선언해야함.
	//어쩔수 없이 값을 변경해야 하는 경우는 제외. 이러면 함수 내에서 매개변수 인스턴스의 값을 변경할 수 없다.
	cout << endl;

	cout << "-----4.1.2 깊은 복사와 얕은 복사-----" << endl;
	//깊은 복사와 얕은 복사.
	//얕은 복사: 값은 하나뿐인데, 포인터가 2개인것 (파이썬에서 배열 수동으로 복사 안하면 이렇게 됨.)
	int* pa, * pb;
	pa = new int;
	*pa = 10;
	pb = new int;
	pb = pa;
	delete pa; //메모리를 지우는데...
	//delete pb; //오류 발생! pa와 pb가 같은 것을 가리키기 때문에 이미 한번 지운 메모리 주소를 다시 한번 지울 수 없어서 오류가 발생함.
	//*pb = *pa; //이런 식이면 문제 해결됨. 포인터가 가지고 있는 메모리의 내용이 복사되기 때문임.

	ShallowCopy sh(10);
	ShallowCopy shh(sh); //겉으로는 아무 이상이 없지만, 속으로는 메모리를 해제하지 않고 만들었기 때문에 오류가 발생해 있음. 깊은 복사를 하지 않아서임.
	//그래서 위의 메모리 지울때 오류 같은 것이 발생할 수 있음.
	//오류 고치려면 복사 생성자가 깊은 복사를 할 수 있도록 만들어야 함. 45번 코드 참고.
	cout << sh.GetData() << endl;
	cout << shh.GetData() << endl;
	cout << endl;
	
	cout << "-----4.1.3 대입 연산자-----" << endl;
	//단순 대입 연산자 = 는 클래스와 구조체에도 적용됨.
	//문제는 = 연산자는 얕은 복사를 수행하기 때문에 클래스를 복사할 때 문제가 발생할 수 있음.
	//자세한건 차후에 설명하겠지만, 해결 방법은 코드를 참조하면 됨.
	ShallowCopy s(10);
	ShallowCopy t(20);
	s = t;
	cout << s.GetData() << endl;
	cout << endl;

	cout << "====4.2 묵시적 변환====!" << endl;
	cout << "-----4.2.1 변환 생성자-----" << endl;
	//변환 생성자: 매개변수가 한개인 생성자.
	//변환 생성자가 은근슬쩍 호출되어, 불필요한 임시 객체를 만들며 프로그램의 성능을 저하시킬 수 있음.
	//TestConversion(19); //매개변수가 하나면 형 변환이 가능하기 때문에 int 자료형이 ConversionTest 형식으로 변환되어 생성됨.
	//원래는 매개변수 형식이 안맞아 실행이 안되어야 하지만, 변환 생성자가 있어서 함수가 호출됨.
	//TestConversion2(21); //참조자 연산을 붙여도 알아서 임시 객체를 생성해서, 이 임시 객체에 대한 참조가 TC2 함수로 넘어간다.
	//임시 객체는 함수가 값을 반환한 동시에 소멸되며, TestConversion2(ConversionTest(21))과 같은 효과를 가지게 만듬.
	//묵시적 개체는 사용자의 편의성을 높여주기 때문에 놔둬도 상관없지만, 객체의 규모가 크다면 호출될 가능성을 차단하는 것이 바람직함.
	//explicit 키워드를 사용해서 이제 TestConversion 함수가 작동을 못함.
	cout << endl;

	cout << "-----4.2.2 허용되는 변환-----" << endl;
	//변환 생성자: int를 클래스로 변환하는 방법 제공하는 역할.
	//그런데 클래스를 int로 바꾸는 방법이 없어서 반쪽임 -> 형변환 연산자를 만들어 넣을 수 있음.
	//ConversionTest 클래스 operator int(void) 부분 참고.
	ConversionTest aint(12);
	cout << aint.GetData() << endl;
	cout << aint << endl; //형변환 연산자 덕에 오류가 발생하지 않고 int 형태로 변환되어 출력됨.
	cout << (int)aint << endl; //강제 형변환 - C언어 스타일
	cout << static_cast<int>(aint) << endl; //C++ 스타일. 사용 방법은 const_cast와 같음. 여러 종류가 있는데 이는 차후에 다룸.
	//operator에도 explicit 키워드를 사용할 수 있는데, 그러면 cout << aint << endl;에서는 묵시적으로 변환을 했기 때문에 오류가 발생함.
	//explicit 키워드가 사용되었다면 static_cast를 사용해야 형변환이 가능함.
	cout << endl;

	cout << "====4.3 임시 객체와 이동 시맨틱====!" << endl;
	cout << "-----4.3.1 이름 없는 임시 객체-----" << endl;
	//함수의 반환 형식이 클래스인 경우 생성을 막을 수 없는, 은밀한 임시 객체가 생성된다.
	//이름 없는 임시 객체 - 존재하는 인스턴스지만 식별자가 부여되지 않은 객체.
	CTestData testb(5, "testb"); //CTestData(int): b 출력
	cout << "Before" << endl;
	testb = TestFunc3(10);
	//지금 실행해보면
	//TF3 함수의 a 클래스 생성 -> 단순 대입 연산 사용 -> a객체 삭제 이렇게 되는데...
	//책에서는 이름이 없는 임시 객체가 복사 생성됨. (int a -> const CTestData& a -> ~CTestData a (원본) -> operator= -> ~CTestData a)
	//이름이 없는 임시 객체의 원본이 객체가 복사 생성된 이후 삭제됨.
	cout << "After" << endl;
	cout << testb.GetData() << endl;
	cout << TestFunc3(15).GetData() << endl;
	//함수가 반환한 임시 객체에 멤버 접근 연산을 사용할 수 있음. 이러면 Method 사용이 끝난 뒤 testa 클래스가 소멸함.
	//이름 없는 임시 객체가 생성되지 않게 하려면 Visual Studio 프로젝트 속성에서 Release 모드로 컴파일하면 됨.
	//참조자를 써서 이름 없는 객체에 별명을 만들 수 있음.
	const CTestData& rData = TestFunc3(22); //책에는 const 없이 나와있지만, 현재는 const를 써야함.
	//const가 없는 참조자는 l-value만 참조할 수 있음. (변수만 가능하다고...)
	cout << endl;

	cout << "-----4.3.2 r-value 참조-----" << endl;
	//변수가 아닌 대상에 참조를 할 수 없었으나, r-value에 대한 참조자가 새롭게 제공됨.
	//&&를 사용해서 표현할 수 있음.
	int&& data = 3 + 4;
	cout << data << endl;
	data++; //상수에 대한 참조인데도 연산 수행이 가능함.
	cout << data << endl;
	//rvalueTestFunc(3 + 4); 이건 작동 안됨. int를 int &로 바꿀 수 없기 때문.
	rvalueTestFuncFixed(3 + 4); //이건 매개변수 형식이 int &&라 작동함.
	//제일 중요! rvalue 참조는 연산에 의해 생성된 임시 객체를 참조하는 것.
	//변수와 상수를 더해도 int 자료형 상수가 되기 때문에 rvalue 참조가 가능함.
	int num = 4;
	rvalueTestFuncFixed(num+4);
	rvalueTestFuncFixed(3);
	rvalueTestFuncFixed(3+4);
	//rvalueTestFuncFixed(num); 이건 안됨.
	//따라서 C++에서는 함수의 매개변수를 int, int&, int&& 중 무엇으로 할지 신중하게 결정해야함.
	//당연히 함수 다중정의로 모호성이 발생할 수 있다.
	//void rvalueTestFuncFixed(int rParam) {
	//	cout << "TestFunc(int &)" << endl;
	//}
	//이런 함수가 있으면 rvalueTestFuncFixed(3+4)를 쓰면 모호성이 발생한다.
	//rvalue참조는 클래스에 적용될 때 진가가 발휘됨. 추후 연산자 다중 정의를 배울 때 참고.
	cout << endl;

	cout << "-----4.3.3 이동 시맨틱-----" << endl;
	//이동 생성자 - 이름 없는 임시 객체가 생성될때 부하를 최소화시키기 위해 사용하는 생성자.
	//임시 객체가 생성될 때 복사 대신 이동 생성자를 사용하는데, 이때 얕은 복사를 사용하기 때문에 메모리를 덜 사용함.
	MoveSemantics sem;
	cout << "Before" << endl;
	sem = TestSemantics(25);
	cout << "After" << endl;
	MoveSemantics sem2(sem);
	//이 역시 컴파일러가 업데이트 된건지 책과 다른 결과로 수행된다...
	return 0;
}