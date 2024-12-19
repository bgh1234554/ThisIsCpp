#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <string.h>

using namespace std;

class Human {
	string name;
	int age;
public:
	Human(const string& name, int age):name(name),age(age){}
	string get_info() { return "Name: " + name + " / Age: " + to_string(age); }
	friend ofstream& operator<<(ofstream& o, Human& h);
};

ofstream& operator<<(ofstream& o, Human& h)
{
	o << h.get_info();
	return o;
}

int main() {
	ifstream in("test.txt"); //fopen 같은거
	//binary 파일로 읽을 때는 std::ios::binary를 뒤에 붙여줘야함.
	string s;
	if (in.is_open()) { //파일 열렸는지 확인
		in >> s; //여긴 fclose 없음. 알아서 닫음.
		cout << "입력받은 문자열: " << s << endl;
	}
	in.close(); //파일 바꿔줄때는 close해야함.
	in.open("other.txt");
	if (in.is_open()) {
		in >> s; //여긴 fclose 없음. 알아서 닫음.
		cout << "입력받은 문자열: " << s << endl;
	}
	//char x[10];
	//in.read(x, 10); //이러면 10바이트를 읽어서 x에 전달해줌.
	//cout << x << endl;

	//파일 전체를 한번에 읽기
	ifstream in2("test.txt");
	string s2;
	if (in2.is_open()) {
		in2.seekg(0, ios::end); //끝으로 옮기기. fseek와 같은 함수.
		int size = in2.tellg(); //시작점으로부터의 위치를 읽기. 파일 크기 찾기.
		s2.resize(size); //s2의 크기를 조절해 메모리 할당.
		in2.seekg(0, ios::beg); //커서 다시 옮기기
		in2.read(&s2[0], size); //size 크기 만큼 읽어들인다.
		cout << s2 << endl;
	}
	//s2.c_str() string을 char[]로 변환해줌.
	// 
	//파일 전체를 한줄씩 읽기.
	in2.close();
	in2.open("test.txt");
	char buf[100];
	if (!in2.is_open()) {
		cout << "Failed" << endl;
		return 0;
	}
	while (in2) { //다음 입력작업이 성공적일때 true가 호출됨.
		//in2.getline(buf, 100); //근데 이러면 buffer가 작아서 성공적으로 읽지 못할수도 있음.
		getline(in2, s2); //위의 문제를 해결하기 위해 string에서 만든 함수.
		//이러면 "\n"이 나올때까지 99글자씩 읽는다. 물론 3번째 인수로 문자를 지정해서 읽게할 수도 있다.
		//cout << buf << endl;
		cout << s2 << endl;
	}

	//파일 쓰기
	ofstream out("write.txt");
	if (out.is_open()) {
		out << "Let's Write"<<endl; //endl은 \n을 파일에 쓰는 것.
	}
	out.close();
	out.open("write.txt", ios::app); //append하는 법
	if (out.is_open()) {
		out << "Append Test" << endl;
	}

	//당연히 파일 << 연산자도 다중정의할 수 있음.
	ofstream of("test2.txt");
	Human h("백지훈", 25);
	of << h << endl;

	//문자열 스트림
	//#include <sstream> 해줘야함.
	istringstream ss("123");
	//문자열을 스트림이라 생각하게 해주는 장치.
	int x;
	ss >> x;
	//이러면 123이 int형으로 반환됨.

	ostringstream oo;
	oo << x; //반대로 문자열 스트림에 변수를 출력할수도 있음.
	cout << oo.str() << endl;
	cout << endl;

	//strtok C++방식 (구별자 하나밖에 못씀)
	string str = "str1 str2 str3";
	istringstream ss2(str);
	string strBuffer;
	vector<string> v;
	v.clear();

	//ss2에는 문자열 버퍼에 구분자(' ')로 자르고 남은 문자열이 저장됨
	while (getline(ss2, strBuffer, ' ')) {
		v.push_back(strBuffer);
	}

	//auto를 사용하면 벡터의 값을 쉽게 가지고 와서 사용할 수 있음
	//아래 주석과 동일한 의미
	//for(int i=0;i<v.size();i++) cout<<v[i]<<endl;
	for (auto i : v) cout << i << endl;
	cout << endl;

	//string 클래스로 strtok 사용하는 방법
	string str2 = "str|str2\tstr3 str4";
	char ch[256];
	//string -> char[]로 변환해줘야 함
	strcpy_s(ch, sizeof(ch), str2.c_str());
	//구분자를 두번째 인자값으로 넣어줌
	//ex | 와 (공백)을 구분자로 사용 => "| "
	char* context;
	//context -> 떨어져나가고 남은 문자열의 시작주소.
	char* ptr = strtok_s(ch, "| \t",&context);
	vector<string> v2;

	//ptr이 null이 아닐 때까지 반복
	while (ptr != NULL) {
		//string으로 변환하여 벡터에 넣어줌
		v2.push_back(string(ptr));
		ptr = strtok_s(NULL, "| \t", &context);
	}

	for (auto i : v2) cout << i << endl;
	return 0;
}
