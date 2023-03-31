#include <chrono>
#include <deque>

class FPSCounter {
public:
    FPSCounter();
    int tick();

private:
    std::deque<std::chrono::steady_clock::time_point> last_second_frames;
};
