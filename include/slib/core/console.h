/*
 *   Copyright (c) 2008-2018 SLIBIO <https://github.com/SLIBIO>
 *
 *   Permission is hereby granted, free of charge, to any person obtaining a copy
 *   of this software and associated documentation files (the "Software"), to deal
 *   in the Software without restriction, including without limitation the rights
 *   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *   copies of the Software, and to permit persons to whom the Software is
 *   furnished to do so, subject to the following conditions:
 *
 *   The above copyright notice and this permission notice shall be included in
 *   all copies or substantial portions of the Software.
 *
 *   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 *   THE SOFTWARE.
 */

#ifndef CHECKHEADER_SLIB_CORE_CONSOLE
#define CHECKHEADER_SLIB_CORE_CONSOLE

#include "definition.h"

#include "string.h"
#include "object.h"
#include "list.h"
#include "variant.h"

namespace slib
{
	
	class SLIB_EXPORT Console
	{
	public:
		static void print(const String& s);

		template <class... ARGS>
		static void print(const String& format, ARGS&&... args);
	
		static void println(const String& s);

		template <class... ARGS>
		static void println(const String& format, ARGS&&... args);
	
		static String readLine();

		static sl_char16 readChar(sl_bool flagPrintEcho = sl_false);

	};
	
	template <class... ARGS>
	void Printf(const String& format, ARGS&&... args);
	
	template <class... ARGS>
	void Println(const String& format, ARGS&&... args);
	
}

#include "detail/console.inc"

#endif
