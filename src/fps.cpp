#include <chrono>
#include <deque>

#include "fps.hpp"

int FPSCounter::tick() {
  auto now = std::chrono::steady_clock::now();
  auto a_second_ago = now - std::chrono::seconds(1);

  while (!last_second_frames.empty() && last_second_frames.front() < a_second_ago) {
    last_second_frames.pop_front();
  }

  last_second_frames.push_back(now);
  return last_second_frames.size();
}

FPSCounter::FPSCounter() : last_second_frames(128) {}
