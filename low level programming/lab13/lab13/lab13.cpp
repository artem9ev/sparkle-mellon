
#define _SILENCE_AMP_DEPRECATION_WARNINGS
#include <iostream>
#include <vector>
#include <chrono>
#include <amp.h>

using namespace std;
using namespace std::chrono;
using namespace concurrency;


void MatrixMult_AMP(double* C, const double* A, const double* B, int n) {
	array_view<const double, 2> a(n, n, A), b(n, n, B);
	array_view<double, 2> c(n, n, C);
	c.discard_data();
	parallel_for_each(c.extent, [=](index<2> indx) restrict(amp)
		{
			int row = indx[0]; 
			int col = indx[1];
			double sum = 0;
			for (int i = 0; i < b.extent[0]; i++)
			{
				sum += a(row, i) * b(i, col);
			}
			c[indx] = sum;
		});
	c.synchronize();
}

void MultParall(const double* A, const double* B, double* C, int n) {
	array_view<const double, 2> a(n, n, A);
	array_view<const double, 2> b(n, n, B);
	array_view<double, 2> c(n, n, C);
	c.discard_data();
	parallel_for_each(c.extent, [=](index<2> indx) restrict(amp)
		{
			int row = indx[0];
			int col = indx[1];
			double sum = 0;
			for (int i = 0; i < b.extent[0]; i++)
			{
				sum += a(row, i) * b(i, col);
				c[indx] = sum;
			}
		});
	c.synchronize();
}

void MatrixMult(double* C, const double* A, const double* B, int n) {
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			double sum = 0;
			for (int i = 0; i < n; i++)
			{
				sum += A[row * n + i] * B[i * n + col];
			}
			C[row * n + col] = sum;
		}
	}
}

int main() {
	const int n = 5;
	int M, N, K;
	M = N = K = n;
	double* pa = new double[n * n];
	for (int i = 0; i < n * n; i++) {
		pa[i] = 1;
	}
	double* pb = new double[n * n];
	for (int i = 0; i < n * n; i++) {
		pb[i] = 2;
	}
	double* pc = new double[n * n];
	for (int i = 0; i < n * n; i++) {
		pc[i] = 0;
	}
	auto t0 = high_resolution_clock::now();

	MatrixMult_AMP(pc, pa, pb, n);

	auto t1 = high_resolution_clock::now();

	MatrixMult(pc, pa, pb, n);

	auto t2 = high_resolution_clock::now();
	cout << "GPU: " << chrono::duration_cast<milliseconds>(t1 - t0).count() << "msec" << endl;
	cout << "CPU: " << chrono::duration_cast<milliseconds>(t2 - t1).count() << "msec" << endl;
}