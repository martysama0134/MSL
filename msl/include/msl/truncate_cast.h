#pragma once

#include <exception>
namespace msl
{
struct truncate_error : public std::exception
{
};
} // namespace msl
