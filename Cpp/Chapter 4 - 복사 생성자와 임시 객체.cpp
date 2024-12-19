#include <iostream>

using namespace std;
class CMyData4{
	int m_nData = 0;
public:
	CMyData4() { cout << "CMyData4()" << endl; }
	CMyData4(int nParam):m_nData(nParam){ cout << "CMyData4(int)" << endl; }
	//���� ������: ��ü�� ���纻�� �����Ҷ� ȣ��Ǵ� ������.
	//Ŭ���� ���ο��� �޸𸮸� �������� �Ҵ��ϰ� �����ϰ�, �̸� ������ ������ ������ ������ ����������.
	CMyData4(const CMyData4& rhs) 
	//:m_nData(rhs.m_nData)
	{
		this->m_nData = rhs.m_nData; //�����ϱ� ���ϰ� this ���.
		cout << "CMyData4(const CMyData4&)" << endl;
	}
	void SetData(int param) { m_nData=param; }
	int GetData() const { return m_nData; }
};
//���� �����ڰ� ȣ��Ǵ� ���
//1. ��������� ��ü�� ���纻�� ����. (CTest a;)
//2. �Լ� ���·� ȣ�� (TestFunc(a))
//2-1. Ŭ������ �Ű������� Ȱ���. 2-2. ��ȯ �������� ����. -> ���� ������ �ֱ� ������ �߿���. (Ư�� return ���� ��)

void TestFunc(CMyData4 param) {
	cout << "TestFunc()" << endl;
	param.SetData(20);
}

void TestFunc2(CMyData4 &param) {
	cout << "TestFunc()" << endl;
	param.SetData(20); //const CMyData4 &param�̾����� �� ���� ����� �۵����� ����.
}

class ShallowCopy {
	int* m_pnData = nullptr;
public:
	ShallowCopy(int nParam) {
		m_pnData = new int;
		*m_pnData = nParam;
	}
	~ShallowCopy() { //�Ҹ�� �������� �޸� ����
		delete m_pnData;
	}
	ShallowCopy(const ShallowCopy& rhs) {
		cout << "ShallowCopy(const ShallowCopy&)" << endl;
		m_pnData = new int; //�޸� �Ҵ� ��
		*m_pnData = *rhs.m_pnData; //�����Ͱ� ����Ű�� ���� �����ؾ� ���� ���簡 �ϼ���.
	}
	ShallowCopy& operator=(const ShallowCopy& rhs) {
		*m_pnData = *rhs.m_pnData;
		return *this; //������ *this�� return �ؾ���.
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
	//��ȯ ������. ������ ��ȯ ������ ���� ���� explicit Ű���� ���.
	explicit ConversionTest(int nParam) :m_nData(nParam) {
		cout << "ConversionTest(int)" << endl;
	}
	operator int(void) { return m_nData; } //Ŭ������ int�� ��ȯ�ϴ� ��� ����.
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
		cout << "CTestData(const CTestData&): " << m_pszName << endl; //const ����� ����
	}
	CTestData& operator=(const CTestData& rhs) {
		cout << "operator=" << endl;
		//���� ����, �̸��� �״��.
		m_nData = rhs.m_nData;
		return *this;
	}
	int GetData() const { return m_nData; }
	void SetData(int nParam) { m_nData = nParam; }
};
//�ڵ� ����: char* m_pszName�� const char* m_pszName���� �ٲٸ� �� �۵��Ѵ�.
//���ڿ� ����� �����Ҷ��� �� �տ� const�� �ٿ�����.

