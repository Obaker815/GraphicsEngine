#include <chrono>

class Stopwatch
{
    public:
        Stopwatch()
        {
            reset();
        }

        void reset()
        {
            startTime = std::chrono::high_resolution_clock::now();
        }

        float elapsed() const
        {
            auto now = std::chrono::high_resolution_clock::now();
            std::chrono::duration<float> diff = now - startTime;
            return diff.count();
        }
    private:
        std::chrono::high_resolution_clock::time_point startTime;
};
