#include <iostream>

using namespace std;

//�ʱ� �������� Ŭ����
class CMyData6 {
private:
	int m_nData = 0;
protected: //�Ļ� Ŭ���������� ���� ����
	void PrintData() { cout << "CMyData::PrintData()" << endl; }
public:
	//������ ���� ����
	CMyData6() { cout << "CMyData6()" << endl; }
	CMyData6(int nParam) :m_nData(nParam) { cout << "CMyData6(int)" << endl; }
	CMyData6(double dParam) :m_nData(dParam) { cout << "CMyData6(double)" << endl; }
	//����, ���� �޼���
	int GetData() const { return m_nData; }
	void SetData(int nparam) { m_nData = nparam; }
};

//�ı� �������� Ŭ����
//����� �⺻���� ���� : �������� ������ �θ�Ŭ���� �̸�.
class CMyData6Ex : public CMyData6 {
public:
	using CMyData6::CMyData6; //������ ���
	//CMyData6Ex() { cout << "CMyData6Ex()" << endl; }
	////�⺻ Ŭ������ 3���� ������ �� int�� ������
	//CMyData6Ex(int nParam) :CMyData6(nParam) { cout << "CMyData6Ex(int)" << endl; }
	////double �Է��ϸ� �⺻ ������ ȣ���ϱ�� ����.
	//CMyData6Ex(double dParam) :CMyData6() { cout << "CMyData6Ex(double)" << endl; }
	void TestFunc() {
		CMyData6::PrintData();
		CMyData6::SetData(5);
		cout << CMyData6::GetData() << endl; //�θ� Ŭ������ �޼ҵ忡 ����
	}
	void SetData(int nparam) { //���� �����ϴ� ����� �߰�. 
		//���� �޼���� �� �޼��带 ���� �۵��ϰ� �Ϸ��� �ǵ�. ��Ӱ� �������� ���� �������� ����.
		if (nparam < 0) { CMyData6::SetData(0); } //�Ļ� Ŭ�������� �⺻ ������ ������ �޼��带 ȣ���Ϸ��� �ϸ� �Ҽ� Ŭ������ ����ؾ���.
		if (nparam > 10) { CMyData6::SetData(10); }
	}
};

class CMyDataA {
protected:
	char* m_pszData;
public:
	CMyDataA() {
		cout << "CMyDataA()" << endl;
		m_pszData = new char[32];
	}
	~CMyDataA() {
		cout << "~CMyDataA()" << endl;
		delete m_pszData;
	}
};

class CMyDataB: public CMyDataA {
public:
	CMyDataB() {
		cout << "CMyDataB()" << endl;
	}
	~CMyDataB() {
		cout << "~CMyDataB()" << endl;
	}
};

class CMyDataC : public CMyDataB {
public:
	CMyDataC() {
		cout << "CMyDataC()" << endl;
	}
	~CMyDataC() {
		cout << "~CMyDataC()" << endl;
		//delete m_pszData; //�Ļ� Ŭ�������� �θ� Ŭ���� ��� �޸𸮸� ������ -> ���� �߻�!!
	}
};

