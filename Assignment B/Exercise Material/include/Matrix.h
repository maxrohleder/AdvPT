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
	}
	// destructor
	~Matrix() { }
	// copy constructor
	Matrix (const Matrix<T, no_rows, no_cols>& n) {
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = n.data[i];
	}
	// assignment just calls copy constructor
	Matrix<T, no_rows, no_cols>& operator=(const Matrix<T, no_rows, no_cols>& n) {
		if (*this == n) return *this;
		for (size_t i = 0; i < no_rows*no_cols; i++) data[i] = n.data[i];
		return *this;
	}
	// value-setter i is the ith row and ranges between 0 and no_rows(excl)
	T& operator()(size_t i, size_t j) {
		assert(i >= 0 && i < no_rows && j >= 0 && j < no_cols);
		return data[i*no_cols + j];
	}
	// value-getter 
	const T& operator()(size_t i, size_t j) const {
		assert(i >= 0 && i < no_rows && j >= 0 && j < no_cols);
		return data[i*no_cols + j];
	}
	// elementwise comparison
	template<size_t r, size_t c>
	bool operator ==(const Matrix<T, r, c>& n) const {
		if (no_rows != r || no_cols != c) return false;
		for (size_t i = 0; i < no_rows; ++i) {
			for (size_t j = 0; j < no_cols; ++j) {
				if (data[i*no_cols + j] != n(i, j)) return false;
			}
		}
		return true;
	}
	// elementwise negative comparison
	template<size_t r, size_t c>
	bool operator !=(const Matrix<T, r, c>& n) const { return !(*this == n); }


	Matrix<T, no_rows, no_cols>& operator +=(const Matrix<T, no_rows, no_cols>& n) {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		for (size_t i = 0; i < no_cols*no_rows; i++) data[i] += n.data[i];
		return *this;
	}

	Matrix<T, no_rows, no_cols> operator +(const Matrix<T, no_rows, no_cols>& n) const {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		Matrix ret = *this;
		ret += n;
		return ret;
	}
	// elementwise subtraction
	Matrix<T, no_rows, no_cols>& operator -=(const Matrix<T, no_rows, no_cols>& n) {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		for (size_t i = 0; i < no_cols*no_rows; i++) data[i] -= n.data[i];
		return *this;
	}

	Matrix<T, no_rows, no_cols> operator -(const Matrix<T, no_rows, no_cols>& n) const {
		//assert(no_rows == n.no_rows && no_cols == n.no_cols);
		Matrix<T, no_rows, no_cols> ret = *this;
		ret -= n;
		return ret;
	}
	// matrix multiplication (pythonic matmul-symbol @ not overloadable)

	template<size_t r, size_t c>
	Matrix<T, no_rows, c> operator *(const Matrix<T, r, c>& n) const {
		// könnte static sein
		assert(no_cols == r);
		//assert
		Matrix<T, no_rows, c> ret(0);
		// run along s1 and s3 and for each datapoint at (s1_r, s3_r) calc weighted sum 
		for (size_t s1_r = 0; s1_r < no_rows; s1_r++) {
			for (size_t s3_r = 0; s3_r < c; s3_r++) {
				T datapoint = 0;
				// loop over s1_rth row of this and s3_rth column of n and calculate weighted sum
				for (size_t i = 0; i < no_cols; i++) {
					datapoint += data[(s1_r*no_cols) + i] * n(i, s3_r);
				}
				ret(s1_r, s3_r) = datapoint;
			}
		}
		return ret;
	}

	Matrix<T, no_rows, no_cols>& operator *=(const Matrix<T, no_rows, no_cols>& n) {
		*this = *this * n;
		return *this;
	}

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
	}

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
	}

	friend istream& operator >>(istream& in, Matrix<T, no_rows, no_cols>& n) {
		for (size_t i = 0; i < no_rows; ++i){
			for (size_t j = 0; j < no_cols; ++j) {
				in >> n(i, j);
			}
		}

		return in;
	}

	// getter for private members
	size_t rows() const { return no_rows; }
	size_t cols() const { return no_cols; }

};