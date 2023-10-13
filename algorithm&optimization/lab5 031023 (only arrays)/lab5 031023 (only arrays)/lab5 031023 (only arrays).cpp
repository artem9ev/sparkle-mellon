#include <iostream>
#include <time.h>
#pragma comment(linker, "/STACK:104857600")

using namespace std;

long long steps = 0;

struct number {
	int* a;
	int n;
};

// ввод числа
void inputNumber(number* N, int size, int length) {
	int a; cin >> a;
	a += pow(10, size);
	for (int i = a, k = size - 1; i > 0 && k >= 0; i /= 10, k--)
	{
		N->a[k] = i % 10;
	}
}
// генерирует число
void createNumber(number* N) {
	for (int i = N->a[i] - 1; i >= 0; i--)
	{
		N->a[i] = rand() % 10;
	}
}
// выводит число A
void print(number* A) {
	for (int i = 0; i < A->n; i++)
	{
		cout << A->a[i];
	}
	cout << endl;
}

// при перемножении считаем что числа положительны

// учитывать ситуации когда в начале числа получаются нули

// делим числа как A = A2-00..00+A1 и B = B2-00..00+B1

// C = A * B = (A2 * B2)(b^n + b^(n/2)) + ((A2 - A1) * (B1 - B2)) + (A1 * B1)(b^(n/2) + 1)

// сумма чисел A и B
number* add(number* A, number* B, int size) {
	//steps_i += 2;
	int z = 0;
	int p;
	int* C = new int[size];
	/*cout << "\tsum: ";
	for (int i = 0; i < size; i++)
	{
		C[i] = 0;
		cout << A[i];
	}
	cout << " + ";
	for (int i = 0; i < size; i++)
	{
		cout << B[i];
	}
	cout << endl;*/
	for (int i = size - 1; i >= 0; i--) // идем по цифрам A и B
	{
		p = (A[i] + B[i] + z);
		C[i] = p % 10;
		z = p / 10;
		//steps_i += 7;
	}
	return C;
}

// sub может выдать отриц число
//     a0 a1 . . . aN-1 aN
//	z0 z1 z2 . . . zN    0
//     b0 b1 . . . bN-1 bN

// вычитание B из A
number* sub(number* A, number* B, int size) {
	bool isPositive = true;
	int* C = new int;
	C = new int[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = 0;
		//steps_i++;

	}
	for (int i = size - 1, k = i; i >= 0; i--, k = i) // первый цикл вычитания (сработвет только он если A > B)
	{
		// если цифра B больше цифры A, то ищем десяток в A, у которого можно занять 10 для вычитания
		// или же продолжеам занимать десятки, пока не найдем цифру у которой можно его занять.
		// допустим, что мы вычитаем 9 от 1000, тогда: (точки стоят между цифрами числа)
		// (1.0.0.0) - (9) => (1.0.-1.10) - (9) => (1.-1.9.10) - (9) => (0.9.9.10) - (9) => (9.9.10) - (9) === 991
		while (B[i] > A[i] || k > 0 && A[k] < 0) // 
		{
			A[k] += 10; // добавляем занятый десяток
			A[k - 1]--; // забираем десяток
			k--;
			isPositive = k + 1; // когда k дойдет до значения -1, то число будет считаться как отрицателье
			//steps_i += 9;
		}
		C[i] = A[i] - B[i];
		//steps_i += 5;
		/*cout << "id(" << (i) << ") a: " << A[i] << "\tb:" << B[i];
		cout << "\tc = " << (A[i] - B[i]) << endl;*/
	}
	/*cout << (isPositive ? "positive" : "negative") << endl;*/
	if (!isPositive) // если число B оказалось больше чем A (необходимо получить отрицательное число)
	{
		int* t = new int[size]; // особое число, которое больше полученного числа (если в числе было 3 цифры, то это будет число = 10^3)
								// оно будет представленно в виде (9.9.10), чтобы от него можно было быстрее отнять
		int u = size - 1;
		while (C[u] == 0) // если в конце полученного числа есть нули, то в конце этого числа будут тоже нули на соот. позициях
		{
			t[u] = 0;
			u--;
			//steps_i += 3;
		}
		t[u--] = 10;
		while (u >= 0)
		{
			t[u--] = 9;
			//steps_i += 3;
		}
		for (int i = size - 1; i >= 0; i--)
		{
			C[i] = t[i] - C[i];
			//steps_i += 2;
		}
		int y = 0;
		while (y < size && C[y] == 0)
		{
			y++;
			//steps_i += 2;
		}
		C[y] *= -1;
		//steps_i += 12;

		delete[] t;
	}
	//steps_i += 3;
	return C;
}

