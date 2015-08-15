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

#include "Keyboard.hpp"

namespace plinth
{

std::string stringFrom(const sf::Keyboard::Key& key)
{
	std::vector<std::string> keyStrings{
		"A",
		"B",
		"C",
		"D",
		"E",
		"F",
		"G",
		"H",
		"I",
		"J",
		"K",
		"L",
		"M",
		"N",
		"O",
		"P",
		"Q",
		"R",
		"S",
		"T",
		"U",
		"V",
		"W",
		"X",
		"Y",
		"Z",
		"0",
		"1",
		"2",
		"3",
		"4",
		"5",
		"6",
		"7",
		"8",
		"9",
		"Escape",
		"Left Control",
		"Left Shift",
		"Left Alt",
		"Left System",
		"Right Control",
		"Right Shift",
		"Right Alt",
		"Right System",
		"Menu",
		"[",
		"]",
		";",
		",",
		".",
		"'",
		"/",
		"\\",
		"~",
		"=",
		"-",
		"Space",
		"Return",
		"Backspace",
		"Tab",
		"Page Up",
		"Page Down",
		"End",
		"Home",
		"Insert",
		"Delete",
		"+ (numpad)",
		"- (numpad)",
		"* (numpad)",
		"/ (numpad)",
		"Left",
		"Right",
		"Up",
		"Down",
		"0 (numpad)",
		"1 (numpad)",
		"2 (numpad)",
		"3 (numpad)",
		"4 (numpad)",
		"5 (numpad)",
		"6 (numpad)",
		"7 (numpad)",
		"8 (numpad)",
		"9 (numpad)",
		"F1",
		"F2",
		"F3",
		"F4",
		"F5",
		"F6",
		"F7",
		"F8",
		"F9",
		"F10",
		"F11",
		"F12",
		"F13",
		"F14",
		"F15",
		"Pause",
		"Unknown"
	};
	if (key < 0)
		return keyStrings[sf::Keyboard::KeyCount];
	else
		return keyStrings[key];
}

} // namespace plinth
