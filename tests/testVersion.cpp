#include <iostream>
#include <utils4cpp/core/Version.h>

int main()
{
    std::cout << UTILS4CPP_VERSION_STR << std::endl;
    std::wcout << UTILS4CPP_VERSION_WSTR << std::endl;

    return 0;
}