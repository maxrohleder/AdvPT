// this file is just for documenting the required interface to compile with MatrixTest.cpp (declarations only)
#include <iostream>
#include <assert.h>

using namespace std;

template <typename T>
class Matrix {
private:
	size_t no_rows;
	size_t no_cols;
	T *data = nullptr;
public:
	// normal constructor
	Matrix(size_t rows, size_t cols, T initValue) : no_cols(cols), no_rows(rows), data(new T[cols*rows]) {
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = initValue;
	};
	// destructor
	~Matrix() { delete[] data; };
	// copy constructor
	Matrix(const Matrix& n) : no_cols(n.no_cols), no_rows(n.no_rows), data(new T[n.no_cols*n.no_rows]) {
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = n.data[i];
	};
	// assignment just calls copy constructor
	Matrix& operator=(const Matrix& n) {
		if (*this == n) return *this;
		delete[] data;
		no_cols = n.no_cols;
		no_rows = n.no_rows;
		data = new T[no_cols*no_rows];
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = n.data[i];
		return *this;
	};
	// value-setter i is the ith row and ranges between 0 and no_rows(excl)
	double& operator()(size_t i, size_t j) {
		assert(i >= 0 && i < no_rows && j >= 0 && j < no_cols);
		return data[i*no_cols + j];
	};
	// value-getter 
	const T& operator()(size_t i, size_t j) const {
		assert(i >= 0 && i < no_rows && j >= 0 && j < no_cols);
		return data[i*no_cols + j];
	};
	// elementwise comparison
	bool operator ==(const Matrix& n) const {
		if (no_rows != n.no_rows || no_cols != n.no_cols) return false;
		for (size_t i = 0; i < no_cols*no_rows; i++) if (data[i] != n.data[i]) return false;
		return true;
	};
	// elementwise negative comparison
	bool operator !=(const Matrix& n) const { return !(*this == n); };

	// arithmetic operators
	// element wise addition
	Matrix& operator +=(const Matrix& n) {
		assert(no_rows == n.no_rows && no_cols == n.no_cols);
		for (size_t i = 0; i < no_cols*no_rows; i++) data[i] += n.data[i];
		return *this;
	};

	Matrix operator +(const Matrix& n) const {
		assert(no_rows == n.no_rows && no_cols == n.no_cols);
		Matrix ret = *this;
		ret += n;
		return ret;
	};
	// elementwise subtraction
	Matrix& operator -=(const Matrix& n) {
		assert(no_rows == n.no_rows && no_cols == n.no_cols);
		for (size_t i = 0; i < no_cols*no_rows; i++) data[i] -= n.data[i];
		return *this;
	};

	Matrix operator -(const Matrix& n) const {
		assert(no_rows == n.no_rows && no_cols == n.no_cols);
		Matrix ret = *this;
		ret -= n;
		return ret;
	};
	// matrix multiplication (pythonic matmul-symbol @ not overloadable)
	/*
	a row has no_cols entries.
	a col has no_rows entries.

	m1@m2 = m3
	(s1, s2) @ (s2, s3) --> (s1, s3)
	(no_rows, no_cols) @ (n.no_rows, n.no_cols) --> (no_rows, n.no_cols)
	*/
	Matrix operator *(const Matrix& n) const {
		assert(no_cols == n.no_rows);
		Matrix<T> ret = Matrix<T>(no_rows, n.no_cols, (T) 0);
		size_t s1 = no_rows;
		size_t s2 = no_cols;
		size_t s3 = n.no_cols;
		// run along s1 and s3 and for each datapoint at (s1_r, s3_r) calc weighted sum 
		for (size_t s1_r = 0; s1_r < s1; s1_r++) {
			for (size_t s3_r = 0; s3_r < s3; s3_r++) {
				T datapoint = 0;
				// loop over s1_rth row of this and s3_rth column of n and calculate weighted sum
				for (size_t i = 0; i < s2; i++) {
					datapoint += data[(s1_r*no_cols) + i] * n.data[(i*n.no_cols) + s3_r];
				}
				ret(s1_r, s3_r) = datapoint;
			}
		}
		return ret;
	};

	Matrix& operator *=(const Matrix& n) {
		*this = *this * n;
		return *this;
	};


	// toString method
	friend ostream& operator <<(ostream&, const Matrix&);
	// readin method
	friend istream& operator >>(istream&, const Matrix&);

	// getter for private members
	size_t rows() const { return no_rows; };
	size_t cols() const { return no_cols; };

};

ostream& operator <<(ostream& out, const Matrix& n) {
	for (size_t i = 0; i < n.no_cols*n.no_rows; i++)
	{
		if (i % n.no_cols == n.no_cols - 1) out << n.data[i] << endl << endl;
		else out << n.data[i] << "\t";
	}
	return out;
};

istream& operator >>(istream& in, const Matrix& n) {
	for (size_t i = 0; i < n.no_cols*n.no_rows; i++)
	{
		in >> n.data[i];
	}

	return in;
};
