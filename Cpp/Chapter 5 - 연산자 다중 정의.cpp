#include <iostream>

using namespace std;

class CMyData5 {
private:
	int m_nData = 0;
public:
	//변환 생성자
	CMyData5(int nparam) :m_nData(nparam) {
		cout << "CMyData5(int)" << endl;
	}
	//복사 생성자
	CMyData5(const CMyData5& rhs):m_nData(rhs.m_nData) {
		cout << "CMyData5(const CMyData&)" << endl;
	}
	//이동 생성자
	CMyData5(const CMyData5&& rhs) :m_nData(rhs.m_nData) {
		cout << "CMyData5(const CMyData&&)" << endl;
	}
	//형 변환
	operator int() {return m_nData;}
	//덧셈 연산
	CMyData5 operator+(const CMyData5& rhs) {
		cout << "operator+" << endl;
		CMyData5 result(0);
		result.m_nData = this->m_nData + rhs.m_nData;
		return result;
	}
	//단순 대입 연산
	CMyData5& operator=(const CMyData5& rhs) {
		cout << "operator=" << endl;
		m_nData = rhs.m_nData;
		return *this;
	}
	//5.6 단항 증감 연산자
	//전위 증가 연산자
	int operator++() {
		cout << "operator++()" << endl;
		return ++m_nData; //그냥 멤버 값을 증가시켜서 출력하면 됨.
	}
	//후위 증가 연산자
	int operator++(int) {
		cout << "operator++(int)" << endl;
		//원래의 값을 반환하고, 그 뒤에 1이 커져야 한다.
		int nData = m_nData; //원래 값 백업
		m_nData++; //1 증가시킴
		return nData; //원래의 값을 돌려준다.
	}
};

class CMyData5ptr {
private:
	int* m_pnData = nullptr; //포인터를 초기화 할때 쓰는 NULL 포인터. C++11에 새로 추가됨.
public:
	explicit CMyData5ptr(int nParam) {
		cout << "CMyData5ptr(int)" << endl;
		m_pnData = new int(nParam); //new로 초기화 해야함.
	}
	~CMyData5ptr() { delete m_pnData; }
	//복사 생성자
	CMyData5ptr(const CMyData5ptr& rhs) {
		cout << "CMyData5ptr(const CMyData5tpr &)" << endl;
	}
	operator int() { return *m_pnData; }
	//덧셈 연산자 다중 정의
	CMyData5ptr operator+(const CMyData5ptr& rhs) {
		cout << "operator+" << endl;
		return CMyData5ptr(*this->m_pnData + *rhs.m_pnData);
	}
	//단순 대입 연산자 다중 정의
	CMyData5ptr& operator=(const CMyData5ptr& rhs) {
		cout << "operator=" << endl;
		if (this == &rhs) { return *this; } //a=a의 연산을 사용할 때 이 if문이 없으면, 바로 멤버가 있는 메모리를 삭제하기 때문에 대입할 수가 없음.
		delete m_pnData;
		m_pnData = new int(*rhs.m_pnData);
		return *this; //반환 형식이 클래스의 참조인 이유: a=b=c와 같은 연산을 수행했을 때, void를 반환하게 되면 void를 l-value의 형식으로 취할 수 없기 때문.
	}
	//복합 대입 연산자 다중 정의 (깊은 복사)
	CMyData5ptr& operator+=(const CMyData5ptr& rhs) {
		int* pResult = new int(*m_pnData);
		*pResult = *pResult + *rhs.m_pnData;
		//!!포인터를 사용하기 때문에 기존 메모리를 삭제하고 대체하는 과정이 꼭 필요함!!
		delete m_pnData;
		m_pnData = new int(*pResult);
		return *this; //반환 형식이 클래스의 참조인 이유: a=b=c와 같은 연산을 수행했을 때, void를 반환하게 되면 void를 l-value의 형식으로 취할 수 없기 때문.
	}
	//이동 대입 연산자 다중 정의 (얕은 복사)
	CMyData5ptr& operator=(CMyData5ptr&& rhs) {
		cout << "operator=(Move)" << endl;
		this->m_pnData = rhs.m_pnData; // 포인터 사용 안하고, 그냥 단순 대입함 : 얕은 복사
		rhs.m_pnData = nullptr;
		return *this; //반환 형식이 클래스의 참조인 이유: a=b=c와 같은 연산을 수행했을 때, void를 반환하게 되면 void를 l-value의 형식으로 취할 수 없기 때문.
	}
	//대입 연산자는 참조자의 형식으로 대상을 반환해야 한다.
	void setData(int nParam) { *m_pnData = nParam; }
};

