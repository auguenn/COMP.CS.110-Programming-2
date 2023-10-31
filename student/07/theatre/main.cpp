#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>
#include <sstream>

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

void printTheatresInOrder(vector<Theatre>& theatres){

    vector<string> theatre_names;

    // Käydään läpi kaikki teatterit ja lisätään niiden nimet
    // theatre_names -vektoriin
    for(auto& theatre : theatres) {
        theatre_names.push_back(theatre.name);
    }

    // Järjestetään teatterien nimet aakkosjärjestykseen
    sort(theatre_names.begin(), theatre_names.end());

    // Tulostetaan teatterien nimet
    for(auto& theatre_name : theatre_names) {
        cout << theatre_name << endl;
    }
}

void printPlaysInOrder(vector<Theatre>& theatres) {
    set<string> uniquePlayTitles;

        for (const auto& theatre : theatres) {
            for (const auto& play : theatre.plays) {
                string playTitle = play.second.title;
                size_t found = playTitle.find('/');


                if (found != string::npos) {
                    playTitle = playTitle.substr(0, found) + " ** " +
                            playTitle.substr(found + 1);
                }

                uniquePlayTitles.insert(playTitle);
            }
        }

        for (const string& playTitle : uniquePlayTitles) {
            cout << playTitle << endl;
        }
}

void printTheatresOfPlay(vector<Theatre>& theatres, const string& playName) {
    vector<string> theatre_names;

    if (playName.find('/') != string::npos) {
           cout << PLAY_NOT_FOUND << endl;
           return;
       }

       // Käydään läpi kaikki teatterit ja etsitään ne, joissa annettu näytelmä
       // esitetään
       for (const auto& theatre : theatres) {
           for (const auto& play : theatre.plays) {
               string playTitle = play.second.title;
               size_t found = playTitle.find('/');

               // Tarkista, onko näytelmän nimi tai alias osa haettua nimeä
               if (playTitle == playName || (found != string::npos &&
                   (playTitle.substr(0, found) == playName ||
                    playTitle.substr(found + 1) == playName))) {
                   theatre_names.push_back(theatre.name);
                   break;  // Lopeta teatterin tarkastelu, koska se löytyi jo
               }
           }
       }

       // Järjestetään teatterien nimet aakkosjärjestykseen
       sort(theatre_names.begin(), theatre_names.end());

       if (theatre_names.empty()) {
           cout << PLAY_NOT_FOUND << endl;
           return;
       }

       // Tulostetaan teatterien nimet
       for (const string& theatre_name : theatre_names) {
           cout << theatre_name << endl;
       }
}

void printPlaysInTheatre(vector<Theatre>& theatres, const string& theatre_name) {
    // Etsitään teatteri, jonka nimi on annettu nimi parametrina.
    auto theatre_iter = find_if(theatres.begin(), theatres.end(),
        [&theatre_name](const Theatre& theatre)
                { return theatre.name == theatre_name; });

    // Jos teatteria ei löydy
    if (theatre_iter == theatres.end()) {
        cout << THEATRE_NOT_FOUND << endl;
        return;
    }

    vector<string> play_titles;

        // Etsitään annetun teatterin kaikki näytelmät ja lisätään ne play_titles-vektoriin
        for (const auto& theatre : theatres) {
            if (theatre.name == theatre_name) {
                for (const auto& play : theatre.plays) {
                    play_titles.push_back(play.second.title);
                }
            }
        }

        // Järjestetään näytelmien nimet aakkosjärjestykseen
        sort(play_titles.begin(), play_titles.end());

        // Poistetaan mahdolliset duplikaatit
        play_titles.erase(unique(play_titles.begin(), play_titles.end()), play_titles.end());

        // Tulostetaan näytelmät
        for (const string& play_title : play_titles) {
            cout << play_title << endl;
        }
}



