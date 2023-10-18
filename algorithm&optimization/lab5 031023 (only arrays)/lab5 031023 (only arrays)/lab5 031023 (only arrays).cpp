#include <iostream>
#include <fstream>
#include <time.h>
//#pragma comment(linker, "/STACK:104857600")

using namespace std;

long long steps = 0;

struct number {
	int* a;
	int n;
	bool isPositive = true;
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
	for (int i = 0; i < N->n; i++)
	{
		N->a[i] = rand() % 10;
	}
}
// выводит число A
void printWithSize(number* A, int size) {
	if (!A->isPositive)
	{
		cout << '-';
	}
	else {
		cout << ' ';
	}
	for (int i = size - 1; i >= 0; i--)
	{
		if (A->n > i)
		{
			cout << A->a[i];
		}
		else {
			cout << ' ';
		}
	}
	cout << endl;
}
// удаляет число A
void clear(number* A) {
	delete[] A->a;
	delete A;
}

// сумма чисел A и B
number* add(number A, number B) {
	steps += 7;
	int z = 0;
	int p;
	int size = (A.n > B.n ? A.n : B.n) + 1;
	number* C = new  number{ new int[size], size };
	for (int i = 0; i < size - 1; i++) // идем по цифрам A и B
	{
		if (A.n > i && B.n > i)
		{
			p = A.a[i] + B.a[i] + z;
			steps += 3;
		}
		else if (A.n > i)
		{
			p = A.a[i] + z;
			steps += 2;
		}
		else if (B.n > i)
		{
			p = B.a[i] + z;
			steps += 2;
		}
		C->a[i] = p % 10;
		z = p / 10;
		steps += 8;
	}
	C->a[size - 1] = z;
	steps += 3;
	return C;
}

// вычитание B из A
number* sub(number oldA, number B) {
	int isPositive = true;
	number* C = new number{ new int[oldA.n], oldA.n };
	number A = { new int[oldA.n], oldA.n };
	steps += 7;
	for (int i = 0; i < oldA.n; i++)
	{
		A.a[i] = oldA.a[i];
	}
	for (int i = 0; i < C->n; i++)
	{
		C->a[i] = 0;
	}
	for (int i = 0, k = i; i < C->n; i++, k = i) // первый цикл вычитания (сработвет только он если A > B)
	{
		if (B.n > i)
		{
			while (k < C->n && (B.a[i] > A.a[i] || A.a[k] < 0)) // 
			{
				A.a[k] += 10; // добавляем занятый десяток
				if (k + 1 < C->n)
				{
					A.a[k + 1]--; // забираем десяток
				}
				k++;
				isPositive = k - C->n; // когда k дойдет до значения -1, то число будет считаться как отрицателье
			}
			C->a[i] = A.a[i] - B.a[i];
		}
		else
		{
			C->a[i] = A.a[i];
		}
	}
	delete[] A.a;
	if (!isPositive) // если число B оказалось больше чем A (необходимо получить отрицательное число)
	{
		number* t = new number{ new int[C->n], C->n };
		int u = 0;
		while (C->a[u] == 0) // если в конце полученного числа есть нули, то в конце этого числа будут тоже нули на соот. позициях
		{
			t->a[u] = 0;
			u++;
			steps += 3;
		}
		t->a[u++] = 10;
		while (u < C->n)
		{
			t->a[u++] = 9;
			steps += 3;
		}
		for (int i = 0; i < C->n; i++)
		{
			C->a[i] = t->a[i] - C->a[i];
			steps += 2;
		}
		C->isPositive = false;
		steps += 10;
		delete[] t->a;
		delete t;
	}
	steps += 2;
	return C;
}

// сдвиг числа на z чисел влево (экв. умножению на 10^z)
number* sh(number A, int z) {
	int size = A.n + z;
	number* N = new number{ new int[size], size };
	for (int i = 0; i < size; i++)
	{
		if (i < z)
		{ 
			N->a[i] = 0;
			steps++;
		}
		else
		{
			N->a[i] = A.a[i - z];
			steps += 2;
		}
		steps++;
	}
	steps += 6;
	return N;
}

