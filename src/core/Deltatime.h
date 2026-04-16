#include "Stopwatch.h"

class Deltatime
{
public:
    static float elapsedTime()
    {
        return stopwatch.elapsed();
    }

    static void update()
    {
        float elapsed = elapsedTime();
        float deltatime = elapsed - lastRead;

        lastRead = elapsed;
        dt = deltatime;
    }

    static void reset()
    {
        stopwatch.reset();
    }

    static float dt;

private:
    static Stopwatch stopwatch;
    static float lastRead;
};

