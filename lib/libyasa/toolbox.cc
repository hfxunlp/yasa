/*

Copyright 2013 RALI

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/  

using namespace std;

#include <cctype>
#include <wctype.h>
#include <wchar.h>
#include <boost/algorithm/string.hpp>
#include <sstream>

#include "toolbox.h"

namespace japa {

// ------------------------------------------------------------------------ //
//std::string& stripAccents( std::string& str )
wstring& stripAccents(wstring& str) {

	static const wstring accents(L"ÇÑSÝÌÍÎÏÒÓÔÕÖÀÁÂÃÄÅÈÉÊËÙÚÛÜçñsýìíîïòóôõöàáâãäåèéêëùúûü«»");
	static const wstring normal(L"CNSYIIIIOOOOOAAAAAAEEEEUUUUcnsyiiiioooooaaaaaaeeeeuuuu\"\"");

	wstring::size_type pos;

	//wcout << "str was: " << str << endl;

	// Change l'accent de chaque caract�re.
	for (size_t i = 0; i < str.size(); i++) {

		pos = accents.find( str[ i ] );

		if( pos != wstring::npos )
			// Un caract�re accentu� a �t� trouv�, il faut le remplacer.
			str[i] = normal[pos];
	}

	//wcout << "str now is: " << str << endl;
	return str;
}

// ------------------------------------------------------------------------ //
int stripSpaces(std::wistream& in) {
	int nb = 0;

	while (in.good() && isspace(in.peek())) {
		in.get();
		nb++;
	}

	return nb;
}

// ------------------------------------------------------------------------ //
bool isAlphabetic(const wstring& str) {
	bool valid = true;

	// On regarde si tous les caract�res sont alphab�tiques
	for (wstring::size_type i = 0; i < str.size() && valid; i++) {

		if (!iswalpha(str[i])) {
			valid = false;
		}
	}

	return valid;
}

// ------------------------------------------------------------------------ //
wstring& toUpperCase(wstring& str) {

	for (wstring::size_type i = 0; i < str.size(); i++) {

		if (iswalpha(str[i]))
		   str[i] = (wchar_t)towupper(str[i]);
	}

	return str;
}

// ------------------------------------------------------------------------ //
bool isDelimiter( wchar_t c) {
	static const std::wstring DELIMITERS = L" \t\n\',.;\"\()[]:<>?!=/{}";

	return DELIMITERS.find(c) != wstring::npos;
}

// ------------------------------------------------------------------------ //
bool isWordDelimiter( wchar_t c) {
	static const wstring DELIMITERS = L",.;\"()[]:<>?!=/{}";

	return DELIMITERS.find(c) != wstring::npos;
}

// ------------------------------------------------------------------------ //
wstring strToWstr( string str )
{
    wchar_t buf[100];
    size_t num_chars = mbstowcs(buf, str.c_str(), str.size());
    wstring ws(buf, num_chars);

    return ws;
}
// ------------------------------------------------------------------------ //

}    // namespace japa
