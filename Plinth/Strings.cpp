//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2015 M.J.Silk
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

#include "Strings.hpp"

namespace plinth
{

// [does not alter any parameters]
std::string lowerCase(std::string string)
{
	makeLowerCase(string);
	return string;
}

// [does not alter any parameters]
std::string upperCase(std::string string)
{
	makeUpperCase(string);
	return string;
}

void makeLowerCase(std::string& string)
{
	const std::string upper{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	const std::string lower{ "abcdefghijklmnopqrstuvwxyz" };
	for (auto& character : string)
	{
		unsigned int stringPosition{ upper.find(character) };
		if (stringPosition != std::string::npos)
			character = lower[stringPosition];
	}
}

void makeUpperCase(std::string& string)
{
	const std::string upper{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
	const std::string lower{ "abcdefghijklmnopqrstuvwxyz" };
	for (auto& character : string)
	{
		unsigned int stringPosition{ lower.find(character) };
		if (stringPosition != std::string::npos)
			character = upper[stringPosition];
	}
}

// [does not alter any parameters]
bool isAlphaNumeric(char c)
{
	const std::string valid{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" };
	return (valid.find(c) != std::string::npos);
}

// [does not alter any parameters]
bool isAlphaNumeric(const std::string& string)
{
	return doesContainOnly(upperCase(string), "ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789");
	/*
	const std::string valid{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" };
	for (auto& character : string)
	{
	if (valid.find(character) == std::string::npos)
	return false;
	}
	return true;
	*/
}

// [does not alter any parameters]
std::string concatenate(const std::vector<std::string>& strings)
{
	std::string concatenation;
	for (auto& string : strings)
		concatenation += string;
	return concatenation;
}

// [does not alter any parameters]
bool doesContainOnly(const std::string& testString, const std::string& validCharacters)
{
	for (auto& character : testString)
	{
		if (validCharacters.find(character) == std::string::npos)
			return false;
	}
	return true;
}

// [does not alter any parameters]
std::string padStringLeft(std::string string, unsigned int width, char character)
{
	if (string.size() >= width)
		return string;
	for (unsigned int i{ 0 }; i < string.size() - width; ++i)
		string = character + string;

	return string;
}

// [does not alter any parameters]
std::string padStringRight(std::string string, unsigned int width, char character)
{
	if (string.size() >= width)
		return string;
	for (unsigned int i{ 0 }; i < string.size() - width; ++i)
		string += character;

	return string;
}

// [does not alter any parameters]
std::string password(const std::string& string, char shieldChar)
{
	return std::string(string.size(), shieldChar);
}

/*
std::string password(std::string string, char shieldChar)
{
for (auto& character : string)
character = shieldChar;
return string;
}
*/

// [does not alter any parameters]
// replace any character in string that exists in supplementary string with specific character.
// e.g. replace 'a' with '-': Hapax -> H-p-x
std::string replaceChars(std::string string, const std::string& charactersToReplace, char characterToReplaceWith)
{
	for (auto& character : string)
	{
		if (charactersToReplace.find(character) != std::string::npos)
			character = characterToReplaceWith;
	}
	return string;
}

// [does not alter any parameters]
// replace any character in string that exists in supplementary string with another string (full string per character - can be empty to remove).
// e.g. replace "Pit" with "123": Plinth -> 123l123n123h
std::string replaceChars(const std::string& string, const std::string& charactersToReplace, const std::string& stringToReplaceWith)
{
	std::string result;
	for (auto& character : string)
	{
		if (charactersToReplace.find(character) != std::string::npos)
			result += stringToReplaceWith;
		else
			result += character;
	}
	return result;
}

} // namespace plinth
