#include <iostream>

using namespace std;

int main()
{
    int n, s, k, res; cin >> n;
    _asm {
        fild n
        fsqrt
        fistp s
        mov ecx, s
        startt:
            xor edx, edx
            mov eax, ecx
            mul ecx
            mov ebx, eax
            xor edx, edx
            mov eax, n
            div ebx
            cmp edx, 1
            jge skipp
                mov res, 0
                jmp exitt
            skipp:
            cmp ecx, 2
            je stopp
            dec ecx
            jmp startt
        stopp:


        exitt:

     }
    cout << res;
}
