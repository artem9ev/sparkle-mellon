#include <iostream>

using namespace std;

int main()
{
    int n;
    cout << "n = "; cin >> n;
    int a[100][100];
    int b[100][100];
    int c[100][100];
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cin >> a[i][k];
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cin >> b[i][k];
        }
    }
    int i, k, stepp, h, g;



    _asm {
        mov eax, n
        mov h, eax
        mov g, eax

        xor edx, edx
        mov eax, 100
        mov ebx, n
        sub eax, ebx
        mov ebx, 4
        mul ebx
        mov stepp, eax

        lea eax, a
        lea ebx, b
        mov i, eax

        startt:
        cmp h, 0
            je exitt
            mov edx, i
            mov eax, [edx]

            tttt :
            cmp g, 0
            je exxx
                
            exxx:

            mov edx, stepp
            add i, edx
            sub h, 1
            jmp startt
        exitt:
    }
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << " " << c[i][k];
        }
        cout << endl;
    }

    //int a[100];
    //int b[100];
    //for (int i = 0; i < n; i++)
    //{
    //    cin >> a[i];
    //} 
    //for (int i = 0; i < n; i++)
    //{
    //    cin >> b[i];
    //}
    //int i, k, scal = 0;
    //// a1b1 + a2b2 + ...
    //_asm {
    //    lea eax, a
    //    lea ebx, b
    //    mov i, eax
    //    mov k, ebx
    //    mov ecx, n

    //    startt:
    //    cmp ecx, 0
    //    je exitt
    //        xor edx, edx
    //        mov edx, i
    //        mov eax, [edx]
    //        mov edx, k
    //        mov ebx, [edx]
    //        
    //        xor edx, edx
    //        mul ebx

    //        add scal, eax
    //        add i, 4
    //        add k, 4
    //        sub ecx, 1
    //        jmp startt
    //    exitt:


    //}
    //cout << scal;
}