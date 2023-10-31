#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

// Fields in the input file
const int NUMBER_OF_FIELDS = 5;

// Command prompt
const string PROMPT = "the> ";

// Error and other messages
const string EMPTY_FIELD = "Error: empty field in line ";
const string FILE_ERROR = "Error: input file cannot be opened";
const string WRONG_PARAMETERS = "Error: wrong number of parameters";
const string THEATRE_NOT_FOUND = "Error: unknown theatre";
const string PLAY_NOT_FOUND = "Error: unknown play";
const string PLAYER_NOT_FOUND = "Error: unknown player";
const string TOWN_NOT_FOUND = "Error: unknown town";
const string COMMAND_NOT_FOUND = "Error: unknown command";
const string NOT_AVAILABLE = "No plays available";


struct Play {
    string actor;
    string title;
    int free_seats;
};

struct Theatre {
    string town;
    string name;
    map<string, Play> plays;
};

// Casual split func, if delim char is between "'s, ignores it.
vector<string> split(const string& str, char delim = ';')
{
  vector<string> result = {""};
  bool inside_quotation = false;
  for ( char current_char : str )
    {
      if ( current_char == '"' )
        {
          inside_quotation = not inside_quotation;
        }
      else if ( current_char == delim and not inside_quotation )
        {
          result.push_back("");
        }
      else
        {
          result.back().push_back(current_char);
        }
    }
  if ( result.back() == "" )
    {
      result.pop_back();
    }
  return result;
}


bool isFormat(ifstream & file_object)
{
    // Tarkistetaan, voiko tiedostoa avata
       if (not file_object) {
           cout << FILE_ERROR << endl;
           return false;
       }

       // Luetaan tiedoston rivit yksi kerrallaan
       string row;
       vector<string> splitted_row;
       while(getline(file_object, row)) {
           // Jaetaan rivi osiin
           splitted_row = split(row, ';');

           // Tarkistetaan, että rivi sisältää viisi osaa ja että ne eivät
           // ole tyhjiä
           if(splitted_row.size() != NUMBER_OF_FIELDS || find(splitted_row.begin(),
               splitted_row.end(), "") != splitted_row.end()) {
               cout << EMPTY_FIELD << endl;
               return false;
           }
       }

       return true;
}


// Main function
int main()
{
    // Alustetaan vektori, johon tallennetaan teatterien tietueet
    vector<struct Theatre> theatries;

    string file_name = "";
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream file_object(file_name);


    // Kokeillaan tiedoston lukemista
    // Jos lukeminen ei onnistu lopetetaan ohjelman suoritus
    if (isFormat(file_object) == false) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
