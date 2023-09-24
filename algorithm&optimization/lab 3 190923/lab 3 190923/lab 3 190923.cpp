#include <iostream>
#include <vector>
#include <time.h>

using namespace std;

short** picture;
short** image;
bool** px_map; // просто карта областей с изображениями
short px0 = 0, px1 = 1;
int n = 0;

void printPic() {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (picture[i][k] == px0) {
                cout << " -";
            }
            else {
                cout << " #";
            }
        }
        cout << endl;
    }
}
void createPic() {
    picture = new short* [n];
    px_map = new bool* [n];
    for (int i = 0; i < n; i++) {
        picture[i] = new short[n];
        px_map[i] = new bool[n];
        for (int k = 0; k < n; k++) {
            picture[i][k] = px0;
            px_map[i][k] = false;
        }
    }
}
void clearPic() {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            picture[i][k] = px0;
            px_map[i][k] = false;
        }
    }
}
void generateImg(int width, int height) {
    image = new short* [height];
    for (int i = 0; i < height; i++) {
        image[i] = new short[width];
        for (int k = 0; k < width; k++) {
            if (k == 0) {
                image[i][k] = px1;
            }
            else if (k == width - 1 && i < height / 2) {
                image[i][k] = px1;
            }
            else if (i == 0) {
                image[i][k] = px1;
            }
            else if (i == height / 2) {
                image[i][k] = px1;
            }
            else {
                image[i][k] = px0;
            }
        }
    }
}

bool F(int x, int y, int width, int height) {
    if (x + width - 1 > n) {
        cout << "Ошибка! Выход за пределы картинки (x)" << endl;
        return false;
    }
    if (y + height - 1 > n) {
        cout << "Ошибка! Выход за пределы картинки (y)" << endl;
        return false;
    }
    for (int i = y; i < y + height; i++) {
        for (int k = x; k < x + width; k++) {
            picture[i][k] = image[i - y][k - x];
        }
    }
    return true;
}

void randomPic(int amount) {
    int countPlaced = 0;
    int rh, rw, rx, ry; // случайные параметры изображения
    int minW, minH = 5;
    int maxW, maxH = sqrt(n * n / (amount + sqrt(amount)));
    bool** isEmptyPx = new bool* [n]; // карта занятых пикселей
    bool canPlace;
    for (int i = 0; i < n; i++)
    {
        isEmptyPx[i] = new bool[n];
        for (int k = 0; k < n; k++)
        {
            isEmptyPx[i][k] = true;
        }
    }
    while (countPlaced < amount)
    {
        canPlace = false;
        rh = rand()%(maxH - minH) + minH;
        minW = (rh + 1) / 2;
        maxW = rh;
        rw = rand()%(maxW - minW) + minW;
        int tries = 0;
        while (!canPlace) // пытаюсь найти место для размещения
        {
            if (tries > 100) // если долго не получается разместить изображение, то рандомим размер меньше
            {
                rh = rand() % (rh - minH) + minH;
                minW = (rh + 1) / 2;
                maxW = rh;
                rw = rand() % (maxW - minW) + minW;
                //cout << "Проблемы в размещении (pic" << (countPlaced + 1) << ")" << endl;
                tries = 0;
            }
            tries++;
            canPlace = true;
            rx = rand()%(n - rw + 1);
            ry = rand()%(n - rh + 1);
            //cout << rx << "\t" << ry << endl;
            for (int i = ry; i < ry + rh; i++)
                for (int k = rx; k < rx + rw; k++)
                    if (isEmptyPx[i][k] == false)
                    {
                        i = n;
                        k = n;
                        canPlace = false;
                    }
        }
        // если найдено место для размещения, то продолжаем
        generateImg(rw, rh);
        F(rx, ry, rw, rh);
        countPlaced++;
        //cout << "pic" << (countPlaced) << ":\t" << rx << "\t" << ry << "\t" << rw << "\t" << rh << endl;
        for (int i = ry - 1; i < n && i <= ry + rh; i++)
        {
            if (i < 0)
                i++;
            for (int k = rx - 1; k < n && k <= rx + rw; k++)
            {
                if (k < 0)
                    k++;
                isEmptyPx[i][k] = false;
            }
        }
    }
}

