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
	ifstream in("test.txt"); //fopen ������
	//binary ���Ϸ� ���� ���� std::ios::binary�� �ڿ� �ٿ������.
	string s;
	if (in.is_open()) { //���� ���ȴ��� Ȯ��
		in >> s; //���� fclose ����. �˾Ƽ� ����.
		cout << "�Է¹��� ���ڿ�: " << s << endl;
	}
	in.close(); //���� �ٲ��ٶ��� close�ؾ���.
	in.open("other.txt");
	if (in.is_open()) {
		in >> s; //���� fclose ����. �˾Ƽ� ����.
		cout << "�Է¹��� ���ڿ�: " << s << endl;
	}
	//char x[10];
	//in.read(x, 10); //�̷��� 10����Ʈ�� �о x�� ��������.
	//cout << x << endl;

	//���� ��ü�� �ѹ��� �б�
	ifstream in2("test.txt");
	string s2;
	if (in2.is_open()) {
		in2.seekg(0, ios::end); //������ �ű��. fseek�� ���� �Լ�.
		int size = in2.tellg(); //���������κ����� ��ġ�� �б�. ���� ũ�� ã��.
		s2.resize(size); //s2�� ũ�⸦ ������ �޸� �Ҵ�.
		in2.seekg(0, ios::beg); //Ŀ�� �ٽ� �ű��
		in2.read(&s2[0], size); //size ũ�� ��ŭ �о���δ�.
		cout << s2 << endl;
	}
	//s2.c_str() string�� char[]�� ��ȯ����.
	// 
	//���� ��ü�� ���پ� �б�.
	in2.close();
	in2.open("test.txt");
	char buf[100];
	if (!in2.is_open()) {
		cout << "Failed" << endl;
		return 0;
	}
	while (in2) { //���� �Է��۾��� �������϶� true�� ȣ���.
		//in2.getline(buf, 100); //�ٵ� �̷��� buffer�� �۾Ƽ� ���������� ���� ���Ҽ��� ����.
		getline(in2, s2); //���� ������ �ذ��ϱ� ���� string���� ���� �Լ�.
		//�̷��� "\n"�� ���ö����� 99���ھ� �д´�. ���� 3��° �μ��� ���ڸ� �����ؼ� �а��� ���� �ִ�.
		//cout << buf << endl;
		cout << s2 << endl;
	}

	//���� ����
	ofstream out("write.txt");
	if (out.is_open()) {
		out << "Let's Write"<<endl; //endl�� \n�� ���Ͽ� ���� ��.
	}
	out.close();
	out.open("write.txt", ios::app); //append�ϴ� ��
	if (out.is_open()) {
		out << "Append Test" << endl;
	}

	//�翬�� ���� << �����ڵ� ���������� �� ����.
	ofstream of("test2.txt");
	Human h("������", 25);
	of << h << endl;

	//���ڿ� ��Ʈ��
	//#include <sstream> �������.
	istringstream ss("123");
	//���ڿ��� ��Ʈ���̶� �����ϰ� ���ִ� ��ġ.
	int x;
	ss >> x;
	//�̷��� 123�� int������ ��ȯ��.

	ostringstream oo;
	oo << x; //�ݴ�� ���ڿ� ��Ʈ���� ������ ����Ҽ��� ����.
	cout << oo.str() << endl;
	cout << endl;

	//strtok C++��� (������ �ϳ��ۿ� ����)
	string str = "str1 str2 str3";
	istringstream ss2(str);
	string strBuffer;
	vector<string> v;
	v.clear();

	//ss2���� ���ڿ� ���ۿ� ������(' ')�� �ڸ��� ���� ���ڿ��� �����
	while (getline(ss2, strBuffer, ' ')) {
		v.push_back(strBuffer);
	}

	//auto�� ����ϸ� ������ ���� ���� ������ �ͼ� ����� �� ����
	//�Ʒ� �ּ��� ������ �ǹ�
	//for(int i=0;i<v.size();i++) cout<<v[i]<<endl;
	for (auto i : v) cout << i << endl;
	cout << endl;

	//string Ŭ������ strtok ����ϴ� ���
	string str2 = "str|str2\tstr3 str4";
	char ch[256];
	//string -> char[]�� ��ȯ����� ��
	strcpy_s(ch, sizeof(ch), str2.c_str());
	//�����ڸ� �ι�° ���ڰ����� �־���
	//ex | �� (����)�� �����ڷ� ��� => "| "
	char* context;
	//context -> ������������ ���� ���ڿ��� �����ּ�.
	char* ptr = strtok_s(ch, "| \t",&context);
	vector<string> v2;

	//ptr�� null�� �ƴ� ������ �ݺ�
	while (ptr != NULL) {
		//string���� ��ȯ�Ͽ� ���Ϳ� �־���
		v2.push_back(string(ptr));
		ptr = strtok_s(NULL, "| \t", &context);
	}

	for (auto i : v2) cout << i << endl;
	return 0;
}
