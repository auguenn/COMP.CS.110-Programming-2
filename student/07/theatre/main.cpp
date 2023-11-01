/* Teatteri
 *
 * Kuvaus:
 *   Ohjelma toteuttaa teatterijärjestelmän, jossa teatterien ja näytelmien
 *   tiedot luetaan csv-tiedostosta. Ohjelma tarkastaa onko tiedosto
 *   luettavissa ja jos on, niin ohjelma tarkistaa onko tiedosto määritelmän
 *   mukainen eli onko siinä esimerkiksi viittä kenttää ja onko kaikissa
 *   kentissä arvo. Jos tiedosto ei ole määritelmän mukainen, tulostetaan
 *   käyttäjälle virheilmoitus ja lopetetaan ohjelman suoritus paluuarvoon
 *   EXIT_FAILURE. Ohjelma jäsentelee tiedostosta lukemansa rivit ja tallentaa
 *   eri teatterien näytelmätiedot ja teatterin paikkakunnan tietorakenteeseen.
 *      Kun tiedosto on luettu, ohjelma alkaa pyytämään käyttäjältä komentoja.
 *   Kun käyttäjältä odotetaan syötettä, tulostetaan rivin alkuun komentokehote
 *   the>. Tämän jälkeen käyttäjä voi valita mitä tietoja hän haluaa
 *   teatterijärjestelmästä ulos. Käyttäjän mahdolliset komennot ovat :
 *   -"theatres"- Tulostaa aakkosjärjestyksessä alekkain kaikki tunnetut
 *      teatterit.
 *   -"plays" - Tulostaa allekkain kaikki näytelmät aakkosjärjestyksessä.
 *      Vaikka sama näytelmä löytyisi useasta teatterista, näytelmän nimi
 *      tulostetaan vain kerran.
 *   -"theatres_of_play <näytelmä>" - Tulostaa teatterit, joissa annettua
 *      näytelmää esitetään. Teatterit tulostetaan niiden nimien mukaisessa
 *      aakkosjärjestyksessä. Komennossa voi käyttää joko näytelmän varsinaista
 *      nimeä tai aliasta, mutta ei niiden yhdistelmää. Näytelmää ei myöskään
 *      löydy sen nimen osalla, vaan nimi tai alias pitää antaa kokonaan.
 *   -"plays_in_theatre <teatteri>" - Tulostaa annetun teatterin näytelmät
 *      niiden nimien mukaisessa aakkosjärjestyksessä.
 *   -"plays_in_town <paikkakunta>" - Tulostaa annetun paikkakunnan
 *      sellaiset näytelmät, joissa on paikkoja vapaana. Tulostuksessa
 *      käytetään ensin teatterin mukaista aakkosjärjestystä, ja saman
 *      teatterin näytelmät tulostetaan näytelmän nimen mukaisessa
 *      aakkosjärjestyksessä, minkä jälkeen tulostetaan vapaiden paikkojen
 *      määrä. Jos paikkakunnalla ei ole yhdessäkään näytelmässä vapaita
 *      paikkoja, tulostetaan virheilmoitus.
 *   ja
 *   -"players_in_play <näytelmä> [<teatteri>]" - Tulostaa halutussa
 *      näytelmässä esiintyvät näyttelijät. Samannimisiä näytelmiä voi olla eri
 *      teattereissa, joten komennolle voidaan antaa toisena parametrina
 *      haluttu teatteri. Jos teatteri annetaan, tulostetaan vain kyseisestä
 *      teatterista löytyvän näytelmän näyttelijät. Jos teatteria ei anneta,
 *       annetun näytelmän näyttelijät tulostetaan kaikista teattereista,
 *       joista näytelmä löytyy. Joka tapauksessa komento tulostaa ensin
 *       teatterin nimen ja sitten näyttelijän nimen. Tulostus noudattaa ensin
 *       teatterin mukaista aakkosjärjestystä, ja saman teatterin näyttelijät
 *       tulostetaan etunimen mukaisessa aakkosjärjestyksessä. Näytelmää voi
 *       etsiä joko varsinaisella nimellä tai aliaksella.
 *   Kehote tulostetaan aina komennon jälkeen uudelleen kunnes käyttäjän antama
 *   komento on "quit", jolloin ohjelman suoritus päättyy.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Enna Augustin
 * Opiskelijanumero: 050235634
 * Käyttäjätunnus: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 * Huomioitavaa ohjelmassa ja sen toteutuksessa:
 * Tiedot tiedostossa oltava muodossa
 * <paikkakunta>;<teatteri>;<näytelmä>;<näyttelijä>;<vapaiden_paikkojen_määrä>,
 * ja jokaisen tietoalkion oltava omalla rivillään. Tyhjiä tietokenttiä
 * syötetiedostossa ei hyväksytä. Antaessa moniosaisia komentoja toimii
 * erottimena välilyönti ' '.
 *
 * */

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


