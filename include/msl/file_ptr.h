#ifndef __MSL_FILE_PTR_H__
#define __MSL_FILE_PTR_H__
///////////////////////////////////////////////////////////////////////////////
//
// Copyright (c) 2018 martysama0134. All rights reserved.
//
// This code is licensed under the MIT License (MIT).
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
///////////////////////////////////////////////////////////////////////////////
#pragma once

#include <cstdio>
#include <cstring>
#include <cwchar>
#include <optional>
#include <string>
#include <string_view>
#include <vector>

//#define MSL_FILE_PTR_ENABLE_IMPLICIT_CONVERSION
//#define MSL_FILE_PTR_ENABLE_WIDE_STRING
#define MSL_FILE_PTR_ENABLE_STORE_FILENAME

namespace msl
{
class file_ptr
{
	std::FILE * m_ptr_{nullptr};
	#ifdef MSL_FILE_PTR_ENABLE_STORE_FILENAME
	std::string m_filename_;
	#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
	std::wstring m_wfilename_;
	#endif
	#endif

public:
	// constructor
	file_ptr() = default;
	explicit file_ptr(const std::string_view & filename, const std::string_view & mode = "r") { open(filename, mode); }
	#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
	explicit file_ptr(const std::wstring_view & filename, const std::wstring_view & mode = L"r") { open(filename, mode); }
	#endif
	explicit file_ptr(std::FILE * ptr) { m_ptr_ = ptr; }
	// move constructor
	file_ptr(file_ptr && fp) noexcept
	{
		reset(fp.m_ptr_);
		fp.m_ptr_ = nullptr;
	}
	file_ptr & operator=(file_ptr && fp) noexcept
	{
		reset(fp.m_ptr_);
		fp.m_ptr_ = nullptr;
		return *this;
	}
	// copy constructor
	file_ptr(const file_ptr &) = delete;
	file_ptr & operator=(const file_ptr &) = delete;
	// destructor
	~file_ptr() { reset(); }

	//! @brief *ptr
	std::FILE * operator*() const { return m_ptr_; }
	//! @brief if (!ptr)
	bool operator!() const { return !m_ptr_; }
	//! @brief ptr->elem
	std::FILE * operator->() const { return m_ptr_; }
	//! @brief if (ptr)
	explicit operator bool() const { return m_ptr_; }
	#ifdef MSL_FILE_PTR_ENABLE_IMPLICIT_CONVERSION
	//! @brief implicit std::FILE ptr conversion
	operator std::FILE *() const { return m_ptr_; }
	#endif

	//! @brief get the file ptr
	std::FILE * get() const { return m_ptr_; }

	//! @brief get the file ptr ref
	std::FILE *& get_ref() { return m_ptr_; }

	//! @brief get the file ptr pointer
	std::FILE ** get_ptr() { return &m_ptr_; }

	#ifdef MSL_FILE_PTR_ENABLE_STORE_FILENAME
	std::string filename() { return m_filename_; }
	#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
	std::wstring wfilename() { return m_wfilename_; }
	#endif
	#endif

	//! @brief close the file ptr and reset it
	void open(const std::string_view & filename, const std::string_view & mode = "r")
	{
		#ifdef _WIN32
		fopen_s(&m_ptr_, filename.data(), mode.data());
		#else
		m_ptr_ = std::fopen(filename.data(), mode.data());
		#endif
		#ifdef MSL_FILE_PTR_ENABLE_STORE_FILENAME
		m_filename_ = filename;
		#endif
	}

	#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
	inline static std::optional<std::string> w2s(const std::wstring_view & wcstr)
	{
		// on Windows, UTF-16 is internal Unicode encoding (UCS2 before WinXP)
		// on Linux, UCS4 is internal Unicode encoding
		// on BSD, UCS4 is internal Unicode encoding
		setlocale(LC_ALL,"en_US.UTF-8");
		const wchar_t * wcs = wcstr.data(); // implicit conversion for compatibility
		auto s = std::mbstate_t();

		#if _WIN32
		size_t target_char_count{};
		if (wcsrtombs_s(&target_char_count, nullptr, 0, &wcs, 0, &s) != 0)
			return {};
		#else
		auto target_char_count = std::wcsrtombs(nullptr, &wcs, 0, &s);
		if (target_char_count == static_cast<std::size_t>(-1))
			return {};
		target_char_count++; // +1 because std::string adds a null terminator which isn't part of size
		#endif

		auto str = std::string(target_char_count, '\0');
		#if _WIN32
		wcsrtombs_s(&target_char_count, str.data(), str.size(), &wcs, str.size(), &s);
		#else
		std::wcsrtombs(str.data(), &wcs, str.size(), &s);
		#endif
		return str;
	}

	//! @brief close the file ptr and reset it
	void open(const std::wstring_view & filename, const std::wstring_view & mode = L"r")
	{
		#ifdef _WIN32
		_wfopen_s(&m_ptr_, filename.data(), mode);
		#else
		auto fn2 = w2s(filename);
		auto mode2 = w2s(mode);
		if (!fn2 || !mode2)
		{
			printf("failed open conversion of %ws %ws\n", filename.data(), mode);
			return;
		}
		m_ptr_ = std::fopen(fn2->c_str(), mode2->c_str());
		#endif
		#ifdef MSL_FILE_PTR_ENABLE_STORE_FILENAME
		m_wfilename_ = filename;
		#endif
	}

