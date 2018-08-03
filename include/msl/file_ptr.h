#pragma once

#include <cstdio>
#include <string>
#include <vector>

namespace msl
{
class file_ptr
{
	std::FILE * m_ptr{nullptr};

public:
	file_ptr(const char * filename, const char * mode = "r") { open(filename, mode); }
	file_ptr(std::FILE * ptr) { m_ptr = ptr; }
	~file_ptr() { std::fclose(m_ptr); }

	std::FILE *& operator*() { return m_ptr; }
	bool operator!() { return is_open(); }
	std::FILE *& operator->() { return m_ptr; }

	/// \brief get the file ptr
	std::FILE * get() { return m_ptr; }

	/// \brief close the file ptr and reset it
	void open(const char * filename, const char * mode = "r")
	{
#ifdef _WIN32
		fopen_s(&m_ptr, filename, mode);
#else
		m_ptr = std::fopen(filename, mode);
#endif
	}
	/// \brief alias of reset()
	void close() { reset(); }

	/// \brief swap two file_ptr
	void swap(file_ptr & fp) { std::swap(m_ptr, *fp); }

	/// \brief reset and reopen new file
	void reset(const char * filename, const char * mode = "r")
	{
		reset();
		open(filename, mode);
	}

	/// \brief reset and reassign new ownership
	void reset(std::FILE * ptr)
	{
		reset();
		m_ptr = ptr;
	}

	/// \brief close the file and reset the ptr
	void reset()
	{
		if (m_ptr)
		{
			std::fclose(m_ptr);
			m_ptr = nullptr;
		}
	}

	/// \brief release the file ptr
	FILE * release()
	{
		auto ptr = m_ptr;
		m_ptr = nullptr;
		return ptr;
	}

	/// \brief return whether or not the file is open
	bool is_open() const { return m_ptr; }

	/// \brief return the file size whether from the current position or from beginning
	std::size_t size(bool from_current = false) const
	{
		auto cur = std::ftell(m_ptr); // get current pos
		std::fseek(m_ptr, 0, SEEK_END); // go to EOF
		std::size_t filesize = std::ftell(m_ptr); // get filesize
		std::fseek(m_ptr, cur, SEEK_SET); // go to current pos
		return (from_current) ? filesize - cur : filesize;
	}
	/// \brief return the file size from the current position; alias of size(true)
	std::size_t remain_size() const { return size(true); }

	/// \brief read the file from the current position as byte stream
	std::vector<char> read(std::size_t n = 0)
	{
		if (n == 0) // 0 implies reading the whole remaining file
			n = this->remain_size();
		std::vector<char> buf(n);
		std::fread(buf.data(), 1, buf.size(), m_ptr);
		return buf;
	}

	/// \brief read the file from the current position as null-terminated string
	std::string string_read(std::size_t n = 0)
	{
		auto vec = this->read(n);
		if (!vec.empty() && vec[vec.size() - 1] != '\0') // append EOS at the end of vector
			vec.emplace_back('\0');
		return std::string(vec.begin(), vec.end()); // convert vector to string
	}
};
} // namespace msl
