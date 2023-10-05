#include <iostream>
#include <time.h>

using namespace std;

void createNumber(int* N, int length) {
	for (int i = 0; i < length; i++)
	{
		N[i] = rand() % 10;
	}
}
int* transform(int* A, int from, int to) {
	int* N = new int[to];
	for (int i = to - 1, k = from - 1; i >= 0; i--, k--)
	{
		if (k >= 0)
		{
			N[i] = A[k];
		}
		else
		{
			N[i] = 0;
		}
	}
	return N;
}
void print(int* A, int length) {
	for (int i = 0; i < length; i++)
	{
		cout << A[i];
	}
	cout << endl;
}

// при перемножении считаем что числа положительны

// учитывать ситуации когда в начале числа получаются нули

// делим числа как A = A2-00..00+A1 и B = B2-00..00+B1

// C = A * B = (A2 * B2)(b^n + b^(n/2)) + ((A2 - A1) * (B1 - B2)) + (A1 * B1)(b^(n/2) + 1)

//number* mult(number* A, number* B) {
//	number* A2, A1, B2, B1;
//	int size = A.n;
//	A2 = { new int[size / 2], A2.n = size / 2 };
//	A1 = { new int[size / 2], A1.n = size / 2 };
//	B2 = { new int[size / 2], B2.n = size / 2 };
//	B1 = { new int[size / 2], B1.n = size / 2 };
//	for (int i = 0; i < size; i++)
//	{
//		if (i < size / 2)
//		{
//			A2.a[i] = A.a[i];
//			B2.a[i] = B.a[i];
//		}
//		else
//		{
//			A1.a[i] = A.a[i];
//			B1.a[i] = B.a[i];
//		}
//	}
//	number C = {};
//	number m1 = mult(A2, B2);
//	number t1 = sh(m1, size);
//	number t2 = sh(m1, size / 2);
//	number a1 = add(t1, t2);
//
//	return C;
//
//	// m1 = mult(A2, B2)
//	// a1 = add( sh(m1, size), sh(m1, size / 2) )
//
//	// s1 = sub(A2, A1)
//	// s2 = sub(B1, B2)
//	// m2 = mult(s1, s2)
//	// a3 = sh(m2, size / 2)
//
//	// m3 = mult(A1, B1)
//	// a1 = add( sh(m3, size / 2), m3 )
//}
/*number add(number A, number B) {
	int z = 0;
	int size = (A.n > B.n) ? A.n : B.n;
	number C = { new int[size + 1], size + 1 };;
	for (int i = size - 1; i >= 0; i--) // идем по цифрам A и B
	{
		C.a[i + 1] = (A.a[i] + B.a[i] + z) % 10;
		z = (A.a[i] + B.a[i] + z) / 10;
	}
	C.a[0] = z;
	return C;
}*/

// sub может выдать отриц число
//     a0 a1 . . . aN-1 aN
//	z0 z1 z2 . . . zN    _
//     b0 b1 . . . bN-1 bN
//
// вычитание B из A

/*number* sub(number* A, number* B) {
	int size = (A->n > B->n) ? A->n : B->n;
	number* Z = new number;
	Z->a = new int[size];
	Z->n = size;
	number* C = new number;
	C->a = new int[size + 1];
	C->n = size + 1;
	for (int i = 0; i < size + 1; i++)
	{
		C->a[i] = 0;
	}
	for (int i = 0; i < size + 1; i++)
	{
		Z->a[i] = 0;
	}
	for (int i = size - 1, k = i; i >= 0; i--, k = i)
	{

		if (B->a[i] > A->a[i])
		{
			while (k >= 0)
			{
				cout << "!!!" << endl;
				Z->a[k] = -1;
				A->a[k] += 10;
				A->a[k - 1]--;
				k--;
				if (A->a[k] >= 0)
				{
					break;
				}
			}
		}
		cout << "id(" << (i) << ") a: " << A->a[i] << "\tb:" << B->a[i];
		if (i < size - 1)
		{
			cout << "\tz: " << Z->a[i + 1];
		}
		cout << endl;
		C->a[i + 1] = A->a[i] - B->a[i];
	}
	for (int i = 0; i < size + 1; i++)
	{
		cout << C->a[i];
	}
	cout << endl;
	if (Z->a[0] == -1)
	{
		number* t = new number;
		t->a = new int[size + 1];
		t->n = size + 1;
		t->a[0] = 0;
		for (int i = size; i >= 0; i--)
		{
			if (C->a[i] == 0)
			{
				t->a[i] = 0;
			}
			else
			{
				t->a[i] = 10;
				while (i > 1)
				{
					i--;
					t->a[i] = 9;
				}
				break;
			}
			if (i == 0)
			{
				t->a[0] = 1;
			}
		}
		cout << "t: ";
		for (int i = 0; i < size + 1; i++)
		{
			cout << t->a[i];
		}
		cout << endl;
		for (int i = 0; i < size; i++)
		{
			Z->a[i] = 0;
		}
		for (int i = size, k = i; i >= 0; i--, k = i)
		{
			C->a[i] = t->a[i] - C->a[i];
		}
		C->a[0] = -1;
	}
	for (int i = 0; i < size + 1; i++)
	{
		cout << C->a[i];
	}
	cout << endl;
	return C;
}*/

// сдвиг числа на z чисел влево (экв. умножению на 10^z)
int* sh(int* A, int size, int z) {
	int* N = new int[size]; 
	for (int i = z; i < size; i++)
	{
		N[i - z] = A[i];
		if (i >= size - z)
		{
			N[i] = 0;
		}
	}
	return N;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	int n;
	cout << "Введите размер чисел A и B: ";
	cin >> n;
	int* A = new int[n], * B = new int[n];
	createNumber(A, n); createNumber(B, n);
	A = transform(A, n, n * 2);
	B = transform(B, n, n * 2);
	n *= 2;
	cout << "A: "; print(A, n);
	cout << "B: "; print(B, n);

	int* J = sh(A, n, 2);
	cout << "J: "; print(J, n);
}
