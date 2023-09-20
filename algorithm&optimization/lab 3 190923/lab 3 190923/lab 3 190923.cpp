#include <iostream>

using namespace std;

int** picture;
int** image;
int height, width;
int n = 0;

void printPic() {
    for (int i = 0; i < n; i++)
    {
        for (int k = 0; k < n; k++)
        {
            cout << picture[i][k];
        }
        cout << endl;
    }
}
void createPic() {
    picture = new int* [n];
    for (int i = 0; i < n; i++)
    {
        picture[i] = new int[n];
        for (int k = 0; k < n; k++)
        {
            picture[i][k] = 0;
        }
    }
}
void generateImg() {
    image = new int* [height];
    
    for (int i = 0; i < height; i++)
    {
        image[i] = new int[width];
        for (int k = 0; k < width; k++)
        {
            image[i][k] = 0;
            if (k == 0)
            {
                image[i][k] = 0;
            }
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            cout << image[i][k];
        }
        cout << endl;
    }
}

bool F(int x, int y) { // добавление изображения --- не учитывается сложность
    if (x + width - 1 > n)
    {
        cout << "Ошибка! Выход за пределы картинки (x)";
        return false;
    }
    if (y + height - 1 > n)
    {
        cout << "Ошибка! Выход за пределы картинки (y)";
        return false;
    }
    for (int i = x; i < x + width; i++)
    {
        for (int k = y; k < y + height; k++)
        {
            picture[i][k] = image[i - x][k - y];
        }
        cout << endl;
    }
    return true;
}

void S() { // анализатор картинки

}

int main()
{
    setlocale(LC_ALL, "RUS");

    cout << "Input size: ";
    cin >> n;

    createPic();

    int x, y;
    bool isAddedImg = false;

    while (!isAddedImg) {
        cout << "Введите координаты x, y: ";
        cin >> x >> y;
        cout << "Введите ширину и высоту: ";
        cin >> width >> height;
        generateImg();
        //isAddedImg = F(x, y);
    }
    
    //printPic();
}
