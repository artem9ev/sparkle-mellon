#include <iostream>
#define CAPACITY 2000

using namespace std;

// анализ коллизий при загруженности таблицы от 0.05 до 0.95 с шагом 0.05
// анализ для:
// 1. хеширования
// 2. лин. рехеширования // 1000 эксперименттов для каждой точки графика
// 3. случ. рехеширования

int hesh(char* str);
int rehesh(int key);

struct {
    char* elem[CAPACITY];
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
    void addLin(char* str) {
        int h = hesh(str); // хешируем
        while (elem[h][0] != '\0') // пока не найдем свободное место...
        {
            h = rehesh(h); // рехешируем
            l_collisions++; // +1 рехеш коллизия
        }
        elem[h] = str; // записывем в таблицу
        size++; // +1 эл-нт в таблице
        full = (float)size / CAPACITY; // пересчет процента заполненности
    }
    void addRand(char* str) {
        int h = hesh(str); // хешируем
        while (elem[h][0] != '\0') // пока не найдем свободное место...
        {
            h = (h + r_id[h]) % CAPACITY; // рехешируем
            l_collisions++; // +1 рехеш коллизия
        }
        elem[h] = str; // записывем в таблицу
        size++; // +1 эл-нт в таблице
        full = (float)size / CAPACITY; // пересчет процента заполненности
        cout << "hesh = " << h << "  \tvalue = " << elem[h] << endl;
    }
    void print() {
        for (int i = 0; i < CAPACITY; i++)
        {
            cout << "hesh = " << i << "  \tvalue = " << elem[i];
            cout << endl;
            if (elem[i][0] != '\0')
            {
                
            }
        }
    }
    void clear() {
        for (int i = 0; i < CAPACITY; i++)
        {
            elem[i] = (char*)"\0";
        }
        size = 0;
        full = 0.0f;
    }
} table;

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
        table.elem[i] = (char*)"\0";
        //cout << table.elem[i] << endl;
    }
    table.newR();
    for (int i = 1900; i <= 1900; i += 100)
    {
        for (int k = 0; k < 1; k++) // эксперементируем
        {
            while (table.full < (float)i / CAPACITY) {
                obj o;
                table.addRand(o.str);
            }
            //table.print();
            cout << "l_col   = " << table.l_collisions << endl;
            table.clear();
        }
    }
}