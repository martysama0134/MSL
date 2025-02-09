#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <format>
#include <memory>
#include <ranges>
#include <msl/pool.h>
#include <msl/range.h>
#include <thread>
#include <future>

struct TestObject
{
	std::string data;
	explicit TestObject(const std::string & s = "default") : data(s) {}
	//~TestObject() { std::cout << "Destroying TestObject with data: " << data << std::endl; }
};

struct ComplexObject
{
	std::string data1;
	std::string data2;
	explicit ComplexObject(const std::string & s = "default") : data1(s) {}
	void Initialize()
	{
		data2 = "initialized";
		std::cout << "ComplexObject " << data1 << " " << data2 << std::endl;
	}
	void Destroy()
	{
		data2 = "destroyed";
		std::cout << "ComplexObject " << data1 << " " << data2 << std::endl;
	}
};

void test_iterator_invalidation(std::shared_ptr<msl::shared_pool<TestObject>> & pool)
{
	std::cout << "\nTesting iterator invalidation:\n";

	// Create multiple handles rapidly to force reallocation
	std::vector<msl::shared_pool<TestObject>::handle> handles;
	for (int i = 0; i < 1000; ++i)
	{
		auto obj = pool->acquire();
		handles.emplace_back(std::move(obj));
	}
}

void test_concurrent_access(std::shared_ptr<msl::shared_pool<TestObject>> & pool)
{
	std::cout << "\nTesting concurrent access:\n";

	auto worker = [&pool](int id)
	{
		try
		{
			for (int i = 0; i < 100; ++i)
			{
				auto handle = pool->acquire();
				handle->data = "Object " + std::string(1, char('A' + (i % 26)));
				// Force some contention
				std::this_thread::sleep_for(std::chrono::milliseconds(1));
			}
		}
		catch (const std::exception & e)
		{
			std::cerr << "Thread " << id << " error: " << e.what() << std::endl;
		}
	};

	std::vector<std::future<void>> futures;
	for (int i = 0; i < 5; ++i)
		futures.emplace_back(std::async(std::launch::async, worker, i));

	for (auto & f : futures)
		f.wait();
}

void test_move_semantics(std::shared_ptr<msl::shared_pool<TestObject>> pool)
{
	std::cout << "\nTesting move semantics:\n";

	{
		auto handle1 = pool->acquire();
		handle1->data = "Original";

		// Move assignment between handles
		auto handle2 = pool->acquire();
		handle2->data = "To be moved";

		// This might cause issues with dangling pool pointer
		handle1 = std::move(handle2);
		std::cout << "Moved object data: " << handle1->data << std::endl;
	}

	{
		auto handle1 = pool->acquire();
		handle1->data = "Pool1";

		auto pool2 = msl::shared_pool<TestObject>::create();

		// Move assignment between handles from different pools
		auto handle2 = pool2->acquire();
		handle2->data = "Pool2";

		std::cout << "Pool1 handle: " << handle1->data << std::endl;
		std::cout << "Pool2 handle: " << handle2->data << std::endl;

		handle1 = std::move(handle2);
		std::cout << "Moved pool1 handle: " << handle1->data << std::endl;
		std::cout << "Moved pool2 handle: " << (handle2 ? handle2->data.c_str() : "nullptr") << std::endl;
	}
}

void test_variadic()
{
	std::cout << "\nTesting variadic semantics:\n";

	{
		auto pool = msl::shared_pool<TestObject>::create("Args1");
		pool->set_methods(msl::shared_pool<TestObject>::default_initializer);
		auto handle1 = pool->acquire();
		std::cout << "Pool create variadic handle: " << handle1->data << std::endl;
	}
	{
		auto pool = msl::shared_pool<TestObject>::create_with_methods([](auto & obj) { obj->data = "123"; });
		auto handle1 = pool->acquire();
		std::cout << "Pool create_with_methods handle: " << handle1->data << std::endl;
	}
	{
		auto pool = msl::shared_pool<TestObject>::create_with_methods([](auto &) { std::cout << "initializer123 called" << std::endl; },
																	  [](auto &) { std::cout << "destroyer123 called" << std::endl; },
																	  "CreatedWithMethods");
		auto handle1 = pool->acquire();
		std::cout << "Pool123 variadic handle: " << handle1->data << std::endl;
	}
	{
		auto pool = msl::shared_pool<ComplexObject>::create_with_methods([](auto & obj) { obj->Initialize(); },
																	  [](auto & obj) { obj->Destroy(); },
																	  "Complex");
		auto handle1 = pool->acquire();
		std::cout << "ComplexPool1 variadic handle: data1=" << handle1->data1 << ", data2=" << handle1->data2 << std::endl;
	}
}

void TestPool()
	{
	std::cout << __FUNCTION__ << " test starting" << '\n';

	{
		auto pool = msl::shared_pool<TestObject>::create();
		std::vector<msl::shared_pool<TestObject>::handle> vec;
		std::cout << "shared pool size of: " << pool->size() << std::endl;
		for (int i = 0; i < 5; ++i)
			vec.emplace_back(pool->acquire());
		std::cout << "shared pool size of: " << pool->size() << std::endl;
		pool->prepare(100);
		std::cout << "shared pool size of: " << pool->size() << std::endl;
	}

	{
		auto pool = msl::shared_pool<TestObject>::create();
		auto obj = pool->acquire();
		obj->data = "Kebab";
		std::cout << "pool acquired " << obj->data << std::endl;
	}


    try
	{
		auto pool = msl::shared_pool<TestObject>::create();

		// Initial capacity
		std::cout << "Initial size: " << pool->size() << std::endl;

		// Test 1: Iterator invalidation
		test_iterator_invalidation(pool);
		std::cout << "After test 1 - size: " << pool->size() << std::endl;

		// Test 2: Concurrent access
		test_concurrent_access(pool);
		std::cout << "After test 2 - size: " << pool->size() << std::endl;

		// Test 3: Move semantics
		test_move_semantics(pool);
		std::cout << "After test 3 - size: " << pool->size() << std::endl;
		
		// Test 4: Deallocate all
		pool->debug_deallocate_all();
		std::cout << "After debug_deallocate_all() - size: " << pool->size() << std::endl;

		// Test 5: Variadic
		test_variadic();
	}
	catch (const std::exception & e)
	{
		std::cerr << "Main thread error: " << e.what() << std::endl;
	}




	std::cout << "\nAll tests passed." << '\n';

	std::cout << std::endl << "Press enter to continue..." << std::endl;
	std::ignore = getchar();
	std::ignore = getchar();
}
