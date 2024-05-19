#include <iostream>
#include <string>
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>

# define M_PI 3.14159265358979323846

using namespace std;

mutex mtx;
condition_variable cv;

bool isOneFinished = false;
float finishX = 15;

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
	float radius;
	float distance = 0; // общее пройденное расстояние
	float speed;
	string name;
	ball(float radius, float speed, string name) {
		this->radius = radius;
		this->speed = speed;
		this->name = name;
		center.setPos(0, radius);
		move(0);
	}
	// передвигает мячик по оси X на шаг с длиной range
	void move(float range) {
		center.addVec(range, 0);
		distance += range;
		float x = center.x + radius * cos(M_PI * 3 / 2 + distance / radius);
		float y = center.y + radius * sin(M_PI * 3 / 2 + distance / radius);
		dot.setPos(x, y); // присвоение новой координаты точке на краю мяча
	}
};

void moveOneBall(ball& b, bool& canMove) {
	unique_lock<mutex> lck(mtx);
	while (b.distance < finishX) // выполняем пока мяч не дойдет до финиша
	{
		while (!canMove) { cv.wait(lck); }
		canMove = false;
		b.move(b.speed);
	}
}

void ActivateThreads(bool& canMove1, bool& canMove2) {
	unique_lock<mutex> lck(mtx);
	canMove1 = true;
	canMove2 = true;
	cv.notify_all();
}

int main()
{
	setlocale(LC_ALL, "RUS");

	float radius = 2;
	float speed1 = 0.5;
	float speed2 = 1.2;

	ball b1(radius, speed1, "Красный шарик"); // мяч 1
	ball b2(radius, speed2, "Синий мячик"); // мяч 2

	finishX = 15; // дистанция до финиша
	bool canMove1 = false;
	bool canMove2 = false;

	thread th1(moveOneBall, ref(b1), ref(canMove1));
	thread th2(moveOneBall, ref(b2), ref(canMove2));
	auto t0 = std::chrono::high_resolution_clock::now();
	ActivateThreads(canMove1, canMove2); // разрешаем потокам 1 раз сдвинуть мячи
	auto t1 = std::chrono::high_resolution_clock::now();
	auto time = std::chrono::duration_cast<std::chrono::microseconds>(t1 - t0);
	cout << time.count() << " мс |" << b1.center.x << " " << b1.center.y << " | " << b1.dot.x << b1.dot.y;
	th1.join();
	th2.join();
	
	cout << endl << "Конец!";

	auto s = std::chrono::high_resolution_clock::now();
	auto e = std::chrono::high_resolution_clock::now();
	

}