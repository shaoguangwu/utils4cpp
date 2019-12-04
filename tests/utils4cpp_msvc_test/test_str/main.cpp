#include <iostream>
#include <string>
#include <utils4cpp/str/UCharCvt.hpp>
#include <utils4cpp/str/UStringCvt.hpp>
#include <utils4cpp/str/UStringTraits.hpp>

enum A {
    AX = 0,
    AY
};

template<A a>
void ppp(int b)
{
    if constexpr (a == AX) {
        std::cout << "X" << std::endl;
    }
    else
    {
        static_assert(a != AX);
    }
}

int main()
{
    using namespace utils4cpp::str;
    std::string str("abcdefg");
    auto wstr = UStringCvt<std::wstring, std::string>::in(str);
    auto u16str = UStringCvt<std::u16string, std::string>::in(str);
    auto u32str = UStringCvt<std::u32string, std::string>::in(str);
    auto str1 = UStringCvt<std::string, std::string>::in(str);

    //UStringCvt<std::wstring, std::string>::intern_char_type dd;
    //UStringCvt<std::string_view, std::string>::intern_char_type ddd;

    ppp<A::AY>(2);

    return 0;
}