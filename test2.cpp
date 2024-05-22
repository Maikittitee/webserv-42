// C++ program to demonstrate functioning of substr()
#include <iostream>
#include <string>

#include <iostream>
#include <string>

// Function to trim leading and trailing tabs from a string
std::string trim(std::string line) {
  size_t start;
  size_t end;

  start = line.find_first_not_of('\t');  // Look for first non-tab character
  end = line.find_last_not_of('\t');    // Look for last non-tab character (reverse search)
	std::cout << std::endl;
	std::cout << "start : " << start << std::endl;
	std::cout << "end : " << end << std::endl;

  // Original condition (returns original string if no non-tab characters)
  if (start != std::string::npos && end != 0) {
    return line.substr(start, end - start + 1);  // Extract substring excluding tabs
  }

  // Optional modification: Return empty string if only tabs
  // Uncomment this block if you want to return an empty string for all-tabs input
  // else {
  //   return "";  // Return empty string if only tabs
  // }

  return line;  // Default: Return original string (original behavior)
}

int main() {
  std::string str1 = "\t\t with tabs \t\t";
  std::string str2 = "\t\t\t";  // String with only tabs
  std::string str3 = "No tabs here";

  // Trim the strings and print the results
//   std::cout << "Original string 1: " << str1 << std::endl;
//   std::cout << "Trimmed string 1: " << trim(str1) << std::endl;

//   // Comment out the next line if you want to return an empty string for all-tabs input
//   std::cout << "Original string 2 (all tabs): " << str2 << std::endl;
//   std::cout << "Trimmed string 2: " << trim(str2) << std::endl;

  std::cout << "Original string 3: " << str3 << std::endl;
//   std::cout << "Trimmed string 3: " << trim(str3) << std::endl;

  return 0;
}
