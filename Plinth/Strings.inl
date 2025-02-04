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

#include "Strings.hpp"

#include "Generic.hpp" // for min()
#include <algorithm> // for std::remove and std::remove_if
#include <sstream>
#include <iomanip>
#include "NumberBase.hpp"

#include "Color.hpp"

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
						format.replace(position, 2_uz, argumentString);
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

	position = 0_uz;
	
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
	return string.erase(0_uz, string.find_first_not_of(charactersToTrim));
}

// [does not alter any parameters]
// trims string from the right of all characters in characterToTrim
inline std::string trimStringRight(std::string string, const std::string& charactersToTrim)
{
	return string.erase(string.find_last_not_of(charactersToTrim) + 1_uz);
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

inline std::string addBracketOpen(const std::string& string, const BracketType bracketType)
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

inline std::string addBracketClose(const std::string& string, const BracketType bracketType)
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

inline std::string addBrackets(const std::string& string, const BracketType bracketType)
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

inline std::string addBrackets(const std::string& string, const BracketType openBracketType, const BracketType closeBracketType)
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

inline std::string addBookends(const std::string& string, const char bookendCharacter, const std::size_t bookendLength)
{
	const std::string bookend(bookendLength, bookendCharacter);
	return bookend + string + bookend;
}

inline std::string stringFrom(const std::string& from)
{
	return from;
}

inline std::string stringFrom(const char* from)
{
	return std::string(from);
}

inline std::string stringFrom(const bool from)
{
	return (from ? "true" : "false");
}

inline std::string stringFrom(const Color::Rgb rgb, const DecimalPrecision decimalPrecision)
{
	return stringFrom(Vector3d(rgb.r, rgb.g, rgb.b), decimalPrecision);
}

template <class T>
inline std::string stringFrom(T* p)
{
	const std::string unpadded{ upperCase(hexFromDec(reinterpret_cast<std::size_t>(p))) };
	return padStringLeft(unpadded, (unpadded.size() > 32_uz) ? 64_uz : (unpadded.size() > 16_uz) ? 32_uz : (unpadded.size() > 8_uz) ? 16_uz : 8_uz, '0');
}

template <class T>
inline std::string stringFrom(T* p, const std::size_t minimumSize)
{
	const std::string padded{ stringFrom(p) };
	return padStringLeft(padded, (padded.size() < minimumSize) ? minimumSize : padded.size(), '0');
}

template<class T>
inline std::string stringFrom(const pl::Vector2<T> from, const DecimalPrecision decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ")";
}

template <class T>
inline std::string stringFrom(const Lax<T> lax, const DecimalPrecision decimalPrecision)
{
	return stringFrom(static_cast<T>(lax), decimalPrecision);
}

template <class T>
inline std::string stringFrom(const std::vector<T> froms, const DecimalPrecision decimalPrecision)
{
	std::string to{};
	for (auto& from : froms)
		to += stringFrom(from, decimalPrecision);
	return to;
}

template<class T>
inline std::string stringFrom(const std::vector<T> froms, const std::string& separator, const DecimalPrecision decimalPrecision)
{
	std::string to{};
	for (auto begin{ froms.begin() }, end{ froms.end() }, it{ begin }; it != end; ++it)
	{
		to += stringFrom(*it, decimalPrecision);
		if ((it + 1_uz) != end)
			to += separator;
	}
	return to;
}

template <class T>
inline std::string stringFrom(const T& from, const DecimalPrecision decimalPrecision)
{
	if (decimalPrecision.type == DecimalPrecision::None)
		return std::to_string(from);

	std::stringstream ss;
	if (decimalPrecision.type == DecimalPrecision::DecimalPlaces)
		ss << std::fixed;
	ss << std::setprecision(decimalPrecision.digits) << static_cast<long double>(from);
	return ss.str();
}

template<class T>
inline std::string stringFrom(const pl::Vector3<T> from, const DecimalPrecision decimalPrecision)
{
	return "(" + stringFrom(from.x, decimalPrecision) + ", " + stringFrom(from.y, decimalPrecision) + ", " + stringFrom(from.z, decimalPrecision) + ")";
}

template<class T>
inline std::string stringFrom(const pl::Size2<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(from.width, decimalPrecision) + " x " + stringFrom(from.height, decimalPrecision);
}
template<class T>
inline std::string stringFrom(const pl::Size3<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(from.width, decimalPrecision) + " x " + stringFrom(from.height, decimalPrecision) + " x " + stringFrom(from.depth, decimalPrecision);
}

template<class T>
inline std::string stringFrom(const pl::Range<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(from.min, decimalPrecision) + " - " + stringFrom(from.max, decimalPrecision);
}

template<class T>
inline std::string stringFrom(const pl::Range<pl::Vector2<T>> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(pl::Vector2<std::string>(stringFrom(pl::Range<T>{ from.min.x, from.max.x }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.y, from.max.y }, decimalPrecision)));
}

template<class T>
inline std::string stringFrom(const pl::Range<pl::Vector3<T>> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(pl::Vector3<std::string>(stringFrom(pl::Range<T>{ from.min.x, from.max.x }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.y, from.max.y }, decimalPrecision), stringFrom(pl::Range<T>{ from.min.z, from.max.z }, decimalPrecision)));
}

template<class T>
inline std::string stringFrom(const pl::RangeArea<T> from, const DecimalPrecision decimalPrecision)
{
	return stringFrom(pl::Range<pl::Vector2<T>>{ from.getLeftBottom(), from.getRightTop() }, decimalPrecision);
}

} // namespace plinth