int main6() {
	cout << "====6.1 ����̶�?====" << endl;
	cout << "-----6.1.1 �⺻ ����-----" << endl;
	//�Ļ� Ŭ������ �ν��Ͻ��� ������ �� �⺻ Ŭ������ �����ڵ� ȣ��ȴ�.
	//�Ļ� Ŭ������ �⺻ Ŭ������ ����� ������ �� �ִ�. ��, private ���� ���� �����ڷ� ����� ����� ���ؼ��� �ȵ�.
	//�Ļ� Ŭ������ �ν��Ͻ��� ���� �⺻ Ŭ���� �޼��带 ȣ���� �� �ִ�.
	CMyData6Ex data;
	//�⺻ Ŭ���� ����
	data.SetData(10);
	cout << data.GetData() << endl;
	//�Ļ� Ŭ���� ����
	data.TestFunc();
	//�Ļ� Ŭ������ �����ڰ� ���� ȣ�������, �����Ǳ� ���� �θ� Ŭ������ �����ڸ� ȣ���ϰ� ������ �� ��ȯ�Ѵ�.
	cout << endl;

	cout << "====6.2 �޼��� ������====" << endl;
	cout << "-----6.2.1 �⺻ ���� �� Ư¡-----" << endl;
	//������(override) - �ż��带 �������ϸ� ������ ���� ���õ�. ������ �͵� ����������, ���ٸ� ���� ���� ��� ���ο� ���� ��ü��.
	CMyData6 a;
	a.SetData(-10);
	cout << a.GetData() << endl;
	CMyData6Ex b;
	b.SetData(15);
	cout << b.GetData() << endl;
	b.CMyData6::SetData(-11); //����� ȣ���� ���� �θ� Ŭ������ �޼��带 ��� ����. ��, public�� ��쿡��.
	cout << endl;
	cout << "-----6.2.2 ���� ���İ� �� ����-----" << endl;
	CMyData6Ex c;
	CMyData6& rData = c; //�Ļ������� �⺻ �������� �����ϴ� ���� �ſ� �ڿ������� ��. �Ļ� ���ĵ� �⺻ ������ �� �����ϱ�.
	rData.SetData(15); // c - ���� ����, rData - ���� ����
	cout << rData.GetData() << endl; //�� ���İ� ���� ������ �ٸ� ��쿡�� ���� ������ �޼���� ȣ���.
	//���� ���� - ������ ����
	CMyData6* pData = new CMyData6Ex;
	pData->SetData(15);
	delete pData;//CMyData::SetData�� ȣ��Ǹ�, ��� �� �ڵ�� �޸� ���� ������ ������ ���Ŀ� �ٷ� ������.\
	//CMyData6Ex Ŭ������ ȣ����� �ʱ� ����.
	cout << endl;

	cout << "====6.3 ��ӿ����� �����ڿ� �Ҹ���====" << endl;
	cout << "-----6.3.1 ȣ�� ����-----" << endl;
	//C�� B�� ��ӹ޾Ұ�, B�� A�� ���Ŭ������� �� ��,
	//���� ���� ȣ��Ǵ� �����ڴ� C-B-A��������, ����Ǵ� ���� A-B-C�̴�.
	//�Ļ� Ŭ������ �⺻ Ŭ������ �����ڸ� �����ϰ� ȣ���Ѵ�.
	//�����ڰ� ���� ���ǵǾ��־ �ϳ��� �����ϰ� ȣ���Ѵ�.
	cout << "BEGIN" << endl;
	CMyDataC data2;
	cout << "END" << endl;
	//�Ļ� Ŭ������ �θ� Ŭ������ ��� ������ "���� ����" ������ ���� �ʴ� ���� �����̴�.
	//�Ļ� Ŭ���� �����ڿ��� �θ� Ŭ���� ��� ������ �ʱ�ȭ ���� �ʴ´�.
	//�����ڿ� �Ҹ��ڴ� ��ü �ڽ��� �ʱ�ȭ �� ������ �����ϴ� ���� �Ǵ�.
	cout << endl;
	cout << "-----6.3.2 ������ ����-----" << endl;
	//�Ļ� Ŭ������ �����ڴ� �ڽ��� ȣ��� �� �⺻ Ŭ������ ������ �� � ���� ȣ����� ������ �� ����.
	//���⼭ �����̶� ������ �ʱ�ȭ ��Ͽ� ���� Ŭ���� �����ڸ� ȣ���ϵ��� ����� �� �ִٴ� ����.
	CMyData6Ex aa;
	CMyData6Ex bb(5);
	CMyData6Ex cc(3.14);
	//������ ��� - �Ļ� Ŭ������ ���� ��, ���� ���ǵ� ���� Ŭ������ �޼��带 �״�� �������� ����.
	//using CMyData::CMyData; �� ���� ������� ����. C++11�� �߰��Ǿ�����, VS2015���� ������.
	return 0;
}