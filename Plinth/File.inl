//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2024 M.J.Silk
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

#ifndef PLINTH_FILE_INL
#define PLINTH_FILE_INL

#include "File.hpp"

namespace plinth
{

template <class sizeT>
inline void saveBinaryFile(const char* data, const std::string& filename, sizeT size)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.is_open())
	{
		file.write(data, static_cast<std::streampos>(size));
		file.close();
	}
}

template <class sizeT>
inline void saveBinaryFile(const std::unique_ptr<char[]>& data, const std::string& filename, sizeT size)
{
	std::ofstream file(filename, std::ios::out | std::ios::binary | std::ios::trunc);
	if (file.is_open())
	{
		file.write(data.get(), static_cast<std::streampos>(size));
		file.close();
	}
}

inline FileSize getFileSize(const std::string& filename)
{
	FileSize size;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0u;
	else
	{
		size = static_cast<FileSize>(file.tellg());
		file.close();
		return size;
	}
}

inline void loadTextFile(std::vector<std::string>& lines, const std::string& filename, const bool stripTrailingNewlines)
{
	std::ifstream file(filename, std::ifstream::in);
	lines.clear();
	std::string line;
	if (!file.is_open())
		return;
	else
	{
		while (std::getline(file, line))
		{
			if (stripTrailingNewlines && !line.empty() && line[line.length() - 1] == '\n')
				line.erase(line.length() - 1);
			lines.push_back(line);
		}
		file.close();
	}
}

inline FileSize loadBinaryFile(char* data, const std::string& filename)
{
	FileSize size;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0u;
	else
	{
		size = static_cast<FileSize>(file.tellg());
		data = new char[size];
		file.seekg(0, std::ios::beg);
		file.read(data, size);
		file.close();
		return size;
	}
}

inline FileSize loadBinaryFile(std::unique_ptr<char[]>& data, const std::string& filename)
{
	FileSize size;
	std::ifstream file(filename, std::ios::in | std::ios::binary | std::ios::ate);
	if (!file.is_open())
		return 0u;
	else
	{
		size = static_cast<FileSize>(file.tellg());
		data.reset(new char[size]);
		file.seekg(0, std::ios::beg);
		file.read(data.get(), size);
		file.close();
		return size;
	}
}

inline void saveTextFile(const std::vector<std::string>& lines, const std::string& filename, const bool addNewlines)
{
	std::ofstream file(filename, std::ofstream::out);
	if (!file.is_open())
		return;
	else
	{
		for (auto& line : lines)
		{
			file << line;
			if (addNewlines)
				file << "\n";
		}
		file.close();
	}
}

} // namespace plinth
#endif // PLINTH_FILE_INL
