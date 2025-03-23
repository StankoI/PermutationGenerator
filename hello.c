#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

// Инициализира масива с числата 0, 1, 2, ..., size - 1
void init(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        array[i] = i;
    }
}

// Принтира масива от позиция 1 до size-1
void printArray(int *array, int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", array[i]);
    }
    // printf("\n");
}

// Премахва елемент на даден индекс от масива
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

    int notUsed[n + 1]; // от 0 до n
    int sizeOfNotUsed = n + 1;

    init(notUsed, sizeOfNotUsed); // неИзползвани числа: 0,1,2,3,...,n

    int start = 1;
    int cur = start;

    while (sizeOfNotUsed > 2)
    { // Остават не по-малко от две числа (0 + поне още 1)
        // Избираме произволно число от неИзползваните, БЕЗ notUsed[0] (което е 0, за удобство)
        int nextIndex = (rand() % (sizeOfNotUsed - 1)) + 1; // от 1 до sizeOfNotUsed - 1
        int next = notUsed[nextIndex];

        // Свързваме cur към next
        result[cur] = next;

        // Премахваме next от списъка на неИзползвани
        removeByIndex(notUsed, &sizeOfNotUsed, nextIndex);

        cur = next;

        // Ако сме се върнали до start, започваме нов цикъл от най-малкия останал
        if (cur == start)
        {
            cyclesCount++;
            if (sizeOfNotUsed <= 1)
                break;          // няма останали числа
            start = notUsed[1]; // взимаме следващото най-малко неИзползвано
            cur = start;
        }
    }

    // Свързваме последното число към последното останало неИзползвано
    if (sizeOfNotUsed == 2)
    {
        result[cur] = notUsed[1];
    }

    // Копираме резултата в arr, като пропускаме елемента на индекс 0
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
    // Проверка за невалидни входни данни
    if (arr == NULL || len <= 0)
        return;

    if (rank < 1)
    {
        arr[0] = 0; // Индикатор за грешка
        return;
    }

    // Заеляме масиви за факториелите и елементите
    int* factorials = (int*)malloc(len * sizeof(int));
    if (factorials == NULL)
    {
        arr[0] = 0; // Грешка при заделяне
        return;
    }

    int f = 1;
    int k, i;
    factorials[len - 1] = f;

    // Изчисляваме факториелите
    for (k = 1, i = len - 2; k < len; ++k, --i)
    {
        f *= k;
        factorials[i] = f;
    }
    f *= len;

    // Проверка дали рангът е извън допустимите стойности
    if (rank > f)
    {
        arr[0] = 0; // Индикатор за грешка
        free(factorials);
        return;
    }

    --rank;

    // Масив за съхранение на наличните елементи
    int* elements = (int*)malloc(len * sizeof(int));
    if (elements == NULL)
    {
        arr[0] = 0; // Грешка при заделяне
        free(factorials);
        return;
    }

    for (i = 0; i < len; ++i)
    {
        elements[i] = 1; // Отбелязваме всички елементи като налични
    }

    // Генерираме пермутацията по ранг
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
        elements[i] = 0; // Отстраняваме елемента
    }

    // Освобождаваме заделената памет
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

        // printf("num of cycles: %d \n", cyclesCount);
        // printArray(array,n);
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
