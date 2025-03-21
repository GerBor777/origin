#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

void vector_sum(const vector<int>& a, const vector<int>& b, vector<int>& result, int start, int end) {
    for (int i = start; i < end; ++i) {
        result[i] = a[i] + b[i];
    }
}

void run_test(int num_threads, int size) {
    vector<int> a(size, 1);
    vector<int> b(size, 2);
    vector<int> result(size);
    vector<thread> threads;

    auto start_time = high_resolution_clock::now();
    int chunk_size = size / num_threads;
    for (int i = 0; i < num_threads; ++i) {
        int start = i * chunk_size;
        int end = (i == num_threads - 1) ? size : start + chunk_size;
        threads.emplace_back(vector_sum, cref(a), cref(b), ref(result), start, end);
    }

    for (auto& t : threads) {
        t.join();
    }

    auto end_time = high_resolution_clock::now();
    duration<double> elapsed = end_time - start_time;
    cout << fixed << setprecision(6) << elapsed.count() << "s";
}

int main() {
    int num_cores = thread::hardware_concurrency();
    cout << "Количество аппаратных ядер - " << num_cores << "\n";
    vector<int> sizes = {1000, 10000, 100000, 1000000};
    vector<int> thread_counts = {1, 2, 4, 8, 16};

    cout << setw(12) << " " ;
    for (int size : sizes) {
        cout << setw(10) << size;
    }
    cout << endl;

    for (int threads : thread_counts) {
        cout << setw(10) << threads << " потоков";
        for (int size : sizes) {
            cout << setw(10);
            run_test(threads, size);
        }
        cout << endl;
    }
    return 0;
}