// Tietue yksittäisen näytelmän tietojen tallentamiseksi
// Näytelmän tiedot koostuvat sen näyttelijästä,
// nimestä ja vapaiden paikkojen määrästä.
struct Play {
    string actor;
    string title;
    int freeSeats;
};

// Tietue yksittäisen teatterin tietojen tallentamiseksi
// Teatterin tiedot koostuvat kaupungista, jossa teatteri sijaitsee,
// teatterin nimestä sekä map-rakenteesta, jossa avaimina toimivat
// string-tyypin muuttujat, jotka kuvaavat näytelmien nimiä.
// Arvoina puolestaan ovat "Play" struktiin kuuluvat jäsenet.
struct Theatre {
    string town;
    string name;
    map<string, Play> plays;
};


// Yksinkertainen split-funktio
// Parametrit: jaettava merkkijono, osien välinen erotin
// jos erotin on ""-merkkien välissä jätetään se huomiotta.
// Paluuarvo: merkkijono jaettuna osiin
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


// Funktio tulostaa teatterien nimet aakkosjärjestyksessä.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot
// Paluuarvo: ei ole
void printTheatresInOrder(vector<Theatre>& theatres) {

    set<string> uniqueTheatres;

    // Käydään läpi kaikki teatterit ja lisätään niiden nimet
    // uniqueTheatres -setiin varmistaen, ettei samaa teatteria lisätä
    // useaan kertaan
    for (const auto& theatre : theatres) {
        uniqueTheatres.insert(theatre.name);
    }

    // Tulostetaan teatterien nimet aakkosjärjestyksessä
    for (const string& theatreName : uniqueTheatres) {
        cout << theatreName << endl;
    }
}


// Funktio tulostaa näytelmien nimet aakkosjärjestyksessä.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot
// Paluuarvo: ei ole
void printPlaysInOrder(vector<Theatre>& theatres) {

    // Alustetaan joukko (set), joka pitää yllä uniikkeja näytelmien
    // otsikoita
    set<string> uniquePlayTitles;
    string playTitle = "";

    for (const auto& theatre : theatres) {
        for (const auto& play : theatre.plays) {
            string playTitle = play.second.title;

            // Tarkistetaan, onko näytelmän otsikossa '/'-merkki
            size_t found = playTitle.find('/');

            // Jos '/' löytyy, korvataan se merkillä ' *** '
            if (found != string::npos) {
                playTitle = playTitle.substr(0, found) + " *** " +
                        playTitle.substr(found + 1);
            }

            // Lisätään muokattu näytelmän otsikko joukkoon
            uniquePlayTitles.insert(playTitle);
        }
    }

    // Tulostetaan kaikki uniikit näytelmien otsikot
    for (const string& playTitle : uniquePlayTitles) {
        cout << playTitle << endl;
    }
}


// Funktio tulostaa kaikki teatterit, joissa näytelmää esitetään
// aakkosjärjestyksessä
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot, näytelmän nimi viitteenä
// Paluuarvo: ei ole
void printTheatresOfPlay(vector<Theatre>& theatres, const string& playName) {

    // Alustetaan joukko (set), joka pitää yllä uniikkeja teatterien nimiä.
    set<string> uniqueTheatreNames;

    // Tarkastetaan onko käyttäjän antamassa näytelmän nimessä /-merkki ja jos
    // näin on niin tulostetaan virheilmoitus.
    if (playName.find('/') != string::npos) {
        cout << PLAY_NOT_FOUND << endl;
        return;
    }

    // Käydään läpi kaikki teatterit ja etsitään ne, joissa annettu näytelmä
    // esitetään
    for (const auto& theatre : theatres) {
        for (const auto& play : theatre.plays) {
            string playTitle = play.second.title;

            // Näytelmän nimen jako varsinaiseen nimeen ja aliakseen
            size_t found = playTitle.find('/');

            // Tarkista, onko näytelmän nimi tai alias osa haettua nimeä
            if (playTitle == playName || (found != string::npos &&
                (playTitle.substr(0, found) == playName ||
                 playTitle.substr(found + 1) == playName))) {
                uniqueTheatreNames.insert(theatre.name);
                // Lopeta teatterin tarkastelu, koska se löytyi jo
                break;
            }
        }
    }

    // Virheilmoitus jos näytelmää ei löydy tietorakenteesta.
    if (uniqueTheatreNames.empty()) {
        cout << PLAY_NOT_FOUND << endl;
        return;
    }

    // Tulostetaan teatterien nimet aakkosjärjestyksessä
    for (const string& theatre_name : uniqueTheatreNames) {
        cout << theatre_name << endl;
    }
}


