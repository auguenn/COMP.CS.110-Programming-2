/* Kirjasto
 *
 * Kuvaus:
 *   Ohjelma toteuttaa kirjastojärjestelmän, jossa kirjastojen ja kirjojen tiedot luetaan
 *   csv-tiedostosta. Ohjelma tarkastaa onko tiedosto luettavissa ja jos on, niin
 *   ohjelma tarkistaa onko tiedosto määritelmän mukainen eli onko siinä esimerkiksi neljää
 *   kenttää ja onko kaikissa kentissä arvo. Jos tiedosto ei ole määritelmän mukainen,
 *   tulostetaan käyttäjälle virheilmoitus ja lopetetaan ohjelman suoritus paluuarvoon
 *   EXIT_FAILURE. Mikäli syötetiedostossa on saman kirjaston samalle kirjalle esitetty
 *   tiedot useammin kuin kerran, voimaan jää se varaustieto joka tuli vastaan tiedostossa
 *   viimeisimpänä. Ohjelma jäsentelee tiedostosta lukemansa rivit ja tallentaa eri kirjastojen
 *   kirjatiedot tietorakenteeseen.
 *      Kun tiedosto on luettu, ohjelma aloittaa ohjelma pyytämään käyttäjältä komentoja.
 *   Kun käyttäjältä odotetaan syötettä, tulostetaan rivin alkuun komentokehote lib>. Tämän
 *   jälkeen käyttäjä voi valita mitä tietoja hän haluaa kirjastojärjestelmästä ulos. Käyttäjän
 *   mahdolliset komennot ovat :
 *   -"libraries"- Tulostaa aakkosjärjestyksessä alekkain kaikki tunnetut kirjastot.
 *   -"material <kirjasto>"- Tulostaa aakkosjärjestyksessä allekkain kaikki annetun kirjaston
 *      kirjat.
 *   -"books <kirjasto> <tekijä>" - Tulostaa aakkosjärjestyksessä allekkain kaikki annetun
 *      kirjaston kirjat.
 *   -"reservable <tekijä> <kirjan_nimi>"- Komento tulostaa lyhyimmän varausjonon halutun
 *      tekijän halutulle kirjalle ja sen alle aakkosjärjestyksessä kirjastot, joista kirja löytyy
 *      tällä samanpituisella varausjonolla.
 *   ja
 *   -"loanable" - Ohjelma tulostaa näytölle kaikkien kirjastojen kaikista kirjoista ne, jotka
 *   löytyvät hyllystä. Kirjoista tulostetaan tekijä ja nimi. Tulostettavassa listassa kirjat
 *   ovat aakkosjärjestyksessä ensin tekijöiden mukaan ja sitten kirjan nimen mukaan. Lisäksi
 *   jokainen kirja on listalla vain kerran, vaikka se löytyisi useammasta kirjastosta.
 *   Ohjelman suoritus päättyy kun käyttäjän antama komento on "quit".
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Enna Augustin
 * Opiskelijanumero: 050235634
 * Käyttäjätunnus: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 * Huomioitavaa ohjelmassa ja sen toteutuksessa:
 * Tiedot tiedostossa oltava muodossa <kirjasto>;<tekijä>;<kirjan_nimi>;<varausten_määrä> ja
 * jokaisen tietoalkion oltava omalla rivillään. Tyhjiä tietokenttiä syötetiedostossa ei hyväksytä
 * (esim ";;Kivi;Seitsemän veljestä;3" ei käy). Antaessa moniosaisia komentoja toimii
 * erottimena välilyönti ' '.
 *
 * */


#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <climits>

using namespace std;

const int MAXIMUM_RESERVATIONS = 100;


// Tietue yksittäisen kirjan tietojen tallentamiseksi
// Kirjan tiedot koostuvat sen kirjoittajasta,
// otsikosta ja varaustilanteesta
struct Book {
    string author;
    string title;
    int reservations;
};

