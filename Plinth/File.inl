//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2025 M.J.Silk
//
// This software is provided 'as-is', without any express or implied
// warranty. In no event will the authors be held liable for any damages
// arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it
// freely, subject to the following restrictions :
//
// 1. The origin of this software must not be misrepresented; you must not
// claim that you wrote the original software.If you use this software
// in a product, an acknowledgment in the product documentation would be
// appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such, and must not be
// misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
// M.J.Silk
// MJSilk2@gmail.com
//
//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "File.hpp"

namespace plinth
{

template <class SizeT>
inline bool saveBinaryFile(const char* data, const std::string& filename, const SizeT size)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!file.is_open())
		return false;
	file.write(data, static_cast<std::streampos>(size));
	return true;
}

template <class SizeT>
inline bool saveBinaryFile(const std::unique_ptr<char[]>& data, const std::string& filename, const SizeT size)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (!file.is_open())
		return false;
	file.write(data.get(), static_cast<std::streampos>(size));
	return true;
}

inline std::size_t getFileSize(const std::string& filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0_uz;
	return static_cast<std::size_t>(file.tellg());
}

inline bool loadTextFile(std::vector<std::string>& lines, const std::string& filename, const bool stripTrailingNewlines)
{
	std::ifstream file(filename, std::ifstream::in);
	if (!file.is_open())
		return false;
	lines.clear();
	std::string line{};
	while (std::getline(file, line))
	{
		if (stripTrailingNewlines && (!line.empty()) && (line[line.length() - 1_uz] == '\n'))
			line.erase(line.length() - 1_uz);
		lines.push_back(line);
	}
	return true;
}

inline std::size_t loadBinaryFile(char* data, const std::string& filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0_uz;
	const std::size_t size{ static_cast<std::size_t>(file.tellg()) };
	data = new char[size];
	file.seekg(0_uz, std::ios::beg);
	file.read(data, size);
	return size;
}

inline std::size_t loadBinaryFile(std::unique_ptr<char[]>& data, const std::string& filename)
{
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0_uz;
	const std::size_t size{ static_cast<std::size_t>(file.tellg()) };
	data = std::make_unique<char[]>(size);
	file.seekg(0_uz, std::ios::beg);
	file.read(data.get(), size);
	return size;
}

inline bool saveTextFile(const std::vector<std::string>& lines, const std::string& filename, const bool addNewlines)
{
	std::ofstream file(filename, std::ofstream::out);
	if (!file.is_open())
		return false;
	for (auto& line : lines)
	{
		file << line;
		if (addNewlines)
			file << "\n";
	}
	return true;
}

} // namespace plinth
