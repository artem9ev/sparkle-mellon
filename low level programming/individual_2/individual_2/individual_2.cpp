#include <iostream>

using namespace std;

int main()
{
    /*
    Написать программу с использованием ассемблерных вставок, которая «рисует» черную букву Х размером h (высота)
    на w (ширина) в центре прямоугольной белей «картинки» размера H × W с использованием алгоритма Брезенхема для
    построения отрезков. Белый пиксель задается битом 0, черный – битом 1. Двумерная картинка записывается в памяти
    построчно, начиная с верхней строки, единой последовательностью бит.*/
    int H, W, h, w, x1, x2, y1, y2;
    cout << "pic H, W: "; cin >> H >> W;
    int picSize = H * W; // размер изображения в битах
    int n = picSize / 16 + 1; // кол-во байт для записи изображения
    short unsigned * pic = new short unsigned[n]; // выделение памяти
    for (int i = 0; i < n; i++)
    {
        pic[i] = 0;
    }
    cout << "img h, w: "; cin >> h >> w;
    int mainAxis, secondaryAxis1, secondaryAxis2;
    double k, s = 0, c = 0.5, r;
    _asm {
        ; нахожу координаты краев буквы по x
        ; x1 = (W - w) / 2, x2 = x1 + w - 1
        mov eax, W
        mov ebx, w
        sub eax, ebx
        mov ebx, 2
        xor edx, edx
        div ebx
        mov x1, eax
        mov eax, w
        dec eax
        mov ebx, x1
        mov x2, ebx
        add x2, eax
        ; нахожу координаты краев буквы по y
        ; y1 = (H - h) / 2, y2 = y1 + h - 1
        mov eax, H
        mov ebx, h
        sub eax, ebx
        mov ebx, 2
        xor edx, edx
        div ebx
        mov y1, eax
        mov eax, h
        dec eax
        mov ebx, y1
        mov y2, ebx
        add y2, eax
        ; подготовка к вычислению углового коэффициента
        fld1
        fild x2
        fild x1
        fsubp st(1), st
        faddp st(1), st
        fld1
        fild y2
        fild y1
        fsubp st(1), st
        faddp st(1), st
        ; сравниваю соотношение высоты и ширины буквы
        mov eax, h
        cmp eax, w
        ja mainY
            ; если X сновная ось для линий
            mov ecx, w
            mov eax, x1
            mov mainAxis, eax
            mov eax, y2
            mov secondaryAxis1, eax
            mov eax, y1
            mov secondaryAxis2, eax
            ; вычисляю угловой коэффициент
            fdivrp st(1), st
            fstp k
            circle1:
                ; записал адрес массива
                mov edi, pic
                ; далее вычисляю адрес пикселя(бита) с координатой(x, y1)
                xor edx, edx
                mov eax, secondaryAxis1
                mul H
                add eax, mainAxis
                xor edx, edx
                mov ebx, 16
                div ebx
                mov ebx, edx
                mov esi, 15
                sub esi, ebx
                shl eax, 1
                add edi, eax
                ; покрасил нужный пиксель(бит) в черный цвет
                bts[edi], esi
                ; записал адрес массива
                mov edi, pic
                ; далее вычисляю адрес пикселя(бита) с координатой(x, y2)
                xor edx, edx
                mov eax, secondaryAxis2
                mul H
                add eax, mainAxis
                xor edx, edx
                mov ebx, 16
                div ebx
                mov ebx, edx
                mov esi, 15
                sub esi, ebx
                shl eax, 1
                add edi, eax
                ; покрасил нужный пиксель(бит) в черный цвет
                bts[edi], esi
                ; ------------------
                ; вычисляю значение s
                fld s
                fld k
                faddp st(1), st
                fld c
                fcomp
                fstsw ax
                sahf; отправил результат в регистр флагов
                jnb skip1
                    ; если s > 0.5
                    fld1
                    fsubp st(1), st
                    dec secondaryAxis1
                    inc secondaryAxis2
                skip1:
                fstp s
                mov eax, h
                inc mainAxis
                dec ecx
            cmp ecx, 0
            ja circle1
            jmp exitt
        mainY:
            ; если Y сновная ось для линий
            mov ecx, h
            mov eax, y1
            mov mainAxis, eax
            mov eax, x2
            mov secondaryAxis1, eax
            mov eax, x1
            mov secondaryAxis2, eax
            ; вычисляю угловой коэффициент
            fdivp st(1), st
            fstp k
            circle2:
                ; записал адрес массива
                mov edi, pic
                ; далее вычисляю адрес пикселя(бита) с координатой(x1, y)
                xor edx, edx
                mov eax, mainAxis
                mul H
                add eax, secondaryAxis1
                xor edx, edx
                mov ebx, 16
                div ebx
                mov ebx, edx
                mov esi, 15
                sub esi, ebx
                shl eax, 1
                add edi, eax
                ; покрасил нужный пиксель(бит) в черный цвет
                bts[edi], esi
                ; записал адрес массива
                mov edi, pic
                ; далее вычисляю адрес пикселя(бита) с координатой(x2, y)
                xor edx, edx
                mov eax, mainAxis
                mul H
                add eax, secondaryAxis2
                xor edx, edx
                mov ebx, 16
                div ebx
                mov ebx, edx
                mov esi, 15
                sub esi, ebx
                shl eax, 1
                add edi, eax
                ; покрасил нужный пиксель(бит) в черный цвет
                bts[edi], esi
                ; ------------------
                ; вычисляю значение s
                fld s
                fld k
                faddp st(1), st
                fld c
                fcomp
                fstsw ax
                sahf; отправил результат в регистр флагов
                jnb skip2
                    ; если s > 0.5
                    fld1
                    fsubp st(1), st
                    dec secondaryAxis1
                    inc secondaryAxis2
                skip2:
                fstp s
                mov eax, h
                inc mainAxis
                dec ecx
            cmp ecx, 0
            ja circle2
            jmp exitt
        exitt:
    }
    // ВЫВОД ГОТОВОГО ИЗОБРАЖЕНИЯ
    for (int i = 0, k = 0, j = SHRT_MAX + 1, l = 0; i < picSize; i++, l++)
    {
        if (i % 16 == 0)
        {
            j = SHRT_MAX + 1;
        }
        k = i / 16;
        cout << " " << pic[k] / j % 2;
        j = j >> 1;
        if (l + 1 == W)
        {
            l = -1;
            cout << endl;
        }
    }
}