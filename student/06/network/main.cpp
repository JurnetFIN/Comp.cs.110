#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";


std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

int depth(const map<string,vector<string>>& verkko,
           const string& henkilo, int montako, int& pisin){
    if (verkko.at(henkilo).size()==0){
        if (montako > pisin){
            pisin = montako;}
        --montako;
         //cout << montako << pisin << henkilo << endl;
    } else {
        ++montako;
    }

    for (auto henkilox : verkko.at(henkilo)){
        depth(verkko, henkilox, montako, pisin); }
    return pisin;
}

int count(map<string,vector<string>> verkko, string henkilo, int& montako){
    for (auto henkilox : verkko.at(henkilo)){
        ++montako;
        count(verkko, henkilox, montako); }
    return montako;
}

void print(const map<string, vector<string>> verkko, string id,
           int laskin, bool miinustettu) {
    int i = 0;
    miinustettu = false;
    while (i < laskin){
        cout << "..";
        i += 1;
    }

    cout << id << endl;

    if (verkko.find(id) == verkko.end()){
        return;
    }

    for (auto& idx : verkko.at(id)){
        laskin += 1;
        if (miinustettu){
            laskin -= 1;
            miinustettu = false;
        } else {
            print(verkko, idx, laskin, miinustettu);
            laskin -= 1;
        }
    }
}

map<string,vector<string>> store(map<string, vector<string>> verkko, string id1, string id2) {

    vector<string> tyhja_nimilista;

    map<string, vector<string>>::iterator nimi;
    nimi = verkko.find(id1);
    if (nimi == verkko.end()) {
        vector<string> nimilista;
        nimilista.push_back(id2);

        verkko.insert(pair<string, vector<string>>(id1, nimilista));
        verkko.insert(pair<string, vector<string>>(id2, tyhja_nimilista));

    } else {
        verkko[id1].push_back(id2);
        verkko.insert(pair<string, vector<string>>(id2, tyhja_nimilista));

    }
    return verkko;
}

int main()
{

    map<string, vector<string>> verkko;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            verkko = store(verkko, id1, id2);

        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int laskin = 0;
            bool arvo = false;
            print(verkko, id, laskin, arvo);

        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int i = 0;
            cout << count(verkko, id, i) << endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            int montako = 1;
            int pisin = 0;
            cout << depth(verkko, id, montako, pisin) << endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
