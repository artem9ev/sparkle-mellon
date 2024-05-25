
#define _SILENCE_AMP_DEPRECATION_WARNINGS
#include <iostream>
#include <vector>
#include <chrono>
#include <amp.h>

using namespace std;
using namespace std::chrono;
using namespace concurrency;


void MatrixMult_AMP(double* C, const double* A, const double* B, int M, int N, int K) {
	array_view<const double, 2> a(M, K, A), b(K, N, B);
	array_view<double, 2> c(M, N, C);
	c.discard_data();
	parallel_for_each(c.extent, [=](index<2> indx) restrict(amp)
		{
			int row = indx[0]; 
			int col = indx[1];
			double sum = 0;
			for (int i = 0; i < b.extent[0]; i++)
			{
				sum += a(row, i) * b(col, i);
			}
			c[indx] = sum;
		});
	c.synchronize();
}
void MatrixMult(double* C, const double* A, const double* B, int M, int N, int K) {
	for (int row = 0; row < M; row++)
	{
		for (int col = 0; col < N; col++)
		{
			double sum = 0;
			for (int i = 0; i < K; i++)
			{
				sum += A[row * K + i] * B[i * N + col];
			}
			C[row * N + col] = sum;
		}
	}
}

//int main() {
//	const int n = 5;
//	int M, N, K;
//	M = N = K = n;
//	double* pa = new double[n * n];
//	for (int i = 0; i < n * n; i++) {
//		pa[i] = 1;
//	}
//	double* pb = new double[n * n];
//	for (int i = 0; i < n * n; i++) {
//		pb[i] = 2;
//	}
//	double* pc = new double[n * n];
//	for (int i = 0; i < n * n; i++) {
//		pc[i] = 0;
//	}
//	auto t0 = high_resolution_clock::now();
//
//	MatrixMult_AMP(pc, pa, pb, M, N, K);
//
//	auto t1 = high_resolution_clock::now();
//
//	MatrixMult(pc, pa, pb, M, N, K);
//
//	auto t2 = high_resolution_clock::now();
//	cout << chrono::duration_cast<milliseconds>(t1 - t0).count() << "msec" << endl;
//	cout << chrono::duration_cast<milliseconds>(t2 - t1).count() << "msec" << endl;
//}
		
int main()
{
    vector<accelerator> accelerators = accelerator::get_all();
    cout << "size: " << accelerators.size() << endl;
	for (int i = 0; i < accelerators.size(); i++)
	{
		wcout << "acc " << accelerators[i].get_description() << endl;
	}
	wcout << accelerator(accelerator::default_accelerator).description << endl;
	wcout << "mem: " << accelerators[0].get_dedicated_memory() << endl;
	wcout << "path: " << accelerators[0].get_device_path() << endl;
	wcout << accelerators[0].get_supports_double_precision() << endl;
}