#include <iostream>

#include "rm_a0/a0_02_leap_year.hpp"

int main() {
  int year = 0;
  if (!(std::cin >> year)) {
    return 0;
  }

  std::cout << rm_a0::FormatLeapYearAnswer(rm_a0::IsLeapYear(year));

  return 0;
}
namespace rm_a0 {

bool IsLeapYear(int year){
  if (year % 400 == 0) {
    return true; 
  } else if (year % 100 == 0) {
    return false; 
  } else if (year % 4 == 0) {
    return true; 
  } else {
    return false;
  }
}

std::string FormatLeapYearAnswer(bool is_leap_year){
  std::string ok;
  if(is_leap_year){
    ok="YES\n";
  }else{
    ok="NO\n";
  }
  return ok;
}

// Parses year from input, returns "YES\n" or "NO\n".
// If parsing fails, ok=false and returns empty string.
std::string SolveLeapYear(const std::string &input, bool &ok){
  try {
        int celsius = std::stod(input);
        bool fahrenheit = IsLeapYear(celsius);
        ok = true;
        return FormatLeapYearAnswer(fahrenheit);
        
    } catch (const std::exception&) {
        ok = false;
        return "";
    }
}

} // namespace rm_a0
