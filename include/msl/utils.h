#pragma once

#include <algorithm>
#include <string>
#include <vector>

namespace msl
{
//! @brief string_split split a string into a vector by providing a single delim character
inline std::vector<std::string> string_split(const std::string & str, char tok = ' ')
{
	std::vector<std::string> vec;
	std::size_t prev = 0;
	std::size_t cur = str.find(tok);
	while (cur != std::string::npos)
	{
		vec.emplace_back(str.substr(prev, cur - prev));
		prev = cur + 1;
		cur = str.find(tok, prev);
	}
	vec.emplace_back(str.substr(prev, cur - prev));
	return vec;
}

//! @brief string_split split a string into a vector by providing the delim string
inline std::vector<std::string> string_split(const std::string & str, const std::string & tok = " ")
{
	std::vector<std::string> vec;
	std::size_t prev = 0;
	std::size_t cur = str.find(tok);
	while (cur != std::string::npos)
	{
		vec.emplace_back(str.substr(prev, cur - prev));
		prev = cur + tok.size();
		cur = str.find(tok, prev);
	}
	vec.emplace_back(str.substr(prev, cur - prev));
	return vec;
}

//! @brief string_split_any split a string into a vector by providing any of the single delim characters
inline std::vector<std::string> string_split_any(const std::string & str, const std::string & toks = " ")
{
	std::vector<std::string> vec;
	std::size_t prev = 0;
	std::size_t cur = str.find_first_of(toks);
	while (cur != std::string::npos)
	{
		vec.emplace_back(str.substr(prev, cur - prev));
		prev = cur + 1;
		cur = str.find_first_of(toks, prev);
	}
	vec.emplace_back(str.substr(prev, cur - prev));
	return vec;
}

inline std::string string_join(const std::vector<std::string> & vec, const char tok = ' ')
{
	std::string str;
	for (auto & elem : vec)
	{
		if (!str.empty())
			str += tok;
		str += elem;
	}
	return str;
}

inline std::string string_join(const std::vector<std::string> & vec, const std::string & tok = " ")
{
	std::string str;
	for (auto & elem : vec)
	{
		if (!str.empty())
			str += tok;
		str += elem;
	}
	return str;
}
} // namespace msl
