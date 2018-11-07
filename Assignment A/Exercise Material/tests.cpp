#include <iostream>
#include <Matrix.h>

using namespace std;

template <typename U> void print(U value) {
	cout << value << endl;
};

template<typename t> class MyClass{
private:
	t data;
public:
	MyClass(t d) : data(d);
	~MyClass() = default;
	static int const p = 1;
	//static const i = t::mem *p;
	//typename t::mem *pi;
	template <typename U> void print(U value);
	t get() {
		return data;
	};

	bool set(t d) {
		data = d;
		return true;
	};
};



template<typename T1, typename T2> 
auto sum(const T1& a, const T2& b) {
	return a + b;
}


int main() {
	// constructor testen
	cout << "Hello World \n";
	double arg1 = 3.2;
	double arg2 = 1.99;

	int erg = sum(arg1, arg2);
	cout << erg;

	// template class
	MyClass<double> k = MyClass<double>(0.9);
	k.print(8);


	// programm soll nicht schließen 
	int c;
	cin >> c;
	return 0;
};