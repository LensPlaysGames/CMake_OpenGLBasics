#include "FPSTimer.h"

std::array<double, FPSTimer::maxDeltaTimes> FPSTimer::deltaTimes;
unsigned short int FPSTimer::frameCounter = 0;
double FPSTimer::deltaTimesSum = 0.0;
unsigned short int FPSTimer::FPS = 0;
double FPSTimer::frameTimeInMilliseconds = 0.0;

void FPSTimer::AddFrame(double deltaTime) {
    frameCounter++;
    // Remove value being overwritten.
    deltaTimesSum -= deltaTimes[frameCounter];
    deltaTimes[frameCounter] = deltaTime;
    // Add current frame time to sum of times
    deltaTimesSum += deltaTimes[frameCounter];
    // Start overwriting beginning of array when reaching max delta times amount.
    if (frameCounter + 1 == maxDeltaTimes) { frameCounter = 0; }
}

void FPSTimer::UpdateValues(double time)
{
    // Calculate average frame time + fps and 
    frameTimeInMilliseconds = (deltaTimesSum / maxDeltaTimes) * 1000;
    FPS = (int)(maxDeltaTimes / deltaTimesSum);
}