// Tietue yksittäisen kirjaston tietojen tallentamiseksi
// Kirjaston tiedot koostuvat kirjaston nimestä sekä
// map-rakenteesta, jossa avaimina toimivat string-tyypin muuttujat,
// jotka kuvaavat kirjojen nimiä.
// Arvoina puolestaan ovat "Book" struktiin kuuluvat jäsenet.
struct Library {
    string name;
    map<string, Book> books;
};



//Jakaa merkkijono osiin.
//Parametrit: jaettava merkkijono, osien välinen erotin
//Paluuarvo: merkkijono jaettuna osiin
vector<string> split(const string& s, const char delimiter) {
    vector<string> result;
    string tmp = s;

    while(tmp.find(delimiter) != string::npos) {
        string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(new_part.empty() == false) {
            result.push_back(new_part);
        }
    }
    result.push_back(tmp);
    return result;
}



//Lisää kirjojen ja kirjastojen tiedot tietorakenteeseen
// Parametrit: kirjasto-tietue ja luetun tiedoston yksittäinen rivi, jonka
// alkiot ovat kirjasto, kirjoittaja, otsikko ja kirjan varaustieto
// Paluuarvo: ei paluuarvoa
void addToStructure(Library& library, const vector<string>& splitted_row) {

    // Otetaan riviltä tiedot talteen merkkijonomuuttujiin
    string library_name = splitted_row[0];
    string author_name = splitted_row[1];
    string book_title = splitted_row[2];
    string reservations = splitted_row[3];

    // Jos kirja on hyllyssä
    if(reservations == "on-the-shelf") {
        reservations = "0";
    }

    // Luodaan uusi kirja-olio ja asetetaan sille arvot
    Book book;
    book.author = author_name;
    book.title = book_title;
    book.reservations = stoi(reservations);

    // Asetetaan kirjaston nimi tietorakenteeseen
    library.name = library_name;

    // Lisätään kirja kirjaston kirjatietokantaan (map-rakenne)
    library.books[book.author + book_title] = book;
}



// Lukee tiedoston ja lisää sen sisällön tietorakenteeseen.
// Parametrit: vector<Library>& libraries - viittaus kirjastovektoriin,
// joka sisältää kirjastojen tiedot
// Paluuarvo: totuusarvo sen mukaan onko luettava tiedosto
// oikeanmallinen tai ylipäänsä luettavissa
bool isFileReadable(vector<Library>& libraries) {
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream tiedosto_olio(file_name);

    // Tarkistetaan, voiko tiedostoa avata
    if (not tiedosto_olio) {
        cout << "Error: input file cannot be opened" << endl;
        return false;
    }

    // Luetaan tiedoston rivit yksi kerrallaan
    string row;
    vector<string> splitted_row;
    while(getline(tiedosto_olio,row)) {
        // Jaetaan rivi osiin
        splitted_row = split(row, ';');

        // Tarkistetaan, että rivi sisältää neljä osaa ja että ne eivät
        // ole tyhjiä
        if(splitted_row.size() != 4 || find(splitted_row.begin(),
            splitted_row.end(), "") != splitted_row.end()) {
            cout << "Error: empty field" << endl;
            return false;
        }

        // Tarkistetaan, onko kirjasto jo olemassa tietorakenteessa
        bool library_exists = false;
        for (auto& library : libraries) {
            if (library.name == splitted_row[0]) {
                // Jos kirjasto on olemassa, lisätään uusi kirja sen
                // tietokantaan
                addToStructure(library, splitted_row);
                library_exists = true;
                break;
            }
        }

        // Jos kirjastoa ei ole vielä tietorakenteessa, luodaan uusi
        // kirjasto-olio ja lisätään se tietorakenteeseen
        if (!library_exists) {
            Library library;
           addToStructure(library, splitted_row);
            libraries.push_back(library);
        }
    }

    tiedosto_olio.close();
    return true;
}



