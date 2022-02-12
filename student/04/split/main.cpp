#include <iostream>
#include <string>
#include <vector>

std::vector< std::string > split(std::string line, char separator, bool a=false)
{
    std::vector< std::string > new_line;

    int merkki = 0;
    std::string sana = "";

    for(char i : line) {
        if (i != separator) {

            sana.append(1, i);
            merkki = 0;

        } else {

            new_line.push_back(sana);
            sana = "";
            if (a==false and merkki > 1) {
                new_line.push_back("");
            }

            merkki += 1;

            if (a==true and merkki > 1) {
                new_line.pop_back();
            }
        }
    }

    new_line.push_back(sana);

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
