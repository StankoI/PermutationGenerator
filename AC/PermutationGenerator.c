#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "PermutationGenerator.h"

// Инициализира масив с числата от 1 до size.
void init(int *array, int size)
{
    for (int i = size; i > 0; --i)
    {
        array[i] = i;
    }
}

// Отпечатва масив.
void printArray(int *array, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("%d ", array[i]);
    }
}

// За време O(n) генерира случайна пермутация с равномерно разпределение.
void generateRandomPermutation(int *arr, int n, PermutInfo *info)
{
    if (!arr || n <= 0 || !info) return;

    if (!info->cycleLenCounters) return;

    arr[0] = 0; // Индикатор за грешка (недостатъчно памет).

    bool * isUsed = (bool*)calloc(n, sizeof(bool));

    if (!isUsed) return;

    int * numbers = (int*)malloc(n * sizeof(int));

    if (!numbers) {free(isUsed); return;}

    memset(info->cycleLenCounters, 0, n * sizeof(int));

    numbers = &(numbers[-1]);
    isUsed = &(isUsed[-1]);
    arr = &(arr[-1]);
    info->cycleLenCounters = &(info->cycleLenCounters[-1]);
    
    info->cycleCounter = 0;
    
    int cntAvailable = n;
    
    init(numbers, cntAvailable);
    
    int start = 1;
    int cur = start;
    int curCycLen = 0;
    isUsed[start] = true;
    
    while (true)
    {
        int nextIndex = (rand() % cntAvailable) + 1;
        int nextNum = numbers[nextIndex];
        
        arr[cur] = nextNum;
        isUsed[cur] = true;
        numbers[nextIndex] = numbers[cntAvailable];
        --cntAvailable;
        ++curCycLen;
        
        cur = nextNum;
        
        if (cur == start)
        {
            ++(info->cycleCounter);
            ++(info->cycleLenCounters[curCycLen]);
            if (!cntAvailable)
                break;         
            do {++start;} while(isUsed[start]);
            cur = start;
            curCycLen = 0;
        }
    }

    info->averageCycleLength = n / info->cycleCounter;

    numbers = &(numbers[+1]);
    isUsed = &(isUsed[+1]);
    arr = &(arr[+1]);
    info->cycleLenCounters = &(info->cycleLenCounters[+1]);
    free(numbers);
    free(isUsed);
}



