#include <iostream>
#include <string>
using namespace std;

char symbol = '\0'; //текущий символ в строке
int marker = 0; //номер текущего символа в строке
string str; //проверяемая строка

void nextsym() //записывает следующий символ в переменную symbol
{
    symbol = str[marker];
    if (str.size() > marker)
        marker++;
}

void sign() //если текущий символ есть ожидаемый минус, то пропускает минус если он есть
{
    if (symbol == '-') nextsym();
}

void number() //если текущие символы ряд цифр, пропускает их всех
{
    while (symbol >= '0' && symbol <= '9')
    {
        nextsym();
    }
}

void realNumber() //пропускает ожидаемое вещественное число
{
    sign();
    number();
    if (symbol == '.') //если встречает . то пропускает эту точку и пропускает все дальнейшие цифры
    {
        nextsym();
        number();
    }
}

bool accept(char sym) //если текущий символ = ожидаемому пропускает его, иначе передаёт false
{
    if (symbol == sym)
    {
        nextsym();
        return true;
    }
    else
    {
        return false;
    }
}

bool Gorner() //проверяет является ли строка схемой Горнера
{
    realNumber();
    bool isGorner = true;
    if (symbol == '+')
    {
        nextsym();
        isGorner = accept('x');
        isGorner = accept('(');
        isGorner = Gorner();
        isGorner = accept(')');
    }
    return isGorner;
}

int main() {

    setlocale(LC_ALL, "Russian");
    getline(cin, str);
    nextsym(); //считывает первый символ
    if (Gorner() && marker == str.size()) {
        cout << "Это схема Горнера";
    }
    else {
        cout << "Это не схема Горнера";
    }
    return 0;
}