// Funktio tulostaa kirjastojen nimet aakkosjärjestyksessä.
// Parametrit: vector<Library>& libraries - viittaus kirjastovektoriin,
// joka sisältää kirjastojen tiedot
// Paluuarvo: ei ole
void printLibrariesInOrder(vector<Library>& libraries){

    vector<string> library_names;

    // Käydään läpi kaikki kirjastot ja lisätään niiden nimet
    // library_names -vektoriin
    for(auto& library : libraries) {
        library_names.push_back(library.name);
    }

    // Järjestetään kirjastojen nimet aakkosjärjestykseen
    sort(library_names.begin(), library_names.end());

    // Tulostetaan kirjastojen nimet
    for(auto& library_name : library_names) {
        cout << library_name << endl;
    }
}



// Funktio tulostaa kaikki lainattavissa olevat kirjat kirjastovektorista.
// Parametrit: vector<Library>& libraries - viittaus kirjastovektoriin,
// joka sisältää kirjastojen tiedot
// Paluuarvo: ei ole
void printLoanableBooks(vector<Library>& libraries) {

    // Alustetaan uusi map-kirjasto lainattaville kirjoille
    map<string, Book> loanable_books;

    // Käydään läpi kaikki kirjastot ja niiden kirjat
    for (auto& library : libraries) {
        for (auto& book_pair : library.books) {
            // Jos kirjalla ei ole varauksia, lisätään se lainattavien
            // kirjojen kirjastoon
             if (book_pair.second.reservations == 0) {
                 loanable_books[book_pair.second.author
                        + book_pair.first] = book_pair.second;
             }
        }
    }

    // Tulostetaan kaikki lainattavissa olevat kirjat
    for (auto& book_pair : loanable_books) {
        cout << book_pair.second.author << ": " << book_pair.second.title << endl;
    }
}



// Funktio tulostaa kirjaston kaikki kirjat aakkosjärjestyksessä
// Parametrit: vector<Library>& libraries - viittaus kirjastovektoriin,
// joka sisältää kirjastojen tiedot, kirjaston nimi
// Paluuarvo: ei ole
void printMaterials(vector<Library>& libraries, const string& library_name) {

    // Etsitään kirjasto, jonka nimi on annettu nimi parametrina.
    auto library_iter = find_if(libraries.begin(), libraries.end(),
        [&library_name](const Library& library)
                { return library.name == library_name; });

    // Jos kirjastoa ei löydy
    if (library_iter == libraries.end()) {
        cout << "Error: unknown library" << endl;
        return;
    }

    // Vektori, joka sisältää kirjoittajien ja kirjojen nimi -parit.
    vector<pair<string, string>> books;
    for (auto& book_pair : library_iter->books) {
        // Lisätään kirjan nimi ja kirjoittaja vectoriin.
        books.emplace_back(book_pair.second.title, book_pair.second.author);
    }

    // Järjestetään kirjat kirjoittajan nimen mukaan.
    sort(books.begin(), books.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second < rhs.second;
    });

    // Tulostetaan kirjoittajan nimi ja kirjan nimi.
    for (auto& book : books) {
        cout << book.second << ": " << book.first << endl;
    }
}



