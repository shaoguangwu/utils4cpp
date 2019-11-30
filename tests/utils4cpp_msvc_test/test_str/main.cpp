#include <iostream>
#include <string>
#include <utils4cpp/str/UCharCvt.hpp>
#include <utils4cpp/str/UStringCvt.hpp>

int main()
{
    using namespace utils4cpp::str;
    UStringCvt<std::u16string, std::string>::intern_string_type a;
    UStringCvt<std::u16string, std::string>::extern_string_type b;
    auto str = UStringCvt<std::u16string, std::string>::in(std::string("hehe"));
    return 0;

    //using InT = char;
    //using OuT = char16_t;

    //auto& f = std::use_facet<std::codecvt<InT, OuT, std::mbstate_t>>(std::locale());
    //char a = 'a';
    //std::basic_string<OuT> external(2, OuT(a));

    //std::mbstate_t mb = std::mbstate_t();
    //std::basic_string<InT> internal(external.size(), '\0');
    //const OuT* from_next;
    //InT* to_next;
    //std::codecvt_base::result res = f.in(mb, &external[0], &external[external.size()], from_next,
    //    &internal[0], &internal[internal.size()], to_next);
    //internal.resize(to_next - &internal[0]);

    //std::u16string u16str(internal.begin(), internal.end());

    //return 0;
    //std::wcout << L"The string in wide encoding: " << internal << '\n';
}