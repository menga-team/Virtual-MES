#ifndef VMES_MESTIME_H
#define VMES_MESTIME_H

#include <chrono>

namespace mestime {

    class Moment {
    public:
        explicit Moment(std::chrono::time_point<std::chrono::high_resolution_clock> point) {
            t = point;
        };
        std::chrono::time_point<std::chrono::high_resolution_clock> t;
    };

    class Duration {
    private:
        std::chrono::nanoseconds d;

    public:
        Duration(Moment a, Moment b) {
            set(a, b);
        };
        Duration() {
            d = std::chrono::nanoseconds(0);
        }
        void set(Moment a, Moment b) {
            d = std::chrono::duration_cast<std::chrono::nanoseconds>(b.t - a.t);
        }
        uint64_t nanoseconds() {
            return d.count();
        };
        uint64_t microseconds() {
            return std::chrono::duration_cast<std::chrono::microseconds>(d).count();
        };
        uint64_t milliseconds() {
            return std::chrono::duration_cast<std::chrono::milliseconds>(d).count();
        };
        uint64_t seconds() {
            return std::chrono::duration_cast<std::chrono::seconds>(d).count();
        };

    };

    class Clock {
    public:
        static Moment now() {
            return Moment(std::chrono::high_resolution_clock::now());
        };
    };
}

#endif //VMES_MESTIME_H
