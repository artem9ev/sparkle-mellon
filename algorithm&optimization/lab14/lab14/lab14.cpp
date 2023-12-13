#include <iostream>
#include <time.h>

using namespace std;

short** picture;
short** image;
short px0 = 0, px1 = 1;
int n = 0;

enum placing
{
    CENTER = 0,
    TOPLEFT = 1,
    TOPRIGHT = 2,
    BOTTOMLEFT = 3,
    BOTTOMRIGHT = 4,
};

struct coords {
    int ly, lx, ry, rx;
};

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
coords findImgP() {
    int lx = 0, ly = 0;
    int rx = n, ry = n;
    bool isFinded = false;
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            if (picture[i][k] == px1)
            {
                lx = k;
                ly = i;
                i = n;
                k = n;
            }
        }
    }
    for (int j = lx; j < n && picture[ly][j] != px0; j++)
    {
        rx = j; // иду по верхней линии
    }
    for (int j = ly; j < n && picture[j][lx] != px0; j++)
    {
        ry = j; // иду по левой боковой линии
    }
    if (rx - lx + 1 < 3 || ry - ly + 1 < 5)
    {
        cout << "Изображение слишком маленькое, чтобы быть опознаным как буква P" << endl;
        return coords{ -1, -1, -1, -1 };
    }
    for (int i = ly; i <= ry; i++) {
        for (int k = lx; k <= rx; k++) {
            if ((k == lx) || (k == rx && i < (ry - ly + 1) / 2 + ly) || (i == ly) || (i == (ry - ly + 1) / 2 + ly))
            {
                if (picture[i][k] != px1) {
                    cout << "wrong line! " << k << " " << i << endl;
                    return coords{ -1, -1, -1, -1 };
                }
            }
            else
            {
                if (picture[i][k] != px0) {
                    cout << "extra pixels! " << i << " " << k << endl;
                    return coords{ -1, -1, -1, -1 };
                }
            }
        }
    }    
    return coords{ ly, lx, ry, rx };
}

void upscaleImg(coords coord, int scale, placing place) {
    int width = coord.rx - coord.lx + 1;
    int height = coord.ry - coord.ly + 1;
    short** oldImg = new short*[height];
    short** newImg = new short* [height * scale];
    for (int i = 0; i < height; i++)
    {
        oldImg[i] = new short[width];
        for (int k = 0; k < width; k++)
        {
            oldImg[i][k] = picture[coord.ly + i][coord.lx + k];
            picture[coord.ly + i][coord.lx + k] = px0; 
        }
    }
    for (int i = 0; i < height * scale; i++)
    {
        newImg[i] = new short[width * scale];
        for (int k = 0; k < width * scale; k++)
        {
            if (oldImg[i / scale][k / scale] == px1)
            {
                newImg[i][k] = px1;
            }
            else
            {
                newImg[i][k] = px0;
            }
        }
    }
    int centerX = (coord.rx - coord.lx + 1) / 2 + coord.lx;
    int centerY = (coord.ry - coord.ly + 1) / 2 + coord.ly;
    switch (place)
    {
    case CENTER:
        for (int i = centerY - height * scale / 2 + 1; i <= centerY + height * scale / 2; i++)
        {
            for (int k = centerX - width * scale / 2 + 1; k <= centerX + width * scale / 2; k++)
            {
                if (i >= 0 && k >= 0 && i < n && k < n)
                {
                    picture[i][k] = newImg[i - (centerY - height * scale / 2 + 1)][k - (centerX - width * scale / 2 + 1)];
                }
            }
        }
        break;
    case TOPLEFT: // 1
        for (int i = coord.ly; i < n && i < coord.ly + height * scale; i++)
        {
            for (int k = coord.lx; k < n && k < coord.lx + width * scale; k++)
            {
                picture[i][k] = newImg[i - coord.ly][k - coord.lx];
            }
        }
        break;
    case TOPRIGHT: // 2
        for (int i = coord.ly; i < n && i < coord.ly + height * scale; i++)
        {
            for (int k = coord.rx - width * scale + 1; k <= coord.rx; k++)
            {
                if (k >= 0)
                {
                    picture[i][k] = newImg[i - coord.ly][k - (coord.rx - width * scale + 1)];
                }
            }
        }
        break;
    case BOTTOMLEFT: // 3
        for (int i = coord.ry - height * scale + 1; i <= coord.ry; i++)
        {
            for (int k = coord.lx; k < n && k < coord.lx + width * scale; k++)
            {
                if (i >= 0)
                {
                    picture[i][k] = newImg[i - (coord.ry - height * scale + 1)][k - coord.lx];
                }
            }
        }
        break;
    case BOTTOMRIGHT: // 4
        for (int i = coord.ry - height * scale + 1; i <= coord.ry; i++)
        {
            for (int k = coord.rx - width * scale + 1; k <= coord.rx; k++)
            {
                if (i >= 0 && k >= 0)
                {
                    picture[i][k] = newImg[i - (coord.ry - height * scale + 1)][k - (coord.rx - width * scale + 1)];
                }
            }
        }
        break;
    default:
        break;
    }
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
    coords coord = findImgP();

    if (coord.ly < 0 || coord.lx < 0 || coord.ry < 0 || coord.rx < 0)
    {
        cout << "не найдено изображение" << endl;
    }
    else
    {
        int place;
        cout << "Во сколько раз увеличить изображение: ";
        cin >> k;
        cout << "Режим размещения: ";
        cin >> place;
        upscaleImg(coord, k, (placing)place);
    }

    printPic();
}
