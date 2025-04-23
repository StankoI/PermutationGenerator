#include "rankOfPermutation.h"

// Намира поредния номер на пермутация в лексикографската наредба.
int rankOfPermutation(int *arr, int len)
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
