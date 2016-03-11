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

#include "Generic.hpp" // for min()

namespace plinth
{

// [does not alter any parameters]
// returns a formatted string based on the format parameter and the following arguments (passed in a vector)
// argument type is templated. all arguments are sent through stringFrom()
// formats a maximum of 10 arguments (%0 - %9). excess arguments are ignored.
// arguments need not be in order in the format
template <class T>
std::string formattedString(std::string format, const std::vector<T>& arguments)
{
	unsigned int argumentIndex{ 0u };
	const unsigned int numberOfArguments{ min(static_cast<unsigned int>(arguments.size()), 10u) }; // cannot format more than 10 arguments as the format syntax only uses 0-9 to specify which argument

	std::string argumentString;
	size_t position{ 0 };
	for (unsigned int argumentIndex{ 0u }; argumentIndex < numberOfArguments; ++argumentIndex)
	{
		argumentString = stringFrom(arguments[argumentIndex]);
		position = 0;
		bool instanceLoop{ true };
		do
		{
			position = format.find("%" + stringFrom(argumentIndex), position);

			if (position != std::string::npos)
			{
				if (format.substr(position - 1, 2) != "%%")
				{
					format.replace(position, 2, argumentString);
					instanceLoop = false;
				}
				++position;
			}
			else
				instanceLoop = false;
		} while (instanceLoop);
	};

	position = 0;
	do
	{
		position = format.find("%%", position);
		if (position != std::string::npos)
		{
			format.replace(position, 2, "%");
			++position;
		}
	} while (position != std::string::npos);

	return format;
}

} // namespace plinth
