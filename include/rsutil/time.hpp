#ifndef RSUTIL_TIME_HPP
#define RSUTIL_TIME_HPP

#include <rsutil/fundamental.hpp>
#include <rsutil/assert.hpp>

#include <chrono>
#include <thread>

namespace rsutil
{
    class timer
    {
    public:
        explicit timer();

        ~timer() = default;

        timer(const timer &);

        timer &operator=(const timer &);

        timer(const timer &&) = delete;

        timer &&operator=(const timer &&) = delete;

        void reset();

        void pause();

        void resume();

        [[nodiscard]] high_precision_float elapsed_seconds() const;

        [[nodiscard]] high_precision_float elaped_milliseconds() const;

        [[nodiscard]] uint64 elapsed_microseconds() const;

        [[nodiscard]] uint64 elapsed_nanoseconds() const;

    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> _start;

        std::chrono::time_point<std::chrono::high_resolution_clock> _pause_time;
        std::chrono::duration<high_precision_float, std::nano>      _pause_duration{ 0 };
        bool                                                        _is_paused{ false };
        std::thread::id                                             _owner;
    };

    inline
    high_precision_float
    timer::elapsed_seconds() const
    {
        return (static_cast<high_precision_float>(elapsed_microseconds()) / 1'000'000.0);
    }

    inline
    high_precision_float
    timer::elaped_milliseconds() const
    {
        return (static_cast<high_precision_float>(elapsed_microseconds()) / 1'000.0);
    }

    inline
    uint64
    timer::elapsed_microseconds() const
    {
        return (elapsed_nanoseconds() / 1000);
    }

    template <typename Func>
    void scheduleInvocation(Func &&callable, high_precision_float delayMs);
}

#endif