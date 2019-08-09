#ifndef __CASE_H
#define __CASE_H

#include <string>

// UWAGA: Poniższe funkcje to rozwiązanie tymczasowe ponieważ nie działa z
// kodowaniem unicode (z tego co wiem to akceptuje tylko ascii)
//
// Docelowo możnaby skorzystać z biblioteki ICU http://site.icu-project.org/

namespace Strings
{

void lower(std::string& str);
std::string lower_copy(const std::string& str);

}

#endif
