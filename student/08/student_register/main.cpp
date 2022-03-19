#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string>
#include <vector>
#include <map>

using namespace std;

const string HELP_TEXT = "N                  = List ordered by student numbers\n"
                              "U                  = List ordered alphabetically by user ids\n"
                              "C <student_number> = Change the given student's phone number\n"
                              "Q                  = Quit\n";

struct Student {
    string student_number;
    string user_id;
    string name;
    string phone_number;
    string email;
    string skype;
};

vector<string> split(const string& s,
                     const char delimiter,
                     const bool ignore_empty = false) {
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos) {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty())) {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty())) {
        result.push_back(tmp);
    }
    return result;
}


bool read_data(const string& file_name,
               map<string, Student* >& alphabetical_order,
               map<string, Student* >& numerical_order) {
    ifstream file_object(file_name);
    if( !file_object ) {
        return false;
    }

    string line = "";

    while( getline( file_object, line ) ) {
        vector<string> parts = split(line, ';');
        if(parts.size() != 6) {
            return false;
        }

        Student* new_student = new Student({parts[0],
                                            parts[1],
                                            parts[2],
                                            parts[3],
                                            parts[4],
                                            parts[5]});
        numerical_order[parts[0]] = new_student;
        alphabetical_order[parts[1]] = new_student;
    }
    file_object.close();
    return true;
}


void print_data(const Student& s) {
    std::cout << s.student_number << " " << s.user_id << std::endl
              << s.name << std::endl
              << s.phone_number << std::endl
              << s.email << std::endl
              << s.skype << std::endl << std::endl;
}

bool is_valid_phone_number(const string number) {
    for(unsigned int i = 0; i < number.length(); ++i) {
        if(!(('0' <= number[i] and number[i] <= '9')
             or number[i] == ' '
             or number[i] == '-')) {
            cout << "Erroneous phone number: "
                      << number
                      << std::endl << std::endl;
            return false;
        }
    }
    return true;
}

void write_file(string file_name, string student_number, string new_phone_number) {
    string output_file = "output.txt";
    ifstream file_in(file_name);
    ofstream file_out(output_file);

    string line = "";
    const char * old_name = file_name.c_str();
    const char * new_name = output_file.c_str();

    while( getline(file_in, line )) {
        vector<string> parts = split(line, ';');
        if (parts.at(0) == student_number) {
            parts.at(3) = new_phone_number;
            line.clear();
            string prefix = "";
            for(unsigned int i = 0; i < 6; ++i) {
                line.append(prefix);
                line.append(parts.at(i));
                prefix = ";";
            }
        }
        file_out << line << endl;
    }
    file_in.close();
    file_out.close();
    remove(old_name);
    rename(new_name, old_name);
}

int main() {
    string file_name = "";
    cout << "Student file: ";
    getline(cin, file_name);

    map<string, Student* > user_ids;
    map<string, Student* > student_numbers;
    if(not read_data(file_name, user_ids, student_numbers)) {
        cout << "Error in reading file!" << endl;
        return EXIT_FAILURE;
    }

    cout << HELP_TEXT << endl;

    while(true) {
        string line;
        cout << "register> ";
        getline(cin, line);
        vector<string> parts = split(line, ' ', true);

        if(parts.empty()) {
            continue;
        }
        string command = parts.at(0);

        // Printing in alphabetical order by user ids
        if(command == "U" or command == "u") {
            if(parts.size() != 1) {
                cout << "Erroneous parameters!" << endl  << HELP_TEXT;
                continue;
            } else {
                for(auto pair: user_ids) {
                    print_data(*(pair.second));
                }
            }

            // Printing in numerical order by student numbers
        } else if(command == "N" or command == "n") {
            if(parts.size() != 1){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            } else {
                for(auto pair: student_numbers) {
                    print_data(*(pair.second));
                }
            }

            // Changing student data
        } else if(command == "C" or command == "c") {
            if(parts.size() != 2){
                cout << "Erroneous parameters!" << endl << HELP_TEXT;
                continue;
            }
            bool name = false;
            for(auto pair: user_ids) {
                if ((*(pair.second)).student_number == parts.at(1)) {
                    name = true;
                    string phone_number;
                    cout << "Enter a new phone number: ";
                    getline(cin, phone_number);
                    cout << "" << endl;
                    if (is_valid_phone_number(phone_number)) {
                        write_file(file_name, (*(pair.second)).student_number, phone_number);
                        (*(pair.second)).phone_number = phone_number;
                    }
                }
            }
            if (name == false) {
                cout << "There is no student with the given number!" << endl;
                cout << "" << endl;
            }

        } else if(command == "Q" or command == "q") {
            // Deleting the data structure: deallocating memory
            // and nullifying pointers
            for(auto pair: student_numbers) {
                pair.second = nullptr;
            }

            for(auto pair: user_ids) {
                delete pair.second;
                pair.second = nullptr;
            }

            return EXIT_SUCCESS;
        } else {
            cout << "Erroneous command!" << endl << HELP_TEXT;
        }
    }
}
