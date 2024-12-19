// AdtSample.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
#include <iostream>
using namespace std;

//�ʱ� ������
#define DEFAULT_FARE	1000
#define MAX 256

class CPerson
{
public:
	CPerson() {}
	virtual ~CPerson() {
		cout << "virtual ~CPerson()" << endl;
	}
	//��ݰ�� �������̽� (���� ���� �Լ�)
	virtual void CalcFare() = 0;

	virtual unsigned int GetFare() { return m_nFare; }
protected:
	unsigned int m_nFare = 0;
};

//�ʱ� Ȥ�� �ı� ������
class CBaby : public CPerson
{
public:
	//������(0~7��)
	virtual void CalcFare()	{
		m_nFare = 0;	//0%
	}
};

class CChild : public CPerson
{
public:
	//���(8~13��) ��ݰ��
	virtual void CalcFare()	{
		m_nFare = DEFAULT_FARE * 50 / 100;	//50%
	}
};

class CTeen : public CPerson
{
public:
	//���(14~19��) ��ݰ��
	virtual void CalcFare()	{
		m_nFare = DEFAULT_FARE * 75 / 100;	//75%
	}
};

class CAdult : public CPerson
{
public:
	//20�� �̻� ����
	virtual void CalcFare()	{
		m_nFare = DEFAULT_FARE;				//100%
	}
};
//����� �ڵ�
int main71(int argc, char* argv[])
{
	int nNumber;
	cin >> nNumber;
	//���ϴ� ��ŭ ����غ����� ������� ���ĺ�....
	CPerson* arList[MAX] = { 0 }; //���� ���� Ŭ������ new �����ڸ� Ȱ���� �� ��� ��� ������ �迭�� ������ �� ����.
	//�׷��� ���� for���� ����� �� ����.
	int nAge = 0;

	//1. �ڷ��Է�: ����� �Է¿� ���� ������ ��ü ����
	//for (auto &person : arList)
	int i = 0;
	for(i=0;i<nNumber;i++)
	{
		cout << "���̸� �Է��ϼ���: ";
		cin >> nAge; //�Է¹��� ���ϱ� ���� if���� �ᵵ ���ɿ� ������ ����.
		if (nAge < 8)
			arList[i] = new CBaby; //���� �Է¹ް� �ٷ� �迭�� ���Ӱ� �޸� �Ҵ�.
		else if (nAge < 14)
			arList[i] = new CChild;
		else if (nAge < 20)
			arList[i] = new CTeen;
		else
			arList[i] = new CAdult;
		//������ ��ü�� �´� ����� �ڵ����� ���ȴ�.
		arList[i]->CalcFare();
		//!!���� �߿��� �κ�!! ��� ����� ���� �迭�� ��������, �Է� �����鼭 �̸��̸� ����ϰ� ���߿� �ѹ��� ����� �� �ִ�.
	}

	//2. �ڷ����: ����� ����� Ȱ���ϴ� �κ�
	//for (auto person : arList)
	for(i=0;i<nNumber;i++)
		cout << arList[i]->GetFare() << "��" << endl;

	//3. �ڷ���� �� ����
	//����� �Ҵ���� ũ�⸸ŭ �����ؾ� �ϴϱ� ���� for���� ����� �� �ִ�.
	for (auto person : arList)
		delete person;
	return 0;
}