void addToStructure(Theatre& theatre, const vector<string>& splitted_row) {

    // Otetaan riviltä tiedot talteen merkkijonomuuttujiin
    string theatre_town = splitted_row[0];
    string theatre_name = splitted_row[1];
    string play_title = splitted_row[2];
    string actor_name = splitted_row[3];
    string free_seats = splitted_row[4];

    // Jos näytelmässä ei ole vapaita paikkoja
    if(free_seats== "none") {
        free_seats = "0";
    }

    // Luodaan uusi näytelmä-olio ja asetetaan sille arvot
    Play play;
    play.title = play_title;
    play.actor = actor_name;
    play.free_seats = stoi(free_seats);

    // Asetetaan teatterin tiedot tietorakenteeseen
    theatre.town = theatre_town;
    theatre.name = theatre_name;

    // Lisätään näytelmä teatterin näytelmätietokantaan (map-rakenne)
    theatre.plays[play.title + play.actor] = play;
}



// Lukee tiedoston ja lisää sen sisällön tietorakenteeseen.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot
// Paluuarvo: totuusarvo sen mukaan onko luettava tiedosto
// oikeanmallinen
bool isFormat(vector<Theatre>& theatres) {
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream file_object(file_name);

    if (!file_object) {
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

        // Tarkistetaan, onko teatteri jo olemassa tietorakenteessa
        bool theatre_exists = false;
        for (auto& theatre : theatres) {
            if (theatre.name == splitted_row[1]) {
                // Jos teatteri on olemassa, lisätään uusi näytelmä sen
                // tietokantaan
                addToStructure(theatre, splitted_row);
                theatre_exists = true;
                break;
            }
        }

        // Jos teatteria ei ole vielä tietorakenteessa, luodaan uusi
        // teatteri-olio ja lisätään se tietorakenteeseen
        if (!theatre_exists) {
            Theatre theatre;
            addToStructure(theatre, splitted_row);
            theatres.push_back(theatre);
        }
    }

    file_object.close();
    return true;
}





bool isCommandLength (vector<string> command_parts,
                      unsigned int right_length) {
    if(command_parts.size() != right_length) {
        cout<<WRONG_PARAMETERS<<endl;
        return false;
    }
    else {
        return true;
    }
}


int main() {
    vector<Theatre> theatres;

    if (!isFormat(theatres)) {
        return EXIT_FAILURE;
    }


    string command;
    vector<string> command_parts;

    // Silmukka, joka kysyy käyttäjältä komentoja ja ohjelma
        // kutsuu eri funktioita komentojen mukaisesti.
        // Silmukka loppuu lopetuskomentoon 'quit'.
        while(command != "quit") {
            cout << PROMPT;
            getline(cin, command);
            command_parts = split(command, ' ');

        // Jokaisen komennon kohdalla tarkistetaan, että komennossa
        // on oikea määrä osia.
        if (command_parts.at(0) == "theatres") {
            if (isCommandLength(command_parts, 1) == true) {
               printTheatresInOrder(theatres);
            }
        }
        else if (command_parts.at(0) == "plays") {
            if (isCommandLength(command_parts, 1) == true) {
               printPlaysInOrder(theatres);
            }
        }
        else if (command_parts.at(0) == "theatres_of_play") {
            if (isCommandLength(command_parts, 2)) {
                string playName = command_parts.at(1);
                printTheatresOfPlay(theatres, playName);
            }
        }
        else if (command_parts.at(0) == "plays_in_theatre") {
            if (isCommandLength(command_parts, 2)) {
                string theatreName = command_parts.at(1);
                printPlaysInTheatre(theatres, theatreName);
            }
        }
        else if (command_parts.at(0) == "quit") {
            if(isCommandLength(command_parts, 1) == true) {
                break;
            }
        }


        // Virheilmoitus, jos annetaan tuntematon komento
        else {
            cout<<COMMAND_NOT_FOUND<<endl;
            continue;
        }
        }


    return EXIT_SUCCESS;
}
