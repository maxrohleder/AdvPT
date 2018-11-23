// this file is just for documenting the required interface to compile with VectorTvest.cpp (declarations only)
#include <iostream>
#include <assert.h>

using namespace std;

template <typename Tv>
class Vector {
private:
	size_t no_elem;
	Tv *data = nullptr;
public:
	// normal constructor
	Vector(size_t size, Tv initValue) : no_elem(size), data(new Tv[no_elem]) {
		for (size_t i = 0; i < no_elem; i++) data[i] = initValue;
	};
	// destructor
	~Vector() { delete[] data; };
	// copy constructor
	Vector(const Vector<Tv>& n) : no_elem(n.no_elem), data(new Tv[n.no_elem]) {
		for (size_t i = 0; i < no_elem; i++) data[i] = n.data[i];
	};
	// assignment just calls copy constructor
	Vector<Tv>& operator=(const Vector<Tv>& n) {
		if (*this == n) return *this;
		delete[] data;
		no_elem = n.no_elem;
		data = new Tv[no_elem];
		for (size_t i = 0; i < no_elem; i++) data[i] = n.data[i];
		return *this;
	};
	// value-setter (returns writable reference)
	Tv& operator()(size_t i) {
		assert(i >= 0 && i < no_elem);
		return data[i];
	};
	// value-getter 
	const Tv& operator()(size_t i) const {
		assert(i >= 0 && i < no_elem);
		return data[i];
	};
	// elementwise comparison
	bool operator ==(const Vector<Tv>& n) const {
		if (no_elem != n.no_elem) return false;
		for (size_t i = 0; i < no_elem; i++) if (data[i] != n.data[i]) return false;
		return true;
	};
	// elementwise negative comparison
	bool operator !=(const Vector<Tv>& n) const { return !(*this == n); };

	// arithmetic operators
	// element wise addition
	Vector<Tv>& operator +=(const Vector<Tv>& n) {
		assert(no_elem == n.no_elem);
		for (size_t i = 0; i < no_elem; i++) data[i] += n.data[i];
		return *this;
	};

	Vector<Tv> operator +(const Vector<Tv>& n) const {
		assert(no_elem == n.no_elem);
		Vector ret = *this;
		ret += n;
		return ret;
	};
	// elementwise subtraction
	Vector<Tv>& operator -=(const Vector<Tv>& n) {
		assert(no_elem == n.no_elem);
		for (size_t i = 0; i < no_elem; i++) data[i] -= n.data[i];
		return *this;
	};

	Vector<Tv> operator -(const Vector<Tv>& n) const {
		assert(no_elem == n.no_elem);
		Vector<Tv> ret = *this;
		ret -= n;
		return ret;
	};
	
	Vector<Tv>& operator *=(const Vector<Tv>& n) {
		*this = *this * n;
		return *this;
	};

	double l2Norm() const {
		double norm = 0.;
		for (int i = 0; i < no_elem; ++i)
			norm += data[i] * data[i];
		return sqrt(norm);
	}

	friend ostream& operator <<(ostream& out, const Vector<Tv>& n) {
		for (size_t i = 0; i < n.no_elem; i++)
		{
			out << n.data[i] << endl;
		}
		return out;
	};

	friend istream& operator >>(istream& in, const Vector<Tv>& n) {
		for (size_t i = 0; i < n.no_elem; i++)
		{
			in >> n.data[i];
		}

		return in;
	};

	// getter for private membaz
	size_t size() const { return no_elem; };

};
