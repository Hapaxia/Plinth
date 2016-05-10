//////////////////////////////////////////////////////////////////////////////
//
// Plinth
//
// Copyright(c) 2014-2016 M.J.Silk
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

#include <algorithm> // for std::remove

namespace
{

const std::string presetWhitespaceCharacters{ " \f\n\r\t\v" };
const std::string upperCaseCharacters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::string lowerCaseCharacters{ "abcdefghijklmnopqrstuvwxyz" };
const std::string alphaNumericCharacters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" };

inline void makeLowerCaseChar(char& input)
{
	const unsigned int stringPosition{ upperCaseCharacters.find(input) };
	if (stringPosition != std::string::npos)
		input = lowerCaseCharacters[stringPosition];
}

inline void makeUpperCaseChar(char& input)
{
	const unsigned int stringPosition{ lowerCaseCharacters.find(input) };
	if (stringPosition != std::string::npos)
		input = upperCaseCharacters[stringPosition];
}

} // namespace

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

// [does not alter any parameters]
std::string capitalized(std::string string)
{
	makeCapitalized(string);
	return string;
}

void makeLowerCase(std::string& string)
{
	for (auto& character : string)
		makeLowerCaseChar(character);
}

void makeUpperCase(std::string& string)
{
	for (auto& character : string)
		makeUpperCaseChar(character);
}

void makeCapitalized(std::string& string)
{
	if (string.size() > 0)
		makeUpperCaseChar(string[0]);
}

// [does not alter any parameters]
bool isAlphaNumeric(const char c)
{
	return (alphaNumericCharacters.find(c) != std::string::npos);
}

// [does not alter any parameters]
bool isAlphaNumeric(const std::string& string)
{
	return doesContainOnly(string, alphaNumericCharacters);
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
std::string padStringLeft(std::string string, const unsigned int width, const char character)
{
	if (string.size() >= width)
		return string;
	for (unsigned int i{ 0 }; i < string.size() - width; ++i)
		string = character + string;

	return string;
}

// [does not alter any parameters]
std::string padStringRight(std::string string, const unsigned int width, const char character)
{
	if (string.size() >= width)
		return string;
	for (unsigned int i{ 0 }; i < string.size() - width; ++i)
		string += character;

	return string;
}

// [does not alter any parameters]
// trims string from the left of all characters in characterToTrim
std::string trimStringLeft(std::string string, const std::string& charactersToTrim)
{
	string.erase(0, string.find_first_not_of(charactersToTrim));
	return string;
}

// [does not alter any parameters]
// trims string from the right of all characters in characterToTrim
std::string trimStringRight(std::string string, const std::string& charactersToTrim)
{
	string.erase(string.find_last_not_of(charactersToTrim) + 1);
	return string;
}

// [does not alter any parameters]
// trims string from both sides of all characters in characterToTrim
std::string trimString(const std::string& string, const std::string& charactersToTrim)
{
	return trimStringLeft(trimStringRight(string, charactersToTrim), charactersToTrim);
}

// [does not alter any parameters]
// trims string from the left of all preset whitespace characters
std::string trimWhitespaceLeft(std::string string)
{
	return trimStringLeft(string, presetWhitespaceCharacters);
}

// [does not alter any parameters]
// trims string from the right of all preset whitespace characters
std::string trimWhitespaceRight(std::string string)
{
	return trimStringRight(string, presetWhitespaceCharacters);
}

// [does not alter any parameters]
// trims string from both sides of all preset whitespace characters
std::string trimWhitespace(const std::string& string)
{
	return trimString(string, presetWhitespaceCharacters);
}

// [does not alter any parameters]
std::string password(const std::string& string, const char shieldChar)
{
	return std::string(string.size(), shieldChar);
}

// [does not alter any parameters]
// replace any character in string that exists in supplementary string with specific character.
// e.g. replace 'a' with '-': Hapax -> H-p-x
std::string replaceChars(std::string string, const std::string& charactersToReplace, const char characterToReplaceWith)
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

// [does not alter any parameters]
// remove all characters in string that matches the given character
// e.g. remove 'a': Hapax -> Hpx
std::string removeChars(std::string string, const char characterToRemove)
{
	string.erase(std::remove(string.begin(), string.end(), characterToRemove), string.end());
	return string;
}

// [does not alter any parameters]
// remove any characters in string that matches any characters in the supplementary string
// e.g. remove "Hpx": Hapax -> aa
std::string removeChars(std::string string, const std::string& charactersToRemove)
{
	for (auto& character : charactersToRemove)
		string.erase(std::remove(string.begin(), string.end(), character), string.end());
	return string;
}

} // namespace plinth
