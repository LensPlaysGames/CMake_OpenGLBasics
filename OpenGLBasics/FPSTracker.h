#ifndef FPS_TRACKER_H
#define FPS_TRACKER_H

#include <array>

class FPSTracker
{
/* The Idea:
*   Keep an array of a certain amount of previous frames' delta times, and calculate average FPS and frame time based off of that data.
*/
public:
    static const unsigned int maxDeltaTimes = 255;
    static std::array<double, maxDeltaTimes> deltaTimes;
    static unsigned short int frameCounter;
    // Sum of all delta times in array (for easy average)
    static double deltaTimesSum;
    // Average frames per second (FPS = maxDeltaTimes / deltaTimesSum)
    static unsigned short int FPS;
    // Average time it takes per frame in milliseconds (ms = (deltaTimesSum / maxDeltaTimes) * 1000)
    static double frameTimeInMilliseconds;

    // Add frame delta time to the deltaTimes array
    static void AddFrame(double deltaTime);
    
    // Calculate FPS and frame time in milliseconds, and set lastTimeFPSUpdated to time
    static void Update();
};

#endif