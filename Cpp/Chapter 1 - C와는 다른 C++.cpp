// Cpp.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include <iostream> //C++은 기본 헤더파일이면 .h 안붙임

void testfunc(int& param) {
    param = 200;
}

void swap(int& a, int& b) {
    int tmp(a);
    a = b;
    b = tmp;
}
int main1()//int argc, char *argv[]
{
    std::cout << "Hello World!" << std::endl; //std -> 걍 소속임. std 소속인 cout이라는 객체에 문자열과 endl을 넘겨줌.
    std::cout << 10.5F << std::endl; // F, U 등을 붙여서 C언어처럼 형식을 지정할수도 있으나, 안그래도 알아서 프린트함.
    std::string string = "This is a string";
    std::cout << string << std::endl; //이러면 문자열 크기 제한 없이 인스턴스 선언이 가능하다.
    std::string name;
    //std::cin >> name;
    //std::cout << "당신의 이름은 " << name << "입니다.";

    int a(10);
    int b(a); //C++ 스타일 변수 생성방법
    auto c(b); //auto 키워드 - 초깃값의 형식에 맞춰 type이 자동으로 결정되게 함. (파이썬이랑 비슷한거 같기도?)
    int(10); //이렇게 이름 없이 선언할 수도 있음.
    void(*pf)(int&) = testfunc; //함수 포인터로는 이렇게 해야하는데
    auto tst2(testfunc); //auto 키워드를 이용하면 함수 포인터를 이렇게 생성할 수 있음.


    //동적 메모리 할당 - malloc과 free 대신에 new와 delete 사용
    int* pData = new int(15); //형식 *(이름) = new 형식(초기값);
    //C언어 스타일 - int *pData=(int *)malloc(sizeof(int));
    //크기를 이제 몰라도 됨.
    std::cout << *pData << std::endl; //포인터 사용법은 C와 같음.
    delete pData;
    int* arr = new int[5];
    for (int i = 0; i < 5; i++) {
        arr[i] = i * 10;
    }
    //for (int i = 0; i < 5; i++) {
    //    std::cout << arr[i] << std::endl;
    //}
    delete[] arr; //배열 형태로 동적 생성하면 배열 형태로 지워줘야 함.


    //참조형 변수 -> C++의 포인터
    int data(10);
    //참조자는 alias다.
    int& ndata = data; //바로 초기화 해줘야함. 포인터 int *p=q;는 q의 주소의 값이라면, C++은 값의 주소 느낌?
    ndata = 20; //포인터에서 *ndata=20;과 같은 느낌.
    std::cout << ndata << std::endl; //C++에서는 주소 대신 참조라고 함.
    testfunc(ndata); //매개변수로 넘길때는 & 쓰면 안됨.
    std::cout << ndata << std::endl; //C++에서는 주소 대신 참조라고 함.\
    //진짜 별명 수준이라 주소를 찍어도 똑같이 나옴.
    std::cout << &data << std::endl;
    std::cout << &ndata << std::endl;
    int x = 2, y = 3;
    swap(x, y);
    std::cout << "x = " << x << ", y = " << y <<std::endl;
    //참조자는 상수 포인터 느낌임. int * const pndata = &a; 실제로 작동하는거 보면 주소도 저장하고 함.


    //r-value 참조. 곧 사라질 임시 결과에 대해 참조 연산을 수행하는 것. &&연산을 사용함. 지금은 잘 모를거니까 패스.
    //int a; a = 10; 에서 a가 l-value, 10이 r-value. 변수가 되는게 l-value. r-value는 변수 또는 연산의 중간 결과에서 생기는 임시 객체로서의 상수.
    int Input = 5;
    int&& InputData = Input + 3; // = Input은 안됨. 임시 결과를 저장하는 거임. 그냥은 안됨.
    //std::cout << InputData << std::endl;
    InputData = 33;
    //std::cout << InputData << std::endl;

    
    //범위 기반 for문. Python의 for i in arr과 비슷한 것. 크기가 달라져도 for문을 변경할 필요가 없음.
    //배열 전체의 요소에 접근할 때 사용할 수 있음.
    int list[5] = { 1,2,3,4,5 };
    for (auto n : list) { //이게 일반 for문하고 동일함.
        n = 10; //이렇게 하면 각 리스트의 요소에 접근할 수 없어서 배열의 요소를 바꿀 수가 없음.
    }
    for (auto n : list) {
        std::cout << n << ' '; //이렇게 값을 읽어서 출력하는건 가능.
    }
    std::cout << std::endl;
    for (auto &n : list) { // &연산자를 사용하면 배열 요소들의 값을 직접 변경할 수 있음.
        //n = 10; //list[i]=10과 같은 효과.
        n = 10 * n; //list[i]*=10;과 같은 효과
    }
    for (auto n : list) {
        std::cout << n << ' ';
    }
    std::cout << std::endl;
    return 0;
}










// 프로그램 실행: <Ctrl+F5> 또는 [디버그] > [디버깅하지 않고 시작] 메뉴
// 프로그램 디버그: <F5> 키 또는 [디버그] > [디버깅 시작] 메뉴

// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.