CTestData TestFunc3(int nParam) {
	//testa�� ���������̱� ������ �Լ��� ��ȯ�Ǹ� �Ҹ��.
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
	//���� ������
	MoveSemantics(const MoveSemantics& rhs):m_nData(rhs.m_nData){ cout << "MoveSemantics(const MoveSemantics&)" << endl; }
	//�̵� ������ (const �Ȼ����. rvalue �����ϱ�.)
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
	cout << "====4.1 ���� ������====!" << endl;
	CMyData4 a;
	a.SetData(10);
	CMyData4 b(a); //���� ������ ȣ��
	cout << b.GetData() << endl;
	cout << endl;
	cout << "-----4.1.1 �Լ� ȣ��� ���� ������-----" << endl;
	CMyData4 x(10);
	TestFunc(x); //���� ���Ѻ��� TestFunc�� ������ �� ���� �����ڰ� ȣ���. param�� a�� �������� �� ���纻��. -> ���α׷� ���� ����.
	//�����ڸ� �̿��ϸ� ���� �������� ������ ���� �� ����.
	cout << "x: " << x.GetData() << endl;
	CMyData4 y(10);
	TestFunc2(y); //���� ������ ���� �ȵ�.
	cout << "y: " << y.GetData() << endl;
	//�ٸ� �� 46�� ���� ������ �Լ��� ������ ���� ȣ���� �ϴ���, ���� ���� ȣ���� �ϴ��� �� �� ����.
	//�˾ƾ� �ϴ� ���� -> �Լ��� ���μ��� ����� ������ �Լ� ȣ��� ���� ���� ���� �� �ֱ� ����. �׷��� �ϴ� Ŭ���� ������ �Ű������� ����� ������ �����ؾ���.
	//��¿�� ���� ���� �����ؾ� �ϴ� ���� ����. �̷��� �Լ� ������ �Ű����� �ν��Ͻ��� ���� ������ �� ����.
	cout << endl;

	cout << "-----4.1.2 ���� ����� ���� ����-----" << endl;
	//���� ����� ���� ����.
	//���� ����: ���� �ϳ����ε�, �����Ͱ� 2���ΰ� (���̽㿡�� �迭 �������� ���� ���ϸ� �̷��� ��.)
	int* pa, * pb;
	pa = new int;
	*pa = 10;
	pb = new int;
	pb = pa;
	delete pa; //�޸𸮸� ����µ�...
	//delete pb; //���� �߻�! pa�� pb�� ���� ���� ����Ű�� ������ �̹� �ѹ� ���� �޸� �ּҸ� �ٽ� �ѹ� ���� �� ��� ������ �߻���.
	//*pb = *pa; //�̷� ���̸� ���� �ذ��. �����Ͱ� ������ �ִ� �޸��� ������ ����Ǳ� ������.

	ShallowCopy sh(10);
	ShallowCopy shh(sh); //�����δ� �ƹ� �̻��� ������, �����δ� �޸𸮸� �������� �ʰ� ������� ������ ������ �߻��� ����. ���� ���縦 ���� �ʾƼ���.
	//�׷��� ���� �޸� ���ﶧ ���� ���� ���� �߻��� �� ����.
	//���� ��ġ���� ���� �����ڰ� ���� ���縦 �� �� �ֵ��� ������ ��. 45�� �ڵ� ����.
	cout << sh.GetData() << endl;
	cout << shh.GetData() << endl;
	cout << endl;
	
	cout << "-----4.1.3 ���� ������-----" << endl;
	//�ܼ� ���� ������ = �� Ŭ������ ����ü���� �����.
	//������ = �����ڴ� ���� ���縦 �����ϱ� ������ Ŭ������ ������ �� ������ �߻��� �� ����.
	//�ڼ��Ѱ� ���Ŀ� �����ϰ�����, �ذ� ����� �ڵ带 �����ϸ� ��.
	ShallowCopy s(10);
	ShallowCopy t(20);
	s = t;
	cout << s.GetData() << endl;
	cout << endl;

	cout << "====4.2 ������ ��ȯ====!" << endl;
	cout << "-----4.2.1 ��ȯ ������-----" << endl;
	//��ȯ ������: �Ű������� �Ѱ��� ������.
	//��ȯ �����ڰ� ���ٽ�½ ȣ��Ǿ�, ���ʿ��� �ӽ� ��ü�� ����� ���α׷��� ������ ���Ͻ�ų �� ����.
	//TestConversion(19); //�Ű������� �ϳ��� �� ��ȯ�� �����ϱ� ������ int �ڷ����� ConversionTest �������� ��ȯ�Ǿ� ������.
	//������ �Ű����� ������ �ȸ¾� ������ �ȵǾ�� ������, ��ȯ �����ڰ� �־ �Լ��� ȣ���.
	//TestConversion2(21); //������ ������ �ٿ��� �˾Ƽ� �ӽ� ��ü�� �����ؼ�, �� �ӽ� ��ü�� ���� ������ TC2 �Լ��� �Ѿ��.
	//�ӽ� ��ü�� �Լ��� ���� ��ȯ�� ���ÿ� �Ҹ�Ǹ�, TestConversion2(ConversionTest(21))�� ���� ȿ���� ������ ����.
	//������ ��ü�� ������� ���Ǽ��� �����ֱ� ������ ���ֵ� ���������, ��ü�� �Ը� ũ�ٸ� ȣ��� ���ɼ��� �����ϴ� ���� �ٶ�����.
	//explicit Ű���带 ����ؼ� ���� TestConversion �Լ��� �۵��� ����.
	cout << endl;

	cout << "-----4.2.2 ���Ǵ� ��ȯ-----" << endl;
	//��ȯ ������: int�� Ŭ������ ��ȯ�ϴ� ��� �����ϴ� ����.
	//�׷��� Ŭ������ int�� �ٲٴ� ����� ��� ������ -> ����ȯ �����ڸ� ����� ���� �� ����.
	//ConversionTest Ŭ���� operator int(void) �κ� ����.
	ConversionTest aint(12);
	cout << aint.GetData() << endl;
	cout << aint << endl; //����ȯ ������ ���� ������ �߻����� �ʰ� int ���·� ��ȯ�Ǿ� ��µ�.
	cout << (int)aint << endl; //���� ����ȯ - C��� ��Ÿ��
	cout << static_cast<int>(aint) << endl; //C++ ��Ÿ��. ��� ����� const_cast�� ����. ���� ������ �ִµ� �̴� ���Ŀ� �ٷ�.
	//operator���� explicit Ű���带 ����� �� �ִµ�, �׷��� cout << aint << endl;������ ���������� ��ȯ�� �߱� ������ ������ �߻���.
	//explicit Ű���尡 ���Ǿ��ٸ� static_cast�� ����ؾ� ����ȯ�� ������.
	cout << endl;

	cout << "====4.3 �ӽ� ��ü�� �̵� �ø�ƽ====!" << endl;
	cout << "-----4.3.1 �̸� ���� �ӽ� ��ü-----" << endl;
	//�Լ��� ��ȯ ������ Ŭ������ ��� ������ ���� �� ����, ������ �ӽ� ��ü�� �����ȴ�.
	//�̸� ���� �ӽ� ��ü - �����ϴ� �ν��Ͻ����� �ĺ��ڰ� �ο����� ���� ��ü.
	CTestData testb(5, "testb"); //CTestData(int): b ���
	cout << "Before" << endl;
	testb = TestFunc3(10);
	//���� �����غ���
	//TF3 �Լ��� a Ŭ���� ���� -> �ܼ� ���� ���� ��� -> a��ü ���� �̷��� �Ǵµ�...
	//å������ �̸��� ���� �ӽ� ��ü�� ���� ������. (int a -> const CTestData& a -> ~CTestData a (����) -> operator= -> ~CTestData a)
	//�̸��� ���� �ӽ� ��ü�� ������ ��ü�� ���� ������ ���� ������.
	cout << "After" << endl;
	cout << testb.GetData() << endl;
	cout << TestFunc3(15).GetData() << endl;
	//�Լ��� ��ȯ�� �ӽ� ��ü�� ��� ���� ������ ����� �� ����. �̷��� Method ����� ���� �� testa Ŭ������ �Ҹ���.
	//�̸� ���� �ӽ� ��ü�� �������� �ʰ� �Ϸ��� Visual Studio ������Ʈ �Ӽ����� Release ���� �������ϸ� ��.
	//�����ڸ� �Ἥ �̸� ���� ��ü�� ������ ���� �� ����.
	const CTestData& rData = TestFunc3(22); //å���� const ���� ����������, ����� const�� �����.
	//const�� ���� �����ڴ� l-value�� ������ �� ����. (������ �����ϴٰ�...)
	cout << endl;

	cout << "-----4.3.2 r-value ����-----" << endl;
	//������ �ƴ� ��� ������ �� �� ��������, r-value�� ���� �����ڰ� ���Ӱ� ������.
	//&&�� ����ؼ� ǥ���� �� ����.
	int&& data = 3 + 4;
	cout << data << endl;
	data++; //����� ���� �����ε��� ���� ������ ������.
	cout << data << endl;
	//rvalueTestFunc(3 + 4); �̰� �۵� �ȵ�. int�� int &�� �ٲ� �� ���� ����.
	rvalueTestFuncFixed(3 + 4); //�̰� �Ű����� ������ int &&�� �۵���.
	//���� �߿�! rvalue ������ ���꿡 ���� ������ �ӽ� ��ü�� �����ϴ� ��.
	//������ ����� ���ص� int �ڷ��� ����� �Ǳ� ������ rvalue ������ ������.
	int num = 4;
	rvalueTestFuncFixed(num+4);
	rvalueTestFuncFixed(3);
	rvalueTestFuncFixed(3+4);
	//rvalueTestFuncFixed(num); �̰� �ȵ�.
	//���� C++������ �Լ��� �Ű������� int, int&, int&& �� �������� ���� �����ϰ� �����ؾ���.
	//�翬�� �Լ� �������Ƿ� ��ȣ���� �߻��� �� �ִ�.
	//void rvalueTestFuncFixed(int rParam) {
	//	cout << "TestFunc(int &)" << endl;
	//}
	//�̷� �Լ��� ������ rvalueTestFuncFixed(3+4)�� ���� ��ȣ���� �߻��Ѵ�.
	//rvalue������ Ŭ������ ����� �� ������ ���ֵ�. ���� ������ ���� ���Ǹ� ��� �� ����.
	cout << endl;

	cout << "-----4.3.3 �̵� �ø�ƽ-----" << endl;
	//�̵� ������ - �̸� ���� �ӽ� ��ü�� �����ɶ� ���ϸ� �ּ�ȭ��Ű�� ���� ����ϴ� ������.
	//�ӽ� ��ü�� ������ �� ���� ��� �̵� �����ڸ� ����ϴµ�, �̶� ���� ���縦 ����ϱ� ������ �޸𸮸� �� �����.
	MoveSemantics sem;
	cout << "Before" << endl;
	sem = TestSemantics(25);
	cout << "After" << endl;
	MoveSemantics sem2(sem);
	//�� ���� �����Ϸ��� ������Ʈ �Ȱ��� å�� �ٸ� ����� ����ȴ�...
	return 0;
}