// Funktio tulostaa kaikki näytelmät tietyssä teatterissa aakkosjärjestyksessä.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot, teatterin nimi viitteenä.
// Paluuarvo: ei ole
void printPlaysInTheatre(vector<Theatre>& theatres,
                         const string& theatreName) {

    // Etsitään teatteri, jonka nimi on annettu nimi parametrina.
    auto theatre_iter = find_if(theatres.begin(), theatres.end(),
        [&theatreName](const Theatre& theatre) {
        return theatre.name == theatreName;
    });

    // Jos teatteria ei löydy tulostetaan virheilmoitus
    if (theatre_iter == theatres.end()) {
        cout << THEATRE_NOT_FOUND << endl;
        return;
    }

    vector<string> playTitles;

    // Etsitään annetun teatterin kaikki näytelmät ja lisätään ne
    // play_titles-vektoriin
    for (const auto& theatre : theatres) {
        if (theatre.name == theatreName) {
            for (const auto& play : theatre.plays) {
                playTitles.push_back(play.second.title);
            }
        }
    }

    // Järjestetään näytelmien nimet aakkosjärjestykseen
    sort(playTitles.begin(), playTitles.end());

    // Poistetaan mahdolliset duplikaatit
    playTitles.erase(unique(playTitles.begin(), playTitles.end()),
                      playTitles.end());

    // Tulostetaan näytelmät
    for (const string& playTitle : playTitles) {
        cout << playTitle << endl;
    }
}


// Funktio tulostaa tietyn kaupungin näytelmät teatterikohtaisesti
// aakkosjärjestyksessä. Lisäksi tulostetaan vapaiden paikkojen määrä.
// parametrit: viite teatterin nimeen, viite näytelmän nimeen, vapaiden
// paikkojen lukumäärä
// Paluuarvo: ei ole
void printPlayInfo(const string& theatreName, const string& playTitle,
                                                            int freeSeats) {
    size_t found = playTitle.find('/');

    // Tulostus jos näytelmän nimessä on alias
    if (found != string::npos) {
        cout << theatreName << " : " << playTitle.substr(0, found) << " --- "
                 << playTitle.substr(found + 1) << " : " << freeSeats << endl;
    }
    // Tulostus jos näytelmän nimessä ei ole aliasta
    else {
       cout << theatreName << " : " << playTitle << " : " << freeSeats << endl;
    }
}


// Funktio etsii tietyn kaupungin näytelmät teatterikohtaisesti.
// Lisäksi tallennetaan tietorakenteessa viimeinen esiintyvä vapaiden paikkojen
// määrä.
// parametrit: unordered_map<string, pair<string, int>>& lastOccurrencePlays -
// viittaus map-rakenteeseen, jossa viimeisimmän näytelmän tiedot
// Paluuarvo: ei ole
void findPlaysInTown(unordered_map<string, pair<string, int>>& lastOccurrencePlays) {

    // Luodaan järjestetty vektori näytelmien tiedoista
    vector<pair<string, pair<string, int>>>
           sortedPlays(lastOccurrencePlays.begin(), lastOccurrencePlays.end());

    // Järjestetään näytelmät teatterin ja näytelmän nimen mukaan
    sort(sortedPlays.begin(), sortedPlays.end(), [](const pair<string,
             pair<string, int>>& a, const pair<string, pair<string, int>>& b) {
        if (a.second.first == b.second.first) {
            return a.first < b.first;
        }
        return a.second.first < b.second.first;
    });

    bool noAvailablePlays = true;

    for (const auto& entry : sortedPlays) {
        const string& playTitle = entry.first;
        const string& theatreName = entry.second.first;
        const int freeSeats = entry.second.second;

        // Tarkistetaan, onko vapaita paikkoja ja tulostetaan näytelmä
        // tietoineen
        if (freeSeats > 0) {
            noAvailablePlays = false;
            printPlayInfo(theatreName, playTitle, freeSeats);
        }
    }
    // Tarkistetaan, onko vapaita näytelmiä saatavilla, muuten tulostetaan
    // ilmoitus, ettei näytelmiä ole saatavilla kyseisessä kaupungissa
    if (noAvailablePlays) {
        cout << NOT_AVAILABLE << endl;
    }
}


