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

#include "Common.hpp"
#include <fstream>
#include <memory>

namespace plinth
{

std::size_t getFileSize(const std::string& filename);

bool loadTextFile(std::vector<std::string>& lines, const std::string& filename, bool stripTrailingNewlines = true);
std::size_t loadBinaryFile(char* data, const std::string& filename); // returns size of data memory block
std::size_t loadBinaryFile(std::unique_ptr<char[]>& data, const std::string& filename); // returns size of data memory block

bool saveTextFile(const std::vector<std::string>& lines, const std::string& filename, bool addNewlines = true);
template <class SizeT>
bool saveBinaryFile(const char* data, const std::string& filename, SizeT size);
template <class SizeT>
bool saveBinaryFile(const std::unique_ptr<char[]>& data, const std::string& filename, SizeT size);

} // namespace plinth
#include "File.inl"
