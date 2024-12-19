#include <iostream>

using namespace std;

class CMyData7 {
protected:
	int m_nData = 10;
public:
	virtual ~CMyData7(){
	}
	virtual void PrintData() {
		cout << "CMyData7: " << m_nData << endl;
	}
	void TestFunc() {
		cout << "***TestFunc()***" << endl;
		PrintData(); //PrintData�� virtual �޼����̱� ������ ������ �ڵ尡 �̷��� �ڵ带 �θ��� ������ �ȴ�!
		//!!���� �Լ��� �����ǵ� �̷��� �ڵ带 ȣ���Ѵ�!!
		cout << "****************" << endl;
	}
	void SetData(int nparam) { m_nData = nparam; }
	int GetData() const { return m_nData; }
};

class CMyData7Ex :public CMyData7 {
public:
	//�����Լ� ��� ������: ���� ���Ǵ� override�Ǿ� ���õ�.
	virtual void PrintData() {
		cout << "CMyData7Ex: " << m_nData*2 << endl;
	}
	void SetData(int nparam) {
		if (nparam > 10) nparam = 10;
		CMyData7::SetData(nparam);
	}
	void PrintData2() {//7.4�� �� �뵵
		cout << "CMyData7Ex: " << GetData() << endl;
	}
};

class CMyDataptr {
private:
	char* m_pszData;
public:
	CMyDataptr() { m_pszData = new char[32]; }
	//�Ҹ��ڸ� ���� �Լ��� �����ϱ�
	virtual ~CMyDataptr() {
		cout << "~CMyDataptr()" << endl;
		delete m_pszData;
	}
};

class CMyDataptrEx : public CMyDataptr {
private:
	int* m_pnData;
public:
	CMyDataptrEx() { m_pnData = new int; }
	~CMyDataptrEx() {
		cout << "~CMyDataptrEx()" << endl;
		delete m_pnData;
	}
};

class vtable {
public:
	vtable() {
		cout << "vtable()" << endl;
	}
	virtual ~vtable() {}
	virtual void TestFunc1() {}
	virtual void TestFunc2() {}
};

class vtableEx : public vtable {
public:
	vtableEx() {
		cout << "vtableEx()" << endl;
	}
	virtual ~vtableEx() {}
	virtual void TestFunc1() {}
	virtual void TestFunc2() { cout << "TestFunc2()" << endl; }
};

void bindTest1(int nParam){}
void bindTest2(int nParam){}

class CMyInterface {
public:
	CMyInterface() {
		cout << "CMyInterface()" << endl;
	}
	//���� �ְ� ���Ǵ� ���� ���������Լ�.
	virtual int GetData() const = 0;
	virtual void SetData(int nparam) = 0;
};

class CMyInterfaceEx : public CMyInterface {
private:
	int m_nData = 0;
public:
	CMyInterfaceEx() {
		cout << "CMyInterfaceEx()" << endl;
	}
	//�ڽ� Ŭ������ �θ� ���� ���� Ŭ������ ���� ���� �Լ��� �ݵ�� �����ؾ���.
	virtual int GetData() const {
		return m_nData;
	}
	virtual void SetData(int nparam) {
		m_nData = nparam;
	}
};
//�ʱ� �������� �ڵ�
class CMyObject {
public:
	CMyObject(){}
	virtual ~CMyObject(){}
	virtual int GetDeviceID() = 0;//���߿� ��� �Ļ� Ŭ������ �� �޼��带 ���� ������ Ȯ���� �� ����.

protected:
	int m_nDeviceID=NULL;
};

void PrintID(CMyObject* pObj) {//� ��ġ������ ������, ��ǰ ID�� �ϰ��ǰ� ����� �� ����. ���� ���� Ŭ�������п�.
	//��ӵ� Ŭ������ �� �̿��� �� �ְ�, �Ϻη� CMyObject*�� �Ű������� ������.
	//virtual �Լ��� ���ǵǾ� �ֱ� ������ ������ �������� ����.
	cout << "Device ID: " << pObj->GetDeviceID() << endl;
}

