#ifndef __DEMANGLED_TYPE_NAME_H
#define __DEMANGLED_TYPE_NAME_H

#include <cxxabi.h>
#include <typeinfo> 
#include <string>

// http://gcc.gnu.org/onlinedocs/libstdc++/manual/ext_demangling.html

// nie działa z aliasami, informacja o aliasach znika w momencie kompilacji.
// Jest możliwe obejście tego problemu przez stringize/stringify macro,
// ale na razie nie chcę się w to zagłębiać
// https://stackoverflow.com/questions/49411422/return-alias-identificator-instead-of-type-in-typeidsome-type-name

namespace Core
{

template <typename T>
std::string getDemangledTypeName()
{
	int status;
	return abi::__cxa_demangle(typeid(T).name(), 0, 0, &status);
}

} // namespace Core

#endif // __DEMANGLED_TYPE_NAME_H
