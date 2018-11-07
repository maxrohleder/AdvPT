// TODO handle all possibly occuring errors

#include <iostream>
#include <Matrix.h>

using namespace std;

int main() {
	int s1, s2, s3;
	if (!(cin >> s1) || !(cin >> s2) || !(cin >> s3)) {
		cerr << "only integers allowed for matrix dimensions!" << endl;
		exit(1);
	};
	Matrix A = Matrix((size_t) s1,(size_t) s2, 0);
	Matrix B = Matrix((size_t) s2,(size_t) s3, 0);
	if (!(cin >> A) || !(cin >> B)) {
		cerr << "input error, only floats or ints allowed" << endl;
		exit(1);
	};
	Matrix C = A * B;
	cout << C;
	// keep promt open to check result
	int a;
	cin >> a;
};