// Funktio etsii tietyn kaupungin teatterit.
// Lisäksi tallennetaan tietorakenteessa viimeinen esiintyvä vapaiden paikkojen
// määrä.
// parametrit: unordered_map<string, pair<string, int>>& lastOccurrencePlays -
// viittaus map-rakenteeseen, jossa viimeisimmän näytelmän tiedot, viite
// kaupungin nimeen
// Paluuarvo: ei ole
void findTheatresInTown(vector<Theatre>& theatres, const string& town) {

    // Luodaan tyhjä tietorakenne näytelmien tallentamiseksi viimeisimmän
    // esiintymisen perusteella
    unordered_map<string, pair<string, int>> lastOccurrencePlays;

    bool townFound = false;

    for (auto& theatre : theatres) {
        if (theatre.town == town) {
            townFound = true;
            // Käydään läpi teatterin näytelmät ja päivitetään viimeisimmät
            // esiintymiset
            for (const auto& play : theatre.plays) {
                lastOccurrencePlays[play.second.title] =
                               make_pair(theatre.name, play.second.freeSeats);
            }
        }
    }
    // Tarkistetaan, onko annettua kaupunkia löytynyt, muuten tulostetaan
    // virheilmoitus
    if (!townFound) {
        cout << TOWN_NOT_FOUND << endl;
        return;
    }

    findPlaysInTown(lastOccurrencePlays);
}


