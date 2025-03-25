#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>

int cyclesCounter = 0;          // Брой цикли в пермутация
double averageCyclesLenght = 0; // Средна дължина на циклите
int cyclesWithLenghtK = 0;      // Брой цикли с дължина K

// Инициализира масив с числата от 0 до size-1
void init(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

// Извежда масив в конзолата
void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}

// Премахва елемент от масив по индекс
void removeByIndex(int *array, int *size, int index)
{
    for (int i = index; i < *size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    (*size)--;
}

// Генерира случайна пермутация с броене на циклите
void generateRandomPermutation(int *arr, int n)
{
    cyclesCounter = 1; 
    int result[n + 1];
    for (int i = 0; i <= n; i++)
    {
        result[i] = 0;
    }

    int notUsed[n + 1]; 
    int sizeOfNotUsed = n + 1;

    init(notUsed, sizeOfNotUsed); 

    int start = 1;
    int cur = start;

    while (sizeOfNotUsed > 2)
    { 
        int nextIndex = (rand() % (sizeOfNotUsed - 1)) + 1; 
        int next = notUsed[nextIndex];

        result[cur] = next;

        removeByIndex(notUsed, &sizeOfNotUsed, nextIndex);

        cur = next;

        if (cur == start)
        {
            cyclesCounter++;
            if (sizeOfNotUsed <= 1)
                break;         
            start = notUsed[1];
            cur = start;
        }
    }

    if (sizeOfNotUsed == 2)
    {
        result[cur] = notUsed[1];
    }

    for (int i = 1; i <= n; i++)
    {
        arr[i - 1] = result[i];
    }

    averageCyclesLenght = n / cyclesCounter;
}

// Генерира случайна пермутация и брои циклите с дължина K
void generateRandomPermutationCountK(int *arr, int n, int k)
{
    int curCycleLenght = 1;
    cyclesCounter = 1; 
    int result[n + 1];
    for (int i = 0; i <= n; i++)
    {
        result[i] = 0;
    }

    int notUsed[n + 1]; 
    int sizeOfNotUsed = n + 1;

    init(notUsed, sizeOfNotUsed); 

    int start = 1;
    int cur = start;

    while (sizeOfNotUsed > 2)
    { 
        int nextIndex = (rand() % (sizeOfNotUsed - 1)) + 1; 
        int next = notUsed[nextIndex];

        result[cur] = next;

        removeByIndex(notUsed, &sizeOfNotUsed, nextIndex);

        cur = next;

        if (cur == start)
        {
            cyclesCounter++;
            if(curCycleLenght == k)
            {
                cyclesWithLenghtK++;
                curCycleLenght = 1;
            }

            if (sizeOfNotUsed <= 1)
                break;         
            start = notUsed[1];
            cur = start;
        }
        else
        {
            curCycleLenght++;
        }
    }

    if (sizeOfNotUsed == 2)
    {
        result[cur] = notUsed[1];
    }

    for (int i = 1; i <= n; i++)
    {
        arr[i - 1] = result[i];
    }
}

// Намира ранга на дадена пермутация
int rankOfPermutation(int* arr, int len)
{
   int sum = 1;
   int factorial = 1;
   for (int k = len - 2; k >= 0; --k)
   {
      int cnt = 0;
      for (int i = k + 1; i < len; ++i)
         if (arr[i] < arr[k])
            ++cnt;
      factorial *= (len - k - 1);
      sum += (cnt * factorial);
   }
   return sum;
}

// Генерира пермутация по даден ранг
void permutationByRank(int* arr, int len, int rank)
{
    if (arr == NULL || len <= 0)
        return;

    if (rank < 1)
    {
        arr[0] = 0; 
        return;
    }

    int* factorials = (int*)malloc(len * sizeof(int));
    if (factorials == NULL)
    {
        arr[0] = 0; 
        return;
    }

    int f = 1;
    for (int k = 1, i = len - 2; k < len; ++k, --i)
    {
        f *= k;
        factorials[i] = f;
    }
    f *= len;

    if (rank > f)
    {
        arr[0] = 0; 
        free(factorials);
        return;
    }

    --rank;

    int* elements = (int*)malloc(len * sizeof(int));
    for (int i = 0; i < len; ++i)
    {
        elements[i] = 1; 
    }

    for (int k = 0; k < len; ++k)
    {
        f = factorials[k];
        int q = rank / f;
        rank -= (q * f);
        ++q;

        int cnt = 0, i = -1;
        while (cnt < q)
        {
            ++i;
            if (elements[i]) ++cnt;
        }

        arr[k] = i + 1;
        elements[i] = 0;
    }

    free(elements);
    free(factorials);
}

// Тества средния брой цикли в пермутация
void averageNumOfCyclesInPermutation(int n, int numOFIterations)
{
    int array[n];
    int cyclesCount[n+1]; 

    for(int i = 1; i < n; i++)
    {
        cyclesCount[i] = 0;
    }

    double sum = 0;

    for(int i = 0; i < numOfIteration; i++)
    {
        generateRandomPermutation(array, n);
        cyclesCount[cyclesCounter]++;
    }

    for(int i = 0; i < n+1; i++)
    {
        sum += cyclesCount[i] * i; 
    }

    double result = sum / numOfIteration; 

    printf("Средният брой на циклите в пермутация с дължина %d е %f\n", n, result );
}

// Тества теоретичните и експерименталните стойности на E[d_r]
void testExpectedNumOfCyclesWithLengthR(int n, int numIterations)
{
    printf("Тестваме пермутации от %d елемента, %d опита на пермутация.\n", n, numIterations);
    printf("r\tЕкспериментално E[d_r]\tТеоретично 1/r\tГрешка\n");

    for (int r = 1; r <= n; r++)
    {
        int totalCyclesWithLengthR = 0;

        for (int i = 0; i < numIterations; i++)
        {
            cyclesWithLenghtK = 0;
            int array[n];
            generateRandomPermutationCountK(array, n, r);
            totalCyclesWithLengthR += cyclesWithLenghtK;
        }

        double experimentalMean = (double)totalCyclesWithLengthR / numIterations;
        double theoreticalMean = 1.0 / r;
        double error = fabs(experimentalMean - theoreticalMean);

        printf("%d\t%.5f\t\t\t%.5f\t%.5f\n", r, experimentalMean, theoreticalMean, error);
    }
}

int main()
{
    srand(time(NULL));

    int n = 16;
    const int numIterations = 1000000;

    testExpectedNumOfCyclesWithLengthR(n, numIterations);

    return 0;
}
