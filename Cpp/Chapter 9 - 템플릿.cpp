#include <iostream>
#include <memory> //shared_ptr을 사용하려면 include 해야함.

using namespace std;

template<typename T>
class CMyData9 {
private:
	T m_Data;
public:
	CMyData9(T param):m_Data(param){}
	T GetData() const{ return m_Data; }
	operator T() { return m_Data; }
	void SetData(int param) { m_Data = param; }
};

//구조적으로 메모리를 자동 동적 할당 및 해제하며 복사 생성자와 이동 시멘틱을 지원함
//개별 요소에 배열 연산자로 접근 가능
template<typename T>
class CMyArray {
private:
	int m_nSize = 0;
	T* m_pData = nullptr;
public:
	explicit CMyArray(int nSize) :m_nSize(nSize) {
		m_pData = new T[nSize];
	}
	~CMyArray() { delete[] m_pData; }//delete[]를 사용해야함.
	//복사 생성자
	CMyArray(const CMyArray& rhs) {
		m_pData = new T[rhs.GetSize()];
		memcpy(m_pData, rhs.m_pData, sizeof(T) * (rhs.m_nSize));
		m_nSize = rhs.m_nSize;
	}
	//대입 연산자
	CMyArray& operator=(const CMyArray& rhs) {
		if (this == &rhs) return *this; //주소가 같아야지! this는 시리얼 넘버니까.
		delete[]m_pData; //새로 만들어줘야 배열의 크기가 달라도 문제가 생기지 않는다.
		m_pData = new T[rhs.GetSize()];
		memcpy(m_pData, rhs.m_pData, sizeof(T) * (rhs.m_nSize));
		m_nSize = rhs.m_nSize;
		return *this; 
	}
	//이동 생성자 (얕은 복사)
	CMyArray(const CMyArray&& rhs) {
		operator=(rhs);
	}
	//이동 대입 연산자 (얕은 복사)
	CMyArray& operator=(const CMyArray&& rhs) {
		//얕으니까 동적 할당 안해도 됨.
		m_pData = rhs.m_pData;
		m_nSize = rhs.m_nSize;
		rhs.m_pData = nullptr;
		rhs.m_nSize = 0;
	}
	//배열 연산자
	T& operator[](int nparam) {
		if (nparam < 0 || nparam >= m_nSize) {
			cout << "ERROR: 배열의 경계에 벗어난 접근입니다." << endl;
			exit(1);
		}
		else
			return m_pData[nparam];
	}
	//상수화된 배열 연산자
	T operator[](int nparam) const {
		return operator[](nparam);
	}
	//배열 요소의 개수를 반환
	int GetSize() const { return m_nSize; }
};

template<typename T>
class CTest9 {
public:
	CTest9();
	T TestFunc();
protected:
	static T m_Data;
};

template<typename T>
CTest9<T>::CTest9()
{
}

template<typename T>
T CTest9<T>::TestFunc()
{	
	return m_Data;
}

template<typename T>
T CTest9<T>::m_Data = 15;

template<typename T>
T Add(T a, T b) { return a + b; }

//문자열일 경우 다르게
template<>
const char* Add(const char* a, const char* b) {
	int nLenLeft = strlen(a);
	int nLenRight = strlen(b);
	char* Result = new char[nLenLeft + nLenRight + 1];
	strcpy_s(Result, nLenLeft + 1, a);
	strcat_s(Result, nLenLeft+nLenRight + 1, b);
	return Result;
}

template<typename T>
class CTemplateTest {
private:
	T m_Data;
public:
	CTemplateTest(T param):m_Data(param){}
	T GetData() const { return m_Data; }
	void SetData(T param) { m_Data = param; }
};

template<>
class CTemplateTest<const char*> {
private:
	char* m_Data;
public:
	CTemplateTest(const char* param){
		int nLen = strlen(param);
		m_Data = new char[nLen + 1];
		strcpy_s(m_Data, nLen + 1, param);
	}
	~CTemplateTest() { delete[] m_Data; }
	const char* GetData() const { return m_Data; }
	void SetData(const char* param) { strcpy_s(m_Data, strlen(param) + 1, param); }
};

template<typename T>
class CInherit {
protected:
	T m_Data=NULL;
public:
	CInherit(){}
};

template<typename T>
class CInheritEx : public CInherit<T> {
public:
	int GetData() const { return this->m_Data; } //protected 접근할때 this-> 연산자 사용하기.
	void SetData(T param) { this->m_Data = param; }
};

class CPtrTest {
public:
	CPtrTest() { cout << "CPtrTest()" << endl; }
	~CPtrTest() { cout << "~CPtrTest()" << endl; }
	void TestFunc() { cout << "CPtrTest::TestFunc()" << endl;  }
};

