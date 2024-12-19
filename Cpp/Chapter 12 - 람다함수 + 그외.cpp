#include <iostream>
#include <string>
#include <vector>
#include <functional> //std::function ��ü�� ����ϱ� ���� ���

using namespace std;

int TestFunc(int nparam) {
	cout << "Function Pointer: " << nparam << endl;
	return nparam;
}

void TestFunc2(const char* pszParam, std::function<int(const char*, int)> param) { //int�� ��ȯ�ϴ� const char*, int�� �μ��� �޴� �Լ�.
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
	cout << "====12.2 ���ٽİ� �Լ� ��ü====" << endl;
	//���ٽ� - �̸� ���� �Լ�
	//[ĸó] mutable throw(�ʿ��� ��쿡��) (�Ű����� ����Ʈ) -> ��ȯ ���� {����;}
	auto func = [](int nparam) -> int {cout << "Lambda: " << nparam << endl; return nparam; };
	func(4);
	auto pfTest = TestFunc;//�Լ� ������ ȣ��
	pfTest(19);
	//[](int nparam) -> int �Ű������� int�ϳ��� ��ȯ���� int��� ��
	//�ʱ갪�� func�� �̸� ���� ȣ���� �� ����. ������ auto�� �ڵ����� ���ٽ��� ���� �� �ִ�.
	cout << "START" << endl;
	TestFunc2("TestFunc2()", [](const char* pszParam, int nParam)->int {cout << pszParam << " " << nParam << endl; return 0; });
	//�����Լ��� �� ��� ���� �μ��� �Լ��� ���� �� �ִ� std::function��ü�� �Լ��� ���� �� ������ ���� ����� �� �ִ�.
	cout << "END" << endl;
	cout << endl;
	cout << "-----12.2.2 �Լ� ��ü-----" << endl;
	//�Լ� ȣ�� �����ڸ� ���������� Ŭ����, � �����̵� �����ų �� �ִ� �Լ� ���ø��� �޸�, Ư�� ���ĸ� �����ϰ� �� �� �ִ�.
	//�ǵ������� ����� �ڵ带 �����ϰ� ���� �� ����ϸ�, Functor��� �θ���.
	Add adder;
	cout << adder(3, 4) << endl;
	cout << adder(3.3, 4.4) << endl;
	Add adder2;
	Adder(adder2); //Ŭ������ �Լ��� �Ű������� �ѱ������, ��ǻ� �Լ��� �Լ��� �Ű������� �ѱ� �Ͱ� ���� ȿ���� ����.
	//�翬�� �Լ� ��ü�� ����� ������. ���� - qsort() �����غ���
	CTestData data;
	CCmpDesc desc;
	CCmpAsce asce;
	data.Sort(desc);
	data.Print();
	data.Sort(asce);
	data.Print();
	//������ �ڵ尡 �ʹ� Ŀ���� ������ ���������ٴ� ����.
	cout << endl;
	cout << "-----12.2.3 ���ٽ����� �����ϱ�-----" << endl;
	//�Լ� ��ü�� ������ �����ؼ� ���°� ���ٽ���. �Ű������� �Լ� ��ü�� ���� �� �ְ� ����.
	CTestData data2;
	data2.SortLambda([](int a, int b)->int {return a - b; }); //������ �� ũ�� �ٲٴ°Ŵϱ� ��������
	data2.Print();
	data2.SortLambda([](int a, int b)->int {return b-a; }); //�������� �� ũ�� �ٲٴ°Ŵϱ� ��������
	data2.Print();
	//�̷��� �ϸ� �츮�� �����ߴ� Ŭ�������� �� �ʿ䰡 �������� ��.
	//������ �Լ� ��ü�� ������ �ʿ䰡 ���� ���ٽ� �ϳ��� �ذ��� ��������.
	cout << endl;
	cout << "-----12.2.4 ���� ĸó-----" << endl;
	//���ٽ� ���ο��� �ܺ� ������ ������ �� �ֵ��� ���ִ� ��. �츮�� �� []�� �� ������ �ϴ� �ſ���.
	//���� ĸó -> ����� ���� �̸��� []�ȿ� ���� ���� ��.
	//���� ĸó -> ����� ���� �̸��� ������ �������� []�ȿ� ���� ���� ��.
	//����Ʈ ���� ĸó -> �� ���� �� ��밡��(���� ���� ������ �̹� ����Ǿ���, �Ҹ����� ���� ��� ������)�ϰ� �ϱ�. [=]�� ����.
	//����Ʈ ���� ĸó -> ���� �� ������ ��� ����. [&]�� ����.
	int nData = 10;
	cout << nData << endl;
	auto func2 = [nData](void)->void {cout << nData << endl; };
	func2();
	//void�� ���� �����ϱ� ������, (void)->void�� (void), (), �ƴϸ� �׳� �ٷ� {}�� ������ ����.
	//���� ĸó�� ĸó �ȿ� ������ �������� ���� ���� ������, ���� ������ �� ����. ���� ĸó�� �����ؾ� ������.
	//�ٸ� ���� ĸó �� ���� �Լ� �ȿ� ���ؼ� ���� �����ϰ� �� ���� ����. -> mutable Ű���� ���.
	auto func3 = [nData](void) mutable->void {++nData;  cout << nData << endl; };
	func3(); //���⼭�� 11�� ��µȴ�.
	cout << nData << endl;
	//������ ������ �������� [x,y]�� ���� ������ ����� �� ������,
	//[&,z]�� ���� �ٸ��� �� ����Ʈ ���� ĸó�ε� z�� ���� ĸó�� �ϰڴٿ� ���� ������ ���� �ִ�.
	return 0;
}