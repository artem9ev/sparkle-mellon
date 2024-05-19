#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mtx;
vector<vector<int>> gr1;
vector<vector<int>> gr2;
int n = 200;
bool flag1 = 1, flag2 = 1;

vector<vector<int>> G1(int n) {
    vector<vector<int>> g1(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            g1[i][j] = g1[j][i] = rand() % 2;
        }
    return g1;
}

vector<vector<int>> G2(vector<vector<int>> g1, int n) {
    vector<vector<int>> g2(n, vector<int>(n));
    bool* isSetted = new bool[n];
    for (int i = 0; i < n; i++)
    {
        isSetted[i] = false;
    }
    int v2, v1 = 0;
    int* rename = new int[n];
    while (v1 < n) // переименование вершин
    {
        v2 = rand() % n;
        while (isSetted[v2]) {
            v2 = (v2 + 1) % n;
        }
        rename[v1] = v2;
        isSetted[v2] = true;
        v1++;
    }
    for (int i = 0; i < n; i++) { // заполнение g2 с учетом переименованых вершин
        for (int k = 0; k < n; k++) {
            if (k >= i) {
                g2[i][k] = g1[rename[i]][rename[k]];
                g2[k][i] = g1[rename[i]][rename[k]];
            }
        }
    }
    return gr2;
}

vector<int> Rename(int n) {
    vector<int> renumber;
    for (int i = 0; i < n; i++) {
        renumber.push_back(i);
    }
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        swap(renumber[i], renumber[j]);
    }
    return renumber;
}

vector<vector<int>> RenameVershInGrph(const vector<vector<int>>& orig, vector<int> r) {
    int n = orig.size();
    vector<vector<int>> g(n, vector<int>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (orig[i][j] == 1) {
                g[r[i]][r[j]] = g[r[j]][r[i]] = 1;
            }
        }
    }
    return g;
}

vector<int> StepenVersh(const vector<vector<int>>& adjacencyMatrix) {
    vector<int> stepeni;
    for (int i = 0; i < adjacencyMatrix.size(); i++) {
        int stepen = 0;
        for (int j = 0; j < adjacencyMatrix[i].size(); j++) {
            if (adjacencyMatrix[i][j] == 1) {
                stepen++;
            }
        }
        stepeni.push_back(stepen);
    }
    return stepeni;
}

bool isIso(const vector<vector<int>>& g1, const vector<vector<int>>& g2) {
    vector<int> stepenG1 = StepenVersh(g1);
    vector<int> stepenG2 = StepenVersh(g2);
    sort(stepenG1.begin(), stepenG1.end());
    sort(stepenG2.begin(), stepenG2.end());
    if (stepenG1 != stepenG2) {
        flag2 = 0;
        return false;
    }
    return true;
}

void checkIsomorphism(int id, const vector<vector<int>>& gr1, const vector<vector<int>>& gr2, int start, int end, int numThreads) {
    for (int i = start; i < end; i++) {
        vector<vector<int>> temp = RenameVershInGrph(gr1, Rename(gr1.size()));
        if (isIso(temp, gr2) && flag1 == 1 && id == numThreads) {
            mtx.lock();
            cout << "Graphs are not isomorphic" << endl;
            mtx.unlock();
            return;
        }
        else if (id == numThreads && flag2 == 0) {
            mtx.lock();
            cout << "Graphs are isomorphic" << endl;
            mtx.unlock();
            return;
        }
    }
}

int main() {
    srand(time(0));
    gr1 = G1(n);
    gr2 = G2(gr1, n);

    int numThreads;
    cout << "threads: "; cin >> numThreads;
    vector<thread> threads;
    int chunk = gr1.size() / numThreads;
    int start = 0;
    int end = chunk;
    auto s = std::chrono::high_resolution_clock::now();
    for (int i = 1; i <= numThreads; ++i) {
        threads.push_back(thread(checkIsomorphism, i + 1, ref(gr1), ref(gr2), start, end, numThreads));
        start = end;
        end += chunk;
    }
    for (auto& thread : threads) {
        thread.join();
    }
    auto e = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<std::chrono::microseconds>(e - s);
    std::cout << "Time taken with " << numThreads << " threads: " << time.count() << " microseconds" << std::endl;
    return 0;
}