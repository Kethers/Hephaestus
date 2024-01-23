﻿#include "heppch.h"
#include "StringUtils.h"

namespace Hep::Utils
{
	std::string GetFilename(const std::string& filepath)
	{
		std::vector<std::string> parts = SplitString(filepath, "/\\");

		if (parts.size() > 0)
			return parts[parts.size() - 1];

		return "";
	}

	std::string GetExtension(const std::string& filename)
	{
		std::vector<std::string> parts = SplitString(filename, '.');

		if (parts.size() > 1)
			return parts[parts.size() - 1];

		return "";
	}

	std::string RemoveExtension(const std::string& filename)
	{
		return filename.substr(0, filename.find_last_of('.'));
	}

	bool StartsWith(const std::string& string, const std::string& start)
	{
		return string.find(start) == 0;
	}

	std::vector<std::string> SplitString(const std::string& string, const std::string& delimiters)
	{
		size_t start = 0;
		size_t end = string.find_first_of(delimiters);

		std::vector<std::string> result;

		while (end <= std::string::npos)
		{
			std::string token = string.substr(start, end - start);
			if (!token.empty())
				result.push_back(token);

			if (end == std::string::npos)
				break;

			start = end + 1;
			end = string.find_first_of(delimiters, start);
		}

		return result;
	}

	std::vector<std::string> SplitString(const std::string& string, const char delimiter)
	{
		return SplitString(string, std::string(1, delimiter));
	}

	std::string ToLower(const std::string& string)
	{
		std::string result;
		for (const auto& character : string)
		{
			result += std::tolower(character);
		}

		return result;
	}
}
