#include <iostream>

using namespace std;

int testfunc(int = 10); //디폴트 매개변수. C++은 디폴트값을 선언 가능.
//함수를 선언한 뒤에 정의할때는 선언 시에만 기본값을 설정할 수 있다. 선언 없이 바로 함수 적을때는 가능.

int testfunc(int a) {
	return a + 10;
}

int multparam(int a, int b=2) {
	return a + b;
}

//함수 다중 정의 - 이름이 같아도 매개변수 구성이 달라지면 C++에서는 다른 함수로 취급함.
int add(int a, int b) {
	return a + b;
}

int add(int a, int b, int c) {
	return a + b + c;
}
double add(double a, double b) {
	return a + b;
}
//안쪽의 매개변수가 달라야 다른 함수로 취급함. 매개변수는 같은데 return하는 형식만 다르면 다른 함수로 취급하지 않음.
//구조체, 클래스, 문자열 등 단순 + 연산으로 하기 어려울때 add()라는 함수 이름을 그대로 사용하면서 덧셈의 개념을 여러가지로 구현할 수 있음.

//다중 정의 + 기본 매개변수 -> 매우 강력한 모호성 발생.
int testfunc2(int a) {
	return a * 10;
}

int testfunc2(int a, int b = 2) {
	return a + b + 10;
}

//다중 정의는 함수를 여러번 만들어야 하기 때문에 유지 보수 측면과 메모리 측면에서 불리함. 그래서 가급적이면 함수 탬플릿을 사용함.
template <typename T>
T test(T a) {
	cout << "매개변수 a: " << a << endl;
	return a;
}

template <typename T>
T add2(T a, T b) {
	return a + b;
}

//인라인 함수
inline int AddNew(int a, int b) {
	return a + b;
}

//네임스페이스
namespace testing
{
	int testint = 10;
	void testfunc() {
		cout << "This is a testfunc" << endl;
	}
	//당연히 네임스페이스 안에도 네임스페이스가 있을 수 있음.
	namespace dev {
		int testint = 20;
		namespace user {
			int testint = 30;
		}
	}
}

int main2() {
	int a(10);
	cout << testfunc() << endl;
	cout << testfunc(20) << endl; //이런식으로 사용할 수 있기 때문에 호출자만으론 함수의 원형을 파악할 수 없다.
	//함수의 매개변수가 여러개인 경우 - 함수 호출 시 왼쪽변수부터 짝을 맞춤.
	//cout << multparam() << endl; 이러면 안됨. a에 값이 없음.
	//만약 a=2고 나머지 기본 값이 없을 시 cout <<multparam(19)<<endl 이렇게 하면 또 안됨. 왼쪽부터 맞추니까. b=2였으면 컴파일 가능.
	//디폴트 매개변수값은 오른쪽부터 사용해야 함. 만약에 3개 이상일 경우 양쪽에는 기본 매개변수가 있고 중간에 빠뜨리는 방식은 안됨.
	//호출자만으로 함수의 원형을 파악할 수 없기 때문에 가능하면 사용을 지양해야 하나, 다른 사용자에게 함수를 넘겨줄때는 유용함.
	//구체적인 예시는 책 62p~63p 참조

	//다중정의+기본매개변수
	//cout << testfunc2(5) << endl; //이러면 두 testfunc2중 어느 함수인지 알 수 없어 모호해져 오류 발생. 조심해야함.

	//함수 탬플릿
	test("2");
	test(23);
	test(4.5);
	cout << add2(3, 4) << endl;
	cout << add2(3.3, 4.5) << endl;
	//알아서 형 변환해서 사용함. T의 형식을 알려주고 싶을떄는 다음과 같이 가능.
	cout << add2<int>(54, 32) << endl;
	//같은 코드를 여러번 써도 되지 않기 때문에 안정적임.

	//인라인 함수 - 함수를 여러번 호출하면 메모리 복사가 일어나고, 메모리 사용량이 증가하기 때문에 간단한 함수들은 매크로를 사용하면 효과적임.
	//하지만, 매크로는 함수가 아니고, 형식도 지정할 수 없기 때문에 예상과 다른 결과를 출력할 수도 있음.
	//그래서 매크로와 함수의 장점만을 합친게 인라인 함수. 함수 앞의 inline 키워드로 구현 가능.
	//다만 매크로처럼 같은 내용이 코드 내내 나올 수 있기 때문에 코드가 일정 길이 이상 길어지면 비효율적이다는 단점이 있음.
	//Visual Studio는 inline을 쓰든 안쓰든 알아서 컴파일함.

	//Namespace - 함수나 변수를 한 범주로 묶어주는 키워드. 소속 느낌. 다른 사용자들과 함수와 변수 이름이 중복되는 일을 막아줌.
	testing::testfunc();
	cout << testing::testint << endl; //::으로 사용 가능.
	cout << testing::dev::testint << endl;
	cout << testing::dev::user::testint << endl;
	cout << ::testfunc(22) << endl; //전역 네임스페이스에는 그냥 ::만 붙일 수 있음.
	//여러 네임스페이스에 이름이 같은 함수가 동명이인처럼 존재할 때 using 키워드를 사용하면 함수에 대한 호출이 모호하다는 오류가 뜸.
	return 0;
}

//C++에서 식별자가 선언된 위치를 검색하는 순서.
//전역 함수인 경우 (클래스 메소드인 경우)
//1. 현재 블록
//2. 현재 블록을 포함하는 상위 블록 범위 (최대 함수 몸체까지)
//(3. 클래스의 멤버 4. 부모 클래스의 멤버)
//3. 가장 최근에 선언된 전역변수나 함수 -> 전역 변수가 네임스페이스보다 우선인 것이 중요하다.
//(6. 호출자 코드가 속한 네임스페이스의 상위 네임스페이스)
//4. using 선언된 네임스페이스 혹은 전역 네임스페이스