// Tulostaa tietyn kirjailijan kirjoittamien kirjojen
// varaustilanteen tietyssä kirjastossa
// Parametrit: kirjastojen tietueet sisältävä vektori, kirjaston nimi,
// ja kirjailijan nimi
// Paluuarvo: ei arvoa
void printBooks(vector<Library>& libraries, const string& library_name,
                const string& author_name) {

    // Etsitään kirjasto vektorista
    auto library_iter = find_if(libraries.begin(), libraries.end(),
        [&library_name](const Library& library)
                { return library.name == library_name; });

     // Jos kirjastoa ei löydy
    if (library_iter == libraries.end()) {
        cout << "Error: unknown library" << endl;
        return;
    }

    bool author_found = false;

    // Käydään läpi kirjastossa olevat kirjat
    for (auto& book_pair : library_iter->books) {
        // Jos kirjailija löytyy
        if (book_pair.second.author == author_name) {
            // Jos kirja on saatavilla eli varauksia ei ole
            if (book_pair.second.reservations == 0) {
                cout << book_pair.second.title << " --- " <<
                        "on the shelf" << endl;
                author_found = true;
            }

            else {
                // Muussa tapauksessa tulosta kirjan nimi ja varauksien määrä
                 cout << book_pair.second.title << " --- " <<
                         book_pair.second.reservations <<
                         " reservations" << endl;
                 author_found = true;
            }
        }
    }

     // Jos kirjailijaa ei löytynyt, tulosta virheilmoitus
    if (!author_found) {
        cout << "Error: unknown author" << endl;
    }
}



// Funktio tulostaa lyhyimmän varausjonon halutun tekijän halutulle kirjalle
// ja sen alle aakkosjärjestyksessä kirjastot, joista kirja löytyy tällä
// samanpituisella varausjonolla.
// Parametrit: kirjastot sisältävä vektori, kirjailijan nimi
// ja kirjan otsikon sisältävä vektori
// Paluuarvo: ei arvoa
void reservable(vector<Library>& libraries, const string& author,
                vector<string>& title) {

    bool found = false;

    multimap<int, string> reservations;

    // muuttuja lyhimmän varausjonon tallentamiseen
    int shortest_reservation = INT_MAX;

    // Käydään läpi kaikki kirjastot ja niiden kirjat
    for (auto& library : libraries) {
        for (auto& book_pair : library.books) {
            for (auto& book_title : title) {

                 // Jos kirja löytyy ja sen tekijä ja nimi ovat oikein
                if (book_pair.second.author == author
                        && book_pair.second.title == book_title) {
                    found = true;

                     // Jos varausmäärä on yli 100, kirjaa ei voi varata
                    if (book_pair.second.reservations >= MAXIMUM_RESERVATIONS) {
                        cout << "Book is not reservable from any library" <<
                                endl;
                        return;
                    }
                    reservations.emplace(book_pair.second.reservations,
                                         library.name);
                    // päivitetään lyhin varausjono
                    shortest_reservation = min(shortest_reservation,
                                               book_pair.second.reservations);
                }
            }
        }
    }

    // Jos kirjaa ei löydy
    if (!found) {
        cout << "Book is not a library book" << endl;
        return;
    }

    // Jos kirjaa on hyllyssä
    if (shortest_reservation == 0) {
        cout << "on the shelf" <<endl;
    }
    else {
        // tulostetaan lyhin varausjono
        cout << shortest_reservation << " reservations" << endl;
    }

    // Tulostetaan lyhimmän varausjonon kirjastot aakkosjärjestyksessä
    auto it = reservations.equal_range(shortest_reservation);

    vector<string> libraries_to_print;

    for (auto it2 = it.first; it2 != it.second; ++it2) {
        libraries_to_print.push_back(it2->second);
    }

    sort(libraries_to_print.begin(), libraries_to_print.end());

    for (auto& library_name : libraries_to_print) {
        cout << "--- " << library_name << endl;
    }

    // Tulostetaan kirjastot, joissa kirja on hyllyssä
    for (auto& library : libraries) {
        for (auto& book_pair : library.books) {
            for (auto& book_title : title) {

                if (book_pair.second.author == author
                        && book_pair.second.title == book_title) {

                    if (book_pair.second.reservations == 0
                            && library.name != libraries_to_print[0]) {
                        cout << "--- " << library.name << endl;
                    }
                }
            }
        }
    }
}



