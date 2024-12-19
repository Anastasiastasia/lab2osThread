// lap2Thread.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <vector>
#include <thread>
#include <chrono>
#include <algorithm>
#include <windows.h>

using namespace std;

vector<int> numbers;
DWORD WINAPI min_max(LPVOID) {
    int min_elem = numbers[0];
    int max_elem = numbers[0];

    for (const auto& num : numbers) {
        Sleep(7); // Пауза
        if (num < min_elem) {
            min_elem = num;
        }
        if (num > max_elem) {
            max_elem = num;
        }
    }

    cout << "Min: " << min_elem << ", Max: " << max_elem << endl;
    return 0;
}
DWORD WINAPI average(LPVOID) {
    double sum = 0;

    for (const auto& num : numbers) {
        sum += num;
        Sleep(12); // Пауза
    }

    double avg = sum / numbers.size();
    cout << "Average: " << avg << endl;
    return 0;
}

int main() {
    int n;

    cout << "Enter the size of the array: ";
    cin >> n;

    numbers.resize(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; ++i) {
        cin >> numbers[i];
    }

    HANDLE hMinMax = CreateThread(NULL, 0, min_max, NULL, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average, NULL, 0, NULL);

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    double sum = 0;
    for (const auto& num : numbers) {
        sum += num;
    }
    double avg = sum / numbers.size();

    
    auto min_elem = *min_element(numbers.begin(), numbers.end());
    auto max_elem = *max_element(numbers.begin(), numbers.end());

    //replace(numbers.begin(), numbers.end(), min_elem, avg);
   // replace(numbers.begin(), numbers.end(), max_elem, avg);
    min_elem = numbers[0];
    max_elem = numbers[0];
    for (int i = 0; i < numbers.size(); i++)
    {
        if (min_elem > numbers[i])
        {
            min_elem = numbers[i];
        }
        if (max_elem< numbers[i])
        {
            max_elem = numbers[i];
        }
    }
    cout << "Modified array: ";
    for (const auto& num : numbers) {
        cout << num << " ";
    }
    cout << endl;

    CloseHandle(hMinMax);
    CloseHandle(hAverage);
    return 0;
}