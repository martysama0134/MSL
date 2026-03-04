#include <iostream>
#include <msl/pool.h>

struct worker
{
    int value = 0;
};

int main()
{
    auto pool = msl::shared_pool<worker>::create();
    auto handle = pool->acquire();
    handle->value = 123;
    std::cout << "value=" << handle->value << '\n';
    return 0;
}
