// this file is just for documenting the required interface to compile with MatrixTest.cpp (declarations only)
#include <iostream>
#include <assert.h>
#include <fstream>
#include <Matrix.h>

using namespace std;

void test_matrix_multiplication() {
	size_t s1 = 5;
	size_t s2 = 6;
	size_t s3 = 7;
	// create Testmatrices
	Matrix A = Matrix(s1, s2, 5);
	Matrix B = Matrix(s2, s3, 4);

	// create identity matrix
	Matrix eye = Matrix(s2, s2, 0);
	for (size_t i = 0; i < s2; i++) eye(i, i) = 1;

	// matmul with identity matrix should return same matrix if implementet correctly
	Matrix C = A * eye;
	assert(C == A);
	Matrix D = A * B;
	cout << D;
};

int main() {
	// constructor testen
	Matrix A = Matrix(2, 3, 5);
	Matrix B = A;
	Matrix C = Matrix(A);
	// getter testen
	double checker = A(0, 0);
	cout << checker << endl;
	// setter testen
	A(0, 0) = 1;
	checker = A(1, 2);
	cout << checker << endl;
	// ostream testen
	cout << "matrix A:\n" << A << endl;
	cout << "matrix B:\n" << B << endl;
	cout << "matrix C:\n" << C << endl;
	// istream testen
	//ifstream mat_file;
	//mat_file.open("testcases/NonSquareInt.output.txt", ifstream::in);
	//mat_file >> B;
	//cin >> A;
	cout << A;
	// == und != testen
	assert((A == B) == false);
	assert((B == C) == true);
	assert((A != B) == true);
	assert((B != C) == false);
	// matrix multiplikation testen
	test_matrix_multiplication();
	// destructor testen
	delete A;
	// programm soll nicht schließen 
	int c;
	cin >> c;
	return 0;
};