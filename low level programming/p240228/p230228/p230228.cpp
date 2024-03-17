#include <iostream>

using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    int n;
    cout << "Размер векторов\nn = "; cin >> n;
    int u[100];
    int o[100];
    for (int i = 0; i < n; i++)
    {
        cin >> u[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> o[i];
    }
    int i, k, scal = 0;
    _asm {
        lea eax, u
        lea ebx, o
        mov i, eax
        mov k, ebx
        mov ecx, n
        startt :
        cmp ecx, 0
            je exitt
            xor edx, edx
            mov edx, i
            mov eax, [edx]
            mov edx, k
            mov ebx, [edx]

            xor edx, edx
            mul ebx
            add scal, eax
            add i, 4
            add k, 4
            sub ecx, 1
            jmp startt
            exitt :
    }
    cout << "Cкалярное произведение = " << scal << endl << endl;


    cout << "Размер матриц\nn = "; cin >> n;
    int a[100][100];
    int b[100][100];
    int r[100][100];
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
    int indexx, s, c, aa, bb, g;
    _asm {
       mov ecx, n
       mov s, ecx

       circleString:
       cmp s, 0
       je exittt
           mov c, ecx
           circleColumn:
           cmp c, 0
           je endCircleEnd
               mov edi, 0
               mov indexx, ecx
               circleElem:
               cmp indexx, 0
               je endCircleElem
                   xor edx, edx
                   mov ebx, indexx
                   dec ebx
                   imul eax, ebx, 4
                   mov g, eax
                   xor edx, edx
                   mov ebx, s
                   dec ebx
                   imul esi, ebx, 400
                   add esi, eax 

                   mov eax, a[esi]
                   mov aa, eax

                   xor edx, edx
                   mov ebx, c
                   dec ebx
                   imul eax, ebx, 4
                   mov g, eax
                   xor edx, edx
                   mov ebx, indexx
                   dec ebx
                   imul esi, ebx, 400
                   add esi, eax

                   mov eax, b[esi]
                   mov bb, eax

                   xor edx, edx
                   mov eax, aa
                   mov ebx, bb
                   mul ebx
                   add edi, eax

                   dec indexx
                   jmp circleElem
               endCircleElem:

               xor edx, edx
               mov ebx, c
               dec ebx
               imul eax, ebx, 4
               mov g, eax
               xor edx, edx
               mov ebx, s
               dec ebx
               imul esi, ebx, 400
               add esi, eax

               mov r[esi], edi

               dec c
               jmp circleColumn
           endCircleEnd:
           dec s
           jmp circleString
       exittt:
    }
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << " " << r[i][k];
        }
        cout << endl;
    }
}