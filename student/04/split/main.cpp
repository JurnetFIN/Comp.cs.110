#include <iostream>
#include <string>
#include <vector>

std::vector< std::string > split(std::string line, char seperator, bool a=false)
{
    std::vector< std::string > new_line;

    int b = 0;

    for(char i : line) {
        if (i != seperator) {
            std::string tmp_string;
            tmp_string.insert(0, 1, i);

            new_line.push_back(tmp_string);

        } else {
            if (a == false) {
                new_line.push_back("");
            }
        b += 1;
        }
    }
    return new_line;
}

int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();


    std::vector<std::string> parts = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector<std::string> parts_no_empty = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