//Tarkistaa, että annetussa komennossa on oikea lukumäärä komponentteja.
//Parametrit: komento vektorina jossa komennon komponentit vektorissa
//omina alkioinaan
//Paluuarvo: oliko komennossa oikea lukumäärä komponentteja vai ei
bool isCommandLength (vector<string> command_parts,
                      unsigned int right_length) {
    if(command_parts.size() != right_length) {
        cout<<"Error: wrong number of parameters"<<endl;
        return false;
    }
    else {
        return true;
    }
}



// Pääfunktio
// Kutsuu ylläolevia funktioita ja toteuttaa ohjelman paluuarvot
// Paluuarvot: jos tiedostoa ei saada luettua, palautetaan EXIT_FAILURE,
// jos ohjelma saadaan suoritettua menestyksekkäästi loppuun,
// palautetaan EXIT_SUCCESS
int main() {

    // Alustetaan vektori, johon tallennetaan kirjastojen tietueet
    vector<struct Library> libraries;

    // Kokeillaan tiedoston lukemista
    // Jos lukeminen ei onnistu lopetetaan ohjelman suoritus
    if (isFileReadable(libraries) == false) {
        return EXIT_FAILURE;
    }

    // Alustetaan vektori, johon käyttäjän antaman komennon eri osat
    // tallennetaan
    string command;
    vector<string> command_parts;

    // Silmukka, joka kysyy käyttäjältä komentoja ja ohjelma
    // kutsuu eri funktioita komentojen mukaisesti.
    // Silmukka loppuu lopetuskomentoon 'quit'.
    while(command != "quit") {
        cout << "lib> ";
        getline(cin, command);
        command_parts = split(command, ' ');

    // Jokaisen komennon kohdalla tarkistetaan, että komennossa
    // on oikea määrä osia.
    if (command_parts.at(0) == "libraries") {
        if (isCommandLength(command_parts, 1) == true) {
           printLibrariesInOrder(libraries);
        }
    }


    else if (command_parts.at(0) == "loanable") {
        if (isCommandLength(command_parts, 1) == true) {
            printLoanableBooks(libraries);
        }
    }


    else if (command_parts.at(0) == "material") {
        if (isCommandLength(command_parts, 2) == true) {
            string library = command_parts.at(1);
            printMaterials(libraries, library);
        }
    }


    else if (command_parts.at(0) == "books") {
        if (isCommandLength(command_parts, 3) == true) {
            string library = command_parts.at(1);
            string author = command_parts.at(2);
            printBooks(libraries, library, author);
        }
    }


    else if (command_parts.at(0) == "reservable") {
        if (command_parts.size() == 1) {
            cout<<"Error: wrong number of parameters"<<endl;
            continue;
        }
        else if (command_parts.size() == 2) {
            cout<<"Error: wrong number of parameters"<<endl;
            continue;
        }
        else {
            string author_name = command_parts.at(1);

            // Alustetaan vektori, johon kirjan otsikko tallennetaan
            vector <string> title;

            string book_name;

            // Erotetaan komennosta kirjan nimi
            istringstream iss(command);
            iss >> command >> author_name >> ws;
            getline(iss, book_name);

            // Katsotaan onko kirjan nimi kirjoitettu lainausmerkeissä
            char quote_mark = book_name.front();

            // Jos kirjan nimi on kirjoitettu lainausmerkeissä
            // poistetaan lainausmerkit kirjan nimen ympäriltä
            if (quote_mark == '"' || quote_mark == '\'') {
                book_name.erase(book_name.begin());
                    book_name.erase(book_name.end()-1);
            }

            // Lisätään kirjan otsikko vektoriin
            title.push_back(book_name);

            reservable(libraries, author_name, title);
        }
    }


    // Ohjelman lopetuskomento
    else if (command_parts.at(0) == "quit") {
        if(isCommandLength(command_parts, 1) == true) {
            break;
        }
    }


    // Virheilmoitus, jos annetaan tuntematon komento
    else {
        cout<<"Error: unknown command"<<endl;
        continue;
    }
    }

    return EXIT_SUCCESS;

}
