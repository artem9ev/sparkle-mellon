#include <iostream>

using namespace std;

int main()
{
    int x, n; cin >> x >> n;
    int i, res = x;
    _asm {
        bsr ebx, n
        mov i, ebx

        
    }
    cout << x << "^" << n << " = " << res << " i = " << i;

    /*
    int x, n; cin >> x >> n;
    int i, res = x;
    _asm {
        xor edx, edx
        mov eax, type n
        mov ebx, 8
        mul ebx
        mov i, eax
        
        mov eax, x
        mov ebx, n
        mov ecx, 0

        circlee:
        cmp ecx, i
        je exitt
            xor edx, edx
            ror n, 1
            
            mov eax, n
            mov ebx, 2
            div ebx
            cmp edx, 1
            xor edx, edx
                mov eax, res
                mov ebx, res
                mul ebx
                mov res, eax
            je oneee
            jmp zeroo
            oneee:
                xor edx, edx
                mov eax, res
                mov ebx, x
                mul ebx
                mov res, eax
            zeroo:
            inc ecx
            jmp circlee
        exitt:
 
    }
    cout << x << "^" << n << " = " << res;
    */
}
