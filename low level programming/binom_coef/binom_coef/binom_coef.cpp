#include <iostream>

int main()
{
    for (int i = 0; i < 5; i++)
    {
        int n, k, c = 0;
        std::cin >> n >> k;
        int u, d, g;
        _asm {
            mov ECX, k

            mov EAX, n
            mov EBX, k
            mov u, 1;
            mov d, 1;

            mov g, ECX

                circle :
            CMP ECX, 0
                JLE circleEnd
                mov EAX, u
                mov EBX, n
                mul EBX
                mov u, EAX

                mov EAX, d
                mov EBX, k
                mul EBX
                mov d, EAX

                mov EAX, n
                mov EBX, k
                sub EAX, 1
                sub EBX, 1
                mov n, EAX
                mov k, EBX

                sub ECX, 1
                JMP circle
                circleEnd :

            mov EDX, g
                mov EAX, u
                CMP EDX, 0
                JE exitt
                mov EDX, 0
                mov EBX, d
                div EBX

                exitt :
            mov c, EAX
        }
        std::cout << "c = " << c << std::endl << std::endl;
    }
    
}