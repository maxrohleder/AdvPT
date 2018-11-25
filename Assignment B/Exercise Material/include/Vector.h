// this file is just for documenting the required interface to compile with VectorTvest.cpp (declarations only)
#include <iostream>
#include <assert.h>
#include <functional>

using namespace std;

template <typename T, size_t no_elem>
class Vector {
private:
	array<T, no_elem> data;
public:
	// normal constructor
	Vector(T initValue) {
		for (size_t i = 0; i < no_elem; i++) data[i] = initValue;
	};
	// lambda constructor
	Vector(std::function<T(T)> init) {
		for (size_t i = 0; i < no_elem; i++) data[i] = init(i);
	};
	// destructor
	~Vector() { };
	// copy constructor
	Vector(const Vector<T, no_elem>& n) {
		for (size_t i = 0; i < no_elem; i++) data[i] = n.data[i];
	};
	// assignment just calls copy constructor
	Vector<T, no_elem>& operator=(const Vector<T, no_elem>& n) {
		if (*this == n) return *this;
		data = array<T, no_rows*no_cols>;
		for (size_t i = 0; i < no_elem; i++) data[i] = n.data[i];
		return *this;
	};
	// value-setter (returns writable reference)
	T& operator()(size_t i) {
		assert(i >= 0 && i < no_elem);
		return data[i];
	};
	// value-getter 
	const T& operator()(size_t i) const {
		assert(i >= 0 && i < no_elem);
		return data[i];
	};
	// elementwise comparison
	bool operator ==(const Vector<T, no_elem>& n) const {
		//if (no_elem != n.no_elem) return false; not neccessary anymore
		for (size_t i = 0; i < no_elem; i++) if (data[i] != n.data[i]) return false;
		return true;
	};
	// elementwise negative comparison
	bool operator !=(const Vector<T, no_elem>& n) const { return !(*this == n); };

	// arithmetic operators
	// element wise addition
	Vector<T, no_elem>& operator +=(const Vector<T, no_elem>& n) {
		//assert(no_elem == n.no_elem);
		for (size_t i = 0; i < no_elem; i++) data[i] += n.data[i];
		return *this;
	};

	Vector<T, no_elem> operator +(const Vector<T, no_elem>& n) const {
		//assert(no_elem == n.no_elem);
		Vector ret = *this;
		ret += n;
		return ret;
	};
	// elementwise subtraction
	Vector<T, no_elem>& operator -=(const Vector<T, no_elem>& n) {
		//assert(no_elem == n.no_elem);
		for (size_t i = 0; i < no_elem; i++) data[i] -= n.data[i];
		return *this;
	};

	Vector<T, no_elem> operator -(const Vector<T, no_elem>& n) const {
		//assert(no_elem == n.no_elem);
		Vector<T, no_elem> ret = *this;
		ret -= n;
		return ret;
	};
	
	Vector<T, no_elem>& operator *=(const Vector<T, no_elem>& n) {
		*this = *this * n;
		return *this;
	};

	double l2Norm() const {
		double norm = 0.;
		for (int i = 0; i < no_elem; ++i)
			norm += data[i] * data[i];
		return sqrt(norm);
	};

	friend ostream& operator <<(ostream& out, const Vector<T, no_elem>& n) {
		for (size_t i = 0; i < n.no_elem; i++)
		{
			out << n.data[i] << endl;
		}
		return out;
	};

	friend istream& operator >>(istream& in, const Vector<T, no_elem>& n) {
		for (size_t i = 0; i < n.no_elem; i++)
		{
			in >> n.data[i];
		}

		return in;
	};

	// getter for private membaz
	size_t size() const { return no_elem; };

};
