#include <iostream>

using namespace std;

int main()
{
	for (int i = 0; i < 6; i++)
	{
        int n, p, res = 0; cout << "n = "; cin >> n;
        _asm {
            cmp n, 1; если n = 1, то результат = 1
            jne skip1
            mov res, 1
            jmp exitt
            skip1 :

            mov p, 2
                start2 :
                mov ebx, 2
                prostoeChecker1 :
                cmp p, ebx
                je isProstoe1
                xor edx, edx
                mov eax, p
                div ebx
                cmp edx, 0
                je skipProstoe1
                inc ebx
                jmp prostoeChecker1
                isProstoe1 :
            xor edx, edx
                mov eax, p
                mul eax; получил квадрат простого числа
                xor edx, edx
                mov ebx, eax
                mov eax, n
                div ebx
                cmp edx, 0;
            jne checkOstatok1
                mov res, 0; число делится на квадрат простого числа
                jmp exitt
                checkOstatok1 :
            cmp edx, n; если остаток = n, то квадрат простого > n
                je skip2
                skipProstoe1 :
            inc p
                jmp start2
                skip2 :
            mov p, 2
                mov ecx, 0; кол - во простых делителей
                start3 :
            mov ebx, 2
                prostoeChecker2 :
                cmp p, ebx
                je isProstoe2
                xor edx, edx
                mov eax, p
                div ebx
                cmp edx, 0
                je skipProstoe2
                inc ebx
                jmp prostoeChecker2
                isProstoe2 :
            xor edx, edx
                mov eax, n
                mov ebx, p
                div ebx
                cmp edx, 0
                jne neDelitel
                inc ecx
                neDelitel :
            cmp edx, n
                je skip3
                skipProstoe2 :
            inc p
                jmp start3
                skip3 :
            xor edx, edx
                mov eax, ecx
                mov ebx, 2
                div ebx
                cmp edx, 0
                jne notZero
                mov res, 1
                jmp exitt
                notZero :
            mov res, -1
                exitt :
        }
        cout << "res = " << res << endl << endl;
	}
}
