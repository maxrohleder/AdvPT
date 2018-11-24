// this file is just for documenting the required interface to compile with VectorTvest.cpp (declarations only)
#include <iostream>
#include <assert.h>
#include <functional>

using namespace std;

template <typename Tv, size_t no_elem>
class Vector {
private:
	Tv *data = nullptr;
public:
	// normal constructor
	Vector(Tv initValue) : data(new Tv[no_elem]) {
		for (size_t i = 0; i < no_elem; i++) data[i] = initValue;
	};
	// lambda constructor
	Vector(std::function<Tv(int i)> init) {
		for (size_t i = 0; i < no_elem; i++) data[i] = init(i);
	};
	// destructor
	~Vector() { delete[] data; };
	// copy constructor
	Vector(const Vector<Tv, no_elem>& n) : data(new Tv[no_elem]) {
		for (size_t i = 0; i < no_elem; i++) data[i] = n.data[i];
	};
	// assignment just calls copy constructor
	Vector<Tv, no_elem>& operator=(const Vector<Tv, no_elem>& n) {
		if (*this == n) return *this;
		delete[] data;
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
	bool operator ==(const Vector<Tv, no_elem>& n) const {
		//if (no_elem != n.no_elem) return false; not neccessary anymore
		for (size_t i = 0; i < no_elem; i++) if (data[i] != n.data[i]) return false;
		return true;
	};
	// elementwise negative comparison
	bool operator !=(const Vector<Tv, no_elem>& n) const { return !(*this == n); };

	// arithmetic operators
	// element wise addition
	Vector<Tv, no_elem>& operator +=(const Vector<Tv, no_elem>& n) {
		//assert(no_elem == n.no_elem);
		for (size_t i = 0; i < no_elem; i++) data[i] += n.data[i];
		return *this;
	};

	Vector<Tv, no_elem> operator +(const Vector<Tv, no_elem>& n) const {
		//assert(no_elem == n.no_elem);
		Vector ret = *this;
		ret += n;
		return ret;
	};
	// elementwise subtraction
	Vector<Tv, no_elem>& operator -=(const Vector<Tv, no_elem>& n) {
		//assert(no_elem == n.no_elem);
		for (size_t i = 0; i < no_elem; i++) data[i] -= n.data[i];
		return *this;
	};

	Vector<Tv, no_elem> operator -(const Vector<Tv, no_elem>& n) const {
		//assert(no_elem == n.no_elem);
		Vector<Tv, no_elem> ret = *this;
		ret -= n;
		return ret;
	};
	
	Vector<Tv, no_elem>& operator *=(const Vector<Tv, no_elem>& n) {
		*this = *this * n;
		return *this;
	};

	double l2Norm() const {
		double norm = 0.;
		for (int i = 0; i < no_elem; ++i)
			norm += data[i] * data[i];
		return sqrt(norm);
	};

	friend ostream& operator <<(ostream& out, const Vector<Tv, no_elem>& n) {
		for (size_t i = 0; i < n.no_elem; i++)
		{
			out << n.data[i] << endl;
		}
		return out;
	};

	friend istream& operator >>(istream& in, const Vector<Tv, no_elem>& n) {
		for (size_t i = 0; i < n.no_elem; i++)
		{
			in >> n.data[i];
		}

		return in;
	};

	// getter for private membaz
	size_t size() const { return no_elem; };

};
