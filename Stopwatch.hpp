#pragma once

#include <chrono>
#include <iostream>
#include <string>

class Stopwatch {
  public:
    Stopwatch(const std::string &text = "Elapsed time:", int precision = 2)
        : text(text), precision(precision) {}

    void start() { start_time = std::chrono::high_resolution_clock::now(); }

    void stop() {
        end_time = std::chrono::high_resolution_clock::now();
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(end_time - start_time);
        elapsed_time = ns.count() / 1'000'000'000.0;
        std::cout << text << " " << std::fixed << std::setprecision(precision) << elapsed_time
                  << "s\n";
    }

    double elapsed() const { return elapsed_time; }

    // RAII
    class ScopedStopwatch {
      public:
        ScopedStopwatch(Stopwatch &sw) : stopwatch(sw) { stopwatch.start(); }

        ~ScopedStopwatch() { stopwatch.stop(); }

      private:
        Stopwatch &stopwatch;
    };

    ScopedStopwatch measure() { return ScopedStopwatch(*this); }

  private:
    std::string text;
    int precision;
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time, end_time;
    double elapsed_time;
};
