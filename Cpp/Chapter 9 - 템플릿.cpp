#include <iostream>
#include <memory> //shared_ptr�� ����Ϸ��� include �ؾ���.

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

//���������� �޸𸮸� �ڵ� ���� �Ҵ� �� �����ϸ� ���� �����ڿ� �̵� �ø�ƽ�� ������
//���� ��ҿ� �迭 �����ڷ� ���� ����
template<typename T>
class CMyArray {
private:
	int m_nSize = 0;
	T* m_pData = nullptr;
public:
	explicit CMyArray(int nSize) :m_nSize(nSize) {
		m_pData = new T[nSize];
	}
	~CMyArray() { delete[] m_pData; }//delete[]�� ����ؾ���.
	//���� ������
	CMyArray(const CMyArray& rhs) {
		m_pData = new T[rhs.GetSize()];
		memcpy(m_pData, rhs.m_pData, sizeof(T) * (rhs.m_nSize));
		m_nSize = rhs.m_nSize;
	}
	//���� ������
	CMyArray& operator=(const CMyArray& rhs) {
		if (this == &rhs) return *this; //�ּҰ� ���ƾ���! this�� �ø��� �ѹ��ϱ�.
		delete[]m_pData; //���� �������� �迭�� ũ�Ⱑ �޶� ������ ������ �ʴ´�.
		m_pData = new T[rhs.GetSize()];
		memcpy(m_pData, rhs.m_pData, sizeof(T) * (rhs.m_nSize));
		m_nSize = rhs.m_nSize;
		return *this; 
	}
	//�̵� ������ (���� ����)
	CMyArray(const CMyArray&& rhs) {
		operator=(rhs);
	}
	//�̵� ���� ������ (���� ����)
	CMyArray& operator=(const CMyArray&& rhs) {
		//�����ϱ� ���� �Ҵ� ���ص� ��.
		m_pData = rhs.m_pData;
		m_nSize = rhs.m_nSize;
		rhs.m_pData = nullptr;
		rhs.m_nSize = 0;
	}
	//�迭 ������
	T& operator[](int nparam) {
		if (nparam < 0 || nparam >= m_nSize) {
			cout << "ERROR: �迭�� ��迡 ��� �����Դϴ�." << endl;
			exit(1);
		}
		else
			return m_pData[nparam];
	}
	//���ȭ�� �迭 ������
	T operator[](int nparam) const {
		return operator[](nparam);
	}
	//�迭 ����� ������ ��ȯ
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

//���ڿ��� ��� �ٸ���
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
	int GetData() const { return this->m_Data; } //protected �����Ҷ� this-> ������ ����ϱ�.
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

//...���� ������ Ÿ���� ���� �� ����.
template<typename T, typename... Types>
void print(T arg, Types... args) {
	cout << arg << ", ";
	print(args...); //...�� �ٿ�����.
}

int main9() {
	cout << "====9.1 Ŭ���� ���ø�====" << endl;
	//Ŭ������ ���� Ʋ ���� ��. �ڷ����� ���� �ٸ��� Ŭ������ ���� Ʋ ���� ����.
	//�Լ� ���ø��� Ŭ������ Ȯ��� ��. �Լ� ���ø��� 2.2 ����
	CMyData9<int> a(5);
	cout << a << endl;
	CMyData9<const char*> c("Hello"); //���ڿ��� �������� ���������� �ʴ´�.
	cout << c << endl;
	//���� - � �����̵� �迭�� ������ �� ���� (std::vector �����ǰ�?)
	CMyArray<int> arr(5);
	for (int i = 0; i < 5; i++) {
		arr[i] = 10 * (i + 1);
	}
	CMyArray<int> arr2(3);
	arr2 = arr;
	for (int i = 0; i < 5; i++) {
		cout << arr2[i] << "\n";
	}
	cout << "-----9.1.1 ��� ���� �� ����-----" << endl;
	//�ʿ��ϴٸ� Ŭ���� ���ø������� ����� ���Ǹ� �и��� �� ������ ���� ����� ���Խ�Ű�� �͵� �����ϴ�.
	//�ٸ� �и��Ǹ� ����� ������ template<typename T>�� �����ؾ���.
	CTest9<double> d;
	cout << d.TestFunc() << endl;
	//����� ���Ǹ� Ŭ���� ������ ������ CTest9<T>ó�� �̸� ������ ������ ����ؾ���.
	cout << endl;
	cout << "-----9.1.2 ���ø� �Ű�����-----" << endl;
	//Template<typename T,typename U> ������.
	//Template<typename T,int nSize>�� ���� ������ ��ü������ �ۼ��� �� ����.
	//�迭�� ������ �Է¹޾Ҵµ� �̶� CMyArray<int> arr(5)�� �ƴ϶�
	//CMyArray<int,5> a; �̷� ������ ����� �� �ִ�.
	//���ø� �Ű������� �⺻���� ������ �� �ִ�.
	//template<typename T = int, int nSize=3>
	//�ڷ����� ����Ʈ��, �ٸ� �Ű������� ����Ʈ���� ���� ������ ������.
	cout << endl;

	cout << "====9.2 ���ø� Ư��ȭ====" << endl;
	cout << "-----9.2.1 �Լ� ���ø� Ư��ȭ-----" << endl;
	//���ø��� ���� ��Ȥ �����Ϳ� ���� Ư���� ������ ���� ��� ���� �ٸ� �ڵ带 �ۼ��ؾ� �� ���� ����
	//�̶��� template<>�� ���� ǥ���� ����ؼ� Ư��ȭ�� ��Ŵ. Add �Լ� ���� ����.
	int Result = Add<int>(3, 4);
	cout << Result << endl;
	const char* pszResult = Add<const char*>("Hello", "World");
	cout << pszResult << endl;
	delete[] pszResult;
	//Ư�� ������ �������� ���� �������״� ������ �������� ����� ���� �����Ϸ����� ����.
	cout << endl;
	cout << "-----9.2.2 Ŭ���� ���ø� Ư��ȭ-----" << endl;
	//Ŭ���� ���ø��� �Լ��� ������ ������� Ư��ȭ�� �� �ִ�.
	CTemplateTest<const char*> aa("Hello");
	cout << aa.GetData() << endl;
	cout << endl;

	cout << "====9.3 Ŭ���� ���ø��� ���====" << endl;
	//�Ϲ� Ŭ���� ��Ӱ� �Ȱ���. �׳� ���ø��� �߰��� ��. ���� ����.
	CInheritEx<int> inh;
	inh.SetData(50);
	cout << inh.GetData() << endl;
	cout << endl;

	cout << "====9.4 ����Ʈ ������====" << endl;
	//�����Ҵ��� �ν��Ͻ��� �ڵ����� �������ִ� ������. �������� ��쿡 ���󼭴� ������ �ذ� �� �� ����
	//auto_ptr, shared_ptr, unique_ptr, weak_ptr�� ����.
	//��� ���ø����� �����Ǿ� ����.
	cout << "-----9.4.1 auto_ptr-----" << endl;
	//���� �������� �����ߴ� ����Ʈ �������ε� ������ ���� ������ ������� ����.
	//���� ���� ������ �ְ�, �迭�� �������� ����.
	cout << "BEGIN" << endl;
	{
		auto_ptr<CPtrTest> ptrTest(new CPtrTest); //�ش� ���������� �����ϰ� �Ҹ�ǰ� �����ϱ� ���ؼ� {} �����.
	}
	cout << "END" << endl;
	//�迭 ���� ������ = �迭�� ������ ���� �ʾ� �޸𸮸� �����Ҷ� ������ �߻���.
	//auto_ptr<CPtrTest> ptrTest2(new CPtrTest[3]); //�޸� ���� �� ���� �߻�
	//���� ���縦 �� �� �߻��ϴ� ������
	auto_ptr<CPtrTest> ptrTest2(new CPtrTest);
	auto_ptr<CPtrTest> ptrNew;
	cout << ptrTest2.get() << endl; //�޸� �ּҰ� �ҷ����� �Լ�.
	ptrNew = ptrTest2; //�ܼ� ���� ���� �� ���� �����Ͱ� ����Ű�� �ּҰ� NULL�� �Ǿ����.
	//cout << ptrTest2.get() << endl;
	//ptrTest2->TestFunc(); //�׷��� �� �ڵ尡 ������ �ȵ�.
	//ptrTest2�� �ڽ��� ����Ű�� CPtrTest�� ���� ptrNew�� �������ְ�, �ڱ� �ڽ��� NULL�� �ʱ�ȭ�ع���
	//��ǻ� ���簡 �ƴ� �̵��� �߻��Ѵٴ� ������ ����.
	//�׷��� ���� ����� shared_ptr
	cout << endl;

	cout << "-----9.4.2 shared_ptr-----" << endl;
	//#include <memory> //shared_ptr�� ����Ϸ��� include �ؾ���.
	//auto_ptr�ʹ� �޸� �������� �� Ƚ���� ����ؼ� 0�̵Ǹ� ����� ������.
	//���� ��� 2���� �����Ͱ� �� ��ü�� ����Ű�� ī��Ʈ ���� 2�� �ǰ�, �� �����Ͱ� �Ҹ��ϴ��� �� ��ü�� �Ҹ����� ����.
	cout << "BEGIN" << endl;
	shared_ptr<CPtrTest> ptr1(new CPtrTest);
	cout << "Counter " << ptr1.use_count() << endl; //use_count ������ �� Ƚ�� ���ִ� �޼���.
	{
		shared_ptr<CPtrTest> ptr2(ptr1); //�Ȱ��� �� ����Ű�� ptr2
		//���� �ϰ� ���߿� ptr2=ptr1���� �ص� ������ ����. auto_ptró�� ptr1�� NULL�� �ٲ�� ���� �߻����� �ʱ� �����̴�.
		cout << "Counter " << ptr2.use_count() << endl;
		ptr2->TestFunc();
	}
	cout << "Counter " << ptr1.use_count() << endl; //ī���� �� 1 ����
	ptr1->TestFunc();
	cout << "END" << endl; //���� ���α׷� ���� �� ��ü �Ҹ��Ŵ.
	//�迭�� ��ü�� delete�� �� �ִ� ����� �����ϴµ�, �� ���� �Լ��� �����ڰ� ���� ������ �Ѵ�.
	shared_ptr<CPtrTest> ptr3(new CPtrTest[5], PtrRemoveTest); //�Ҹ��� �Լ��� ������ �����.
	ptr3.reset(); //���Ѵٸ� ����� �����ؼ� ���� ������ �� ����. - reset �޼���.
	cout << endl;

	cout << "-----9.4.3 unique_ptr-----" << endl;
	//share_pointer�ϰ� ���������� use_count()�� ���� 1�θ� �����ϰ� ��. �� ����� �� �����ͷθ� ����ų �� ����.
	//�� �����ͷ� �̵��� ����������, ����� �ȵ�.
	unique_ptr<CPtrTest> uptr(new CPtrTest);
	unique_ptr<CPtrTest> uptr2 = move(uptr); //�̰� ���� - ������ ������.
	//uptr2 = uptr; //���� �߻�. ������ �Ұ���.
	//���ʿ� ���� �����Ͱ� �� ����� ����ų ��츦 ������ �� ����. ���� ���� ���簡 �Ͼ ���ɼ��� �����ϴ� ����.	
	
	//����Ʈ ������ ���� �޼���
	//get - �ּ� ��ȯ, use_count - ī���� �� ��ȯ, reset - �޸� ����/����� ���� ����
	//release - �Ϲ� �����ͷ� �������� �Ѱ���
	//CPtrTest* p = uptr2.release()
	//���� uptr2�� ����� �� ����. ���� ����
	//swap - �� ������ ��ȯ p1.swap(p2)
	cout << "-----9.4.4 weak_ptr-----" << endl;
	//shared_ptr�� ����Ű�� ��� ���� �������� ������ �� �� ����. ������ �����ؼ�, ī���� ���ڰ� �ðų� ���� ����.
	//�����ø��ϰ� ��ü�� ������ �� ����. �����Ϸ��� �ϸ� shared_ptr�� ��ȯ���Ѿ��ؼ� �� ���� ����.
	cout << endl;

	cout << "====���� - ���� ���� ���ø�====" << endl;
	return 0;
}