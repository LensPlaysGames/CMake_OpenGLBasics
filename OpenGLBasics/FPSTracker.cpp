#include "FPSTracker.h"

std::array<double, FPSTracker::maxDeltaTimes> FPSTracker::deltaTimes;
unsigned short int FPSTracker::frameCounter = 0;
double FPSTracker::deltaTimesSum = 0.0;
unsigned short int FPSTracker::FPS = 0;
double FPSTracker::frameTimeInMilliseconds = 0.0;

void FPSTracker::AddFrame(double deltaTime) {
    frameCounter++;
    // Remove value being overwritten.
    deltaTimesSum -= deltaTimes[frameCounter];
    deltaTimes[frameCounter] = deltaTime;
    // Add current frame time to sum of times
    deltaTimesSum += deltaTimes[frameCounter];
    // Start overwriting beginning of array when reaching max delta times amount.
    if (frameCounter + 1 == maxDeltaTimes) { frameCounter = 0; }
}

void FPSTracker::Update()
{
    // Calculate average frame time + fps and 
    frameTimeInMilliseconds = (deltaTimesSum / maxDeltaTimes) * 1000;
    FPS = (int)(maxDeltaTimes / deltaTimesSum);
}
