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

#pragma once

// remove unwanted min/max macros
#ifdef min
#undef min
#endif // min
#ifdef max
#undef max
#endif // max

#include "Exception.hpp"

namespace plinth
{

constexpr long double defaultEpsilon{ 0.00001 };

} // namespace plinth

#ifndef PLINTH_NO_NAMESPACE_SHORTCUT
namespace pl = plinth; // create shortcut namespace
#endif // PLINTH_NO_NAMESPACE_SHORTCUT

#include <vector>
#include <string>
#include <cstddef>

#define MAKE_ENUM_BITWISE(x)                                                                                                    \
inline x operator|(x a, x b) { return static_cast<x>(static_cast<unsigned long int>(a) | static_cast<unsigned long int>(b)); }  \
inline x operator^(x a, x b) { return static_cast<x>(static_cast<unsigned long int>(a) ^ static_cast<unsigned long int>(b)); }  \
inline x operator&(x a, x b) { return static_cast<x>(static_cast<unsigned long int>(a) & static_cast<unsigned long int>(b)); }  \
inline x operator~(x a) { return static_cast<x>(~static_cast<unsigned long int>(a)); }                                          \
inline x operator>>(x a, std::size_t bits) { return static_cast<x>(static_cast<unsigned long int>(a) >> bits); }                \
inline x operator<<(x a, std::size_t bits) { return static_cast<x>(static_cast<unsigned long int>(a) << bits); }

constexpr std::size_t operator ""_uz(unsigned long long unsignedInteger) noexcept { return static_cast<std::size_t>(unsignedInteger); }
constexpr unsigned char operator ""_uc(unsigned long long unsignedInteger) noexcept { return static_cast<unsigned char>(unsignedInteger); }
