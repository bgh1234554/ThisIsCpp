#include <iostream>
#include <string>
#include <vector>
#include <functional> //std::function 객체를 사용하기 위한 방법

using namespace std;

int TestFunc(int nparam) {
	cout << "Function Pointer: " << nparam << endl;
	return nparam;
}

void TestFunc2(const char* pszParam, std::function<int(const char*, int)> param) { //int를 반환하는 const char*, int를 인수로 받는 함수.
	cout << pszParam << endl;
	param("Hello", 10);
}

class Add {
public:
	int operator()(int a, int b) { return a + b; }
	double operator()(double a, double b) { return a + b; }
};

void Adder(Add& add) {
	cout << "Adder()" << endl;
	add(3, 4);
}

class CCompareBase {
public:
	virtual int operator()(int a, int b) const = 0;
};

class CCmpDesc : public CCompareBase {
public:
	int operator()(int a, int b) const { return b - a; }
};

class CCmpAsce :public CCompareBase {
public:
	int operator()(int a, int b) const { return a - b; }
};

class CTestData {
private:
	int m_array[5];
public:
	CTestData() {
		m_array[0] = 30;
		m_array[1] = 10;
		m_array[2] = 20;
		m_array[3] = 90;
		m_array[4] = 80;
	}
	void Print() {
		for (auto& n : m_array) {
			cout << n << "\t";
	
		}
		cout << endl;
	}
	void Sort(const CCompareBase& cmp) {
		int nTmp;
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (cmp(m_array[i], m_array[j]) > 0) {
					nTmp = m_array[i];
					m_array[i] = m_array[j];
					m_array[j] = nTmp;
				}
			}
		}
	}
	void SortLambda(function<int(int, int)> cmp) {
		int nTmp;
		for (int i = 0; i < 4; i++) {
			for (int j = i + 1; j < 5; j++) {
				if (cmp(m_array[i], m_array[j]) > 0) {
					nTmp = m_array[i];
					m_array[i] = m_array[j];
					m_array[j] = nTmp;
				}
			}
		}
	}
};

int main12() {
	cout << "====12.2 람다식과 함수 객체====" << endl;
	//람다식 - 이름 없는 함수
	//[캡처] mutable throw(필요한 경우에만) (매개변수 리스트) -> 반환 형식 {구문;}
	auto func = [](int nparam) -> int {cout << "Lambda: " << nparam << endl; return nparam; };
	func(4);
	auto pfTest = TestFunc;//함수 포인터 호출
	pfTest(19);
	//[](int nparam) -> int 매개변수가 int하나고 반환형도 int라는 뜻
	//초깃값은 func로 이를 통해 호출할 수 있음. 형식은 auto라 자동으로 람다식을 담을 수 있다.
	cout << "START" << endl;
	TestFunc2("TestFunc2()", [](const char* pszParam, int nParam)->int {cout << pszParam << " " << nParam << endl; return 0; });
	//람다함수의 실 사용 예시 인수로 함수를 받을 수 있는 std::function개체에 함수를 넣을 때 다음과 같이 사용할 수 있다.
	cout << "END" << endl;
	cout << endl;
	cout << "-----12.2.2 함수 객체-----" << endl;
	//함수 호출 연산자를 다중정의한 클래스, 어떤 형식이든 적용시킬 수 있는 함수 템플릿과 달리, 특정 형식만 지원하게 할 수 있다.
	//의도적으로 사용자 코드를 제한하고 싶을 때 사용하며, Functor라고도 부른다.
	Add adder;
	cout << adder(3, 4) << endl;
	cout << adder(3.3, 4.4) << endl;
	Add adder2;
	Adder(adder2); //클래스를 함수의 매개변수로 넘긴거지만, 사실상 함수를 함수의 매개변수로 넘긴 것과 같은 효과를 가짐.
	//당연히 함수 객체도 상속이 가능함. 예제 - qsort() 구현해보기
	CTestData data;
	CCmpDesc desc;
	CCmpAsce asce;
	data.Sort(desc);
	data.Print();
	data.Sort(asce);
	data.Print();
	//문제는 코드가 너무 커지고 구조가 복잡해진다는 거임.
	cout << endl;
	cout << "-----12.2.3 람다식으로 변경하기-----" << endl;
	//함수 객체의 단점을 보완해서 나온게 람다식임. 매개변수에 함수 자체를 넣을 수 있게 해줌.
	CTestData data2;
	data2.SortLambda([](int a, int b)->int {return a - b; }); //왼쪽이 더 크면 바꾸는거니까 오름차순
	data2.Print();
	data2.SortLambda([](int a, int b)->int {return b-a; }); //오른쪽이 더 크면 바꾸는거니까 내림차순
	data2.Print();
	//이렇게 하면 우리가 정의했던 클래스들은 다 필요가 없어지는 것.
	//별도의 함수 객체를 구현할 필요가 없이 람다식 하나면 해결이 가능해짐.
	cout << endl;
	cout << "-----12.2.4 람다 캡처-----" << endl;
	//람다식 내부에서 외부 변수에 접근할 수 있도록 해주는 것. 우리가 본 []가 그 역할을 하는 거였음.
	//복사 캡처 -> 사용할 변수 이름을 []안에 직접 적는 것.
	//참조 캡처 -> 사용할 변수 이름을 참조자 형식으로 []안에 직접 적는 것.
	//디폴트 복사 캡처 -> 걍 전부 다 사용가능(람다 선언 직전에 이미 선언되었고, 소멸하지 않은 모든 변수들)하게 하기. [=]로 가능.
	//디폴트 참조 캡처 -> 전부 다 참조로 사용 가능. [&]로 가능.
	int nData = 10;
	cout << nData << endl;
	auto func2 = [nData](void)->void {cout << nData << endl; };
	func2();
	//void는 생략 가능하기 때문에, (void)->void는 (void), (), 아니면 그냥 바로 {}로 들어갈수도 있음.
	//복사 캡처는 캡처 안에 선언한 변수들을 읽을 수만 있으며, 값을 변경할 수 없음. 참조 캡처로 선언해야 가능함.
	//다만 복사 캡처 시 람다 함수 안에 한해서 값을 변경하게 할 수가 있음. -> mutable 키워드 사용.
	auto func3 = [nData](void) mutable->void {++nData;  cout << nData << endl; };
	func3(); //여기서만 11로 출력된다.
	cout << nData << endl;
	//복사할 변수가 여러개면 [x,y]와 같은 형식을 사용할 수 있으며,
	//[&,z]와 같이 다른건 다 디폴트 참조 캡처인데 z만 복사 캡처를 하겠다와 같이 선언할 수도 있다.
	return 0;
}