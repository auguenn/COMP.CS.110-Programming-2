#include <iostream>
#include <string>

using namespace std;

bool check_lenght(string& key)
{
    if (key.size() != 26) {
        return false;
    }
    else {
        return true;
    }
}

bool is_lower(string& key)
{
    int size = 26;
    for (int i = 0 ; i < size ; ++i) {
        if (isupper(key.at(i))) {
            return false;
        }
    }
    return true;
}

int main()
{
    string key = "";
    cout << "Enter the encryption key: ";
    getline(cin, key);

    if (!check_lenght(key)) {
        cout << "Error! The encryption key must contain 26 characters." <<endl;
        return EXIT_FAILURE;
    }

    if (!is_lower(key)) {
        cout << "Error! The encryption key must contain only lower case characters." <<endl;
        return EXIT_FAILURE;
    }

    char temp = 1;
       for (char c : key) {
           if (c == temp) {
               cout << "Error! The encryption key must contain all alphabets a-z." << endl;
               return 1;
           } else {
               temp = c;
           }
       }

       // getting the text to be encrypted from the user
       cout << "Enter the text to be encrypted: ";
       string text_to_be_encrypted = "";
       cin >> text_to_be_encrypted;

       // encrypt the text
       string encrypted_text = "";
       for (char c : text_to_be_encrypted) {
           encrypted_text += key.at(c-97);
       }

       // print the encrypted key
       cout << "Encrypted text: " << encrypted_text << endl;
       return 0;

}
