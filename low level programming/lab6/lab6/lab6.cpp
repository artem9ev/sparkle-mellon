#include <iostream>

using namespace std;

int main()
{
    double a, b, c, fc, two = 2, three = 3, eps = 0.001;
    _asm {
        fldpi
        fstp a; -> a

        fldpi
        fmul three
        fdiv two
        fstp b; -> b

        startt:
            fld a
            fadd b
            fdiv two
            fstp c

            fld1
            fld c
            fyl2x
            fld c
            fsin
            fmul three
            faddp st(1), st;->f(c)
            fstp fc

            fld eps
            fld a
            fld b
            fsubp st(1), st
            fabs
            
            fcompp
            fstsw ax
            sahf; отправил результат в регистр флагов
            jb exitt; если eps > f(c)

            fld1
            fld a
            fyl2x
            fld a
            fsin
            fmul three
            faddp st(1), st; f(a)
            fmul fc; f(a)* f(c)
                
            fldz; загрузил 0 для последующего сравнения : f(a) * f(c) < 0
            fcompp
            fstsw ax
            sahf
            fld c
            jb elsee
                ; если f < 0
                fstp b
                jmp nextt
            elsee:
                ; если f >= 0
                fstp a
            nextt:
            jmp startt
        exitt:
    }
    cout << "c = " << c << " | a = " << a << ", b = " << b;
}