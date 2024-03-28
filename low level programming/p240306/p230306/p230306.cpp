#include <iostream>

using namespace std;

int main()
{
    for (int i = 0; i < 6; i++)
    {
        int x, n; cin >> x >> n;
        int res;
        _asm {
            bsr ecx, n
            mov eax, 1

            jnz metka
                mov ecx, 0
            metka:
            cmp ecx, -1
            jle exitt
                xor edx, edx
                mov ebx, eax
                mul ebx
                bt n, ecx
                jnc nextt
                    xor edx, edx
                    mul x
                nextt:
                dec ecx
                jmp metka
            exitt:
            mov res, eax
        }
        cout << x << "^" << n << " = " << res << endl << endl;
    }
}
