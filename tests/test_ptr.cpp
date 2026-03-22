#include "test_common.h"

#include <functional>
#include <memory>

#include <msl/ptr.h>

namespace
{
void test_scoped_shared_ptr_access()
{
    struct Obj { int value = 42; };
    auto sp = std::make_shared<Obj>();
    msl::scoped_shared_ptr<Obj> scoped(sp);

    MSL_EXPECT(static_cast<bool>(scoped));
    MSL_EXPECT(!(!scoped));
    MSL_EXPECT(scoped->value == 42);
}

void test_scoped_shared_ptr_null()
{
    msl::scoped_shared_ptr<int> scoped(std::shared_ptr<int>{});
    MSL_EXPECT(!scoped);
    MSL_EXPECT(!static_cast<bool>(scoped));
}

void test_no_owner_access()
{
    struct Obj { int value = 99; };
    Obj obj;
    msl::no_owner<Obj> ptr(&obj);

    MSL_EXPECT(static_cast<bool>(ptr));
    MSL_EXPECT(!(!ptr));
    MSL_EXPECT(ptr->value == 99);
}

void test_no_owner_null()
{
    msl::no_owner<int> ptr(nullptr);
    MSL_EXPECT(!ptr);
    MSL_EXPECT(!static_cast<bool>(ptr));
}

void test_no_owner_reassign()
{
    struct Obj { int val; };
    Obj a{1}, b{2};
    msl::no_owner<Obj> ptr(&a);
    MSL_EXPECT(ptr->val == 1);

    ptr = &b;
    MSL_EXPECT(ptr->val == 2);

    ptr = nullptr;
    MSL_EXPECT(!ptr);
}

void test_observer_ptr_basics()
{
    int val = 10;
    msl::observer_ptr<int> obs(&val);

    MSL_EXPECT(static_cast<bool>(obs));
    MSL_EXPECT(obs.get() == &val);
    MSL_EXPECT(*obs.get() == 10);
}

void test_observer_ptr_default_null()
{
    msl::observer_ptr<int> obs;
    MSL_EXPECT(!obs);
    MSL_EXPECT(obs.get() == nullptr);
}

void test_observer_ptr_reset_release()
{
    int a = 1, b = 2;
    msl::observer_ptr<int> obs(&a);
    MSL_EXPECT(obs.get() == &a);

    obs.reset(&b);
    MSL_EXPECT(obs.get() == &b);

    auto released = obs.release();
    MSL_EXPECT(released == &b);
    MSL_EXPECT(obs.get() == nullptr);

    obs.reset();
    MSL_EXPECT(!obs);
}

void test_observer_ptr_swap()
{
    int a = 1, b = 2;
    msl::observer_ptr<int> p1(&a);
    msl::observer_ptr<int> p2(&b);

    p1.swap(p2);
    MSL_EXPECT(p1.get() == &b);
    MSL_EXPECT(p2.get() == &a);
}

void test_observer_ptr_copy()
{
    int val = 5;
    msl::observer_ptr<int> p1(&val);
    msl::observer_ptr<int> p2 = p1;

    MSL_EXPECT(p1.get() == p2.get());
    MSL_EXPECT(p2.get() == &val);
}

void test_observer_ptr_make_observer()
{
    int val = 7;
    auto obs = msl::observer_ptr<int>::make_observer(&val);
    MSL_EXPECT(obs.get() == &val);
}

void test_observer_ptr_hash()
{
    int a = 1, b = 2;
    std::hash<msl::observer_ptr<int>> hasher;
    auto h1 = hasher(msl::observer_ptr<int>(&a));
    auto h2 = hasher(msl::observer_ptr<int>(&b));
    auto h1_again = hasher(msl::observer_ptr<int>(&a));

    MSL_EXPECT(h1 == h1_again);
    MSL_EXPECT(h1 != h2); // different pointers should (almost certainly) differ
}
} // namespace

void run_ptr_tests()
{
    test_scoped_shared_ptr_access();
    test_scoped_shared_ptr_null();
    test_no_owner_access();
    test_no_owner_null();
    test_no_owner_reassign();
    test_observer_ptr_basics();
    test_observer_ptr_default_null();
    test_observer_ptr_reset_release();
    test_observer_ptr_swap();
    test_observer_ptr_copy();
    test_observer_ptr_make_observer();
    test_observer_ptr_hash();
}
