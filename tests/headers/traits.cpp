#include <msl/traits.h>

int header_smoke_traits()
{
    return msl::traits::is_raw_v<int> ? 0 : 1;
}