void PtrRemoveTest(CPtrTest *ptrTest) {
	cout << "PtrRemoveTest(CPtrTest *)" << endl;
	delete[] ptrTest;
}

//...으로 여러개 타입을 받을 수 있음.
template<typename T, typename... Types>
void print(T arg, Types... args) {
	cout << arg << ", ";
	print(args...); //...을 붙여야함.
}

int main9() {
	cout << "====9.1 클래스 템플릿====" << endl;
	//클래스를 찍어내는 틀 같은 것. 자료형에 따라서 다르게 클래스를 찍어내는 틀 같은 거임.
	//함수 탬플릿이 클래스로 확장된 것. 함수 탬플릿은 2.2 참조
	CMyData9<int> a(5);
	cout << a << endl;
	CMyData9<const char*> c("Hello"); //문자열을 동적으로 생성하지는 않는다.
	cout << c << endl;
	//예제 - 어떤 형식이든 배열로 관리할 수 있음 (std::vector 같은건가?)
	CMyArray<int> arr(5);
	for (int i = 0; i < 5; i++) {
		arr[i] = 10 * (i + 1);
	}
	CMyArray<int> arr2(3);
	arr2 = arr;
	for (int i = 0; i < 5; i++) {
		cout << arr2[i] << "\n";
	}
	cout << "-----9.1.1 멤버 선언 및 정의-----" << endl;
	//필요하다면 클래스 템플릿에서도 선언과 정의를 분리할 수 있으며 정적 멤버를 포함시키는 것도 가능하다.
	//다만 분리되면 기술될 때마다 template<typename T>를 선언해야함.
	CTest9<double> d;
	cout << d.TestFunc() << endl;
	//멤버의 정의를 클래스 밖으로 빼낼때 CTest9<T>처럼 이름 다음에 형식을 기술해야함.
	cout << endl;
	cout << "-----9.1.2 템플릿 매개변수-----" << endl;
	//Template<typename T,typename U> 가능함.
	//Template<typename T,int nSize>와 깉이 형식을 구체적으로 작성할 수 있음.
	//배열의 개수를 입력받았는데 이때 CMyArray<int> arr(5)가 아니라
	//CMyArray<int,5> a; 이런 식으로 기술할 수 있다.
	//템플릿 매개변수도 기본값을 지정할 수 있다.
	//template<typename T = int, int nSize=3>
	//자료형의 디폴트값, 다른 매개변수의 디폴트값을 동시 선언한 형태임.
	cout << endl;

	cout << "====9.2 템플릿 특수화====" << endl;
	cout << "-----9.2.1 함수 템플릿 특수화-----" << endl;
	//템플릿을 만들어도 간혹 포인터와 같은 특수한 형식이 들어올 경우 전혀 다른 코드를 작성해야 할 때가 있음
	//이때는 template<>와 같은 표현을 사용해서 특수화를 시킴. Add 함수 예제 참조.
	int Result = Add<int>(3, 4);
	cout << Result << endl;
	const char* pszResult = Add<const char*>("Hello", "World");
	cout << pszResult << endl;
	delete[] pszResult;
	//특정 형식은 개발자인 내가 정의할테니 별도로 생성하지 마라는 뜻을 컴파일러에게 전달.
	cout << endl;
	cout << "-----9.2.2 클래스 템플릿 특수화-----" << endl;
	//클래스 템플릿도 함수와 동일한 방법으로 특수화할 수 있다.
	CTemplateTest<const char*> aa("Hello");
	cout << aa.GetData() << endl;
	cout << endl;

	cout << "====9.3 클래스 탬플릿과 상속====" << endl;
	//일반 클래스 상속과 똑같음. 그냥 템플릿이 추가된 것. 예제 참조.
	CInheritEx<int> inh;
	inh.SetData(50);
	cout << inh.GetData() << endl;
	cout << endl;

	cout << "====9.4 스마트 포인터====" << endl;
	//동적할당한 인스턴스를 자동으로 삭제해주는 포인터. 편리하지만 경우에 따라서는 오히려 해가 될 수 있음
	//auto_ptr, shared_ptr, unique_ptr, weak_ptr가 있음.
	//모두 템플릿으로 구현되어 있음.
	cout << "-----9.4.1 auto_ptr-----" << endl;
	//가장 예전부터 존재했던 스마트 포인터인데 문제가 많아 이제는 사용하지 않음.
	//얕은 복사 문제가 있고, 배열을 지원하지 않음.
	cout << "BEGIN" << endl;
	{
		auto_ptr<CPtrTest> ptrTest(new CPtrTest); //해당 구간에서만 존재하고 소멸되게 유도하기 위해서 {} 사용함.
	}
	cout << "END" << endl;
	//배열 관련 문제점 = 배열로 삭제를 하지 않아 메모리를 해제할때 오류가 발생함.
	//auto_ptr<CPtrTest> ptrTest2(new CPtrTest[3]); //메모리 해제 시 오류 발생
	//얕은 복사를 할 때 발생하는 문제점
	auto_ptr<CPtrTest> ptrTest2(new CPtrTest);
	auto_ptr<CPtrTest> ptrNew;
	cout << ptrTest2.get() << endl; //메모리 주소값 불러오는 함수.
	ptrNew = ptrTest2; //단순 대입 연산 시 원본 포인터가 가리키는 주소가 NULL이 되어버림.
	//cout << ptrTest2.get() << endl;
	//ptrTest2->TestFunc(); //그래서 이 코드가 실행이 안됨.
	//ptrTest2가 자신이 가리키는 CPtrTest의 값을 ptrNew에 복사해주고, 자기 자신을 NULL로 초기화해버려
	//사실상 복사가 아닌 이동이 발생한다는 문제가 있음.
	//그래서 나온 대안이 shared_ptr
	cout << endl;

	cout << "-----9.4.2 shared_ptr-----" << endl;
	//#include <memory> //shared_ptr을 사용하려면 include 해야함.
	//auto_ptr와는 달리 포인팅이 된 횟수를 계산해서 0이되면 대상을 삭제함.
	//예를 들어 2개의 포인터가 한 객체를 가리키면 카운트 값은 2가 되고, 한 포인터가 소멸하더라도 그 객체는 소멸하지 않음.
	cout << "BEGIN" << endl;
	shared_ptr<CPtrTest> ptr1(new CPtrTest);
	cout << "Counter " << ptr1.use_count() << endl; //use_count 포인팅 된 횟수 세주는 메서드.
	{
		shared_ptr<CPtrTest> ptr2(ptr1); //똑같은 걸 가리키는 ptr2
		//선언만 하고 나중에 ptr2=ptr1으로 해도 문제가 없다. auto_ptr처럼 ptr1이 NULL로 바뀌는 일은 발생하지 않기 때문이다.
		cout << "Counter " << ptr2.use_count() << endl;
		ptr2->TestFunc();
	}
	cout << "Counter " << ptr1.use_count() << endl; //카운팅 수 1 감소
	ptr1->TestFunc();
	cout << "END" << endl; //이후 프로그램 종료 시 객체 소멸시킴.
	//배열로 객체를 delete할 수 있는 방법을 제공하는데, 이 삭제 함수를 개발자가 직접 만들어야 한다.
	shared_ptr<CPtrTest> ptr3(new CPtrTest[5], PtrRemoveTest); //소멸할 함수를 별도로 등록함.
	ptr3.reset(); //원한다면 대상을 지정해서 직접 삭제할 수 있음. - reset 메서드.
	cout << endl;

	cout << "-----9.4.3 unique_ptr-----" << endl;
	//share_pointer하고 유사하지만 use_count()의 값을 1로만 가능하게 함. 한 대상은 한 포인터로만 가리킬 수 있음.
	//새 포인터로 이동은 가능하지만, 복사는 안됨.
	unique_ptr<CPtrTest> uptr(new CPtrTest);
	unique_ptr<CPtrTest> uptr2 = move(uptr); //이건 가능 - 소유권 이전임.
	//uptr2 = uptr; //오류 발생. 참조가 불가함.
	//애초에 여러 포인터가 한 대상을 가리킬 경우를 차단할 수 있음. 따라서 얕은 복사가 일어날 가능성을 차단하는 것임.	
	
	//스마트 포인터 관련 메서드
	//get - 주소 반환, use_count - 카운터 값 반환, reset - 메모리 해제/대상을 직접 삭제
	//release - 일반 포인터로 소유권을 넘겨줌
	//CPtrTest* p = uptr2.release()
	//이후 uptr2는 사용할 수 없음. 접근 금지
	//swap - 두 포인터 교환 p1.swap(p2)
	cout << "-----9.4.4 weak_ptr-----" << endl;
	//shared_ptr가 가리키는 대상에 참조 형식으로 포인팅 할 수 있음. 참조만 가능해서, 카운팅 숫자가 늘거나 줄지 않음.
	//포인팅만하고 객체를 참조할 수 없음. 참조하려고 하면 shared_ptr로 변환시켜야해서 잘 쓰지 않음.
	cout << endl;

	cout << "====번외 - 가변 길이 템플릿====" << endl;
	return 0;
}