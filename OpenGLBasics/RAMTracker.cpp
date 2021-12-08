#include "RAMTracker.h"

#include "ProgramMemory.h"

long long RAMTracker::CurrentRAMUsage = 0;
long long RAMTracker::PeakRAMUsage = 0;
std::array<size_t, RAMTracker::maxRAMUsageValues> RAMTracker::RAMValues;
long long RAMTracker::RAMValuesSum = 0;
unsigned short int RAMTracker::RAMValueIndexCounter = 0;

void RAMTracker::Update() {
    CurrentRAMUsage = getCurrentRSS();
    PeakRAMUsage = getPeakRSS();
}

void RAMTracker::AddCurrentRAMValue() {
    RAMValueIndexCounter++;
    RAMValuesSum -= RAMValues[RAMValueIndexCounter];
    RAMValues[RAMValueIndexCounter] = CurrentRAMUsage;
    RAMValuesSum += RAMValues[RAMValueIndexCounter];
    if (RAMValueIndexCounter + 1 == maxRAMUsageValues) RAMValueIndexCounter = 0;
}