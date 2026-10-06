#include "ArrayUtils.h"

extern "C" ARRAYUTILS_API void ReplaceMinMax(int* arr, int size, int minIdx, int maxIdx, double average) {
    if (!arr || size <= 0) return;

    int avgValue = static_cast<int>(average);

    if (minIdx >= 0 && minIdx < size) {
        arr[minIdx] = avgValue;
    }
    if (maxIdx >= 0 && maxIdx < size) {
        arr[maxIdx] = avgValue;
    }
}