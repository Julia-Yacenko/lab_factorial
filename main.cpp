//#include <QCoreApplication>
#include <iostream>
#include <thread>
#include <chrono>


using namespace std;

void factorial(int a, int b, unsigned long long& res){
    unsigned long long n = 1;
    for(int i = a; i <= b; i++){
        n = n * i;
    }
    res = n;
}

void thread_1(){
    int number;
    unsigned long long res = 1;
    cout << "Enter a positive number  " << endl;
    cin >> number;
    factorial(1, number, res);
    cout << number << "! = " << res << endl;
}

void thread_2(){
    int number;
    unsigned long long res_1 = 1, res_2 = 1, res = 1;
    cout << "Enter a positive number  " << endl;
    cin >> number;
    int c = int(number / 2);
    thread thread1(factorial, 1, c, ref(res_1));
    thread thread2(factorial, (c + 1), number, ref(res_2));
    thread1.join();
    thread2.join();
    res = res_1 * res_2;
    //cout << c << "  " << res_1 << "  " << res_2 << endl;
    cout << number << "! = " << res << endl;
}

void thread_4(){
    int number;
    unsigned long long res_1 = 1, res_2 = 1, res_3 = 1, res_4 = 1, res = 1;
    cout << "Enter a positive number  " << endl;
    cin >> number;
    int c = int(number / 4);
    thread thread1(factorial, 1, c, ref(res_1));
    thread thread2(factorial, (c + 1), (2 * c), ref(res_2));
    thread thread3(factorial, (2 * c + 1), (3 * c), ref(res_3));
    thread thread4(factorial, (3 * c + 1), number, ref(res_4));
    thread1.join();
    thread2.join();
    thread3.join();
    thread4.join();
    res = res_1 * res_2 * res_3 * res_4;
    //cout << c << "  " << res_1 << "  " << res_2 << res_3 << "  " << res_4 << endl;
    cout << number << "! = " << res << endl;
}

int main()
{
    const auto start=chrono::high_resolution_clock::now();
    int k = thread::hardware_concurrency();
    cout << "Maximum number of threads: " << k << endl;

    const auto start1=chrono::high_resolution_clock::now();
    thread_1();
    const double time1=chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now()-start1).count();
    cout << "Time: " << time1/1000.0 << "ms." << endl;

    const auto start2=chrono::high_resolution_clock::now();
    thread_2();
    const double time2=chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now()-start2).count();
    cout << "Time: " << time2/1000.0 << "ms." << endl;

    const auto start4=chrono::high_resolution_clock::now();
    thread_4();
    const double time4=chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now()-start4).count();
    cout << "Time: " << time4/1000.0 << "ms." << endl;

    const double time=chrono::duration_cast<chrono::microseconds>(chrono::high_resolution_clock::now()-start).count();
    cout << "All time: " << time/1000.0 << "ms." << endl;

    return 0;
}
