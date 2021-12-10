#ifndef RAM_TRACKER_H
#define RAM_TRACKER_H
#include <array>

class RAMTracker {
public:
    static const unsigned short int maxRAMUsageValues = 25555;
    static std::array<size_t, maxRAMUsageValues> RAMValues;
    static long long CurrentRAMUsage;
    static long long PeakRAMUsage;
    static long long RAMValuesSum;
    static unsigned short int RAMValueIndexCounter;

    static void Update();

    static void AddCurrentRAMValue();

    static size_t GetMegabytesFromBytes(size_t bytes) {
        return (bytes / 1000 / 1000);
    }
};

#endif