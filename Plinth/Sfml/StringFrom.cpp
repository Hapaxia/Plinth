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

#include "StringFrom.hpp"

namespace plinth
{

std::string stringFrom(const sf::Vector2<std::string> from)
{
	return "(" + from.x + ", " + from.y + ")";
}

std::string stringFrom(const sf::Vector3<std::string> from)
{
	return "(" + from.x + ", " + from.y + ", " + from.z + ")";
}

std::string stringFrom(const sf::Color from, const SfmlColorList colorList, const bool separateAlpha)
{
	std::string s;
	sf::Color color{ from };
	if (separateAlpha)
		color.a = 255;
	if (colorList == SfmlColorList::Standard)
	{
		if (color == sf::Color::Black)
			s = "black";
		else if (color == sf::Color::Blue)
			s = "blue";
		else if (color == sf::Color::Red)
			s = "red";
		else if (color == sf::Color::Magenta)
			s = "magenta";
		else if (color == sf::Color::Green)
			s = "green";
		else if (color == sf::Color::Cyan)
			s = "cyan";
		else if (color == sf::Color::Yellow)
			s = "yellow";
		else if (color == sf::Color::White)
			s = "white";
		else if (color == sf::Color::Transparent)
			s = "transparent";
		else
		{
			if (separateAlpha)
				s = stringFrom(pl::Vector3u{ color.r, color.g, color.b });
			else
				s = "(" + stringFrom(color.r) + ", " + stringFrom(color.g) + ", " + stringFrom(color.b) + ", " + stringFrom(color.a) + ")";
		}
	}
	else if (colorList == SfmlColorList::Extended)
	{
		// standards
		if (color == Colors::Black)
			s = "black";
		else if (color == Colors::Blue)
			s = "blue";
		else if (color == Colors::Red)
			s = "red";
		else if (color == Colors::Magenta)
			s = "magenta";
		else if (color == Colors::Green)
			s = "green";
		else if (color == Colors::Cyan)
			s = "cyan";
		else if (color == Colors::Yellow)
			s = "yellow";
		else if (color == Colors::White)
			s = "white";
		else if (color == Colors::Brown)
			s = "brown";
		else if (color == Colors::Orange)
			s = "orange";
		else if (color == Colors::Pink)
			s = "pink";
		else if (color == Colors::BabyPink)
			s = "baby pink";
		else if (color == Colors::HotPink)
			s = "hot pink";
		else if (color == Colors::Salmon)
			s = "salmon";
		else if (color == Colors::Violet)
			s = "violet";
		else if (color == Colors::Purple)
			s = "purple";
		else if (color == Colors::Peach)
			s = "peach";
		else if (color == Colors::Lime)
			s = "lime";
		else if (color == Colors::Mint)
			s = "mint";
		else if (color == Colors::Gray)
			s = "grey";

		// lights
		else if (color == Colors::LightBlack)
			s = "light black";
		else if (color == Colors::LightBlue)
			s = "light blue";
		else if (color == Colors::LightRed)
			s = "light red";
		else if (color == Colors::LightMagenta)
			s = "light magenta";
		else if (color == Colors::LightGreen)
			s = "light green";
		else if (color == Colors::LightCyan)
			s = "light cyan";
		else if (color == Colors::LightYellow)
			s = "light yellow";
		else if (color == Colors::LightBrown)
			s = "light brown";
		else if (color == Colors::LightOrange)
			s = "light orange";
		else if (color == Colors::LightPink)
			s = "light pink";
		else if (color == Colors::LightBabyPink)
			s = "light baby pink";
		else if (color == Colors::LightHotPink)
			s = "light hot pink";
		else if (color == Colors::LightSalmon)
			s = "light salmon";
		else if (color == Colors::LightViolet)
			s = "light violet";
		else if (color == Colors::LightPurple)
			s = "light purple";
		else if (color == Colors::LightPeach)
			s = "light peach";
		else if (color == Colors::LightLime)
			s = "light lime";
		else if (color == Colors::LightMint)
			s = "light mint";
		else if (color == Colors::LightGray)
			s = "light grey";

		// darks
		else if (color == Colors::DarkBlue)
			s = "dark blue";
		else if (color == Colors::DarkRed)
			s = "dark red";
		else if (color == Colors::DarkMagenta)
			s = "dark magenta";
		else if (color == Colors::DarkGreen)
			s = "dark green";
		else if (color == Colors::DarkCyan)
			s = "dark cyan";
		else if (color == Colors::DarkYellow)
			s = "dark yellow";
		else if (color == Colors::DarkWhite)
			s = "dark white";
		else if (color == Colors::DarkBrown)
			s = "dark brown";
		else if (color == Colors::DarkOrange)
			s = "dark orange";
		else if (color == Colors::DarkPink)
			s = "dark pink";
		else if (color == Colors::DarkBabyPink)
			s = "dark baby pink";
		else if (color == Colors::DarkHotPink)
			s = "dark hot pink";
		else if (color == Colors::DarkSalmon)
			s = "dark salmon";
		else if (color == Colors::DarkViolet)
			s = "dark violet";
		else if (color == Colors::DarkPurple)
			s = "dark purple";
		else if (color == Colors::DarkPeach)
			s = "dark peach";
		else if (color == Colors::DarkLime)
			s = "dark lime";
		else if (color == Colors::DarkMint)
			s = "dark mint";
		else if (color == Colors::DarkGray)
			s = "dark grey";

		// transparent
		else if (color == Colors::Transparent)
			s = "transparent";

		// unknown colour
		else
		{
			if (separateAlpha)
				s = stringFrom(pl::Vector3u{ color.r, color.g, color.b });
			else
				s = "(" + stringFrom(color.r) + ", " + stringFrom(color.g) + ", " + stringFrom(color.b) + ", " + stringFrom(color.a) + ")";
		}
	}
	else
	{
		if (separateAlpha)
			s = stringFrom(pl::Vector3u{ color.r, color.g, color.b });
		else
			s = "(" + stringFrom(color.r) + ", " + stringFrom(color.g) + ", " + stringFrom(color.b) + ", " + stringFrom(color.a) + ")";
	}
	if (separateAlpha && (from.a < 255))
		s += " (alpha: " + stringFrom(from.a) + ")";
	return s;
}

std::string stringFrom(const sf::VideoMode from, bool sizeOnly)
{
	return stringFrom(pl::Size2u{ from.width, from.height }) + (sizeOnly ? "" : " (" + stringFrom(from.bitsPerPixel) + ")");
}

std::string stringFrom(const sf::Keyboard::Key from)
{
	switch (from)
	{
	case sf::Keyboard::Key::A:
		return "A";
	case sf::Keyboard::Key::B:
		return "B";
	case sf::Keyboard::Key::C:
		return "C";
	case sf::Keyboard::Key::D:
		return "D";
	case sf::Keyboard::Key::E:
		return "E";
	case sf::Keyboard::Key::F:
		return "F";
	case sf::Keyboard::Key::G:
		return "G";
	case sf::Keyboard::Key::H:
		return "H";
	case sf::Keyboard::Key::I:
		return "I";
	case sf::Keyboard::Key::J:
		return "J";
	case sf::Keyboard::Key::K:
		return "K";
	case sf::Keyboard::Key::L:
		return "L";
	case sf::Keyboard::Key::M:
		return "M";
	case sf::Keyboard::Key::N:
		return "N";
	case sf::Keyboard::Key::O:
		return "O";
	case sf::Keyboard::Key::P:
		return "P";
	case sf::Keyboard::Key::Q:
		return "Q";
	case sf::Keyboard::Key::R:
		return "R";
	case sf::Keyboard::Key::S:
		return "S";
	case sf::Keyboard::Key::T:
		return "T";
	case sf::Keyboard::Key::U:
		return "U";
	case sf::Keyboard::Key::V:
		return "V";
	case sf::Keyboard::Key::W:
		return "W";
	case sf::Keyboard::Key::X:
		return "X";
	case sf::Keyboard::Key::Y:
		return "Y";
	case sf::Keyboard::Key::Z:
		return "Z";
	case sf::Keyboard::Key::Num0:
		return "0";
	case sf::Keyboard::Key::Num1:
		return "1";
	case sf::Keyboard::Key::Num2:
		return "2";
	case sf::Keyboard::Key::Num3:
		return "3";
	case sf::Keyboard::Key::Num4:
		return "4";
	case sf::Keyboard::Key::Num5:
		return "5";
	case sf::Keyboard::Key::Num6:
		return "6";
	case sf::Keyboard::Key::Num7:
		return "7";
	case sf::Keyboard::Key::Num8:
		return "8";
	case sf::Keyboard::Key::Num9:
		return "9";
	case sf::Keyboard::Key::Escape:
		return "Escape";
	case sf::Keyboard::Key::LControl:
		return "Left Control";
	case sf::Keyboard::Key::LShift:
		return "Left Shift";
	case sf::Keyboard::Key::LAlt:
		return "Left Alt";
	case sf::Keyboard::Key::LSystem:
		return "Left System";
	case sf::Keyboard::Key::RControl:
		return "Right Control";
	case sf::Keyboard::Key::RShift:
		return "Right Shift";
	case sf::Keyboard::Key::RAlt:
		return "Right Alt";
	case sf::Keyboard::Key::RSystem:
		return "Right System";
	case sf::Keyboard::Key::Menu:
		return "Menu";
	case sf::Keyboard::Key::LBracket:
		return "[";
	case sf::Keyboard::Key::RBracket:
		return "]";
	case sf::Keyboard::Key::SemiColon:
		return ";";
	case sf::Keyboard::Key::Comma:
		return ",";
	case sf::Keyboard::Key::Period:
		return ".";
	case sf::Keyboard::Key::Quote:
		return "'";
	case sf::Keyboard::Key::Slash:
		return "/";
	case sf::Keyboard::Key::BackSlash:
		return "\\";
	case sf::Keyboard::Key::Tilde:
		return "~";
	case sf::Keyboard::Key::Equal:
		return "=";
	case sf::Keyboard::Key::Dash:
		return "-";
	case sf::Keyboard::Key::Space:
		return "Space";
	case sf::Keyboard::Key::Return:
		return "Return";
	case sf::Keyboard::Key::BackSpace:
		return "Backspace";
	case sf::Keyboard::Key::Tab:
		return "Tab";
	case sf::Keyboard::Key::PageUp:
		return "Page Up";
	case sf::Keyboard::Key::PageDown:
		return "Page Down";
	case sf::Keyboard::Key::End:
		return "End";
	case sf::Keyboard::Key::Home:
		return "Home";
	case sf::Keyboard::Key::Insert:
		return "Insert";
	case sf::Keyboard::Key::Delete:
		return "Delete";
	case sf::Keyboard::Key::Add:
		return "+ (numpad)";
	case sf::Keyboard::Key::Subtract:
		return "- (numpad)";
	case sf::Keyboard::Key::Multiply:
		return "* (numpad)";
	case sf::Keyboard::Key::Divide:
		return "/ (numpad)";
	case sf::Keyboard::Key::Left:
		return "Left";
	case sf::Keyboard::Key::Right:
		return "Right";
	case sf::Keyboard::Key::Up:
		return "Up";
	case sf::Keyboard::Key::Down:
		return "Down";
	case sf::Keyboard::Key::Numpad0:
		return "0 (numpad)";
	case sf::Keyboard::Key::Numpad1:
		return "1 (numpad)";
	case sf::Keyboard::Key::Numpad2:
		return "2 (numpad)";
	case sf::Keyboard::Key::Numpad3:
		return "3 (numpad)";
	case sf::Keyboard::Key::Numpad4:
		return "4 (numpad)";
	case sf::Keyboard::Key::Numpad5:
		return "5 (numpad)";
	case sf::Keyboard::Key::Numpad6:
		return "6 (numpad)";
	case sf::Keyboard::Key::Numpad7:
		return "7 (numpad)";
	case sf::Keyboard::Key::Numpad8:
		return "8 (numpad)";
	case sf::Keyboard::Key::Numpad9:
		return "9 (numpad)";
	case sf::Keyboard::Key::F1:
		return "F1";
	case sf::Keyboard::Key::F2:
		return "F2";
	case sf::Keyboard::Key::F3:
		return "F3";
	case sf::Keyboard::Key::F4:
		return "F4";
	case sf::Keyboard::Key::F5:
		return "F5";
	case sf::Keyboard::Key::F6:
		return "F6";
	case sf::Keyboard::Key::F7:
		return "F7";
	case sf::Keyboard::Key::F8:
		return "F8";
	case sf::Keyboard::Key::F9:
		return "F9";
	case sf::Keyboard::Key::F10:
		return "F10";
	case sf::Keyboard::Key::F11:
		return "F11";
	case sf::Keyboard::Key::F12:
		return "F12";
	case sf::Keyboard::Key::F13:
		return "F13";
	case sf::Keyboard::Key::F14:
		return "F14";
	case sf::Keyboard::Key::F15:
		return "F15";
	case sf::Keyboard::Key::Pause:
		return "Pause";
	case sf::Keyboard::Key::Unknown:
	default:
		return "Unknown";
	}
}

std::string stringFrom(const sf::Time time)
{
	return stringFrom(time.asSeconds()) + " seconds";
}

std::string stringFrom(const sf::Time time, unsigned int decimalPrecision)
{
	return stringFrom(time.asSeconds(), decimalPrecision) + " seconds";
}

} // namespace plinth
