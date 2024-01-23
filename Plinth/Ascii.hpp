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

#include "Common.hpp"

namespace plinth
{
	namespace Ascii
	{

namespace Controls
{

	// control code constants (from the lists here: http://en.wikipedia.org/wiki/ASCII and here: http://www.theasciicode.com.ar/)
	constexpr unsigned char Null{ 0_uc };
	constexpr unsigned char StartOfHeader{ 1_uc };
	constexpr unsigned char StartOfText{ 2_uc };
	constexpr unsigned char EndOfText{ 3_uc };
	constexpr unsigned char EndOfTransmission{ 4_uc };
	constexpr unsigned char Enquiry{ 5_uc };
	constexpr unsigned char Acknowledgment{ 6_uc };
	constexpr unsigned char Bell{ 7_uc };
	constexpr unsigned char Backspace{ 8_uc };
	constexpr unsigned char HorizontalTab{ 9_uc };
	constexpr unsigned char LineFeed{ 10_uc };
	constexpr unsigned char VerticalTab{ 11_uc };
	constexpr unsigned char FormFeed{ 12_uc };
	constexpr unsigned char CarriageReturn{ 13_uc };
	constexpr unsigned char ShiftOut{ 14_uc };
	constexpr unsigned char ShiftIn{ 15_uc };
	constexpr unsigned char DataLinkEscape{ 16_uc };
	constexpr unsigned char DeviceControl1{ 17_uc };
	constexpr unsigned char DeviceControl2{ 18_uc };
	constexpr unsigned char DeviceControl3{ 19_uc };
	constexpr unsigned char DeviceControl4{ 20_uc };
	constexpr unsigned char NegativeAcknowledgment{ 21_uc };
	constexpr unsigned char SynchronousIdle{ 22_uc };
	constexpr unsigned char EndOfTransmissionBlock{ 23_uc };
	constexpr unsigned char Cancel{ 24_uc };
	constexpr unsigned char EndOfMedium{ 25_uc };
	constexpr unsigned char Substitute{ 26_uc };
	constexpr unsigned char Escape{ 27_uc };
	constexpr unsigned char FileSeparator{ 28_uc };
	constexpr unsigned char GroupSeparator{ 29_uc };
	constexpr unsigned char RecordSeparator{ 30_uc };
	constexpr unsigned char UnitSeparator{ 31_uc };
	constexpr unsigned char Delete{ 127_uc };

	// aliases
	constexpr unsigned char Newline{ LineFeed };
	constexpr unsigned char Return{ CarriageReturn };
	constexpr unsigned char Tab{ HorizontalTab };
	constexpr unsigned char XOn{ DeviceControl1 };
	constexpr unsigned char XOff{ DeviceControl3 };
	constexpr unsigned char CtrlZ{ Substitute };
	constexpr unsigned char EndOfFile{ Substitute };
	//const unsigned char EOF{ EndOfFile };

} // namespace Controls
namespace Characters
{
	namespace Standard
	{

		// character constants
		constexpr unsigned char Space{ 32_uc };

	} // namespace Standard
	namespace Extended
	{
		namespace Set1
		{

			// (as listed here: http://www.theasciicode.com.ar/)
			constexpr unsigned char Pound{ 156_uc };
			constexpr unsigned char Multiply{ 158_uc };
			constexpr unsigned char Function{ 159_uc };
			constexpr unsigned char Registered{ 169_uc };
			constexpr unsigned char Copyright{ 184_uc };
			constexpr unsigned char Cent{ 189_uc };
			constexpr unsigned char Yen{ 190_uc };
			constexpr unsigned char Pipe{ 221_uc };
			constexpr unsigned char Divide{ 246_uc };
			constexpr unsigned char Degree{ 248_uc };

		} // namespace Set1
		namespace Iso88591
		{

			// (as listed here: http://www.ascii-code.com/ - "ISO 8859-1, also called ISO Latin-1")
			constexpr unsigned char Euro{ 128_uc };
			constexpr unsigned char Function{ 131_uc };
			constexpr unsigned char Bullet{ 149_uc };
			constexpr unsigned char EnDash{ 150_uc };
			constexpr unsigned char EmDash{ 151_uc };
			constexpr unsigned char TradeMark{ 153_uc };
			constexpr unsigned char Cent{ 162_uc };
			constexpr unsigned char Pount{ 163_uc };
			constexpr unsigned char Currency{ 164_uc };
			constexpr unsigned char Yen{ 165_uc };
			constexpr unsigned char Pipe{ 166_uc };
			constexpr unsigned char Copyright{ 169_uc };
			constexpr unsigned char RegisteredTradeMark{ 174_uc };
			constexpr unsigned char Degree{ 176_uc };
			constexpr unsigned char PlusMinus{ 177_uc };
			constexpr unsigned char Micro{ 181_uc };
			constexpr unsigned char MiddleDot{ 183_uc };
			constexpr unsigned char OneQuarter{ 188_uc };
			constexpr unsigned char OneHalf{ 189_uc };
			constexpr unsigned char ThreeQuarters{ 190_uc };
			constexpr unsigned char Multiply{ 215_uc };
			constexpr unsigned char Divide{ 247_uc };

			// aliases
			constexpr unsigned char Registered{ RegisteredTradeMark };
			constexpr unsigned char Quarter{ OneQuarter };
			constexpr unsigned char Half{ OneHalf };

		} // namespace Iso88591
	} // namespace Extended
} // namespace Characters

	} // namespace Ascii
} // namespace plinth
