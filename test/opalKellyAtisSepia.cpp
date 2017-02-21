#include "catch.hpp"

#include "../source/opalKellyAtisSepia.hpp"

#include <mutex>
#include <iostream>

TEST_CASE("Event counter", "[opalKellyAtisSepia]") {
    std::exception_ptr sharedException;
    std::mutex lock;
    lock.lock();
    try {
        auto count = static_cast<std::size_t>(0);
        auto timestampThreshold = static_cast<uint64_t>(0);
        auto camera = opalKellyAtisSepia::make_camera(
            [&](sepia::Event event) -> void {
                if (event.timestamp  > timestampThreshold) {
                    std::cout << count << " events / second" << std::endl;
                    timestampThreshold = event.timestamp + 1e6;
                    count = 0;
                }
                ++count;
            },
            [&](std::exception_ptr exception) {
                sharedException = exception;
                lock.unlock();
            }
        );
        lock.lock();
        lock.unlock();
        if (sharedException) {
            std::rethrow_exception(sharedException);
        }
    } catch (const std::runtime_error& exception) {
        std::cout << "\e[31m" << exception.what() << "\e[0m" << std::endl;
    }
}
