#include <iostream>
#include <vector>

using namespace std;

char** picture;
char** image;
bool** px_map; // просто карта занятых пикселей
char px0 = '0', px1 = '1';
int height, width;
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
            //cout << picture[i][k];
        }
        cout << endl;
    }
}
void createPic() {
    picture = new char* [n];
    px_map = new bool* [n];
    for (int i = 0; i < n; i++) {
        picture[i] = new char[n];
        px_map[i] = new bool[n];
        for (int k = 0; k < n; k++) {
            picture[i][k] = px0;
            px_map[i][k] = false;
        }
    }
}
void generateImg() {
    image = new char* [height];
    for (int i = 0; i < height; i++) {
        image[i] = new char[width];
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

bool F(int x, int y) { 
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

void S2() { // анализатор картинки
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
                                isAreaClosed = false;
                                count += 1; // 2 присвоения
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
                                    count++; // присвоение
                                }
                                isAreaClosed = false;
                                count += 2; // 2 присвоения и сравнение
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
                                isAreaClosed = false;
                                count += 2; // 2 присвоения и сравнение
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
                cout << endl << "Изображение " << imgCounter << ": " << endl;
                cout << "Верхняя правая точка: " << highX << "\t" << highY << endl;
                cout << "Нижняя левая точка:   " << downX << "\t" << downY << endl;
            }
            count += 2;
        }
    }
    cout << endl << "Найдено изображений: " << imgCounter << endl;
    cout << endl << "Кол-во операций: " << count << endl << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");

    cout << "Input size: ";
    cin >> n;

    createPic();

    int x, y, imgKol, ImgCount = 0;
    bool isAddedImg = false;

    cout << "Введите кол-во изображений: ";
    cin >> imgKol;
    while (ImgCount < imgKol) {
        cout << "Ввод изображения " << (ImgCount + 1) << ": " << endl;
        cout << "Введите координаты x, y: ";
        cin >> x >> y;
        cout << "Введите ширину и высоту: ";
        cin >> width >> height;
        generateImg();
        isAddedImg = F(x, y);
        if (isAddedImg)
        {
            ImgCount++;
        }
    }
    S2();
    //
    // Разные вводы и результаты:
    //
    // ---- 3 разных изображения на картинке 20х20
    // 20 3 1 2 3 5 4 9 6 10 13 4 4 7
    // --> S1 ищет за 4728 операций
    // --> S2 ищет за 1271 операций
    //
    //  ---- 1 большое изображение на картинке 30х30
    // 30 1 3 3 20 25
    // S1 ---> 5123 операций
    // S2 ---> 2996 операций
    //
    // ---- 5 разных изображений на картинке 50х50
    // 50 5 1 2 3 5 3 19 14 20 10 0 6 10 24 7 10 20 40 40 6 9
    // S1 ---> 42667 операций
    // S2 ---> 7080 операций
    //
    // ---- 2 разных изображения на 20х20
    // 20 2 1 2 3 5 10 4 5 8
    // ---> 1061
    // 20 2 2 3 3 5 12 7 5 8
    // ---> 1061
    // т.е. результат не зависит от расположения изображений
    printPic();
}
