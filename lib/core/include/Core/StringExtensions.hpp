#ifndef INCLUDED_ADVENT_OF_CODE_CORE_STRING_EXTENSIONS_HPP_
#define INCLUDED_ADVENT_OF_CODE_CORE_STRING_EXTENSIONS_HPP_

#include <vector>
#include <string>

class StringExtensions
{
public:
    static std::string loadFileToString(const std::string& _path);
    static std::vector<std::string> splitStringByDelimeter(const std::string& _parameter, const std::string& _delimeter);

    static std::size_t hash(const std::string& _string);
    
    static std::vector<std::string> splitStringByLines(const std::string& _string);
    static std::vector<std::string> splitStringByString(const std::string& _string, const std::string& _splitString);

    static bool startsWith(const std::string& _str, const std::string& _start);
    static bool endsWith(const std::string& _str, const std::string& _end);

    static std::string stripLeadingWhitespace(const std::string& _str);

    static void replaceAll(std::string& _string, const std::string& _substring, const std::string& _replacement);

    template <typename T>
    static std::vector<T> splitLineToNumbers(const std::string& line, const std::string& delimiter)
    {
        std::vector<T> nums;

        for (const auto& numToken : splitStringByDelimeter(line, delimiter))
        {
            nums.emplace_back((T)std::stoll(numToken));
        }

        return nums;
    }

private:
    StringExtensions(void) = delete;
    ~StringExtensions(void) = delete;
};

#endif // INCLUDED_ADVENT_OF_CODE_CORE_STRING_EXTENSIONS_HPP_