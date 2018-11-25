#pragma once

#include <cassert>
#include <utility> //std::swap
#include <algorithm> // std::find_if
#include <vector>

#include "MatrixLike.h"

template<typename T>
using StencilEntry = std::pair<int, T>; // convenience type for stencil entries

template<typename T, size_t no_rows, size_t no_cols>
class Stencil : public MatrixLike<T, Stencil<T, no_rows, no_cols>, no_rows, no_cols> {
public:
	Stencil(const std::vector<StencilEntry<T> >& boundaryEntries, const std::vector<StencilEntry<T> >& innerEntries)
		: boundaryStencil_(boundaryEntries), innerStencil_(innerEntries) { }

	Stencil(const std::vector<StencilEntry<T> >& innerEntries)	// c'tor for stencils w/o explicit boundary handling
		: boundaryStencil_(innerEntries), innerStencil_(innerEntries) { }

	Stencil(const Stencil & o) : innerStencil_(o.innerStencil_), boundaryStencil_(o.boundaryStencil_) { }

	//Stencil(Stencil && o) noexcept;

	~Stencil( ) noexcept override { }

	Stencil& operator=(const Stencil & o) {
		innerStencil_ = o.innerStencil_;
		boundaryStencil_ = o.boundaryStencil_;
	};
	//Stencil& operator=(Stencil && o) noexcept;

	// HINT: stencil entries are stored as offset/coefficient pair, that is the offset specifies which element of a
	// vector, relative to the current index, is to be regarded. It is then multiplied with the according coefficient.
	// All of these expressions are evaluated and then summed up to get the final result.
	Vector<T, no_rows> operator* (const Vector<T, no_cols> & o) const override {
		Vector<T, no_rows> ret(0.);
		int no_ro = (int)no_rows;
		std::vector < StencilEntry<T> > io_sten;
		for (int i = 0; i < no_ro; ++i)
		{
			if (!(i == 0 || i == no_ro - 1)) io_sten = innerStencil_;
			else io_sten = boundaryStencil_;
			ret(i) = (T)0;
			for (int j = 0; j < io_sten.size(); ++j) {
				// starting from pos i at vector multiply and sum offsetted entries with respective stencil
				int offset = io_sten[j].first;
				T value = io_sten[j].second;
				assert(i + offset >= 0 && i + offset < no_ro);
				ret(i) += o(i + offset) * value;
			}
		}
		return ret;
	};

	Stencil<T, no_rows, no_cols> inverseDiagonal() const override {
		//static_assert(no_rows == no_cols);
		auto inner = find_if(innerStencil_.begin(), innerStencil_.end(), [](const StencilEntry<T> & s) {return s.first == 0; });
		auto bound = find_if(boundaryStencil_.begin(), boundaryStencil_.end(), [](const StencilEntry<T> & s) {return s.first == 0; });
		assert(inner->second != 0);
		assert(bound->second != 0);

		Stencil<T, no_rows, no_cols> ret({ {0, 1/bound->second} }, { {0, 1/inner->second} });

		/*
		Stencil<T, no_rows, no_cols> ret = *this;
		for (int i = 0; i < ret.boundaryStencil_.size(); ++i) {
			if (ret.boundaryStencil_[i].first != 0) {
				ret.boundaryStencil_[i].second = 0;
			}
			else {
				assert(ret.boundaryStencil_[i].second != 0);
				ret.boundaryStencil_[i].second = 1 / ret.boundaryStencil_[i].second;
			}
		};
		for (int i = 0; i < ret.innerStencil_.size(); ++i) {
			if (ret.innerStencil_[i].first != 0) {
				ret.innerStencil_[i].second = 0;
			}
			else {
				assert(ret.innerStencil_[i].second != 0);
				ret.innerStencil_[i].second = 1 / ret.innerStencil_[i].second;
			}
		};
		*/
		return ret;
	};

	friend ostream& operator <<(ostream& out, const Stencil<T, no_rows, no_cols>& n) {
		//out << n.boundaryStencil_;
		//out << n.innerStencil_;
		out << "boundary\t{\t";
		for each (StencilEntry<T> var in n.boundaryStencil_)
		{
			out << var.second << ",\t";
		}
		out << "}\n";
		out << "inner\t\t{\t";
		for each (StencilEntry<T> var in n.innerStencil_)
		{
			out << var.second << ",\t";
		}
		out << "}\n";
		//cout << n.boundaryStencil_ << '\n';
		return out;
	};

protected:
	// containers for the stencil entries -> boundary stencils represent the first and last rows of a corresponding
	// matrix and are to be applied to the first and last element of a target vector; inner stencils correspond to
	// the remaining rows of the matrix
	std::vector<StencilEntry<T> > boundaryStencil_;	// feel free to change the datatype if convenient
	std::vector<StencilEntry<T> > innerStencil_;	// feel free to change the datatype if convenient
};
