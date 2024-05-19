#include <iostream>
#include <string>
#include <math.h>
#include <thread>
#include <mutex>
#include <condition_variable>

# define M_PI 3.14159265358979323846

using namespace std;
using time_point = std::chrono::steady_clock::time_point;

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
	bool isFinished = false;
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

void moveOneBall(ball& b, bool& canMove, time_point& tickTime) {
	unique_lock<mutex> lck(mtx);
	while (b.distance < finishX) // выполняем пока мяч не дойдет до финиша
	{
		while (!canMove) { cv.wait(lck); } // ждем разрешение на действие
		canMove = false;

		time_point EndTime = chrono::high_resolution_clock::now();

		int time = chrono::duration_cast<chrono::milliseconds>(EndTime - tickTime).count();
		float speed = isOneFinished ? b.speed * 2 : b.speed;
		float range = speed * time / 1000;
		b.move(range);
	}
}

// оповещение потоков
void ActivateThreads(bool& canMove1, bool& canMove2, time_point& tickTime) {
	unique_lock<mutex> lck(mtx);
	canMove1 = true;
	canMove2 = true;
	tickTime = chrono::high_resolution_clock::now();
	this_thread::sleep_for(chrono::milliseconds { 100 });
	cv.notify_all();
}

int main()
{
	setlocale(LC_ALL, "RUS");

	float radius = 1;
	float speed1 = 0.5;
	float speed2 = 1.2;

	cout << "Скорость первого мяча: "; cin >> speed1;
	cout << "Скорость второго мяча: "; cin >> speed2;

	ball b1(radius, speed1, "Красный шарик"); // мяч 1
	ball b2(radius, speed2, "Синий мячик"); // мяч 2

	finishX = 15; // дистанция до финиша
	bool canMove1 = false;
	bool canMove2 = false;

	cout << "Мяч 1 - " + b1.name << endl;
	cout << "Мяч 2 - " + b2.name << endl;
	cout << "Расстояние до финиша: " << finishX;

	// выводит сначала координаты точек первого мяча, затем второго
	cout << endl << "0 мс | ц1: " << fixed << b1.center.x << " " << b1.center.y << "; вн1: " << b1.dot.x << " " << b1.dot.y << " ||| ц2: "
		<< b2.center.x << " " << b2.center.y << "; вн2: " << b1.dot.x << " " << b1.dot.y << endl;

	time_point tickTime;

	thread th1(moveOneBall, ref(b1), ref(canMove1), ref(tickTime));
	thread th2(moveOneBall, ref(b2), ref(canMove2), ref(tickTime));

	time_point t0 = chrono::high_resolution_clock::now();

	while (b1.distance < finishX || b2.distance < finishX)
	{
		ActivateThreads(canMove1, canMove2, tickTime); // разрешаем потокам 1 раз сдвинуть мячи
		time_point t1 = chrono::high_resolution_clock::now();
		auto time = chrono::duration_cast<chrono::milliseconds>(t1 - t0);
		cout << time.count() << " мс | ц1: " << fixed << b1.center.x << " " << b1.center.y << "; вн1: " << b1.dot.x << " " << b1.dot.y << " ||| ц2: "
			<< b2.center.x << " " << b2.center.y << "; вн2: " << b1.dot.x << " " << b1.dot.y << endl;
		if (b1.distance >= finishX && !b1.isFinished)
		{
			cout << endl << b1.name << " финишировал!!!" << endl;
			b1.isFinished = true;
			if (!isOneFinished)
			{
				cout << b2.name << " ускорился в 2 раза!" << endl << endl;
			}
			isOneFinished = true;
		}
		if (b2.distance >= finishX && !b2.isFinished)
		{
			cout << endl << b2.name << " финишировал!!!" << endl;
			b2.isFinished = true; 
			if (!isOneFinished)
			{
				cout << b1.name << " ускорился в 2 раза!" << endl << endl;
			}
			isOneFinished = true;
		}
	}
	
	th1.join();
	th2.join();
	
	cout << endl << "Конец!";
}