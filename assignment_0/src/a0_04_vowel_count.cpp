#include <cctype>
#include <iostream>
#include <string>

#include "rm_a0/a0_04_vowel_count.hpp"

int main() {
  std::string line;
  if (!std::getline(std::cin, line)) {
    return 0;
  }

  std::cout << rm_a0::CountVowels(line) << "\n";

  return 0;
}
namespace {
    namespace a0_04_detail {

        bool IsVowelChar(unsigned char c) {
            // TODO: 完成下面函数的实现
            c=std::tolower(c);
            char vowel[]={'a','e','i','o','u'};
            for(int i=0;i<5;i++){
                if(vowel[i]==c)
                return true;
            }
            return false;
        }

    } // namespace a0_04_detail
} // namespace

std::size_t CountVowels(const std::string& line) {
    std::size_t count = 0;
    // TODO: 完成下面函数的实现
    for(char c:line){
        if(a0_04_detail::IsVowelChar(c))
        count++;
    }
        
    return count;
}