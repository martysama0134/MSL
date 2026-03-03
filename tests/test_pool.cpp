#include "test_common.h"

#include <atomic>
#include <memory>
#include <thread>
#include <vector>

#include <msl/pool.h>

namespace
{
struct pool_object
{
    int value{0};
};

void test_get_matches_operator_arrow()
{
    auto pool = msl::shared_pool<pool_object>::create();
    auto handle = pool->acquire();

    MSL_EXPECT(handle.get() != nullptr);
    MSL_EXPECT(handle.get() == handle.operator->());
}

void test_move_constructor_preserves_destroyer()
{
    std::atomic<int> destroy_calls{0};

    {
        auto pool = msl::shared_pool<pool_object>::create_with_methods(
            msl::shared_pool<pool_object>::default_initializer,
            [&destroy_calls](auto & obj) {
                obj->value = -1;
                ++destroy_calls;
            }
        );

        auto handle = pool->acquire();
        handle->value = 42;

        auto moved_handle(std::move(handle));
        MSL_EXPECT(!handle);
        MSL_EXPECT(static_cast<bool>(moved_handle));

        pool.reset();
    }

    MSL_EXPECT(destroy_calls.load() == 1);
}

void test_reserve_and_prepare_capacity()
{
    auto pool = msl::shared_pool<pool_object>::create();

    pool->reserve(16);
    MSL_EXPECT(pool->capacity() >= 16);

    pool->prepare(8);
    MSL_EXPECT(pool->size() >= 8);
    MSL_EXPECT(pool->available() >= 8);
    MSL_EXPECT(pool->capacity() >= pool->size());
}

void test_multithreaded_acquire_release_smoke()
{
    auto pool = msl::shared_pool<pool_object>::create();
    std::atomic<int> acquire_count{0};
    std::atomic<bool> failed{false};

    constexpr int thread_count = 4;
    constexpr int per_thread = 250;

    std::vector<std::thread> threads;
    threads.reserve(thread_count);

    for (int t = 0; t < thread_count; ++t)
    {
        threads.emplace_back([&, t]() {
            try
            {
                for (int i = 0; i < per_thread; ++i)
                {
                    auto handle = pool->acquire();
                    handle->value = t + i;
                    ++acquire_count;
                }
            }
            catch (...)
            {
                failed = true;
            }
        });
    }

    for (auto & worker : threads)
        worker.join();

    MSL_EXPECT(!failed.load());
    MSL_EXPECT(acquire_count.load() == thread_count * per_thread);
    MSL_EXPECT(pool->size() > 0);
}
} // namespace

void run_pool_tests()
{
    test_get_matches_operator_arrow();
    test_move_constructor_preserves_destroyer();
    test_reserve_and_prepare_capacity();
    test_multithreaded_acquire_release_smoke();
}