// сдвиг числа на z чисел влево (экв. умножению на 10^z)
number* sh(number* A, int z) {
	int* N = new int[size]; 
	for (int i = z; i < size; i++)
	{
		N[i - z] = A[i];
		if (i >= size - z)
		{
			N[i] = 0;
			//steps_i++;
		}
		//steps_i += 4;
	}
	//steps_i++;
	//delete[] A;
	return N;
}

number* mult(number* A, number* B, int size, int n) {
	int* C = new int[size];
	int* m1 = new int[size];
	int* m2 = new int[size];
	int* m3 = new int[size];
	cout << steps << endl;
	for (int i = 0; i < size; i++)
	{
		C[i] = 0;
		m1[i] = 0;
		m2[i] = 0;
		m3[i] = 0;
	}
	if (n == 2) // n = 2 (кол-во цифр в числе = 2)
	{
		//cout << "----------- !!! n = 2:" << endl;
		int s = size - 2, f = size - 1;
		m1[f] = (A[s] * B[s]) % 10;
		m1[s] = (A[s] * B[s]) / 10;
		//cout << "\tA2 * B2: ";  print(m1, size);
		m1 = add(sh(m1, size, 2), sh(m1, size, 1), size); // (A2 * B2)(100 + 10)
		//cout << "\tm1 * 110: ";  print(m1, size);
		
		m3[f] = (A[f] * B[f]) % 10;
		m3[s] = (A[f] * B[f]) / 10;
		//cout << "\tA1 * B1: ";  print(m3, size);
		m3 = add(sh(m3, size, 1), m3, size); // (A1 * B1)(10 + 1)
		//cout << "\tm3 * 11: ";  print(m3, size);

		m1 = add(m1, m3, size);
		//cout << "\tm1 + m3: ";  print(m1, size);

		int s1 = A[s] - A[f]; // A2 - A1
		int s2 = B[f] - B[s]; // B1 - B2 --- !!!!!!!
		m2[f] = (abs(s1) * abs(s2)) % 10;
		m2[s] = (abs(s1) * abs(s2)) / 10;
		m2 = sh(m2, size, 1);
		//cout << "\tm2: ";  print(m2, size);
		if (s1 < 0 && s2 > 0 || s1 > 0 && s2 < 0)
		{
			C = sub(m1, m2, size);
		}
		else
		{
			C = add(m1, m2, size);
		}
		return C;
	}
	else
	{
		int* A2 = new int[size];
		int* A1 = new int[size];
		int* B2 = new int[size];
		int* B1 = new int[size];
		//cout << "----------- ??? рекурсия еьать:" << endl;
		int start = size - n; // индекс начала чисел A2, A1, B2, B1
		int h = n / 2;
		for (int i = size - 1; i >= 0; i--)
		{
			if (i >= start + h)
			{
				A2[i] = A[i - h];
				B2[i] = B[i - h];
				steps += 4;
			}
			else
			{
				A2[i] = 0; B2[i] = 0;
				steps += 2;
			}
			steps += 2;
		}
		for (int i = size - 1; i >= 0; i--)
		{
			if (i >= start + h)
			{
				A1[i] = A[i];
				B1[i] = B[i];
				steps += 2;
			}
			else
			{
				A1[i] = 0; B1[i] = 0;
				steps += 2;
			}
			steps += 2;
		}
		/*cout << "A1: "; print(A1, size);
		cout << "A2: "; print(A2, size);
		cout << "B1: "; print(B1, size);
		cout << "B2: "; print(B2, size);*/

		//cout << "(m1) A2 * B2: ";
		m1 = mult(A2, B2, size, h);
		//cout << "res\n(m1) A2 * B2 = "; print(m1, size);
		int* a1 = add(sh(m1, size, n), sh(m1, size, h), size);

		//cout << "(m3) A1 * B1: ";
		m3 = mult(A1, B1, size, h);
		//cout << "res\n(m3) A1 * B1 = "; print(m3, size);
		int* a3 = add(sh(m3, size, h), m3, size);

		m1 = add(a1, a3, size);

		int* sA = sub(A2, A1, size);
		int* sB = sub(B1, B2, size);
		//cout << "(sA) A2 - A1 = "; print(sA, size);
		//cout << "(sB) B1 - B2 = "; print(sB, size);
		bool isPosA = true, isPosB = true;
		for (int i = start; i < size; i++)
		{
			if (sA[i] < 0)
			{
				isPosA = false;
				sA[i] *= -1;
				break;
			}
		}
		for (int i = start; i < size; i++)
		{
			if (sB[i] < 0)
			{
				isPosB = false;
				sB[i] *= -1;
				break;
			}
		}
		//cout << "(m1) sA * sB: ";
		m2 = mult(sA, sB, size, h);
		m2 = sh(m2, size, h);
		//cout << "res\n(m2) sA * sB = "; print(m2, size);
		if (isPosA && isPosB || !isPosA && !isPosB)
		{
			C = add(m1, m2, size);
		}
		else
		{
			C = sub(m1, m2, size);
		}

		/*delete[] A2;
		delete[] A1;
		delete[] B2;
		delete[] B1;*/
	}

	delete[] m1;
	delete[] m2;
	delete[] m3;

	return C;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	//int n, l = 0;
	//long long s[12];
	//for (int i = 0; i < 12; i++)
	//{
	//	s[i] = 0;
	//}
	//// 8 16  32 64 128 256 512 1024 2048 4096 8192 16384
	//for (int h = 8, l = 0; h <= 16384; h *= 2, l++)
	//{
	//	n = h * 2;
	//	int* A = new int[n], * B = new int[n];
	//	for (int k = 0; k < 40; k++)
	//	{
	//		steps = 0;
	//		createNumber(A, n, h); createNumber(B, n, h);
	//		int* C = mult(A, B, n, n / 2);
	//		cout << "A: "; print(A, n);
	//		cout << "B: "; print(B, n);
	//		cout << "C: "; print(C, n);
	//		cout << "k =\t" << k << "\tsteps = " << steps << endl;
	//		s[l] += steps;
	//	}
	//	delete[] A;
	//	delete[] B;
	//	delete[] C;
	//	cout << "--------------------------------" << endl;
	//	cout << "n = " << h << endl;
	//	cout << fixed << "steps: " << ((float)s[l] / 100) << endl;
	//}
	//for (int i = 0, n = 8; i < 12; i++, n *= 2)
	//{
	//	cout << fixed << "n =\t" << n << "\tsteps: " << ((float)s[l] / 100) << endl;
	//}
	int n;
	cout << "Введите размер чисел A и B: ";
	cin >> n;
	number* A = new number { new int[n], n };
	number* B = new number { new int[n], n };
	//cout << "A: "; inputNumber(A, n, h); cout << "B: "; inputNumber(B, n, h);
	createNumber(A); createNumber(B);
	cout << "A: "; print(A);
	cout << "B: "; print(B);
	//int* F = sub(A, B, n);
	int* J = sh(A, 2);
	//number* C = mult(A, B, n, n / 2);
	cout << "C: "; print(C);
	cout << "steps: " << steps;
}