int S() { // анализатор картинки
    int imgCounter = 0;
    int count = 0;
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            if (px_map[i][k] == false && picture[i][k] == px1) // нашел самый высокий пиксель
            {
                int highX = k;
                int highY = i;
                int downX = k;
                int downY = i;
                count += 4; // инициализация точек
                for (bool isAreaClosed = false; !isAreaClosed; )
                {
                    // алгоритм делает 3 проверки вокруг #### области: (точки - это уже пройденные поисковиком пиксели, очевидно что среди них нет частей изображения)
                    //  . .... .
                    //  . #### 1
                    //  2 #### 1
                    //  2 3333 3
                    // -----------------------------------------------------
                    isAreaClosed = true;
                    if (downX < n) // иду по правому краю области
                        for (int x = downX + 1, y = highY; y < n && y <= downY; y++)
                        {
                            if (picture[y][x] == px1) {
                                downX = x;
                                count += 1;
                                isAreaClosed = false;
                                break;
                            }
                            count++; // сравнение
                        }
                    if (highX - 1 >= 0) // иду по левому краю области
                        for (int x = highX - 1, y = highY + 1; y < n && y <= downY + 1; y++)
                        {
                            if (picture[y][x] == px1) {
                                highX = x;
                                if (downY < y)
                                {
                                    downY = y;
                                    count++;
                                }
                                count += 2;
                                isAreaClosed = false;
                                break;
                            }
                            count++; // сравнение
                        }
                    if (downY + 1 < n) //иду по нижнему краю области
                        for (int y = downY + 1, x = highX; x <= downX + 1; x++)
                        {
                            if (picture[y][x] == px1) {
                                downY = y;
                                if (downX < x)
                                {
                                    downX = x;
                                    count++; // присвоение
                                }
                                count += 2;
                                isAreaClosed = false;
                                break;
                            }
                            count++; // сравнение
                        }
                    count += 3; // 3 сравнения
                }
                for (int y = highY; y <= downY; y++)
                {
                    for (int x = highX; x <= downX; x++)
                    {
                        px_map[y][x] = true;
                        count++;
                    }
                }
                imgCounter++;
                //cout << endl << "Изображение " << imgCounter << ": " << endl;
                //cout << "Верхняя правая точка: " << highX << "\t" << highY << endl;
                //cout << "Нижняя левая точка:   " << downX << "\t" << downY << endl;
            }
            count += 2;
        }
    }
    //cout << "Найдено изображений: " << imgCounter << endl;
    //cout << endl << "Кол-во операций: " << count << endl << endl;
    return count;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    cout << "Release" << endl;
    long long sum;
    int amount;
    for (n = 100; n <= 1000; n += 100)
    {
        createPic();
        cout << "Размер картинки: " << n << endl;
        sum = 0;
        amount = n * n / 1000;
        amount = n * sqrt(n) / 200;
        cout << "кол-во изображений: " << amount << endl;
        cout << "макс. высота изоб.: " << int(sqrt(n * n / (amount + sqrt(amount)))) << endl;
        for (int k = 0; k < 100; k++)
        {
            clearPic();
            randomPic(amount);
            //printPic();
            //cout << "Изображение " << (k + 1) << " готово" << endl << endl;
            sum += S();
        }
        double mid = sum / (double)100;
        cout << fixed << "Среднее кол-во операций: " << mid << endl;
        cout << "-------------------------------------------------------" << endl;
    }
    /*cout << "Input size: ";
    cin >> n;
    createPic();
    int x, y, height, width, imgKol, ImgCount = 0;
    bool isAddedImg = false;
    cout << "Введите кол-во изображений: ";
    cin >> imgKol;
    while (ImgCount < imgKol) {
        cout << "Ввод изображения " << (ImgCount + 1) << ": " << endl;
        cout << "Введите координаты x, y: ";
        cin >> x >> y;
        cout << "Введите ширину и высоту: ";
        cin >> width >> height;
        generateImg(width, height);
        isAddedImg = F(x, y, width, height);
        if (isAddedImg)
        {
            ImgCount++;
        }
    }
    cout << "\nшаги:" << S() << endl;
    printPic();*/

    // 2n^2 + 

    // Разные вводы и результаты:
    //
    // ---- 3 разных изображения на картинке 20х20
    // 20 3 1 2 3 5 4 9 6 10 13 4 4 7
    // ---> 1217
    //
    //  ---- 1 большое изображение на картинке 30х30
    // 30 1 3 3 20 25
    // ---> 2927
    //
    // ---- 5 разных изображений на картинке 50х50
    // 50 5 1 2 3 5 3 19 14 20 10 0 6 10 24 7 10 20 40 40 6 9
    // ---> 6918
    //
    // ---- 2 разных изображения на 20х20
    // 20 2 1 2 3 5 10 4 5 8
    // ---> 1061
    // 20 2 2 3 3 5 12 7 5 8
    // ---> 1061
    // т.е. результат не зависит от расположения изображений
    
    //   5 --> 50
    //  10 --> 200
    //  10 --> 200
    //  20 --> 800
    //  30 --> 1800
    //  40 --> 3200
    //  50 --> 5000
    //  60 --> 7200
    //  70 --> 9800
    //  80 --> 12800
    //  90 --> 16200
    // 100 --> 20000
    // 200 --> 80000
    // 300 --> 180000
    // 400 --> 320000
    // 500 --> 500000
    // 600 --> 720000
    // 700 --> 980000
    // 800 --> 1280000
    // 900 --> 1620000
    //1000 --> 2000000
    //
    /*  Размер картинки : 100 24339.250000
        ------------------------------------------------------ -
        Размер картинки : 200 99006.810000
        ------------------------------------------------------ -
        Размер картинки : 300 222852.810000
        ------------------------------------------------------ -
        Размер картинки : 400 398348.850000
        ------------------------------------------------------ -
        Размер картинки : 500 626188.410000
        ------------------------------------------------------ -
        Размер картинки : 600 902923.760000
        ------------------------------------------------------ -
        Размер картинки : 700 1227422.260000
        ------------------------------------------------------ -
        Размер картинки : 800 1602099.760000
        ------------------------------------------------------ -
        Размер картинки : 900 2041894.310000
        ------------------------------------------------------ -
        Размер картинки : 1000 2518413.890000*/
}
