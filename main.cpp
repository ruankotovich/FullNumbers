#include "xYah_fullnumbers.hpp"

template <typename _Tp>
void assert(const _Tp& X, const _Tp& Y)
{
    if ((X) != (Y)) {
        std::cout << "Not equals : " << X << " and " << Y << std::endl;
        throw "Error parsing numbers";
    }
}

int main()
{
    FullNumber::FullNumberParser parser;
    std::string search;
    size_t expected;
    size_t got;
    try {
        std::string word;

        while (std::getline(std::cin, word)) {
            size_t seek = word.find(':');
            search = word.substr(0, seek);
            expected = atoll(word.substr(seek + 1, word.size() - 1).c_str());
            got = parser.parse(search);
            std::cout << search << " (Expected : " << expected << " <-> Got : " << got << ")" << std::endl;
            assert(got, expected);
        }

        std::cout << "Everything went okay" << std::endl;
    } catch (const char* ex) {
        std::cout << "On " << search << " : " << ex << std::endl;
    }
}