/*#include <iostream>
#include <time.h>
#pragma comment(linker, "/STACK:104857600")

using namespace std;

long long steps_i = 0;
// ввод числа
void inputNumber(int* N, int size, int length) {
	int a; cin >> a;
	a += pow(10, size);
	for (int i = size - 1; i > 0; i--)
	{
		N[i] = 0;
	}
	for (int i = a, k = size - 1; i > 0 && k >= size - length; i /= 10, k--)
	{
		N[k] = i % 10;
	}
}
// генерирует число
void createNumber(int* N, int size, int length) {
	for (int i = size - 1; i >= 0; i--)
	{
		N[i] = 0;
		if (i >= size - length)
		{
			N[i] = rand() % 10;
		}
	}
}
// выводит число A
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

// сумма чисел A и B
int* add(int* A, int* B, int size) {
	//steps_i += 2;
	int z = 0;
	int p;
	int* C = new int[size];
	/*cout << "\tsum: ";
	for (int i = 0; i < size; i++)
	{
		C[i] = 0;
		cout << A[i];
	}
	cout << " + ";
	for (int i = 0; i < size; i++)
	{
		cout << B[i];
	}
	cout << endl;
	for (int i = size - 1; i >= 0; i--) // идем по цифрам A и B
	{
		p = (A[i] + B[i] + z);
		C[i] = p % 10;
		z = p / 10;
		//steps_i += 7;
	}
	return C;
}

// sub может выдать отриц число
//     a0 a1 . . . aN-1 aN
//	z0 z1 z2 . . . zN    0
//     b0 b1 . . . bN-1 bN

// вычитание B из A
int* sub(int* A, int* B, int size) {
	bool isPositive = true;
	int* C = new int;
	C = new int[size];
	for (int i = 0; i < size; i++)
	{
		C[i] = 0;
		//steps_i++;

	}
	for (int i = size - 1, k = i; i >= 0; i--, k = i) // первый цикл вычитания (сработвет только он если A > B)
	{
		// если цифра B больше цифры A, то ищем десяток в A, у которого можно занять 10 для вычитания
		// или же продолжеам занимать десятки, пока не найдем цифру у которой можно его занять.
		// допустим, что мы вычитаем 9 от 1000, тогда: (точки стоят между цифрами числа)
		// (1.0.0.0) - (9) => (1.0.-1.10) - (9) => (1.-1.9.10) - (9) => (0.9.9.10) - (9) => (9.9.10) - (9) === 991
		while (B[i] > A[i] || k > 0 && A[k] < 0) // 
		{
			A[k] += 10; // добавляем занятый десяток
			A[k - 1]--; // забираем десяток
			k--;
			isPositive = k + 1; // когда k дойдет до значения -1, то число будет считаться как отрицателье
			//steps_i += 9;
		}
		C[i] = A[i] - B[i];
		//steps_i += 5;
		/*cout << "id(" << (i) << ") a: " << A[i] << "\tb:" << B[i];
		cout << "\tc = " << (A[i] - B[i]) << endl;
	}
	/*cout << (isPositive ? "positive" : "negative") << endl;
	if (!isPositive) // если число B оказалось больше чем A (необходимо получить отрицательное число)
	{
		int* t = new int[size]; // особое число, которое больше полученного числа (если в числе было 3 цифры, то это будет число = 10^3)
								// оно будет представленно в виде (9.9.10), чтобы от него можно было быстрее отнять
		int u = size - 1;
		while (C[u] == 0) // если в конце полученного числа есть нули, то в конце этого числа будут тоже нули на соот. позициях
		{
			t[u] = 0;
			u--;
			//steps_i += 3;
		}
		t[u--] = 10;
		while (u >= 0)
		{
			t[u--] = 9;
			//steps_i += 3;
		}
		for (int i = size - 1; i >= 0; i--)
		{
			C[i] = t[i] - C[i];
			//steps_i += 2;
		}
		int y = 0;
		while (y < size && C[y] == 0)
		{
			y++;
			//steps_i += 2;
		}
		C[y] *= -1;
		//steps_i += 12;

		delete[] t;
	}
	//steps_i += 3;
	return C;
}

// сдвиг числа на z чисел влево (экв. умножению на 10^z)
int* sh(int* A, int size, int z) {
	int* N = new int[size];
	for (int i = z; i < size; i++)
	{
		N[i - z] = A[i];
		if (i >= size - z)
		{
			N[i] = 0;
			//steps_i++;
		}
		//steps_i += 4;
	}
	//steps_i++;
	//delete[] A;
	return N;
}

int* mult(int* A, int* B, int size, int n) {
	int* C = new int[size];
	int* m1 = new int[size];
	int* m2 = new int[size];
	int* m3 = new int[size];
	cout << steps_i << endl;
	for (int i = 0; i < size; i++)
	{
		C[i] = 0;
		m1[i] = 0;
		m2[i] = 0;
		m3[i] = 0;
		steps_i += 4;
	}
	if (n == 2) // n = 2 (кол-во цифр в числе = 2)
	{
		//cout << "----------- !!! n = 2:" << endl;
		int s = size - 2, f = size - 1;
		m1[f] = (A[s] * B[s]) % 10;
		m1[s] = (A[s] * B[s]) / 10;
		//cout << "\tA2 * B2: ";  print(m1, size);
		m1 = add(sh(m1, size, 2), sh(m1, size, 1), size); // (A2 * B2)(100 + 10)
		//cout << "\tm1 * 110: ";  print(m1, size);

		m3[f] = (A[f] * B[f]) % 10;
		m3[s] = (A[f] * B[f]) / 10;
		//cout << "\tA1 * B1: ";  print(m3, size);
		m3 = add(sh(m3, size, 1), m3, size); // (A1 * B1)(10 + 1)
		//cout << "\tm3 * 11: ";  print(m3, size);

		m1 = add(m1, m3, size);
		//cout << "\tm1 + m3: ";  print(m1, size);

		int s1 = A[s] - A[f]; // A2 - A1
		int s2 = B[f] - B[s]; // B1 - B2 --- !!!!!!!
		m2[f] = (abs(s1) * abs(s2)) % 10;
		m2[s] = (abs(s1) * abs(s2)) / 10;
		m2 = sh(m2, size, 1);
		//cout << "\tm2: ";  print(m2, size);
		if (s1 < 0 && s2 > 0 || s1 > 0 && s2 < 0)
		{
			C = sub(m1, m2, size);
			steps_i++;
		}
		else
		{
			C = add(m1, m2, size);
			steps_i++;
		}
		steps_i += 34;
		return C;
	}
	else
	{
		int* A2 = new int[size];
		int* A1 = new int[size];
		int* B2 = new int[size];
		int* B1 = new int[size];
		//cout << "----------- ??? рекурсия еьать:" << endl;
		int start = size - n; // индекс начала чисел A2, A1, B2, B1
		int h = n / 2;
		for (int i = size - 1; i >= 0; i--)
		{
			if (i >= start + h)
			{
				A2[i] = A[i - h];
				B2[i] = B[i - h];
				steps_i += 4;
			}
			else
			{
				A2[i] = 0; B2[i] = 0;
				steps_i += 2;
			}
			steps_i += 2;
		}
		for (int i = size - 1; i >= 0; i--)
		{
			if (i >= start + h)
			{
				A1[i] = A[i];
				B1[i] = B[i];
				steps_i += 2;
			}
			else
			{
				A1[i] = 0; B1[i] = 0;
				steps_i += 2;
			}
			steps_i += 2;
		}
		/*cout << "A1: "; print(A1, size);
		cout << "A2: "; print(A2, size);
		cout << "B1: "; print(B1, size);
		cout << "B2: "; print(B2, size);

		//cout << "(m1) A2 * B2: ";
		m1 = mult(A2, B2, size, h);
		//cout << "res\n(m1) A2 * B2 = "; print(m1, size);
		int* a1 = add(sh(m1, size, n), sh(m1, size, h), size);

		//cout << "(m3) A1 * B1: ";
		m3 = mult(A1, B1, size, h);
		//cout << "res\n(m3) A1 * B1 = "; print(m3, size);
		int* a3 = add(sh(m3, size, h), m3, size);

		m1 = add(a1, a3, size);

		int* sA = sub(A2, A1, size);
		int* sB = sub(B1, B2, size);
		//cout << "(sA) A2 - A1 = "; print(sA, size);
		//cout << "(sB) B1 - B2 = "; print(sB, size);
		bool isPosA = true, isPosB = true;
		for (int i = start; i < size; i++)
		{
			if (sA[i] < 0)
			{
				isPosA = false;
				sA[i] *= -1;
				steps_i += 3;
				break;
			}
			steps_i++;
		}
		for (int i = start; i < size; i++)
		{
			if (sB[i] < 0)
			{
				isPosB = false;
				sB[i] *= -1;
				steps_i *= 3;
				break;
			}
			steps_i++;
		}
		//cout << "(m1) sA * sB: ";
		m2 = mult(sA, sB, size, h);
		m2 = sh(m2, size, h);
		//cout << "res\n(m2) sA * sB = "; print(m2, size);
		if (isPosA && isPosB || !isPosA && !isPosB)
		{
			C = add(m1, m2, size);
			steps_i++;
		}
		else
		{
			C = sub(m1, m2, size);
			steps_i++;
		}
		steps_i += 19;

		/*delete[] A2;
		delete[] A1;
		delete[] B2;
		delete[] B1;
	}

	delete[] m1;
	delete[] m2;
	delete[] m3;

	steps_i += 2;
	return C;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	//int n, l = 0;
	//long long s[12];
	//for (int i = 0; i < 12; i++)
	//{
	//	s[i] = 0;
	//}
	//// 8 16  32 64 128 256 512 1024 2048 4096 8192 16384
	//for (int h = 8, l = 0; h <= 16384; h *= 2, l++)
	//{
	//	n = h * 2;
	//	int* A = new int[n], * B = new int[n];
	//	for (int k = 0; k < 40; k++)
	//	{
	//		steps = 0;
	//		createNumber(A, n, h); createNumber(B, n, h);
	//		int* C = mult(A, B, n, n / 2);
	//		cout << "A: "; print(A, n);
	//		cout << "B: "; print(B, n);
	//		cout << "C: "; print(C, n);
	//		cout << "k =\t" << k << "\tsteps = " << steps << endl;
	//		s[l] += steps;
	//	}
	//	delete[] A;
	//	delete[] B;
	//	delete[] C;
	//	cout << "--------------------------------" << endl;
	//	cout << "n = " << h << endl;
	//	cout << fixed << "steps: " << ((float)s[l] / 100) << endl;
	//}
	//for (int i = 0, n = 8; i < 12; i++, n *= 2)
	//{
	//	cout << fixed << "n =\t" << n << "\tsteps: " << ((float)s[l] / 100) << endl;
	//}
	int n, h;
	cout << "Введите размер чисел A и B: ";
	cin >> h;
	n = h * 2;
	int* A = new int[n], * B = new int[n];
	//cout << "A: "; inputNumber(A, n, h); cout << "B: "; inputNumber(B, n, h);
	createNumber(A, n, h); createNumber(B, n, h);
	cout << "A: "; print(A, n);
	cout << "B: "; print(B, n);
	//int* F = sub(A, B, n);
	//int* J = sh(A, n, 2);
	int* C = mult(A, B, n, n / 2);
	cout << "C: "; print(C, n);
	cout << "steps: " << steps_i;
}*/

