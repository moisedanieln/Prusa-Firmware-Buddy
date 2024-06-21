#pragma once

#include <type_traits>
#include <array>
#include <cstdint>
#include <stddef.h>

namespace freertos {

// C++ wrapper for FreeRTOS counting semaphore.
class CountingSemaphore {
public:
    // We use erased storage in order to not pollute the scope with FreeRTOS internals.
    // The actual size and alignment are statically asserted in implementation file.
#ifdef UNITTESTS
    static constexpr size_t semaphore_storage_size = 168;
    static constexpr size_t semaphore_storage_align = 8;
#else
    static constexpr size_t semaphore_storage_size = 80;
    static constexpr size_t semaphore_storage_align = 4;
#endif
    using Storage = std::array<uint8_t, semaphore_storage_size>;

private:
    alignas(semaphore_storage_align) Storage semaphore_storage;

public:
    CountingSemaphore(size_t max_count, size_t initial_count);
    ~CountingSemaphore();
    CountingSemaphore(const CountingSemaphore &) = delete;
    CountingSemaphore &operator=(const CountingSemaphore &) = delete;

    /// Increments the internal counter and unblocks one acquirer
    /// Raises a bsod if you try to call this when the semaphore is not acquired
    void release();

    /// Decrements the internal counter or blocks until it can.
    void acquire();

    /// Tries to decrement the internal counter without blocking.
    bool try_acquire() { return try_acquire_for(0); }

    /// Tries to decrement the internal counter, blocking for up to a duration milliseconds.
    bool try_acquire_for(size_t duration_ms);
};

} // namespace freertos