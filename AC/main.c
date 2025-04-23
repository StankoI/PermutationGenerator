#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

#include "PermutationGenerator.h"
#include "PermutationByRank.h"
#include "RankOfPermutation.h"
#include "TestRandPerm.h"

int main()
{   
    printf("\n");

    printf("\n=====================================================\n\n");
    
    printf("Пет случайни пермутации на седем елемента:\n\n");
    
    testRandomPermGenWithLength7(5);
    
    printf("\n=====================================================\n\n");
    
    printf("Тест за равномерност на разпределението\n");
    printf("на случайна пермутация на четири елемента:\n\n");
    
    testUniformRandomPermGenWithLength4(10000);
    
    printf("\n=====================================================\n\n");
    
    printf("Тест за статистиката на циклите\n");
    printf("на пермутации на десет елемента:\n\n");
    
    testCyclesInPermutation(10, 10000);
    
    printf("\n=====================================================\n\n");
    
    return 0;
}
