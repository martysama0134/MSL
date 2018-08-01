#pragma once

#include <cstdio>

namespace msl
{
class file_ptr
{
	std::FILE * m_ptr{};

public:
#ifdef _WIN32
	file_ptr(const char * filename, const char * mode = "r") { fopen_s(&m_ptr, filename, mode); }
#else
	file_ptr(const char * filename, const char * mode = "r") { m_ptr = std::fopen(filename, mode); }
#endif
	file_ptr(std::FILE * ptr) { m_ptr = ptr; }
	~file_ptr() { std::fclose(m_ptr); }
	std::FILE * operator*() { return m_ptr; }

	bool is_open() { return m_ptr; }
	std::FILE * get() { return m_ptr; }
};
} // namespace msl
