#include <rsutil/time.hpp>

rsutil::timer::timer()
    : _owner(std::this_thread::get_id())
{
    reset();
}

rsutil::timer::timer(const timer &other)
    : _start(other._start)
    , _pause_time(other._pause_time)
    , _pause_duration(other._pause_duration)
    , _is_paused(other._is_paused)
    , _owner(std::this_thread::get_id())
{}

rsutil::timer &
rsutil::timer::operator=(const timer &other)
{
    if (this != &other)
    {
        _start          = other._start;
        _pause_time     = other._pause_time;
        _pause_duration = other._pause_duration;
        _is_paused      = other._is_paused;
        _owner          = std::this_thread::get_id();
    }
    return *this;
}

void
rsutil::timer::reset()
{
    dynamic_assert(std::this_thread::get_id() == _owner,
                   "[ rsutil::timer::reset() ] Function invocation can only be done from owning thread");

    _start          = std::chrono::high_resolution_clock::now();
    _pause_duration = std::chrono::nanoseconds::zero();
    _pause_time     = _start;
    _is_paused      = false;
}

void
rsutil::timer::pause()
{
    dynamic_assert(std::this_thread::get_id() == _owner,
                   "[ rsutil::timer::pause() ] Function invocation can only be done by the owning thread");

    dynamic_assert(_is_paused == false, "[ rsutil::timer::pause() ] timer is already paused");

    _pause_time = std::chrono::high_resolution_clock::now();
    _is_paused  = true;
}

void
rsutil::timer::resume()
{
    dynamic_assert(std::this_thread::get_id() == _owner,
                   "[ rsutil::timer::resume() ] Function invocation can only be done by the owning thread");

    dynamic_assert(_is_paused == true, "[ rsutil::timer::resume() ] timer is not paused");

    const auto now = std::chrono::high_resolution_clock::now();
    _pause_duration += now - _pause_time;
    _is_paused = false;
}

rsutil::uint64
rsutil::timer::elapsed_nanoseconds() const
{
    const auto                                             now     = std::chrono::high_resolution_clock::now();
    std::chrono::duration<high_precision_float, std::nano> elapsed = now - _start;

    elapsed -= _pause_duration;

    if (_is_paused)
    {
        elapsed -= (now - _pause_time);
    }

    return static_cast<uint64>(elapsed.count());
}

void
rsutil::scheduleInvocation(std::function<void()> func, const high_precision_float delayMs)
{
    const std::chrono::duration<high_precision_float, std::milli> delay(delayMs);
    std::jthread(
        [callable = std::forward<std::function<void()>>(func), delay]
        {
            std::this_thread::sleep_for(delay);
            callable();
        })
        .detach();
}