// перемножение чисел A и B
number* mult(number A, number B) {
	number* C = new number{ new int[A.n], A.n };
	number* m1 = new number{ new int[A.n], A.n };
	number* m2 = new number{ new int[A.n], A.n };
	number* m3 = new number{ new int[A.n], A.n };
	steps += 12;
	for (int i = 0; i < A.n; i++)
	{
		C->a[i] = 0;
		m1->a[i] = 0;
		m2->a[i] = 0;
		m3->a[i] = 0;
		steps += 4;
	}
	if (A.n == 2) // дно рекурсии n = 2 (кол-во цифр в числе = 2)
	{
		int s = 1, f = 0;
		steps += 2;
		m1->a[f] = (A.a[s] * B.a[s]) % 10;
		m1->a[s] = (A.a[s] * B.a[s]) / 10;
		steps += 6;
		number* sh1 = sh(*m1, 2);
		number* sh2 = sh(*m1, 1);
		number* a1 = add(*sh1, *sh2); // (A2 * B2)(100 + 10)
		steps += 3;
		m3->a[f] = (A.a[f] * B.a[f]) % 10;
		m3->a[s] = (A.a[f] * B.a[f]) / 10;
		steps += 6;
		number* sh3 = sh(*m3, 1);
		number* a3 = add(*sh3, *m3); // (A1 * B1)(10 + 1)
		steps += 2;
		number* a2 = add(*a1, *a3);
		steps++;
		int s1 = A.a[s] - A.a[f]; // A2 - A1
		int s2 = B.a[f] - B.a[s]; // B1 - B2 --- !!!!!!!
		m2->a[f] = (abs(s1) * abs(s2)) % 10;
		m2->a[s] = (abs(s1) * abs(s2)) / 10;
		number* sh0 = sh(*m2, 1);
		steps += 11;
		if (s1 < 0 && s2 > 0 || s1 > 0 && s2 < 0)
		{
			C = sub(*a2, *sh0);
			steps++;
		}
		else
		{
			C = add(*a2, *sh0);
			steps++;
		}
		steps += 4;
		clear(a1);
		clear(a2);
		clear(a3);
		clear(sh1);
		clear(sh2);
		clear(sh3);
		clear(sh0);
	}
	else
	{
		int size = A.n / 2;
		number* A2 = new number{ new int[size], size };
		number* A1 = new number{ new int[size], size };
		number* B2 = new number{ new int[size], size };
		number* B1 = new number{ new int[size], size };
		steps += 14;
		for (int i = 0; i < A.n; i++)
		{
			if (i < size) // 0 1 2 3 - 4
			{
				A1->a[i] = A.a[i];
				B1->a[i] = B.a[i];
				steps += 2;
			}
			else
			{
				A2->a[i - size] = A.a[i];
				B2->a[i - size] = B.a[i];
				steps += 4;
			}
			steps++;
		}
		m1 = mult(*A2, *B2);
		number* sh1 = sh(*m1, A.n);
		number* sh2 = sh(*m1, size);
		number* a1 = add(*sh1, *sh2);
		steps += 4;
		m3 = mult(*A1, *B1);
		number* sh3 = sh(*m3, size);
		number* a3 = add(*sh3, *m3);
		steps += 3;
		number* a2 = add(*a1, *a3);
		steps++;
		number* sA = sub(*A2, *A1);
		number* sB = sub(*B1, *B2);
		steps += 2;
		m2 = mult(*sA, *sB);
		number* sh0 = sh(*m2, size);
		steps += 2;
		if (sA->isPositive && sB->isPositive || !sA->isPositive && !sB->isPositive)
		{
			sA->isPositive = true;
			sB->isPositive = true;
			C = add(*a2, *sh0);
			steps += 3;
		}
		else
		{
			sA->isPositive = true;
			sB->isPositive = true;
			C = sub(*a2, *sh0);
			steps += 3;
		}
		steps += 4;
		clear(a1);
		clear(a2);
		clear(a3);
		clear(sA);
		clear(sB);
		clear(sh1);
		clear(sh2);
		clear(sh3);
		clear(sh0);
	}
	clear(m1);
	clear(m2);
	clear(m3);
	steps += 2; // if и return
	return C;
}

int main()
{
	setlocale(LC_ALL, "RUS");
	srand(time(NULL));

	// 128 256 512 1024 2048 4096 8192 16384
	/*ofstream outRes("res.txt");
	
	cout << "n:\t" << "steps:" << endl;
	outRes << "n:\t" << "steps:" << endl;
	for (int n = 128; n <= 16384; n *= 2)
	{
		steps = 0;

		number* A = new number{ new int[n], n };
		number* B = new number{ new int[n], n };
		createNumber(A); createNumber(B); // генерация чисел A и B
		number* J = mult(*A, *B);
		cout << n << "\t" << steps << endl;
		outRes << n << "\t" << steps << endl;
		clear(A);
		clear(B);
		clear(J);
	}*/
	
	int n;
	cout << "Введите размер чисел A и B: ";
	cin >> n;
	number* A = new number{ new int[n], n };
	number* B = new number{ new int[n], n };
	createNumber(A); createNumber(B);

	number* J = mult(*A, *B);
	cout << "C = A * B" << endl;
	cout << "A: "; printWithSize(A, J->n);
	cout << "B: "; printWithSize(B, J->n);
	cout << "C: "; printWithSize(J, J->n);

	clear(A);
	clear(B);
	clear(J);
	cout << "steps: " << steps;
}

