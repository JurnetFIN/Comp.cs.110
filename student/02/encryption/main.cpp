#include <iostream>

using namespace std;

int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    int pituus = 0;
    pituus = key.length();
    if (pituus != 26) {
        cout << "Error! The encryption key must contain 26 characters." << endl;
        return EXIT_FAILURE;
    }

    int ind = 0;
    while (ind < 26){
        int ascii = static_cast < int > (key[ind]);
        if (ascii > 122 or
                ascii < 97){
            cout << "Error! The encryption key must contain only"
            " lower case characters." << std::endl;
            return EXIT_FAILURE;
            }
        ind += 1;
    }

    for( char kirjain = 'a'; kirjain <= 'z'; ++kirjain) {
        if(key.find(kirjain) == string::npos){
            cout<< "Error! The encryption key must contain all "
            "alphabets a-z."<< endl;
            return EXIT_FAILURE;
        }
    }
    string salattava = "";
    cout<< "Enter the text to be encrypted: ";
    cin >> salattava;

    int indx = 0;
    int pituusx = salattava.length();
    while (indx < pituusx){
        int ascii = static_cast < int > (salattava[indx]);
        if (ascii > 122 or
                ascii < 97){
            cout << "Error! The text to be encrypted must contain only"
            " lower case characters." << std::endl;
            return EXIT_FAILURE;
        }
        indx += 1;
    }

    string salattu = "";
    pituus = salattava.length();
    for (int luku = 0; luku < pituus; ++luku){
        int ascii = static_cast < int > (salattava[luku]);
        salattu += key[ascii-97];
    }

    std::cout << "Encrypted text: " << salattu << std::endl;

    return EXIT_SUCCESS;
}

