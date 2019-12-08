#include <iostream>
#include <string>
#include <utils4cpp/str/UCharCvt.hpp>
#include <utils4cpp/str/UStringCvt.hpp>
#include <utils4cpp/str/UStringTraits.hpp>

#include <string_view>

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

    std::string str11("Abcd"), str22("abcd");
    int r = UStringTraits<std::string>::compare<UCaseInsensitive>(str11, str22);

    std::string str33("aaaaa");
    std::string_view v = "abc";
    auto list = UStringTraits<std::string>::split<UCaseInsensitive>(str33, "abc", true);

    std::string str44("acdba");
    std::vector<char> seps{ 'g', 'h', 'G' };
    auto list1 = UStringTraits<std::string>::split(str44, seps, false);

    const char* s = "abcdabab";
    std::string t1 = s;
    std::string t2 = s;
    std::string b = "ab";
    std::string af1 = "kk";
    std::string af2 = "gggg";
    auto s1 = UStringTraits<std::string>::replace(t1, b, af1);
    auto s2 = UStringTraits<std::string>::replaceRnth(t2, b, af2, 1);

    ppp<A::AY>(2);

    return 0;
}
