#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void init(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
}

void removeByIndex(int *array, int *size, int index)
{
    for (int i = index; i < *size - 1; i++)
    {
        array[i] = array[i + 1];
    }
    (*size)--;
}

int cyclesCount = 0;

void generateRandomPermutation(int *arr, int n)
{
    cyclesCount = 1; 
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
            cyclesCount++;
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
}

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
    int k, i;
    factorials[len - 1] = f;

    for (k = 1, i = len - 2; k < len; ++k, --i)
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
    if (elements == NULL)
    {
        arr[0] = 0; 
        free(factorials);
        return;
    }

    for (i = 0; i < len; ++i)
    {
        elements[i] = 1; 
    }

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
        elements[i] = 0;
    }

    free(elements);
    free(factorials);
}

void countPerm()
{
    int n = 4; 
    int array[n];

    int count[25];
    for(int i = 1; i < 25; i++)
    {
        count[i] = 0;
    }

    for (int i = 0; i < 10000000; i++)
    {
        generateRandomPermutation(array, n);

        count[rankOfPermutation(array,n)]++;
    }

    for(int i = 1; i < 25; i++)
    {
        int tempArr[n];
        permutationByRank(tempArr,n,i);
        printArray(tempArr,n);
        printf("is generated: ");
        printf("%d times\n", count[i]);
    }

}


int main()
{
    srand(time(NULL));

    // int n = 4; 
    // int array[n];

    countPerm();

    // for (int i = 0; i < 100; i++)
    // {

    //     generateRandomPermutation(array, n);
    //     printf("num of cycles: %d \n", cyclesCount);
        // printArray(array,n);
    // }

    // int res = rankOfPermutation(array,n);

    // printf("%d \n", res);

    return 0;
}