//�ı� �������� �ڵ�
class CMyTV :public CMyObject {
public:
	CMyTV(int nID) { m_nDeviceID = nID; }
	virtual int GetDeviceID() {
		cout << "CMyTV::GetDeviceID()" << endl;
		return m_nDeviceID;
	}
};

class CMyPhone :public CMyObject {
public:
	CMyPhone(int nID) { m_nDeviceID = nID; }
	virtual int GetDeviceID() {
		cout << "CMyPhone::GetDeviceID()" << endl;
		return m_nDeviceID;
	}
};
//�̷��� � ��� class�� ����� PrintID �޼��带 ������ �� �ֵ��� ���� �� ����.

class COperatorTest {
protected:
	int m_nData = 0;
public:
	COperatorTest(int nParam):m_nData(nParam){}
	COperatorTest operator+(const COperatorTest& rhs) {
		return COperatorTest(m_nData + rhs.m_nData);
	}
	COperatorTest& operator=(const COperatorTest& rhs) {
		m_nData = rhs.m_nData;
		return *this;
	}
	operator int() { return m_nData; }
};

class COperatorTestEx :public COperatorTest {
public:
	COperatorTestEx(int nParam):COperatorTest(nParam){}
	//�ذ� ��� 1.
	//COperatorTestEx operator+(const COperatorTestEx& rhs) {
	//	//����ȯ ��밡��
	//	return COperatorTestEx(static_cast<int>(COperatorTest::operator+(rhs)));
	//}
	//�ذ� ��� 2
	using COperatorTest::operator+;
	using COperatorTest::operator=;
};

class CMyObject2 {
public:
	CMyObject2() {
		cout << "CMyObject()" << endl;
	}
	virtual ~CMyObject2(){}
};

class CMyImage:virtual public CMyObject2 {
protected:
	int m_nHeight;
	int m_nWidth;
public:
	CMyImage(int nHeight, int nWidth) :m_nHeight(nHeight), m_nWidth(nWidth) {
		cout << "CMyImage(int,int)" << endl;
	}
	int GetHeight() const { return m_nHeight; }
	int GetWidth() const { return m_nWidth; }
	int GetSize() const { return m_nHeight* m_nWidth; }
};

class CMyShape: virtual public CMyObject2{
protected:
	int m_nType;
public:
	CMyShape(int nType) :m_nType(nType) {
		cout << "CMyShape(int)" << endl;
	}
	int GetType() const { return m_nType; }
	int GetSize() const { return 1; }
};

class CMyPicture : public CMyImage, public CMyShape {
public:
	CMyPicture() :CMyImage(10, 20), CMyShape(1) {
		cout << "CMyPicture()" << endl;
	}
};

class CMyUSB {
public:
	virtual int GetUSBVersion() = 0;
	virtual int GetTransferRate() = 0;
};

class CMySerial {
public:
	virtual int GetSerial() = 0;
	virtual int GetRate() = 0;
};

class CMyDevice : public CMyUSB, public CMySerial {
public:
	virtual int GetUSBVersion() { return 45; }
	virtual int GetTransferRate() { return 2; }
	virtual int GetSerial() { return 12312322; }
	virtual int GetRate() { return 9; }
};

