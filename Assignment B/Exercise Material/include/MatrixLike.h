#pragma once

// forward declarations
template<typename T, size_t no_elem>
class Vector;

template<typename T, typename Derived, size_t no_rows, size_t no_cols >
class MatrixLike {
public:
	/// c'tor/ d'tor
	virtual ~MatrixLike ( ) noexcept = 0; // pure virtual destructor

	/// virtual operators
	virtual Vector<T, no_rows> operator* (const Vector<T, no_rows> & o) const = 0;

	/// other functions
	virtual Derived inverseDiagonal( ) const = 0;
	// feel free to extend as required

protected:
};

// MatrixLike d'tor implementation
template<typename T, class Derived, size_t no_rows,size_t no_cols>
inline MatrixLike<T, Derived, no_rows, no_cols>::~MatrixLike ( ) noexcept { }
