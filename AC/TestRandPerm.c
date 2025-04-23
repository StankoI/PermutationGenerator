#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "TestRandPerm.h"
#include "PermutationInfo.h"
#include "PermutationGenerator.h"
#include "rankOfPermutation.h"
#include "PermutationByRank.h"

// Тества равномерното разпределение при генерирането на случайна пермутация.
void testUniformRandomPermGenWithLength4(int numOfIterations)
{
#define n 4
#define n_factorial 24

    int *countPerm = (int *)calloc(n_factorial, sizeof(int));
    if (!countPerm)
    {
        printf("Няма достатъчно памет.\n");
        return;
    }

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr)
    {
        free(countPerm);
        printf("Няма достатъчно памет.\n");
        return;
    }

    PermutInfo info; // Just a placeholder (not used).
    info.cycleLenCounters = (int *)malloc(n * sizeof(int));
    if (!info.cycleLenCounters)
    {
        free(arr);
        free(countPerm);
        printf("Няма достатъчно памет.\n");
        return;
    }

    countPerm = &(countPerm[-1]);

    for (; numOfIterations > 0; --numOfIterations)
    {
        generateRandomPermutation(arr, n, &info);
        if (!arr[0])
        {
            countPerm = &(countPerm[+1]);
            free(countPerm);
            free(arr);
            free(info.cycleLenCounters);
            printf("Няма достатъчно памет.\n");
            return;
        }
        ++countPerm[rankOfPermutation(arr, n)];
    }

    free(info.cycleLenCounters);

    for (int i = 1; i <= n_factorial; ++i)
    {
        permutationByRank(arr, n, i);
        if (!arr[0])
        {
            printf("Няма достатъчно памет.\n");
            break;
        }
        printf("Пермутацията ");
        printArray(arr, n);
        printf("е генерирана %d пъти.\n", countPerm[i]);
    }

    countPerm = &(countPerm[+1]);
    free(countPerm);
    free(arr);

#undef n
#undef n_factorial
}

void sumArrays(double *arr1, int *arr2, int len)
{
    for (--len; len >= 0; --len)
        arr1[len] += arr2[len];
}

void divideArray(double *values, int len, double divisor)
{
    for (--len; len >= 0; --len)
        values[len] /= divisor;
}

// Тества статистиката на циклите на пермутация.
void testCyclesInPermutation(int n, int numOfIterations)
{
    int *array = (int *)malloc(n * sizeof(int));
    if (!array)
    {
        printf("Няма достатъчно памет.\n");
        return;
    }

    PermutInfo info;
    info.cycleLenCounters = (int *)malloc(n * sizeof(int));
    if (!info.cycleLenCounters)
    {
        free(array);
        printf("Няма достатъчно памет.\n");
        return;
    }

    double sumCycleCounter = 0.0;
    double sumAverageCycleLength = 0.0;
    double *sumCycleLenCounters = (double *)calloc(n, sizeof(double));
    if (!sumCycleLenCounters)
    {
        free(info.cycleLenCounters);
        free(array);
        printf("Няма достатъчно памет.\n");
        return;
    }

    for (int i = 1; i <= numOfIterations; ++i)
    {
        generateRandomPermutation(array, n, &info);
        if (!array[0])
        {
            free(info.cycleLenCounters);
            free(array);
            printf("Няма достатъчно памет.\n");
            return;
        }
        sumArrays(sumCycleLenCounters, info.cycleLenCounters, n);
        sumArrays(&sumCycleCounter, &(info.cycleCounter), 1);
        sumAverageCycleLength += (info.averageCycleLength);
    }

    free(info.cycleLenCounters);
    free(array);

    divideArray(sumCycleLenCounters, n, numOfIterations);
    divideArray(&sumCycleCounter, 1, numOfIterations);
    divideArray(&sumAverageCycleLength, 1, numOfIterations);

    sumCycleLenCounters = &(sumCycleLenCounters[-1]);

    printf("Експериментални резултати за пермутации с дължина %d:\n", n);
    printf("1) Средният брой на циклите е %f.\n", sumCycleCounter); // theoretical: ln n
    printf("2) Средната дължина на цикъл е %f.\n", sumAverageCycleLength);
    printf("3) Средният брой на циклите с дадена дължина е:\n");
    for (int r = 1; r < n; ++r)
    {
        printf("   %f цикъла с дължина %d;\n", sumCycleLenCounters[r], r);
        // theoretical value: 1/r
    }
    printf("   %f цикъла с дължина %d.\n", sumCycleLenCounters[n], n);
    // theoretical value: 1/n

    sumCycleLenCounters = &(sumCycleLenCounters[+1]);
    free(sumCycleLenCounters);
}

void testRandomPermGenWithLength7(int numOfPermutations)
{
#define n 7

    int *arr = (int *)malloc(n * sizeof(int));
    if (!arr)
    {
        printf("Няма достатъчно памет.\n");
        return;
    }

    PermutInfo info; // Just a placeholder (not used).
    info.cycleLenCounters = (int *)malloc(n * sizeof(int));
    if (!info.cycleLenCounters)
    {
        free(arr);
        printf("Няма достатъчно памет.\n");
        return;
    }

    for (; numOfPermutations > 0; --numOfPermutations)
    {
        generateRandomPermutation(arr, n, &info);
        if (!arr[0])
        {
            printf("Няма достатъчно памет.\n");
            break;
        }
        printArray(arr, n);
        printf("\n");
    }

    free(info.cycleLenCounters);
    free(arr);

#undef n
}