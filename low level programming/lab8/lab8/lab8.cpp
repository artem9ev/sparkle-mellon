#include <iostream>
#include <thread>
#include <vector>
#include <mutex>

using namespace std;
mutex mtx;

void scal(vector<int> v1, vector<int> v2, int& sum, int s, int e){
	for (int i = s; i < e; i++)
	{
		mtx.lock();
		sum += v1[i] * v2[i];
		mtx.unlock();
	}
}

void sssort(vector<int>& v, int& i, int& k) {
	mtx.lock();
	while (i < v.size())
	{
		k = i + 1;
		while (k < v.size()) {
			if (v[i] > v[k])
			{
				int t = v[i];
				v[i] = v[k];
				v[k] = t;
			}
			k++;
		}
		i++;
	}
	mtx.unlock();
}


int main()
{
    int sum = 0;
	int n = 10000;
	vector<int> v(n);
	for (int i = 0; i < n; i++)
	{
		v[i] = rand() % 100;
	}
	int superI = 0, superK;
	auto t0 = chrono::high_resolution_clock::now();
	thread th1(sssort, ref(v), ref(superI), ref(superK));
	thread th2(sssort, ref(v), ref(superI), ref(superK));
	th1.join();
	th2.join();
	auto t1 = chrono::high_resolution_clock::now();
	
	for (int i = 0; i < n; i++)
	{
		//cout << v[i] << " ";
	}
	cout << "2 th -> " << chrono::duration_cast<chrono::milliseconds>(t1 - t0).count() << " msec" << endl;

    /*vector<int> v1(n);
    vector<int> v2(n);
	for (int i = 0; i < n; i++)
	{
		v1[i] = 1;
		v2[i] = 1;
	}
	thread th1(scal, v1, v2, ref(sum), 0, v1.size() / 2);
	thread th2(scal,v1, v2, ref(sum), v1.size() / 2, v1.size());
	th1.join();
	th2.join();
	cout << "scal = " << sum << endl;*/
}