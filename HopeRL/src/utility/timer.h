#pragma once

#include <chrono>
#include <iostream>
#include <string>

using timestamp = std::chrono::high_resolution_clock::time_point;
using timespan = std::chrono::duration<double, std::milli>;

inline double InMilliseconds(timespan t)
{
  return std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
}

inline timestamp GetTimestamp()
{
  return std::chrono::high_resolution_clock::now();
}

class Timer {
  std::string Name;
  timestamp StartTime;
  timestamp EndTime;

public:
  Timer(std::string name) : Name(name) {}

  inline void Start()
  {
    StartTime = GetTimestamp();
  }

  inline double Stop()
  {
    EndTime = GetTimestamp();
    return InMilliseconds(EndTime - StartTime);
  }

  inline double CurrentElapsedMS()
  {
    timestamp now = GetTimestamp();
    return InMilliseconds(now - StartTime);
  }

  inline void ReportElapsedTime()
  {
    std::cout << Name << " elapsed in " << InMilliseconds(EndTime - StartTime) << " ms." << std::endl;
  }
};