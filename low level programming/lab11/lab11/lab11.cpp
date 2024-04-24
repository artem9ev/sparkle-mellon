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
	ball(int radius) {
		this->radius = radius;
		dot.setPos(center.x, center.y - radius);
	}
	ball(int radius, float x, float y) {
		this->radius = radius;
		center.setPos(x, y);
		dot.setPos(x, y + radius);
		
	}
	// l - пройденное мячиком растояние
	void move(float l) {
		//center.addVec(l, 0);
		float x = center.x - radius * cos(M_PI * 3 / 2 + l / radius);
		float y = center.y - radius * sin(M_PI * 3 / 2 + l / radius);
		dot.setPos(x, y); // присвоение новой координаты точке на краю мяча
		cout << fixed << "c1: " << center.x << " " << center.y << endl;
		cout << fixed << "d1: " << dot.x << " " << dot.y << endl;
	}
};

int main()
{
	int radius = 5;
	float s = 0;
	int n = 27;
	int** pic = new int* [n];
	pos picCenter(n / 2, n / 2);
	for (int i = 0; i < n; i++)
	{
		pic[i] = new int[n]; 
		for (int k = 0; k < n; k++)
		{
			pic[i][k] = 0;
		}
	}
	ball b(radius, picCenter.x, picCenter.y);
	float l; cout << "l = "; cin >> l;

	b.move(l);
	//exit(1);
	pic[(int)picCenter.y][(int)picCenter.x] = 1;

	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			// для каждой точки считаю расстояние до центра окружности
			if (b.center.getRange(i, k) < radius)
			{
				pic[i][k] = 1;
			}
		}
	}
	pic[(int)b.dot.y][(int)b.dot.x] = 2;
	cout << "c: " << b.center.x << " " << b.center.y << endl;
	cout << "d: " << b.dot.x << " " << b.dot.y << endl;

	string str = "";
	for (int i = 0; i < n; i++)
	{
		for (int k = 0; k < n; k++)
		{
			if (pic[i][k] == 0)
			{
				str += " -";
			}
			else if (pic[i][k] == 1)
			{
				str += " #";
			}
			else if (pic[i][k] == 2)
			{
				str += " X";
			}
		}
		str += "\n";
		cout << str;
		str = "";
	}
}