#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#ifdef ARRAYUTILS_EXPORTS
#define ARRAYUTILS_API __declspec(dllexport)
#else
#define ARRAYUTILS_API __declspec(dllimport)
#endif

extern "C" {
    ARRAYUTILS_API void ReplaceMinMax(int* arr, int size, int minIdx, int maxIdx, double average);
}

#endif 