//메모리 관리를 포함한 int 배열.
class CIntArray {
private:
	int* m_pnData; //배열 메모리
	int m_nSize; //배열 요소의 개수
public:
	CIntArray(int nSize) {
		m_nSize = nSize;
		m_pnData = new int[nSize];
		memset(m_pnData, 0, sizeof(int)*nSize); //memset(배열, 값, 용량(바이트))
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
	cout << "====5.1 연산자 함수란?====" << endl;
	//연산자를 이용하듯 호출할 수 있는 메서드. 절대로 오류가 발생해서 안됨.
	//사용자 코드쪽에서의 문제점을 확인하기 더 어려울 수 있지만, 훨씬 유용함.
	//절대로 논리 연산자를 다중정의해서는 안됨.
	cout << "====5.2 산술 연산자====" << endl;
	//operator int(), CMyData5 operator=(const CMyData &rhs), CMyData5& operator+(const CMyData &rhs)
	//형 변환, 단순 대입, 덧셈 연산자 다중정의
	cout << "BEGIN" << endl;
	CMyData5 a(0), b(4), c(5);
	//b+c 연산을 수행하면 임시 객체 생성, 이 객체가 a에 대입됨.
	a = b + c;
	cout << a << endl;
	cout << "END" << endl;
	cout << endl;

	cout << "====5.3 단순 대입 연산자====" << endl;
	//깊은 복사때문에 다중 정의가 필요한 연산자.
	CMyData5ptr aa(0), bb(2), cc(3);
	aa = bb = cc; //참고로 3임.
	cout << aa << endl;
	cout << endl;
	cout << "-----5.3.1 복합 대입 연산자-----" << endl;
	//이미 실습 과제에서 해본 것들임 operator+=같은 것. 다만 포인터를 사용할 경우 좀 까다로울 수 있음. 코드 참조.
	aa.setData(50), bb.setData(20), cc.setData(33);
	aa += bb;
	aa += cc;
	cout << aa << endl;
	cout << endl;
	cout << "-----5.3.2 이동 대입 연산자-----" << endl;
	//이름 없는 임시 객체에 대응하기 위한 이동 대입 연산자도 존재함.
	aa.setData(0), bb.setData(3), cc.setData(4);
	aa = bb + cc; //여기서 이동 대입 연산자가 실행된다.
	cout << aa << endl;
	aa = bb;
	cout << aa << endl;
	//bb+cc 연산을 operator+ 연산자로 수행한 뒤에 나오는 임시 객체를 r-value 삼아서 바로 단순 대입 연산을 시행할 때, 이동 대입 연산자가 호출된다.
	//일반 대입 연산자는 깊은 복사를, 이동 대입 연산자는 얕은 복사를 수행함. 복사 생성자와 이동 생성자처럼.
	cout << endl;

	cout << "====5.4 배열 연산자====" << endl;
	//배열 연산자의 매개변수는 int 하나. index용으로 사용됨.
	//int& operator[] (int index) -> 일반적인 배열 참조. l-value, r-value 모두로 사용 가능.
	//int operator[] (int index) const -> 상수형 참조를 통해서만 호출할 수 있고, r-value로만 사용 가능.
	CIntArray arr(5);
	for (int i=0; i < 5; i++) {
		arr[i] = i* 10;
	}
	TestFunc(arr);
	cout << endl;

	cout << "====5.5 관계 연산자====" << endl;
	//관계 연산자 : 상등, 부등 연산자와 비교 연산자를 합쳐 관계 연산자라고 함.
	//int형을 반환하며 참이면 1, 거짓이면 0을 반환함.
	//배열 단위 비교의 가장 흔한 예는 문자열임 -> 예시는 CMystring 파일에서 확인할 것.
	cout << endl;

	cout << "====5.6 단항 증감 연산자====" << endl;
	//for문에서 흔히 볼 수 있는 ++와 --연산자를 말함.
	//앞에 붙으면 전위문, 뒤에 붙으면 후위문.
	//int operator++() : 전위문, int operator++(int) : 후위문
	CMyData5 x(10);
	cout << ++x << endl;
	cout << x++ << endl;
	cout << x << endl;
	return 0;
}