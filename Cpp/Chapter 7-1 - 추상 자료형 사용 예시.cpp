// AdtSample.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
#include <iostream>
using namespace std;

//초기 제작자
#define DEFAULT_FARE	1000
#define MAX 256

class CPerson
{
public:
	CPerson() {}
	virtual ~CPerson() {
		cout << "virtual ~CPerson()" << endl;
	}
	//요금계산 인터페이스 (순수 가상 함수)
	virtual void CalcFare() = 0;

	virtual unsigned int GetFare() { return m_nFare; }
protected:
	unsigned int m_nFare = 0;
};

//초기 혹은 후기 제작자
class CBaby : public CPerson
{
public:
	//영유아(0~7세)
	virtual void CalcFare()	{
		m_nFare = 0;	//0%
	}
};

class CChild : public CPerson
{
public:
	//어린이(8~13세) 요금계산
	virtual void CalcFare()	{
		m_nFare = DEFAULT_FARE * 50 / 100;	//50%
	}
};

class CTeen : public CPerson
{
public:
	//어린이(14~19세) 요금계산
	virtual void CalcFare()	{
		m_nFare = DEFAULT_FARE * 75 / 100;	//75%
	}
};

class CAdult : public CPerson
{
public:
	//20세 이상 성인
	virtual void CalcFare()	{
		m_nFare = DEFAULT_FARE;				//100%
	}
};
//사용자 코드
int main71(int argc, char* argv[])
{
	int nNumber;
	cin >> nNumber;
	//원하는 만큼 계산해보려고 나름대로 고쳐본....
	CPerson* arList[MAX] = { 0 }; //순수 가상 클래스는 new 연산자를 활용할 수 없어서 사람 명수대로 배열을 생성할 수 없다.
	//그래서 범위 for문도 사용할 수 없다.
	int nAge = 0;

	//1. 자료입력: 사용자 입력에 따라서 생성할 객체 선택
	//for (auto &person : arList)
	int i = 0;
	for(i=0;i<nNumber;i++)
	{
		cout << "나이를 입력하세요: ";
		cin >> nAge; //입력받을 때니까 다중 if문을 써도 성능에 지장이 없음.
		if (nAge < 8)
			arList[i] = new CBaby; //나이 입력받고 바로 배열에 새롭게 메모리 할당.
		else if (nAge < 14)
			arList[i] = new CChild;
		else if (nAge < 20)
			arList[i] = new CTeen;
		else
			arList[i] = new CAdult;
		//생성한 객체에 맞는 요금이 자동으로 계산된다.
		arList[i]->CalcFare();
		//!!제일 중요한 부분!! 계산 결과를 담은 배열을 만들어놓아, 입력 받으면서 미리미리 계산하고 나중에 한번에 출력할 수 있다.
	}

	//2. 자료출력: 계산한 요금을 활용하는 부분
	//for (auto person : arList)
	for(i=0;i<nNumber;i++)
		cout << arList[i]->GetFare() << "원" << endl;

	//3. 자료삭제 및 종료
	//여기는 할당받은 크기만큼 삭제해야 하니까 범위 for문을 사용할 수 있다.
	for (auto person : arList)
		delete person;
	return 0;
}
