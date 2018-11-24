#include <iostream>
#include <chrono>

#include "Matrix.h"
#include "Vector.h"
#include "Stencil.h"


#define PI 3.141592653589793

template<typename T, typename MatrixImpl, size_t numPoints>
void solve(const MatrixLike<T, MatrixImpl, numPoints, numPoints>& A,
		   const Vector<T, numPoints>& b, 
		   Vector<T, numPoints>& u)
{	

	double initRes = (b - A * u).l2Norm( ); // determine the initial residual
	double curRes = initRes;
	std::cout << "Initial residual:\t\t" << initRes << std::endl;

	unsigned int curIt = 0; // store the current iteration index

	while (curRes > 1.e-5 * initRes) { // solve until the residual is reduced by a certain amount
		++curIt;

		u += A.inverseDiagonal( ) * (b - A * u); // Jacobi step

		curRes = (b - A * u).l2Norm( ); // update the residual

		if (0 == curIt % 500) { // print some info every few steps
			std::cout << "Residual after iteration " << curIt << ":\t" << curRes << std::endl;
		}
	}

	std::cout << "Residual after iteration " << curIt << ":\t" << curRes << std::endl << std::endl; // print the final number of iterations and the final residual
}

template<size_t numPoints>
double testFullMatrix () {
	const double hx = 1. / (numPoints - 1);
	const double hxSq = hx * hx;

	//const size_t numPoints = (const size_t)numGridPoints;

	std::cout << "Starting full matrix solver for " << numPoints << " grid points" << std::endl;

	Matrix<double, numPoints, numPoints> A( 0. );
	Vector<double, numPoints> u( 0.);
	Vector<double, numPoints> b( 0.);

	A(0, 0) = 1.;
	for (int x = 1; x < numPoints - 1; ++x) {
		A(x, x - 1) = 1. / hxSq;
		A(x, x) = -2. / hxSq;
		A(x, x + 1) = 1. / hxSq;
	}
	A(numPoints - 1, numPoints - 1) = 1.;

	for (int x = 0; x < numPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numPoints - 1)));
	}

	std::cout << "Initialization complete\n";
	//std::cout <<"A: " << A <<"b: " << b << "u: " << u;

	// start timing
	//MatrixLike<double, Matrix<double>> A = A;
	auto start = std::chrono::system_clock::now();
	
	solve<double, Matrix<double, numPoints, numPoints>, numPoints>( A, b, u);
	// end timing and print elapsed time
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	cout << "elapsed seconds: " << elapsed.count() << endl;
	return elapsed.count();
}

template<size_t numPoints>
double testStencil() {

	const double hx = 1. / (numPoints - 1);
	const double hxSq = hx * hx;

	std::cout << "Starting full Stencil solver for " << numPoints << " grid points" << std::endl;

	Stencil<double> sten = Stencil<double>({ { 0, 1. } }, { { -1, 1. / hxSq },{ 0, -2. / hxSq },{ 1, 1. / hxSq } });
	Vector<double> u(numPoints, 0.);
	Vector<double> b(numPoints, 0.);

	for (int x = 0; x < numPoints; ++x) {
		b(x) = sin(2. * PI * (x / (double)(numPoints - 1)));
	}

	std::cout << "Initialization complete\n";
	//std::cout << "using Stencil\n" << "b: " << b << "u: " << u;

	// start timing
	//MatrixLike<double, Matrix<double>> A = A;
	auto start = std::chrono::system_clock::now();

	solve<double, Stencil<double>, numPoints>(sten, b, u);
	// end timing and print elapsed time
	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed = end - start;
	cout << "elapsed seconds: " << elapsed.count() << endl;
	return elapsed.count();
}

int main(int argc, char** argv) {
	double s17 = testStencil<17>();
	double s33 = testStencil<33>();
	double s65 = testStencil<65>();
	double s129 = testStencil<129>();

	double m17 = testFullMatrix<17>(); // 146
	double m33 = testFullMatrix<33>(); // 594
	double m65 = testFullMatrix<65>();	
	double m129 = testFullMatrix<129>();

	cout << "stats:\n";
	cout << "stencil times: " << s17 << '\t' << s33 << '\t' << s65 << '\t' << s129 << '\n';
	cout << "matrix times: " << m17 << '\t' << m33 << '\t' << m65 << '\t' << m129 << '\n';

	int a;
	cin >> a;
}
