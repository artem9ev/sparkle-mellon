#include <iostream>
#include <fstream>

#define CAPACITY 2000

using namespace std;

int hesh(char* str);
int rehesh(int key);

struct obj {
    char* str;
    int l;
    obj() {
        l = rand() % 16 + 5;
        str = new char[l + 1];
        str[l] = '\0';
        for (int i = 0; str[i]; i++)
        {
            str[i] = rand() % ('z' - 'a') + 'a';
        }
    }
};

struct {
    obj elem[CAPACITY];
    int r_id[CAPACITY];
    int size = 0; // кол-во добавленных эл-ов в таблицу
    int l_collisions = 0; // кол-во коллизий при линейном рехешировании
    int r_collisions = 0; // кол-во коллизий при случайном рехешировании
    float full = 0.0f; // %
    void newR() {
        for (int i = 0; i < CAPACITY; i++)
        {
            r_id[i] = rand() % CAPACITY;
        }
    }
    void addLin(obj o) {
        int h = hesh(o.str); // хешируем
        while (elem[h].str != NULL) // пока не найдем свободное место...
        {
            h = rehesh(h); // рехешируем
            l_collisions++; // +1 рехеш коллизия
        }
        elem[h].str = o.str; // записывем в таблицу
        size++; // +1 эл-нт в таблице
        full = (float)size / CAPACITY; // пересчет процента заполненности
    }
    void addRand(obj o) {
        int h = hesh(o.str); // хешируем
        int i = h;
        while (elem[h].str != NULL) // пока не найдем свободное место...
        {
            h = (h + r_id[i]) % CAPACITY; // рехешируем
            i = ++i % CAPACITY;
            r_collisions++; // +1 рехеш коллизия
        }
        elem[h].str = o.str; // записывем в таблицу
        size++; // +1 эл-нт в таблице
        full = (float)size / CAPACITY; // пересчет процента заполненности
    }
    void clear() {
        for (int i = 0; i < CAPACITY; i++)
        {
            delete[] elem[i].str;
            elem[i].str = nullptr;
        }
        l_collisions = 0;
        r_collisions = 0;
        size = 0;
        full = 0.0f;
    }
} table;

int hesh(char* str) {
    long c = 0;
    for (int k = 0; str[k]; k++)
    {
        c += str[k];
    }
    return c % CAPACITY;
}

int rehesh(int key) {
    return (key + 1) % CAPACITY;
}

void print(obj o) {
    cout << "len: " << o.l << "  \tkey: " << hesh(o.str) << "  \tvalue: ";
    for (int k = 0; o.str[k]; k++)
    {
        cout << o.str[k];
    }
    cout << endl;
}

int main()
{
    srand(time(NULL));
    for (int i = 0; i < CAPACITY; i++)
    {
        table.elem[i].str = nullptr;
    }
    table.newR();

    ofstream outRes("res.txt");

    float sR[19];
    float sL[19];
    for (int i = 0; i < 19; i++)
    {
        sR[i] = 0;
        sL[i] = 0;
    }

    for (int i = 100, j = 0; i <= 1900; i += 100, j++)
    {
        for (int k = 0; k < 1000; k++) // эксперементируем
        {
            while (table.full < (float)i / CAPACITY) { // хеширование с случайноным рехешированием
                obj o;
                table.addRand(o);
            }
            sR[j] += (float)table.r_collisions / 1000;
            table.clear();

            while (table.full < (float)i / CAPACITY) { // хеширование с линейным рехешированием
                obj o;
                table.addLin(o);
            }
            sL[j] += (float)table.l_collisions / 1000;
            table.clear();
        }
        cout << fixed << ((float)i / CAPACITY) << "    \t" << sR[j] << "    \t" << sL[j] << endl;
        outRes << fixed << ((float)i / CAPACITY) << "    \t" << sR[j] << "    \t" << sL[j] << endl;
    }
}