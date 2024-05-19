#include <iostream>
#include <string>
#include <math.h>

# define M_PI 3.14159265358979323846

using namespace std;


struct pos {
	float x;
	float y;
	pos() {
		x = 0;
		y = 0;
	}
	pos(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void setPos(float x, float y) {
		this->x = x;
		this->y = y;
	}
	void addVec(float x, float y) {
		this->x += x;
		this->y += y;
	}
	float getRange(pos s) {
		return sqrt((this->x - s.x) * (this->x - s.x) + (this->y - s.y) * (this->y - s.y));
	}
	float getRange(float x, float y) {
		return sqrt((this->x - x) * (this->x - x) + (this->y - y) * (this->y - y));
	}
};

struct ball {
	pos center; // центр мячика
	pos dot; // точка на краю мячика
	int radius;
	float distance = 0; // общее пройденное расстояние
	ball(int radius) {
		this->radius = radius;
		dot.setPos(center.x, center.y - radius);
	}
	ball(int radius, float x, float y) {
		this->radius = radius;
		center.setPos(x, y);
		dot.setPos(x, y + radius);
		
	}
	// передвигает мячик по оси X на шаг с длиной range
	void move(float range) {
		center.addVec(range, 0);
		distance += range;
		float x = center.x - radius * cos(M_PI * 3 / 2 + distance / radius);
		float y = center.y - radius * sin(M_PI * 3 / 2 + distance/ radius);
		dot.setPos(x, y); // присвоение новой координаты точке на краю мяча
		cout << fixed << "c1: " << center.x << " " << center.y << endl;
		cout << fixed << "d1: " << dot.x << " " << dot.y << endl;
	}
};

int main()
{
	int radius = 6;
	float s = 0;
	int n = 13, m = 41;
	int** pic = new int* [n];
	pos picCenter(n / 2, n / 2);
	for (int y = 0; y < n; y++)
	{
		pic[y] = new int[m]; 
		for (int x = 0; x < m; x++)
		{
			pic[y][x] = 0;
		}
	}
	ball b(radius, 2 + radius, picCenter.y);


	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			// для каждой точки считаю расстояние до центра окружности
			if (b.center.getRange(x, y) < radius)
			{
				pic[y][x] = 1;
			}
		}
	}
	pic[(int)b.dot.y][(int)b.dot.x] = 2;
	cout << "c: " << b.center.x << " " << b.center.y << endl;
	cout << "d: " << b.dot.x << " " << b.dot.y << endl;

	string str = "";
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (pic[y][x] == 0)
			{
				str += " -";
			}
			else if (pic[y][x] == 1)
			{
				str += " #";
			}
			else if (pic[y][x] == 2)
			{
				str += " X";
			}
			else if (pic[y][x] == 4)
			{
				str += " @";
			}
		}
		str += "\n";
		cout << str;
		str = "";
	}
	// ---------------------------------------

	float l; cout << "l = "; cin >> l;
	b.move(l);

	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (b.center.getRange(x, y) < radius)
			{
				pic[y][x] = 1;
			}
			else
			{
				pic[y][x] = 0;
			}
		}
	}
	pic[(int)b.dot.y][(int)b.dot.x] = 2;
	for (int y = 0; y < n; y++)
	{
		for (int x = 0; x < m; x++)
		{
			if (pic[y][x] == 0)
			{
				str += " -";
			}
			else if (pic[y][x] == 1)
			{
				str += " #";
			}
			else if (pic[y][x] == 2)
			{
				str += " X";
			}
			else if (pic[y][x] == 4)
			{
				str += " @";
			}
		}
		str += "\n";
		cout << str;
		str = "";
	}
}