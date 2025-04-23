#pragma once

typedef struct PermutInfo {
    int cycleCounter;
    double averageCycleLength;
    int *cycleLenCounters;
} PermutInfo;