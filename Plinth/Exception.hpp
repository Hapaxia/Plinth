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

#ifndef PLINTH_EXCEPTION_HPP
#define PLINTH_EXCEPTION_HPP

#include <exception>
#include <string>

#ifdef _MSC_VER
#define NOEXCEPT
#else
#define NOEXCEPT noexcept
#endif

namespace plinth
{

class Exception : public std::exception
{
public:
	Exception(const std::string& errorMessage = "Unknown error.") :
		m_errorMessage("[Plinth] " + errorMessage)
	{
	}
	virtual const char* what() const NOEXCEPT override
	{
		return m_errorMessage.c_str();
	}

private:
	std::string m_errorMessage;
};

} // namespace plinth
#include "Common.hpp"
#endif // PLINTH_EXCEPTION_HPP
