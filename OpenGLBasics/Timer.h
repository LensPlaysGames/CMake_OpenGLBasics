#ifndef TIMER_H
#define TIMER_H

class Timer {
public:
    static double time;
    static double previousTime;
    static double deltaTime;

    static void Update(double newTime) {
        time = newTime;
        deltaTime = time - previousTime;
    }
};

#endif