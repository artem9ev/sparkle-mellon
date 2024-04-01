#include <iostream>

using namespace std;

int main()
{
    int n, k; cout << "n = "; cin >> n;
    double res;
    _asm {
        mov k, 1
        mov ecx, n
        fldz
        circle :
        fld1
            fild k
            fdivp st(1), st; получил 1 / k
            faddp st(1), st
            fst res
            inc k
            dec ecx
            cmp ecx, 0
            jne circle
            fst res
            fldln2
            fild n
            fyl2x; получил ln(n)
            fst res
            fsubp st(1), st; sum - ln(n)
            fstp res
    }
    cout << "res: " << res << endl;
}