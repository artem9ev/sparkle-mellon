#include <iostream>

using namespace std;

int main()
{
    for (int j = 0; j < 4; j++)
    {
        double a[10];
        double b[10];
        int n = 10;
        for (int i = 0; i < n; i++)
        {
            cin >> a[i];
        }
        for (int i = 0; i < n; i++)
        {
            cin >> b[i];
        }
        double res;
        _asm {
            lea esi, a
            lea ebx, b
            mov ecx, n
            fldz
            start :
            fld qword ptr[esi]
                fld qword ptr[ebx]
                fsubp st(1), st
                fmul st, st
                faddp st(1), st

                add esi, 8
                add ebx, 8
                dec ecx
                jnz start

                fsqrt
                fstp res
        }
        cout << res << endl << endl;
    }
}