	//! @brief reset and reopen new file
	void reset(const std::wstring_view & filename, const std::wstring_view & mode = L"r")
	{
		reset();
		open(filename, mode);
	}
	#endif

	//! @brief alias of reset()
	void close() { reset(); }

	//! @brief swap two file_ptr
	void swap(file_ptr & fp) noexcept { std::swap(m_ptr_, fp.m_ptr_); }

	//! @brief reset and reopen new file
	void reset(const std::string_view & filename, const std::string_view & mode = "r")
	{
		reset();
		open(filename, mode);
	}

	//! @brief reset and reassign new ownership
	void reset(std::FILE * ptr)
	{
		reset();
		m_ptr_ = ptr;
	}

	//! @brief close the file and reset the ptr
	void reset()
	{
		if (m_ptr_)
		{
			std::fclose(m_ptr_);
			m_ptr_ = nullptr;
			#ifdef MSL_FILE_PTR_ENABLE_STORE_FILENAME
			m_filename_ = {};
			#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
			m_wfilename_ = {};
			#endif
			#endif
		}
	}

	//! @brief release the file ptr
	std::FILE * release()
	{
		const auto ptr = m_ptr_;
		m_ptr_ = nullptr;
		return ptr;
	}

	//! @brief return whether or not the file is open
	bool is_open() const { return m_ptr_; }

	//! @brief return the file size whether from the current position or from beginning
	std::size_t size(bool from_current = false) const
	{
		const auto cur = tell(); // get current pos
		seek(0, SEEK_END); // go to EOF
		const auto filesize = tell(); // get filesize
		seek(cur, SEEK_SET); // go to current pos
		return from_current ? filesize - cur : filesize;
	}
	//! @brief return the file size from the current position; alias of size(true)
	std::size_t remain_size() const { return size(true); }

	//! @brief write into the file from stream
	template<class... Args>
	void write(const char* _Format, Args&&... args) const { std::fprintf(m_ptr_, _Format, std::forward<Args>(args)...); }
	//! @brief write into the file from byte vector
	std::size_t write(const std::vector<char> & vec) const { return std::fwrite(vec.data(), vec.size(), 1, m_ptr_); }
	//! @brief write into the file from c array
	std::size_t write(const void * buf, size_t size) const { return std::fwrite(buf, size, 1, m_ptr_); }

	//! @brief write into the file from string
	std::size_t string_write(const std::string_view & str) const { return std::fwrite(str.data(), str.size(), 1, m_ptr_); }

	#ifdef MSL_FILE_PTR_ENABLE_WIDE_STRING
	//! @brief write into the file from wstring
	void string_write(const std::wstring_view& str) const { std::fwrite(str.data(), str.size(), 1, m_ptr_); }
	#endif

	//! @brief read the file from the current position as byte stream returning a vector
	std::vector<char> read(std::size_t n = 0) const
	{
		if (n == 0) // 0 implies reading the whole remaining file
			n = this->remain_size();
		std::vector<char> buf(n);
		std::fread(buf.data(), 1, buf.size(), m_ptr_);
		return buf;
	}

	//! @brief read the file as std::fread as does
	std::size_t fread(void* buf, std::size_t n) const
	{
		return std::fread(buf, 1, n, m_ptr_);
	}

	//! @brief read the file from the current position as byte stream using a buffer
	std::size_t read(void * buf, std::size_t n = 0) const
	{
		if (n == 0) // 0 implies reading the whole remaining file
			n = this->remain_size();
		return std::fread(buf, 1, n, m_ptr_);
	}

	//! @brief read the next line from the current position as string
	std::optional<std::string> getline(char delim = '\n') const
	{
		std::string ret;
		int buf;
		while ((buf = std::fgetc(m_ptr_)) != EOF)
		{
			if (buf == delim) // if newline, return the current line
				return ret;
			ret += static_cast<char>(buf);
		}
		return (ret.empty()) ? std::nullopt : std::optional<std::string>{ret};
	}

	//! @brief tell the file
	long tell() const
	{
		return std::ftell(m_ptr_);
	}

	//! @brief seek the file
	void seek(long offset, int origin = SEEK_SET) const
	{
		std::fseek(m_ptr_, offset, origin);
	}

	//! @brief read the file from the current position returning null-terminated string
	std::string string_read(const std::size_t n = 0) const
	{
		auto vec = this->read(n);
		if (!vec.empty() && vec[vec.size() - 1] != '\0') // append EOS at the end of vector
			vec.emplace_back('\0');
		return std::string(vec.begin(), vec.end()); // convert vector to string
	}

	//! @brief read the file from the current position using a null-terminated string buffer
	void string_read(char buf[], const std::size_t n = 0) const
	{
		this->read(buf, n);
		if (buf[n - 1] != '\0')
			buf[n - 1] = '\0';
	}

	//! @brief move unwritten memory buffer data to the target file.
	void flush() const
	{
		std::fflush(m_ptr_);
	}
};
} // namespace msl
#endif
