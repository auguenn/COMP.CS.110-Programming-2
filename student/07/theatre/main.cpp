#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>

using namespace std;

const int NUMBER_OF_FIELDS = 5;

const string PROMPT = "the> ";

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

vector<string> split(const string& str, char delim = ';') {
    vector<string> result = {""};
    bool inside_quotation = false;
    for (char current_char : str) {
        if (current_char == '"') {
            inside_quotation = !inside_quotation;
        } else if (current_char == delim && !inside_quotation) {
            result.push_back("");
        } else {
            result.back().push_back(current_char);
        }
    }
    if (result.back().empty()) {
        result.pop_back();
    }
    return result;
}

void addPlayToStructure(Theatre& theatre, const vector<string>& splitted_row) {
    string play_title = splitted_row[2];
       string actor_name = splitted_row[3];
       string free_seats = splitted_row[4];

       if (free_seats == "none") {
           free_seats = "0";
       }

       Play play;
       play.actor = actor_name;
       play.title = play_title;
       play.free_seats = stoi(free_seats);

       theatre.plays.emplace(play.actor + play.title, play);

       string theatre_town = splitted_row[0];
       string theatre_name = splitted_row[1];

       theatre.town = theatre_town;
       theatre.name = theatre_name;


}

void addTheatreToStructure(vector<Theatre>& theatres, const vector<string>& splitted_row) {


    bool theatre_exists = false;
    for (auto& theatre : theatres) {
        if (theatre.name == splitted_row[1] && theatre.town == splitted_row[0]) {
            addPlayToStructure(theatre, splitted_row);
            theatre_exists = true;
            break;
        }
    }

    if (!theatre_exists) {
        Theatre theatre;
        addPlayToStructure(theatre, splitted_row);
        theatres.push_back(theatre);
    }
}

bool isFormat(ifstream& file_object) {
    string row;
    vector<string> splitted_row;

    while (getline(file_object, row)) {
        splitted_row = split(row, ';');

        if (splitted_row.size() != NUMBER_OF_FIELDS || find(splitted_row.begin(),
            splitted_row.end(), "") != splitted_row.end()) {
            cout << EMPTY_FIELD << row << endl;
            return false;
        }
    }

    return true;
}

int main() {
    vector<Theatre> theatres;

    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream file_object(file_name);

    if (!file_object) {
        cout << FILE_ERROR << endl;
        return EXIT_FAILURE;
    }

    if (!isFormat(file_object)) {
        return EXIT_FAILURE;
    }

    string row;
    vector<string> splitted_row;

    while (getline(file_object, row)) {
        splitted_row = split(row, ';');
        addTheatreToStructure(theatres, splitted_row);
    }


    return EXIT_SUCCESS;
}
