#include <iostream>
#include <assert.h>
#include <array>

#include "MatrixLike.h"

using namespace std;

template <typename T, size_t no_rows, size_t no_cols>
class Matrix : public MatrixLike<T, Matrix<T, no_rows, no_cols>, no_rows, no_cols> {
private:
	array<T, no_rows*no_cols> data;
public:
	// normal constructor
	Matrix(T initValue) {
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = initValue;
	};
	// destructor
	~Matrix() { };
	// copy constructor
	Matrix (const Matrix<T, no_rows, no_cols>& n) {
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = n.data[i];
	};
	// assignment just calls copy constructor
	Matrix<T, no_rows, no_cols>& operator=(const Matrix<T, no_rows, no_cols>& n) {
		if (*this == n) return *this;
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = n.data[i];
		return *this;
	};
	// value-setter i is the ith row and ranges between 0 and no_rows(excl)
	T& operator()(size_t i, size_t j) {
		assert(i >= 0 && i < no_rows && j >= 0 && j < no_cols);
		return data[i*no_cols + j];
	};
	// value-getter 
	const T& operator()(size_t i, size_t j) const {
		assert(i >= 0 && i < no_rows && j >= 0 && j < no_cols);
		return data[i*no_cols + j];
	};
	// elementwise comparison
	bool operator ==(const Matrix<T, no_rows, no_cols>& n) const {
		//if (no_rows != n.no_rows || no_cols != n.no_cols) return false; typechecking does that for us
		for (size_t i = 0; i < no_cols*no_rows; i++) if (data[i] != n.data[i]) return false;
		return true;
	};
	// elementwise negative comparison
	bool operator !=(const Matrix<T, no_rows, no_cols>& n) const { return !(*this == n); };

	// arithmetic operators
	// element wise addition
	Matrix<T, no_rows, no_cols>& operator +=(const Matrix<T, no_rows, no_cols>& n) {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		for (size_t i = 0; i < no_cols*no_rows; i++) data[i] += n.data[i];
		return *this;
	};

	Matrix<T, no_rows, no_cols> operator +(const Matrix<T, no_rows, no_cols>& n) const {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		Matrix ret = *this;
		ret += n;
		return ret;
	};
	// elementwise subtraction
	Matrix<T, no_rows, no_cols>& operator -=(const Matrix<T, no_rows, no_cols>& n) {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		for (size_t i = 0; i < no_cols*no_rows; i++) data[i] -= n.data[i];
		return *this;
	};

	Matrix<T, no_rows, no_cols> operator -(const Matrix<T, no_rows, no_cols>& n) const {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		Matrix<T, no_rows, no_cols> ret = *this;
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
	Matrix<T, no_rows, no_cols> operator *(const Matrix<T, no_rows, no_cols>& n) const {
		assert(no_cols == no_rows);
		//assert
		Matrix<T, no_rows, no_cols> ret = Matrix<T, no_rows, no_cols>((T) 0);
		size_t s1 = no_rows;
		size_t s2 = no_cols;
		size_t s3 = no_cols;
		// run along s1 and s3 and for each datapoint at (s1_r, s3_r) calc weighted sum 
		for (size_t s1_r = 0; s1_r < s1; s1_r++) {
			for (size_t s3_r = 0; s3_r < s3; s3_r++) {
				T datapoint = 0;
				// loop over s1_rth row of this and s3_rth column of n and calculate weighted sum
				for (size_t i = 0; i < s2; i++) {
					datapoint += data[(s1_r*no_cols) + i] * n.data[(i*no_cols) + s3_r];
				}
				ret(s1_r, s3_r) = datapoint;
			}
		}
		return ret;
	};

	Matrix<T, no_rows, no_cols>& operator *=(const Matrix<T, no_rows, no_cols>& n) {
		*this = *this * n;
		return *this;
	};

	// matrix vector multiplication
	Vector<T, no_rows> operator* (const Vector<T, no_rows> &o) const {
		//assert(no_cols == no_elem);
		Vector<T, no_rows> output = Vector<T, no_rows>((T) 0);
		for (size_t y = 0; y < no_rows; y++){
			for (size_t x = 0; x < no_cols; x++){
				output(y) += o(x) * data[y*no_cols + x];
			}
		}
		return output;
	};

	Matrix<T, no_rows, no_cols> inverseDiagonal() const {
		assert(no_cols == no_rows);
		Matrix<T, no_rows, no_cols> diag = *this;
		for (size_t c = 0; c < no_cols; c++){
			for (size_t r = 0; r < no_rows; r++){
				if (r != c) 
					diag(c, r) = (T) 0;
				else {
					T val = diag(c, r);
					assert(val != (T) 0.);
					diag(c, r) = 1 / val;
				}
			}
		}
		return diag;
	};

	friend ostream& operator <<(ostream& out, const Matrix<T, no_rows, no_cols>& n) {
		for (size_t i = 0; i < no_cols*no_rows; i++)
		{
			if (i % no_cols == no_cols - 1) out << n.data[i] << endl << endl;
			else out << n.data[i] << "\t";
		}
		return out;
	};

	friend istream& operator >>(istream& in, const Matrix<T, no_rows, no_cols>& n) {
		for (size_t i = 0; i < no_rows; ++i){
			for (size_t j = 0; j < no_cols; ++j) {
				in >> n(i, j);
			}
		}

		return in;
	};

	// getter for private members
	size_t rows() const { return no_rows; };
	size_t cols() const { return no_cols; };

};
