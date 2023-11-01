#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <algorithm>
#include <set>
#include <unordered_map>

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
        }
        else if (current_char == delim && !inside_quotation) {
            result.push_back("");
        }
        else {
            result.back().push_back(current_char);
        }
    }

    return result;
}

void printTheatresInOrder(vector<Theatre>& theatres) {

    set<string> uniqueTheatres;

    // Käydään läpi kaikki teatterit ja lisätään niiden nimet
    // uniqueTheatres -setiin varmistaen, ettei samaa teatteria lisätä
    // useaan kertaan
    for (const auto& theatre : theatres) {
        uniqueTheatres.insert(theatre.name);
    }

    // Tulostetaan teatterien nimet aakkosjärjestyksessä
    for (const string& theatre_name : uniqueTheatres) {
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
                playTitle = playTitle.substr(0, found) + " *** " +
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

    set<string> uniqueTheatreNames;

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
                uniqueTheatreNames.insert(theatre.name);
                break;  // Lopeta teatterin tarkastelu, koska se löytyi jo
            }
        }
    }

    if (uniqueTheatreNames.empty()) {
        cout << PLAY_NOT_FOUND << endl;
        return;
    }

    // Tulostetaan teatterien nimet aakkosjärjestyksessä
    for (const string& theatre_name : uniqueTheatreNames) {
        cout << theatre_name << endl;
    }
}


void printPlaysInTheatre(vector<Theatre>& theatres,
                         const string& theatre_name) {

    // Etsitään teatteri, jonka nimi on annettu nimi parametrina.
    auto theatre_iter = find_if(theatres.begin(), theatres.end(),
        [&theatre_name](const Theatre& theatre) {
        return theatre.name == theatre_name;
    });

    // Jos teatteria ei löydy
    if (theatre_iter == theatres.end()) {
        cout << THEATRE_NOT_FOUND << endl;
        return;
    }

    vector<string> play_titles;

    // Etsitään annetun teatterin kaikki näytelmät ja lisätään ne
    // play_titles-vektoriin
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
    play_titles.erase(unique(play_titles.begin(), play_titles.end()),
                      play_titles.end());

    // Tulostetaan näytelmät
    for (const string& play_title : play_titles) {
        cout << play_title << endl;
    }
}


void printPlaysInTown(vector<Theatre>& theatres, const string& town) {
    unordered_map<string, pair<string, int>> lastOccurrencePlays;

    for (auto& theatre : theatres) {
        if (theatre.town == town) {
            for (const auto& play : theatre.plays) {
                lastOccurrencePlays[play.second.title] = make_pair(theatre.name, play.second.free_seats);
            }
        }
    }

    vector<pair<string, pair<string, int>>> sortedPlays(lastOccurrencePlays.begin(), lastOccurrencePlays.end());


    // Lajittele näytelmät teatterin mukaan ja näytelmän nimen mukaan
    sort(sortedPlays.begin(), sortedPlays.end(), [](const pair<string, pair<string, int>>& a, const pair<string, pair<string, int>>& b) {
        if (a.second.first == b.second.first) {
            return a.first < b.first;
        }
        return a.second.first < b.second.first;
    });

    // Tulosta näytelmät
    for (const auto& entry : sortedPlays) {
        const string& playTitle = entry.first;
        const string& theatreName = entry.second.first;
        const int freeSeats = entry.second.second;

        if (freeSeats > 0) {
            size_t found = playTitle.find('/');

            if (found != string::npos) {
                cout << theatreName << " : " << playTitle.substr(0, found) << " --- " << playTitle.substr(found + 1) << " : " << freeSeats << endl;
            } else {
                cout << theatreName << " : " << playTitle << " : " << freeSeats << endl;
            }
        }
    }
}


void printPlayersInPlay(const vector<Theatre>& theatres, const string& playName,
                        const string& theatreName) {

    map<string, set<string>> theatrePlayers;

    if (playName.find('/') != string::npos) {
        cout << PLAY_NOT_FOUND << endl;
        return;
    }

    for (const auto& theatre : theatres) {
        if (theatreName.empty() || theatre.name == theatreName) {
            for (const auto& play : theatre.plays) {

                string fullPlayName = play.second.title +
                                            " (" + play.second.actor + ")";

                if (playName.empty() || fullPlayName.find(playName) !=
                                                            string::npos) {
                    theatrePlayers[theatre.name].insert(play.second.actor);
                }
            }
        }
    }

    for (const auto& entry : theatrePlayers) {
        const string& theatreName = entry.first;
        const set<string>& players = entry.second;

        for (const string& player : players) {
            cout << theatreName << " : " << player << endl;
        }
    }

    if (theatrePlayers.empty()) {
        cout << PLAY_NOT_FOUND << endl;
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
    if(free_seats == "none") {
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
    int line_number = 1;
    string row;
    vector<string> splitted_row;

    while(getline(file_object, row)) {
        // Jaetaan rivi osiin
        splitted_row = split(row, ';');

        // Tarkistetaan, että rivi sisältää viisi osaa ja että ne eivät
        // ole tyhjiä
        if(splitted_row.size() != NUMBER_OF_FIELDS ||
                find(splitted_row.begin(), splitted_row.end(), "")
                                                       != splitted_row.end()) {
            cout << EMPTY_FIELD << line_number << endl;
            return false;
        }

        // Luodaan uusi teatteri-olio
        Theatre theatre;

        // Kutsutaan addToStructure-funktiota teatterin ja rivin tietojen
        // lisäämiseksi
        addToStructure(theatre, splitted_row);

        // Lisätään teatteri tietorakenteeseen loppuun
        theatres.push_back(theatre);

        line_number++;
    }

    file_object.close();
    return true;
}


bool validatePlayAndTheatre(const vector<Theatre>& theatres,
                           const string& playName, const string& theatreName) {

    bool playFound = false;
    // Oletusarvoisesti oletetaan, että teatteri on kunnossa, ellei toista
    // parametria ole annettu.
    bool theatreFound = true;

    // Tarkistetaan, onko annettua teatterin nimeä olemassa
    if (!theatreName.empty()) {
        theatreFound = false;
        for (const auto& theatre : theatres) {
            if (theatre.name == theatreName) {
                theatreFound = true;
                break;
            }
        }
    }

    // Etsitään, onko annettua näytelmän nimeä olemassa
    for (const auto& theatre : theatres) {
        for (const auto& play : theatre.plays) {
            string fullPlayName = play.second.title +
                                            " (" + play.second.actor + ")";

            if (fullPlayName.find(playName) != string::npos) {
                playFound = true;
                break;
            }
        }
    }

    if (!theatreFound) {
        cout << THEATRE_NOT_FOUND << endl;
    }

    else if (!playFound) {
        cout << PLAY_NOT_FOUND << endl;
    }

    return theatreFound && playFound;
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
        else if (command_parts.at(0) == "plays_in_town") {
            if (isCommandLength(command_parts, 2)) {
                string townName = command_parts.at(1);
                printPlaysInTown(theatres, townName);
            }
        }
        else if (command_parts.at(0) == "players_in_play") {
            if (command_parts.size() < 2 || command_parts.size() > 3) {
                cout << WRONG_PARAMETERS << endl;
                continue;
            }
            string playName = command_parts.at(1);
            string theatreName = "";

            if (command_parts.size() == 3) {
                theatreName = command_parts.at(2);
            }

            // Kutsu virhetarkastelufunktiota
            if (validatePlayAndTheatre(theatres, playName, theatreName)) {
                printPlayersInPlay(theatres, playName, theatreName);
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
