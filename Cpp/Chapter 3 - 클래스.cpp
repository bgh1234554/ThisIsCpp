#include <string>
#include <iostream>

using namespace std;

//C++ 스타일 클래스 만드는 법
class USERDATA {
public:
	int age = 20;
	char name[32] = "홍길동"; //이게 제일 나은 방식임.
	//int age = 20;
	//char name[32] = "홍길동"; //이런식으로 초기화 할 수 있음.
	//USERDATA() {
	//	age = 20;
	//	strcpy_s(name, 32, "홍길동"); 이걸 적으면 왜 user에서 오류가 나는거지?
	//}
	void Print(void) {
		printf("%d, %s\n", age, name);
	}
};

class CTest {
public:
	CTest() {
		cout << "CTest 생성자 함수" << endl;
		nData = 10;
	}
	//CTest() :nData(10) {}; //생성자 목록을 통해서 초기화 하는 방법.
	int nData;
	void printdata() {
		cout << nData << endl;
	}
};
//클래스 안쪽에는 함수 선언만 하고 정의는 클래스 바깥에서 하는 방법도 있다.
//void CTest::printdata(void) {
//	cout << nData << endl;
//}

//private, protected, public과 같은 키워드로 사용자가 특정 요소에 접근하지 못하게 막아둘 수 있음.
class MyData {
	int data;
public:
	int GetData(void) { return data; }
	void SetData(int m) { data = m; } //게터와 세터를 통해서 사용자의 값을 통제할 수 있음. 음량 조절 할때 100을 넘길 수 없는 것처럼.
	//private 공간에 생성자 함수를 만드는 실수를 하지 않아야 함.
	MyData() {
		data = 245;
		cout << "Test Class generated" << endl;
	}
	~MyData() { //소멸자 - 클래스가 소멸할때 출력되는 거임. 지역 변수의 범위가 끝났을 때라던가, 프로그램이 끝났을 때라던가...
		cout << "Test Class deleted" << endl;
	}
};
//C++에서는 클래스 생성자가 메인함수 밖에 있으면 메인함수보다 먼저 호출됨.
//생성자는 다중정의가 가능함. 소멸자는 안됨.

//MyData s; 전역변수로 선언된 class는 main 함수보다 먼저 생성됨.

//참조자도 클래스의 멤버 변수로 선언할 수 있음.
class RefTest {
	int& ndata;
public:
	RefTest(int& nParam) :ndata(nParam) {}; //참조자를 생성자에서 초기화 할때는 무조건 생성자 초기화 목록을 이용해 초기화해야함.
	int getdata(void) { return ndata; }
};

//생성자 다중 정의
class CMyData {
	int mdata;
public:
	CMyData():mdata(-1) {};
	CMyData(int n) { mdata = n; }
	CMyData(int x, int y) { mdata = x + y; }
	void SetData(int m) { mdata = m; }
	int GetData(void) const { return mdata; } //상수형 메서드 - const 키워드를 사용하며, 멤버 변수에 읽기는 가능하지만 쓰기는 허용하고 싶지 않을 때 사용.
	//그래서 저 메소드 안에서 mdata의 값을 수정할 수 없음. 세터로도 안됨.
	//메소드도 다중정의가 가능함.
	//void SetData(double m) { mdata = 0; }//int 멤버에 double 형을 집어 넣으려해서 못하게 막는 방식.
	//다만 이렇게 하기보다는 double을 입력하는 경우를 완전히 차단할 수 있음.
	void SetData(double m) = delete;
	//이러면 double 형태로 SetData를 호출할 경우 컴파일 오류가 남.
};

//생성자 다중 정의는 유지 보수 측면에서 단점이 있기 때문에, 생성자 내에서 다른 생성자를 부를 수 있는 기능이 추가됨.
//생성자 초기화 목록에서 썼던 방식으로 가능.
class MyPoint {
	int mx=0;
	int my=0;
public:
	MyPoint(int x) {
		if (x >= 100) { mx = 100; }
		else { mx = x; }
	}
	MyPoint(int x, int y): MyPoint(x) { //x관련은 이미 만들어놨으니까.
		if (y >= 100) { my = 100; }
		else { my = y; }
	}
	void print() {
		cout << "x = " << mx << endl;
		cout << "y = " << my << endl;
	}
};

//명시적 디폴트 생성자.
class DefaultTest {
int m_nData = 5;
int mutable nData = 10;
public:
	DefaultTest(void) = default; //명시적 디폴트 생성자. 별도로 정의를 기술하지 않아도 선언과 정의가 분리됨.
	//DefaultTest(void) = delete; 디폴트 생성자를 없앨 때 사용할 수 있음.
	int GetData() const {
		nData = 20;
		return m_nData, nData; //mutable 키워드를 사용해 선언한 변수는 상수 메소드 안에서도 쓰기가 가능함.
	}
};

//const_cast<자료형>(대상) 연산
void TestFunc(const int& param) {
	//상수형 참조자 연산이지만, const_cast<자료형>(대상) 연산을 통해서 강제로 쓰게 할 수 있다. 억지로 쓰게해야할 경우에 사용한다.
	//자주 사용하는 것은 바람직하지 않다. 대상을 반드시 괄호로 묶어야 한다!
	int& nNewParam = const_cast<int&>(param);
	nNewParam = 20;
}

//static 예약어를 통해서 인스턴스를 선언하지 않고 클래스의 인수를 직접 호출할 수 있음.
//객체지향 프로그래밍에서의 전역변수의 대안.
class StaticTest {
	int mData;
	static int mCount; //static 변수 선언
public:
	StaticTest(int nparam) :mData(nparam) { mCount++; }
	int GetData() const { return mData; }
	void ResetCount() { mCount = 0; }
	static int GetCount() { return mCount; } //static 메소드. mCount가 static int니까.
	//정적 멤버는 사실상 전역함수, 전역변수와 같기 때문에 this 포인터를 사용할 수 없음.
};
int StaticTest::mCount = 0; //static 변수 정의 (밖에서 해야함)

//57번째 줄에 있음.
int main3() {
	USERDATA user = { 19, "철수"}; //생성자 없이 초기화 하는 법. C 구조체 스타일.
	user.Print();
	USERDATA u;
	u.Print();

	CTest t;
	t.printdata();
	cout << "start" << endl;

	//클래스도 당연히 new 연산자와 delete 연산자로 동적으로 생성 가능.
	MyData* pnew = new MyData;
	MyData x;
	delete pnew; //이때 소멸자 문구가 나옴.
	cout << "end" << endl;

	int a = 10;
	RefTest ref(a);
	cout << ref.getdata() << endl;
	a = 20;
	cout << ref.getdata() << endl; //참조자도 결국에는 포인터기 때문에 원본이 바뀌었으니까 클래스 안 참조자 멤버의 값도 바뀜.

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
	//객체 지향 프로그래밍에서 전역변수와 함수를 남발하면 객체지향과 상관없는 코드로 변질될 수 있기 때문에 정적 멤버를 사용하는 것이 좋음.
	return 0;
}
//메인함수가 다 끝난 뒤에 MyData 클래스 2개가 종료됨.