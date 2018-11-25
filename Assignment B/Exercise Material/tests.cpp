#include <iostream>

using namespace std;

template<class T> struct A {
	static void print(T a) { std::cout << "base" << std::endl; }
};

template<> struct A<char> {
	using T = char;
	static void print(T a) { std::cout << "char" << std::endl; }
};

template<> void A<bool>::print(bool a) { std::cout << "bool" << std::endl; }

void main() {
	A<bool>::print('1');

	int a;
	cin >> a;
};