// Funktio tulostaa kaikki näyttelijät, jotka näyttelevät halutussa näytelmässä
// aakkosjärjestyksessä. Jos ei anneta teatterin nimeä, tulostetaan näyttelijät
// teattereittain aakkosjärjestyksessä.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot, näytelmän nimi viitteenä, teatterin nimi
// viitteenä
// Paluuarvo: ei ole
void printPlayersInPlay(const vector<Theatre>& theatres,
                           const string& playName, const string& theatreName) {

    // Alustetaan map, joka pitää yllä teatterien ja niissä esiintyvien
    // näyttelijöiden tiedot
    map<string, set<string>> theatrePlayers;

    // Tarkastetaan onko käyttäjän antamassa näytelmän nimessä /-merkki ja jos
    // näin on niin tulostetaan virheilmoitus.
    if (playName.find('/') != string::npos) {
        cout << PLAY_NOT_FOUND << endl;
        return;
    }
    for (const auto& theatre : theatres) {
        // Tarkistetaan, että joko teatterin nimi on tyhjä (käyttäjä ei antanut
        // teatterin nimeä) tai teatterin nimi vastaa annettua teatterin nimeä
        if (theatreName.empty() || theatre.name == theatreName) {
            for (const auto& play : theatre.plays) {

                string fullPlayName = play.second.title +
                                            " (" + play.second.actor + ")";

                // Tarkista, onko annettua näytelmän nimeä olemassa ja löytyykö
                // se tämän teatterin näytelmistä
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

    // Virheilmoitus jos näytelmää ei löydy tietorakenteesta.
    if (theatrePlayers.empty()) {
        cout << PLAY_NOT_FOUND << endl;
    }
}


// Lisää teatterien ja näytelmien tiedot tietorakenteeseen
// Parametrit: teatteri-tietue ja luetun tiedoston yksittäinen rivi, jonka
// alkiot ovat teatterin paikkakunta, teatterin nimi, näytelmän nimi,
// näyttelijän nimi ja vapaiden paikkojen määrä
// Paluuarvo: ei paluuarvoa
void addToStructure(Theatre& theatre, const vector<string>& splittedRow) {

    // Otetaan riviltä tiedot talteen merkkijonomuuttujiin
    string theatreTown = splittedRow[0];
    string theatreName = splittedRow[1];
    string playTitle = splittedRow[2];
    string actorName = splittedRow[3];
    string freeSeats = splittedRow[4];

    // Jos näytelmässä ei ole vapaita paikkoja
    if(freeSeats == "none") {
        freeSeats = "0";
    }

    // Luodaan uusi näytelmä-olio ja asetetaan sille arvot
    Play play;
    play.title = playTitle;
    play.actor = actorName;
    play.freeSeats = stoi(freeSeats);

    // Asetetaan teatterin tiedot tietorakenteeseen
    theatre.town = theatreTown;
    theatre.name = theatreName;

    // Lisätään näytelmä teatterin näytelmätietokantaan (map-rakenne)
    theatre.plays[play.title + play.actor] = play;
}


// Lukee tiedoston ja lisää sen sisällön tietorakenteeseen.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot
// Paluuarvo: totuusarvo sen mukaan onko luettava tiedosto
// oikeanmallinen tai ylipäänsä luettavissa
bool isFormat(vector<Theatre>& theatres) {

    string file_name = "";
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream file_object(file_name);

    // Tarkistetaan onko tiedosto avattavissa
    if (!file_object) {
        cout << FILE_ERROR << endl;
        return false;
    }

    // Luetaan tiedoston rivit yksi kerrallaan
    int line_number = 1;
    string row = "";
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


// Funktio tutkii käyttäjän antamasta komennosta onko näytelmää tai teatteria
// olemassa tietorakenteessa. Teatterin olemassaolo tutkitaan ensin.
// Parametrit: vector<Theatre>& theatres - viittaus teatterivektoriin,
// joka sisältää teatterien tiedot, viite näytelmän nimeen, viite teatterin
// nimeen
// Paluuarvo: totuusarvo onko näytelmää tai teatteria olemassa.
bool validatePlayAndTheatre(const vector<Theatre>& theatres,
                           const string& playName, const string& theatreName) {

    bool playFound = false;
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

    // Virheilmoitus jos teatteria ei ole olemassa
    if (!theatreFound) {
        cout << THEATRE_NOT_FOUND << endl;
    }

    // Virheilmoitus jos näytelmää ei ole olemassa
    else if (!playFound) {
        cout << PLAY_NOT_FOUND << endl;
    }

    return theatreFound && playFound;
}


//Tarkistaa, että annetussa komennossa on oikea lukumäärä komponentteja.
//Parametrit: komento vektorina jossa komennon komponentit vektorissa
//omina alkioinaan
//Paluuarvo: oliko komennossa oikea lukumäärä komponentteja vai ei
bool isCommandLength (vector<string> command_parts,
                      unsigned int right_length) {

    if(command_parts.size() != right_length) {
        cout << WRONG_PARAMETERS << endl;
        return false;
    }
    else {
        return true;
    }
}


// Funktio, joka tutkii käyttäjän antaman komennon ja kutsuu haluttua funktiota
// komennon mukaisesti.
// Parametrit: viite käyttäjän antamaan komentoon, vector<Theatre>& theatres -
// viittaus teatterivektoriin, joka sisältää teatterien tiedot
// Paluuarvo: ei ole
void processCommand(const string& command, vector<Theatre>& theatres) {

    // Alustetaan tyhjä vektori, johon käyttäjän antaman komennon eri osat
    // tallennetaan
    vector<string> command_parts = split(command, ' ');

    // Tyhjä komento = vieras komento
    if (command_parts.empty()) {
        cout << COMMAND_NOT_FOUND << endl;
        return;
    }
    // Tunnetut komennot
    if (command_parts[0] == "theatres") {
        if (isCommandLength(command_parts, 1)) {
            printTheatresInOrder(theatres);
        }
    }
    else if (command_parts[0] == "plays") {
        if (isCommandLength(command_parts, 1)) {
            printPlaysInOrder(theatres);
        }
    }
    else if (command_parts[0] == "theatres_of_play") {
        if (isCommandLength(command_parts, 2)) {
            string playName = command_parts[1];
            printTheatresOfPlay(theatres, playName);
        }
    }
    else if (command_parts[0] == "plays_in_theatre") {
        if (isCommandLength(command_parts, 2)) {
            string theatreName = command_parts[1];
            printPlaysInTheatre(theatres, theatreName);
        }
    }
    else if (command_parts[0] == "plays_in_town") {
        if (isCommandLength(command_parts, 2)) {
            string townName = command_parts[1];
            findTheatresInTown(theatres, townName);
        }
    }
    else if (command_parts[0] == "players_in_play") {
        if (command_parts.size() == 2 || command_parts.size() == 3) {
            string playName = command_parts[1];
            string theatreName = (command_parts.size() == 3) ?
                                                    command_parts[2] : "";
            // Kutsu virhetarkastelufunktiota
            if (validatePlayAndTheatre(theatres, playName, theatreName)) {
                printPlayersInPlay(theatres, playName, theatreName);
            }
        }
        // Komennossa annetaan väärä määrä parametreja
        else {
            cout << WRONG_PARAMETERS << endl;
        }
    }
    else if (command_parts[0] == "quit") {
        if (isCommandLength(command_parts, 1)) {
            return;
        }
    }
    // Vieraan komennon virhetuloste
    else {
        cout << COMMAND_NOT_FOUND << endl;
    }
}


// Pääfunktio
int main() {

    vector<Theatre> theatres;

       if (!isFormat(theatres)) {
           return EXIT_FAILURE;
       }

       string command = "";

       // Pääsilmukka, joka odottaa ja käsittelee käyttäjän komentoja.
       while (true) {
           cout << PROMPT;
           getline(cin, command);
           processCommand(command, theatres);
       }

       return EXIT_SUCCESS;
}
