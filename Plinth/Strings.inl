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

#ifndef PLINTH_STRINGS_INL
#define PLINTH_STRINGS_INL

#include "Strings.hpp"

#include "Generic.hpp" // for min()
#include "StringFrom.hpp"
#include <algorithm> // for std::remove and std::remove_if

namespace plinth
{

// [does not alter any parameters]
// returns a formatted string based on the format parameter and the following arguments (passed in a vector)
// argument type is templated. all arguments are sent through stringFrom()
// formats a maximum of 10 arguments (%0 - %9). excess arguments are ignored.
// arguments need not be in order in the format
template <class T>
inline std::string formattedString(std::string format, const std::vector<T>& arguments)
{
	const std::size_t numberOfArguments{ min(arguments.size(), 10_uz) }; // cannot format more than 10 arguments as the format syntax only uses 0-9 to specify which argument

	std::size_t position{ 0_uz };
	for (std::size_t argumentIndex{ 0_uz }; argumentIndex < numberOfArguments; ++argumentIndex)
	{
		std::string argumentString{ stringFrom(arguments[argumentIndex]) };
		position = 0_uz;
		bool instanceLoop{ true };
		while (instanceLoop)
		{
			position = format.find("%" + stringFrom(argumentIndex), position);

			if (position != std::string::npos)
			{
				if (position == 0_uz)
				{
					if (format.size() > 1_uz && format.substr(0_uz, 2_uz) == "%%")
						continue;
					else
					{
						format.replace(position, 2uz, argumentString);
						instanceLoop = false;
					}
				}
				else if (format.substr(position - 1_uz, 2_uz) != "%%")
				{
					format.replace(position, 2_uz, argumentString);
					instanceLoop = false;
				}
				++position;
			}
			else
				instanceLoop = false;
		}
	}

	position = 0uz;
	
	while ((position = format.find("%%", position)) != std::string::npos)
	{
		format.replace(position, 2_uz, "%");
		++position;
	}
	
	/*
	do
	{
		position = format.find("%%", position);
		if (position != std::string::npos)
		{
			format.replace(position, 2u, "%");
			++position;
		}
	} while (position != std::string::npos);
	*/

	return format;
}

const std::string presetWhitespaceCharacters{ " \f\n\r\t\v" };
const std::string upperCaseCharacters{ "ABCDEFGHIJKLMNOPQRSTUVWXYZ" };
const std::string lowerCaseCharacters{ "abcdefghijklmnopqrstuvwxyz" };
const std::string digits{ "0123456789" };
const std::string alphaNumericCharacters{ upperCaseCharacters + lowerCaseCharacters + digits };

inline void makeLowerCaseChar(char& input)
{
	const std::size_t stringPosition{ upperCaseCharacters.find(input) };
	if (stringPosition != std::string::npos)
		input = lowerCaseCharacters[stringPosition];
}

inline void makeUpperCaseChar(char& input)
{
	const std::size_t stringPosition{ lowerCaseCharacters.find(input) };
	if (stringPosition != std::string::npos)
		input = upperCaseCharacters[stringPosition];
}

// [does not alter any parameters]
inline std::string lowerCase(std::string string)
{
	makeLowerCase(string);
	return string;
}

// [does not alter any parameters]
inline std::string upperCase(std::string string)
{
	makeUpperCase(string);
	return string;
}

// [does not alter any parameters]
inline std::string capitalized(std::string string)
{
	makeCapitalized(string);
	return string;
}

inline void makeLowerCase(std::string& string)
{
	for (auto& character : string)
		makeLowerCaseChar(character);
}

inline void makeUpperCase(std::string& string)
{
	for (auto& character : string)
		makeUpperCaseChar(character);
}

inline void makeCapitalized(std::string& string)
{
	if (!string.empty())
		makeUpperCaseChar(string[0u]);
}

// [does not alter any parameters]
inline bool isAlphaNumeric(const char c)
{
	return (alphaNumericCharacters.find(c) != std::string::npos);
}

// [does not alter any parameters]
inline bool isAlphaNumeric(const std::string& string)
{
	return doesContainOnly(string, alphaNumericCharacters);
}

// [does not alter any parameters]
inline std::string concatenate(const std::vector<std::string>& strings)
{
	std::string concatenation{};
	for (auto& string : strings)
		concatenation += string;
	return concatenation;
}

// [does not alter any parameters]
inline bool doesContainOnly(const std::string& testString, const std::string& validCharacters)
{
	for (auto character : testString)
	{
		if (validCharacters.find(character) == std::string::npos)
			return false;
	}
	return true;
}

// [does not alter any parameters]
inline std::string padStringLeft(const std::string& string, const std::size_t width, const char character)
{
	std::string prefix{};
	for (std::size_t i{ string.size() }; i < width; ++i)
		prefix += character;

	return prefix + string;
}

// [does not alter any parameters]
inline std::string padStringRight(std::string string, const std::size_t width, const char character)
{
	for (std::size_t i{ string.size() }; i < width; ++i)
		string += character;

	return string;
}

// [does not alter any parameters]
// trims string from the left of all characters in characterToTrim
inline std::string trimStringLeft(std::string string, const std::string& charactersToTrim)
{
	string.erase(0_uz, string.find_first_not_of(charactersToTrim));
	return string;
}

// [does not alter any parameters]
// trims string from the right of all characters in characterToTrim
inline std::string trimStringRight(std::string string, const std::string& charactersToTrim)
{
	string.erase(string.find_last_not_of(charactersToTrim) + 1_uz);
	return string;
}

// [does not alter any parameters]
// trims string from both sides of all characters in characterToTrim
inline std::string trimString(const std::string& string, const std::string& charactersToTrim)
{
	return trimStringLeft(trimStringRight(string, charactersToTrim), charactersToTrim);
}

// [does not alter any parameters]
// trims string from the left of all preset whitespace characters
inline std::string trimWhitespaceLeft(std::string string)
{
	return trimStringLeft(string, presetWhitespaceCharacters);
}

// [does not alter any parameters]
// trims string from the right of all preset whitespace characters
inline std::string trimWhitespaceRight(std::string string)
{
	return trimStringRight(string, presetWhitespaceCharacters);
}

// [does not alter any parameters]
// trims string from both sides of all preset whitespace characters
inline std::string trimWhitespace(const std::string& string)
{
	return trimString(string, presetWhitespaceCharacters);
}

// [does not alter any parameters]
inline std::string password(const std::string& string, const char shieldChar)
{
	return std::string(string.size(), shieldChar);
}

// [does not alter any parameters]
// replace any character in string that exists in supplementary string with specific character.
// e.g. replace 'a' with '-': Hapaxia -> H-p-xi-
inline std::string replaceChars(std::string string, const std::string& charactersToReplace, const char characterToReplaceWith)
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
inline std::string replaceChars(const std::string& string, const std::string& charactersToReplace, const std::string& stringToReplaceWith)
{
	std::string result{};
	for (auto character : string)
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
// e.g. remove 'a': Hapaxia -> Hpxi
inline std::string removeChars(std::string string, const char characterToRemove)
{
	string.erase(std::remove(string.begin(), string.end(), characterToRemove), string.end());
	return string;
}

// [does not alter any parameters]
// remove any characters in string that matches any characters in the supplementary string
// e.g. remove "Hpx": Hapaxia -> aaia
inline std::string removeChars(std::string string, const std::string& charactersToRemove)
{
	string.erase(std::remove_if(string.begin(), string.end(), [&charactersToRemove](const char& c) { return (charactersToRemove.find(c) != std::string::npos); }), string.end());
	return string;
}

std::string addBracketOpen(const std::string& string, const BracketType bracketType)
{
	switch (bracketType)
	{
	case BracketType::Brace:
		return "{" + string;
	case BracketType::Angled:
		return "<" + string;
	case BracketType::Square:
		return "[" + string;
	case BracketType::Parenthesis:
	default:
		return "(" + string;
	}
}

std::string addBracketClose(const std::string& string, const BracketType bracketType)
{
	switch (bracketType)
	{
	case BracketType::Brace:
		return string + "}";
	case BracketType::Angled:
		return string + ">";
	case BracketType::Square:
		return string + "]";
	case BracketType::Parenthesis:
	default:
		return string + ")";
	}
}

std::string addBrackets(const std::string& string, const BracketType bracketType)
{
	switch (bracketType)
	{
	case BracketType::Brace:
		return "{" + string + "}";
	case BracketType::Angled:
		return "<" + string + ">";
	case BracketType::Square:
		return "[" + string + "]";
	case BracketType::Parenthesis:
	default:
		return "(" + string + ")";
	}
}

std::string addBrackets(const std::string& string, const BracketType openBracketType, const BracketType closeBracketType)
{
	std::string openBracket{};
	std::string closeBracket{};

	switch (openBracketType)
	{
	case BracketType::Brace:
		openBracket = "{";
		break;
	case BracketType::Angled:
		openBracket = "<";
		break;
	case BracketType::Square:
		openBracket = "[";
		break;
	case BracketType::Parenthesis:
	default:
		openBracket = "(";
	}

	switch (closeBracketType)
	{
	case BracketType::Brace:
		closeBracket = "}";
		break;
	case BracketType::Angled:
		closeBracket = ">";
		break;
	case BracketType::Square:
		closeBracket = "]";
		break;
	case BracketType::Parenthesis:
	default:
		closeBracket = ")";
	}
	
	return openBracket + string + closeBracket;
}

std::string addBookends(const std::string& string, const char bookendCharacter, const std::size_t bookendLength)
{
	const std::string bookend(bookendLength, bookendCharacter);
	return bookend + string + bookend;
}

} // namespace plinth
#endif // PLINTH_STRINGS_INL
