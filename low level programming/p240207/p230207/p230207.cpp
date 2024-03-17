#include <iostream>

using namespace std;

int main()
{
    int number, r, d;
    cin >> number;
    _asm {
        mov EAX, number
        mov EDX, 0

        mov EBX, EAX
        div 2
        mov EAX, EBX

        CMP EDX, 0
        JE zero
        CMP EDX, 1
        JE one

        zero : mov r, 10
        ; выход

        one : mov r, 20
        ; выход

        exit : 

        mov EDX, 0
    
    }
    /*_asm {
        mov EAX, number
        mov EBX, b
        mov EDX, 0

        check : CMP EAX, 2
        JGE exit

        

        exit : 
        mov r, EAX;
        mov d, EDX;
    }*/
    cout << r << " " << d;


    /*int n, r = 0;
    cin >> n;
    _asm {
        mov EAX, 1
        mov EBX, 1
        mov ECX, n

        circle : mul EBX
        add EBX, 1
        loop circle

        mov r, EAX
    }
    cout << "res = " << r;*/


    /*int a1, step, n, sum = 0;
    cout << "a1 = "; cin >> a1;
    cout << "step = "; cin >> step;
    cout << "n = "; cin >> n;

    _asm {
        mov EAX, a1
        mov EBX, step
        mov EDX, 0
        mov ECX, n

        circle : add EDX, EAX
        add EAX, EBX
        loop circle

        mov sum, EDX
    }
    cout << "sum = " << sum;*/



    /*int n;
    int f2 = 1;
    cin >> n;
    int f1, f3;
    f1 = 1;
    f3 = 0;
    n = n - 2;
    _asm {
        mov EAX, 1; поместили значение 1 в EAX
        mov EBX, f2; поместили значение f2 в EBX
        mov EDX, 0; поместили 0 в EDX
        mov ECX, n; поместили n в ECX

        metka : add EDX, EAX; Добавили к EDX значение EAX
        add EDX, EBX; прибавили к EDX значение EBX
        mov EAX, EBX; EAX = EBX
        mov EBX, EDX; EBX = EDX
        mov EDX, 0; EDX = 0
        loop metka; Переходим к строке помеченной как metka, если ECX > 0, уменьшаем ECX на 1 
        mov f1, EBX; f1 = EBX
    }
    cout << " = " << f1;*/
}