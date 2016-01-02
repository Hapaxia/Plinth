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

#ifndef PLINTH_ASCII_HPP
#define PLINTH_ASCII_HPP

#include "Common.hpp"

namespace plinth
{
	namespace Ascii
	{

namespace Controls
{

	// control code constants (from the lists here: http://en.wikipedia.org/wiki/ASCII and here: http://www.theasciicode.com.ar/)
	const unsigned char Null{ 0 };
	const unsigned char StartOfHeader{ 1 };
	const unsigned char StartOfText{ 2 };
	const unsigned char EndOfText{ 3 };
	const unsigned char EndOfTransmission{ 4 };
	const unsigned char Enquiry{ 5 };
	const unsigned char Acknowledgment{ 6 };
	const unsigned char Bell{ 7 };
	const unsigned char Backspace{ 8 };
	const unsigned char HorizontalTab{ 9 };
	const unsigned char LineFeed{ 10 };
	const unsigned char VerticalTab{ 11 };
	const unsigned char FormFeed{ 12 };
	const unsigned char CarriageReturn{ 13 };
	const unsigned char ShiftOut{ 14 };
	const unsigned char ShiftIn{ 15 };
	const unsigned char DataLinkEscape{ 16 };
	const unsigned char DeviceControl1{ 17 };
	const unsigned char DeviceControl2{ 18 };
	const unsigned char DeviceControl3{ 19 };
	const unsigned char DeviceControl4{ 20 };
	const unsigned char NegativeAcknowledgment{ 21 };
	const unsigned char SynchronousIdle{ 22 };
	const unsigned char EndOfTransmissionBlock{ 23 };
	const unsigned char Cancel{ 24 };
	const unsigned char EndOfMedium{ 25 };
	const unsigned char Substitute{ 26 };
	const unsigned char Escape{ 27 };
	const unsigned char FileSeparator{ 28 };
	const unsigned char GroupSeparator{ 29 };
	const unsigned char RecordSeparator{ 30 };
	const unsigned char UnitSeparator{ 31 };
	const unsigned char Delete{ 127 };

	// aliases
	const unsigned char Newline{ LineFeed };
	const unsigned char Return{ CarriageReturn };
	const unsigned char Tab{ HorizontalTab };
	const unsigned char XOn{ DeviceControl1 };
	const unsigned char XOff{ DeviceControl3 };
	const unsigned char CtrlZ{ Substitute };
	const unsigned char EndOfFile{ Substitute };
	//const unsigned char EOF{ EndOfFile };

} // namespace Controls
namespace Characters
{
	namespace Standard
	{

		// character constants
		const unsigned char Space{ 32 };

	} // namespace Standard
	namespace Extended
	{
		namespace Set1
		{

			// (as listed here: http://www.theasciicode.com.ar/)
			const unsigned char Pound{ short int(156) };
			const unsigned char Multiply{ 158 };
			const unsigned char Function{ 159 };
			const unsigned char Registered{ 169 };
			const unsigned char Copyright{ 184 };
			const unsigned char Cent{ 189 };
			const unsigned char Yen{ 190 };
			const unsigned char Pipe{ 221 };
			const unsigned char Divide{ 246 };
			const unsigned char Degree{ 248 };

		} // namespace Set1
		namespace Iso88591
		{

			// (as listed here: http://www.ascii-code.com/ - "ISO 8859-1, also called ISO Latin-1")
			const unsigned char Euro{ 128 };
			const unsigned char Function{ 131 };
			const unsigned char Bullet{ 149 };
			const unsigned char EnDash{ 150 };
			const unsigned char EmDash{ 151 };
			const unsigned char TradeMark{ 153 };
			const unsigned char Cent{ 162 };
			const unsigned char Pount{ 163 };
			const unsigned char Currency{ 164 };
			const unsigned char Yen{ 165 };
			const unsigned char Pipe{ 166 };
			const unsigned char Copyright{ 169 };
			const unsigned char RegisteredTradeMark{ 174 };
			const unsigned char Degree{ 176 };
			const unsigned char PlusMinus{ 177 };
			const unsigned char Micro{ 181 };
			const unsigned char MiddleDot{ 183 };
			const unsigned char OneQuarter{ 188 };
			const unsigned char OneHalf{ 189 };
			const unsigned char ThreeQuarters{ 190 };
			const unsigned char Multiply{ 215 };
			const unsigned char Divide{ 247 };

			// aliases
			const unsigned char Registered{ RegisteredTradeMark };
			const unsigned char Quarter{ OneQuarter };
			const unsigned char Half{ OneHalf };

		} // namespace Iso88591
	} // namespace Extended
} // namespace Characters

	} // namespace Ascii
} // namespace plinth
#endif // PLINTH_ASCII_HPP
