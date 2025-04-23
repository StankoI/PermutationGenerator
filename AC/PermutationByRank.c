#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include "PermutationByRank.h"

// Намира пермутация по поредния номер в лексикографската наредба.
void permutationByRank(int *arr, int len, int rank)
{
    // Проверка за невалидни входни данни.
    if (arr == NULL || len <= 0)
        return;

    if (rank < 1)
    {
        arr[0] = 0; // Индикатор за грешка.
        return;
    }

    // Масиви за факториелите и елементите.
    int* factorials = (int*)malloc(len * sizeof(int));
    if (factorials == NULL)
    {
        arr[0] = 0; // Грешка при заделяне на памет.
        return;
    }

    int f = 1;
    int k, i;
    factorials[len - 1] = f;

    // Изчисляване на факториелите.
    for (k = 1, i = len - 2; k < len; ++k, --i)
    {
        f *= k;
        factorials[i] = f;
    }
    f *= len;

    // Проверка дали рангът е извън допустимите стойности.
    if (rank > f)
    {
        arr[0] = 0; // Индикатор за грешка
        free(factorials);
        return;
    }

    --rank;

    // Масив за съхранение на наличните елементи.
    int* elements = (int*)malloc(len * sizeof(int));
    if (elements == NULL)
    {
        arr[0] = 0; // Грешка при заделяне на памет.
        free(factorials);
        return;
    }

    for (i = 0; i < len; ++i)
    {
        elements[i] = 1; // Всички елементи са налични
    }

    // Генериране на пермутацията по пореден номер.
    for (k = 0; k < len; ++k)
    {
        f = factorials[k];
        int q = rank / f;
        rank -= (q * f);
        ++q;

        int cnt = 0;
        i = -1;
        while (cnt < q)
        {
            ++i;
            if (elements[i]) ++cnt;
        }

        arr[k] = i + 1;
        elements[i] = 0; // Отстраняване на елемент.
    }

    // Освобождаване на заделената памет.
    free(elements);
    free(factorials);
}
