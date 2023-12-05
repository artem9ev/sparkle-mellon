#include <iostream>
#include <time.h>

using namespace std;

short** picture;
short** image;
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
    for (int i = 0; i < n; i++) {
        picture[i] = new short[n];
        for (int k = 0; k < n; k++) {
            picture[i][k] = px0;
        }
    }
}
void clearPic() {
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            picture[i][k] = px0;
        }
    }
}
// создает изображение буквы Р ширины width и высоты hight
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
// пытается разместить изображение размера (width, height) в картинку на позицию (x, y)
bool setImg(int x, int y, int width, int height) {
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

// ищет изображение на картинке
void findImg() {
    int lx = 0, ly = 0;
    int rx = n, ry = n;
    bool isFinded = false;
    for ( ; ly < n && !isFinded; ly++)
    {
        for (; lx < n && !isFinded; lx++)
        {
            if (picture[ly][lx] == px1)
            {
                for (int j = lx; j < n && picture[ly][j] != px0; j++)
                {
                    rx = j;
                }
                for (int j = ly; j < n && picture[j][lx]; j++)
                {
                    ry = j;
                }
                if (rx - lx < 3 || ry - ly < 5)
                {
                    cout << "Изображение слишком маленькое, чтобы быть опознаным как буква P" << endl;
                    return;
                }

                int center = ry - ly / 2 + ly;
                for (int j = lx; j <= rx; j++)
                {
                    if (picture[center][j] == px0)
                    {
                        cout << "Неправильная центральная линия!" << endl; 
                        return;
                    }
                }
                for (int j = ry; j <= center; j++)
                {
                    if (picture[j][rx] == px0)
                    {
                        cout << "Неправильная крайная правая линия!" << endl;
                        return;
                    }
                }
                isFinded = true;
            }
        }
    }
    cout << "Найдено изображение:\nЛевый верхний угол: " << lx << '\t' << ly << "\nПравый нижний угол: " << rx << '\t' << ry << endl;
}

int main()
{
    setlocale(LC_ALL, "RUS");
    srand(time(0));

    cout << "Размер картинки (n): ";
    cin >> n;

    createPic();

    int width, height, x, y, k;
    cout << "Размер изображения: ";
    cin >> width >> height;
    generateImg(width, height);
    do
    {
        cout << "Координаты размещения (x, y): ";
        cin >> x >> y;
    } while (!setImg(x, y, width, height));

    printPic();

    cout << "Во сколько раз увеличить изображение: ";
    cin >> k;


}
