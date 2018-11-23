//#include "Vector.h"
#include <iostream>
#include "Matrix.h"
#include "Vector.h"

using namespace std;

template<typename T1, typename T2>
class zwiebel {
private:
	size_t schalenzahl;
	T1 name;
	T2 nachname;
public:
	zwiebel<T1, T2>(T1 a, T2 b) : name(a), nachname(b) { cout << "constructor 1 used" << endl; };

	//zwiebel<char*, int>(char* a, int b) : name(a), nachname(b) { cout << "constructor 2" << endl; };
	
	T1 getname() const {
		return this->name;
	}

};

void get_invers(int a) {
	cout << "inline check" << endl;
};

void run_vector_tests() {
	cout << "begin vector tests\n";
	Vector<double> a = Vector<double>(5, 4.);
	Vector<double> b = Vector<double>(7, 3.);
	cout << "a: " << a;
	a = b;
	cout << "a(b): " << a;
	cout << a + b;

	Matrix<double> A = Matrix<double>(10, 5, 2);
	Matrix<double> B = A;
	cout << "A:\n" << A;
	cout << "B:\n" << B;
	cout << A * b;
	//cout << b * A;
	cout << "b: " << b;
	b += a;
	cout << "b+a: " << b;
};

int main(int argc, char** argv) {

	zwiebel<char*, int> z = zwiebel<char*, int>("zwiebel1", 5);
	Matrix<double> A = Matrix<double>(5, 10, 10);
	Matrix<double> B = Matrix<double>(10, 5, 5);
	Matrix<double> C = A * B;

	Vector<double> asdf = Vector<double>(5, 6);
	Vector<double> sdfg = Vector<double>(5, 20);

	cout << asdf + sdfg;
	cout << C;
	cout << C.inverseDiagonal();
	Matrix<double> Ci = C.inverseDiagonal();
	Matrix<double> Cii = Ci.inverseDiagonal();
	cout << Cii;
	Vector<double> dfgh = B * asdf;
	cout << dfgh;
	Vector<double> unit = Vector<double>(2, 1);
	cout << "length of (1,1): " << unit.l2Norm() << endl;
	cout << dfgh.l2Norm();
	cout << z.getname() << endl;
	get_invers(5);





	cout << "-----------------------------------------------------\n";
	run_vector_tests();








	int a = 0;
	cin >> a;
}