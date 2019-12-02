#include <iostream>
#include <string>
#include <utils4cpp/str/UCharCvt.hpp>
#include <utils4cpp/str/UStringCvt.hpp>

template<int Num>
class A 
{
public:
    enum {
        Result = Num * A<Num - 1>::Result
    };
};

template<>
class A<0>
{
public:
    enum {
        Result = 1
    };
};

int main()
{
    int a = sizeof(A<10>);
    //using namespace utils4cpp::str;
    //UStringCvt<std::u16string, std::string>::intern_string_type a;
    //UStringCvt<std::u16string, std::string>::extern_string_type b;
    //auto str = UStringCvt<std::u16string, std::string>::in(std::string("hehe"));
    //auto str1 = UStringCvt<std::string, std::u16string>::in(std::u16string(u"abcdefg"));

    auto& f = std::use_facet<std::codecvt<std::int32_t, char, std::mbstate_t>>(std::locale());
    int b = f.max_length();

    int res = A<10>::Result;
    return 0;
}