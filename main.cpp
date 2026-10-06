#include <iostream>
#include <windows.h>

using namespace std;

struct ThreadData {
    int* arr;
    int size;
    int min_idx;
    int max_idx;
    double avg;
};

DWORD WINAPI min_max_thread(LPVOID param) {
    ThreadData* data = (ThreadData*)param;
    if (!data || data->size <= 0) return 0;

    int min_i = 0;
    int max_i = 0;

    for (int i = 0; i < data->size; ++i) {
        if (data->arr[i] < data->arr[min_i]) {
            min_i = i;
        }
        Sleep(7);

        if (data->arr[i] > data->arr[max_i]) {
            max_i = i;
        }
        Sleep(7);
    }

    data->min_idx = min_i;
    data->max_idx = max_i;

    cout << "Минимальный элемент: " << data->arr[min_i] << endl;
    cout << "Максимальный элемент: " << data->arr[max_i] << endl;

    return 0;
}

DWORD WINAPI average_thread(LPVOID param) {
    ThreadData* data = (ThreadData*)param;
    if (!data || data->size <= 0) return 0;

    double sum = 0;
    for (int i = 0; i < data->size; ++i) {
        sum += data->arr[i];
        Sleep(12);
    }

    data->avg = sum / data->size;

    cout << "Среднее арифметическое: " << data->avg << endl;

    return 0;
}

typedef void (*ReplaceFunc)(int*, int, int, int, double);

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    cout << "Введите размер массива: ";
    cin >> n;

    if (n <= 0) {
        cout << "Размер массива должен быть положительным числом." << endl;
        return 1;
    }

    int* arr = new int[n];
    cout << "Введите элементы массива: ";
    for (int i = 0; i < n; ++i) {
        cin >> arr[i];
    }

    ThreadData data;
    data.arr = arr;
    data.size = n;
    data.min_idx = 0;
    data.max_idx = 0;
    data.avg = 0.0;

    HANDLE hMinMax = CreateThread(NULL, 0, min_max_thread, &data, 0, NULL);
    HANDLE hAverage = CreateThread(NULL, 0, average_thread, &data, 0, NULL);

    if (!hMinMax || !hAverage) {
        cerr << "Ошибка при создании потоков." << endl;
        delete[] arr;
        return 1;
    }

    WaitForSingleObject(hMinMax, INFINITE);
    WaitForSingleObject(hAverage, INFINITE);

    CloseHandle(hMinMax);
    CloseHandle(hAverage);

    HMODULE hLib = LoadLibraryA("ArrayUtils.dll");
    if (hLib) {
        ReplaceFunc replace_fn = (ReplaceFunc)GetProcAddress(hLib, "replace_min_max");
        if (replace_fn) {
            replace_fn(arr, n, data.min_idx, data.max_idx, data.avg);
        }
        FreeLibrary(hLib);
    }
    else {
        cerr << "Ошибка загрузки библиотеки ArrayUtils.dll" << endl;
    }

    cout << "\nПолученный массив: ";
    for (int i = 0; i < n; ++i) {
        cout << arr[i] << " ";
    }
    cout << endl;

    delete[] arr;
    return 0;
}