int main7() {
	cout << "====7.1 �����Լ�====" << endl;
	cout << "-----7.1.1 �⺻ ����-----" << endl;
	//���� �Լ�: virtual Ű���� ���. �Ļ� ���Ŀ��� �޼��带 �������ϸ� ������ ���ǰ� ������ ���õ�.
	CMyData7Ex a;
	a.PrintData();
	CMyData7& b = a;
	b.PrintData(); //virtual �޼���� �� ���Ŀ� ���ǵǾ��ִ� PrintData �Լ��� ȣ���Ѵ�.
	a.TestFunc(); //TestFunc�ȿ� �ִ� PrintData�� CMyData7Ex::PrintData()�� ȣ���Ѵ�.
	//�Ϲ� �޼���� ���� ������ ������, ���� �޼���� �� ������ ������.
	//�Ļ� Ŭ�������� ���� �Լ��� ���������� ���ϰ�
	//virtual void PrintData() final;
	//�� ���� final Ű���带 ����ؼ� �����Ǹ� ������ �� ����.
	cout << endl;
	cout << "-----7.1.3 �Ҹ��� ����ȭ-----" << endl;
	CMyDataptr* pData = new CMyDataptrEx; //������
	delete pData; //���� ������ �Ҹ��ڸ� ȣ��ǰ�, �� ������ �Ҹ��ڰ� ȣ����� �ʾ� �������� �޸� ���� ������ �߻���.
	//�����ϰ� �ذ� - �Ҹ����� ����ȭ.
	//�θ� Ŭ������ �Ҹ��ڰ� ����ȭ�Ǹ�, �ڽ� Ŭ������ ���� �Լ� ������ ���� �ʾƵ� �ڵ����� ����ȭ�� �ȴ�.
	cout << endl;

	cout << "====7.2 ���� �Լ� ���̺�====" << endl;
	//vtable - �Լ� ������ �迭
	vtable* vp = new vtableEx;
	vp->TestFunc2();
	delete vp;
	//�� �����ڿ� �극��ũ ����Ʈ �ɰ� ������ϸ� VS2022 ȭ�� �ϴܿ� �ִ� ���ÿ� __vfptr��� ���� ����.
	//���� �Լ��� �ּҰ� ����ִ� �迭. �����Լ��� ����� ��� �Լ����� �ּҿ� �迭 ���·� ������ �� ����.
	//���� �Լ��� ����� ���� ��� Ŭ������ ���� �ڽŸ��� ������ �����Լ� ���̺��� ���µ�, �� ���̺��� __vfptr�� ����Ű�� ��.
	//���ε� - �Լ��� ������ �ּҰ� �����Ǵ� ��.
	//�̸� ���ε� - ������ Ÿ�ӿ� �����Ǵ� ��.
	//���� ���ε� - ���α׷��� ����Ǵ� ���߿� �����Ǵ� ��. �����Լ��� �̿� �ش���. -> ���� ���ε��̶�� �θ�.
	bindTest1(10); //����� �� �𽺾����â�� �Ѻ��� call bindTest1(�ּҰ�) �̷��� ��������. �̸� ���ε�.
	int nInput = 0;
	//cin >> nInput;
	void(*pfTest)(int) = NULL;
	if (nInput > 10) { pfTest = bindTest1; }
	else { pfTest = bindTest2; }
	pfTest(10); //�𽺾����â�� �Ѻ��� call qword ptr[pfTest]�� ���� Ȯ���Ǿ� ���� ����. ���� ���ε�.
	cout << endl;

	cout << "====7.3 ���� ���� Ŭ����====" << endl;
	//JAVA�� interface�� ���� ������ �� ����.
	//���� �����Լ��� ����� ���� Ŭ����
	//���� �̸� �س��� ������ ���߿� �ϴ°�. JAVA�� �߻� �޼���� ����.
	//����: virtual int GetData() const = 0; �ڿ� =0�� ����.
	//CMyInterface i; //���� ���� Ŭ������ �ν��Ͻ��� ���� �� ������ �� ����.
	CMyInterfaceEx ie;
	ie.SetData(5);
	cout << ie.GetData() << endl;
	cout << endl;
	cout << "-----7.3.1 �������̽� ���-----" << endl;
	//���� ���� Ŭ������ ����ϴ� ���� : �ٸ� ��ġ��� ��ȣ�ۿ��� ��, ��𼭵��� ����� �� �ֵ��� �������� �������̽��� ������ �� ����.
	//CMyObject ���� Ŭ���� ���� ����.
	CMyTV tv(12);
	CMyPhone phone(15);
	PrintID(&tv);
	PrintID(&phone);
	cout << endl;
	cout << "-----7.3.2 �߻� �ڷ����� ��� ��-----" << endl;
	//���� ������ �ʿ��� ������ switch-case ���̳� ���� if���� ����ϴ� ���� ��ȿ������.
	//�����οﶧ �̸� �����صθ�, ������ ó���ؾ� �� �� ������. -> ����� �Է��� ���� ��.
	//switch-case�� ���� ��쿡�� ����� �Է� ������ �����ϴ� ���� ����.
	// 
	cout << "AdtSample.cpp �ڵ� ����." << endl;
	//CalcFare()�Լ��� ���� �Լ��̱� ������ ��� �޾Ƶ� �� ������ �Լ��� ȣ���. switch-case���� ������� �ʰ�, ȿ������ ������ ����� �� ����.
	//���� ���� Ŭ������ ��쿡�� new ������ ����� �� ����!
	//�߻� �ڷ����� �̿��ϸ� ����� ���� �ƹ��� �þ��, �������̶� ������ ���� �������� ������ ������.
	cout << endl;

	cout << "====7.4 ��Ӱ� ����ȯ====" << endl;
	//C������ ���� ����ȯ ������ �� �ϳ��� ����������, C++���� �ſ� �پ��� ����� ������.
	//const_cast<int> - �̹� �����. ����� ������/�������� const�� ���ٶ� ����.
	int num=6;
	cout << "num: " << num << endl;
	const int& nparam = num;
	int& nNewparam = const_cast<int&>(nparam); //����� �������� ���� ���Ⱑ ��������.
	nNewparam = 7;
	cout << "num: " << num << endl;
	cout << endl;
	cout << "-----7.4.1 static_cast-----" << endl;
	//��� �����϶� �⺻ ������ �θ��� �������� ������ �� �� �ִµ�,
	//�⺻ ���� �����Ͱ� ����Ű�� ����� �ٽ� �Ļ� ���� �����ͷ� ����ȯ�ϴ� ���� ��ȯ�� ��Ӱ��迡���� ������.
	CMyData7* ppData = new CMyData7Ex; //�ڽĿ��� �θ�� ���������� ����ȯ
	CMyData7Ex* pNewData = NULL;
	ppData->SetData(15);
	pNewData = static_cast<CMyData7Ex*>(ppData); //�θ� Ŭ�������� �ڽ� Ŭ������ ����ȯ�� ����
	pNewData->PrintData2();
	delete ppData;
	//�ٵ� 230�� �ٿ��� CMyData7Ex�� CMyData7�� �ٲ㵵 static_cast ������ �������� �����.
	//�ڽ� Ŭ������ �θ� Ŭ���� �̿��� ��� ������ ������ �ְų�, �θ� Ŭ������ ��� �����͸� ȣ�������� �ʰ� �ֱ� ����.
	cout << endl;
	cout << "-----7.4.2 dynamic_cast-----" << endl;
	//�������� ������ ��ü�� ����Ű�� �����Ͱ� �⺻ ������ ���, ��ü������ � �ν��Ͻ����� Ȯ���Ҷ� �����.
	//�ٸ� ���������� ������ �Ǳ� ������ �ڵ尡 �߸� ����ǰ� �ִٴ� ��ȣ��� �� �� ����.
	//dynamic_cast�� ����ȯ�� �����ϸ� NULL�� ��ȯ�ϴµ�, �̸� ���� NULL���� �ƴ��� ���ǹ����� Ȯ���ϸ鼭 �ٸ� ��ȯ���� �ƴ��� Ȯ���� �� ����.
	//�̿� ���� ����� RTTI��� ��.
	//�ٸ�, ��κ��� ��쿡 switch-case���� RTTI�� ���� �Լ��� �߻� �ڷ����� ����ϴ� ������� ��ȯ�� �� �ֱ� ������ ������� �ʴ� ���� �ٶ�����.
	//reinterpret_cast - C���� ���Ǵ� ������ȯ�� ���� ������ ���� �� �ʿ� ����, �� �ʿ��ϴٸ� C��� ��Ÿ�Ϸ� �ص� ��.
	cout << endl;

	cout << "====7.5 ��Ӱ� ������ ���� ����====" << endl;
	//�Ļ� Ŭ�������� �⺻ Ŭ������ ���� �����ڸ� �״�� ���� ������ using �⺻Ŭ����::�⺻Ŭ���� �� ����ϸ� ������.
	//�⺻������ ��� �����ڴ� �Ļ� ���Ŀ� �ڵ������� ���ӵ�����, �ܼ� ���� �����ڴ� ������.
	COperatorTest aa(3), bb(4);
	cout << aa + bb << endl;
	COperatorTestEx cc(33), dd(44), ee(0);
	ee = cc + dd; //�Ϲ������δ� ���� �߻�. �ܼ� ������ ����� �ȵǱ� ����. �ٵ� ���� ������ �ص� ������ �ȸ¾Ƽ� ������ �ȵ�.
	//�ذ� ��� 1. �������� �����ڸ� �����. COperatorTestEx operator+(const COperatorTestEx& rhs)
	//�ذ� ��� 2. �˸��̴� �״�ΰ� ���ĸ� �ٲ� ��쿡�� using Ű���带 ����� �� �ִ�.
	cout << ee << endl;
	cout << endl;

	cout << "====7.6 ���� ���====" << endl;
	cout << "-----7.6.1 ���� ��Ӱ� ��ȣ��-----" << endl;
	//JAVA�� �߻�Ŭ������ Ŭ������ ���߻���� �ȵ�����, C++�� �����.
	//�ٸ�, �ڹٿ��� �����ϵ��� ��ȣ���� ��Ȯ�Ǽ��� ������Ű�� ������ �������̽� ���߻�� �ܿ��� �������� ����.
	//���߻���� �� Ŭ������ ��� ���� ������ �����.
	CMyPicture pic;
	cout << "Width: " << pic.GetWidth() << endl;
	cout << "Height: " << pic.GetHeight() << endl;
	cout << "Type: " << pic.GetType() << endl;
	//�� ���� Ŭ���� �޼��� ��ο� ������ �����ϴ�.
	//�� ���� Ŭ���� ��ο� GetSize()�޼��尡 �ִµ�, �̶��� �� �� ��� ������ Ư�����ָ� ����� �� �ִ�.
	cout << "Size: " << pic.CMyImage::GetSize() << endl;
	cout << endl;
	cout << "-----7.6.2 ���� ���-----" << endl;
	//���� CMyImage�� CMyShape�� ����� �θ�Ŭ���� CMyObject�� ������ �ִٸ�
	//CMyPicture Ŭ������ �����Ҷ� CMyObject Ŭ���� �����ڰ� 2���� �ȴ�.
	//���� ����� ����ϸ� �ذ��� �� �ִ�. ��� �ڵ带 �ۼ��� �� �Ļ� ���� Ŭ������ virtual Ű���带 �ۼ��ϸ� �ȴ�.
	//�ٸ� �� �θ� Ŭ�������� ���� �ֻ��� Ŭ������ ������� �����ϰ� �̷� ��Ȳ�� �Ǹ� ���� ���������Ƿ�, ���� ����� ������� �ʴ� ���� ����.
	//���� ����ϸ� �� �ڷ� �� �̻��� �Ļ� Ŭ������ ������ ���� ���� ����ϳ�, ��õ������ �ʴ´�.
	cout << endl;
	cout << "-----7.6.3 �������̽� ���� ���-----" << endl;
	//���� ����� ���� ������ ���.
	//�ڹٿ��� �������̽��� ~~able�� �̸��� ������ ��, ���� ������ Ȱ���ϵ���, C++������ �˸��̴� �ϳ��ε� Ȱ������ ���������� ��쿡 �����.
	//�ڹ��� �������̽��� �߻� �޼��常 ������ ��ó��, C++������ �������̽��� �����Ҷ��� ���� ���� Ŭ������ ������.
	//CMyUSB, CMyDevice, CMySerial Ŭ���� ����
	CMyDevice dev; //dev�� �� Ŭ������ ���� �������̽�/����� ��� ������.
	//�������̽����� Ȱ���� �� ���� �ڽ��� ȯ�濡 �´� �������� ��ü�� ������ �� ����.
	return 0;
}
