/**
 * Yliopisto
 *
 * Kuvaus:
 * Ohjelma toteuttaa yliopistojärjestelmän, jota voidaan käyttää uusien
 * kurssien ja käyttäjätilien luomiseen sekä kurssien ja käyttäjätilien
 * tietojen tulostamiseen.
 * Ohjelma on jaettu 8 pääosaan: account.hh, account.cpp, course.hh,
 * course.cpp, main.cc, university.hh, university.cpp, utils.hh,
 * utils.cpp.
 *
 * main.cc-tiedosto sisältää ohjelman pääfunktion, joka on ohjelman
 * sisäänkäyntipiste.
 *
 * university.hh-tiedosto sisältää luokan University, joka on ohjelman
 * pääluokka. university.cpp-tiedosto sisältää luokan University
 * toteutuksen.
 *
 * account.hh-tiedosto sisältää luokan Account, joka edustaa käyttäjätiliä
 * yliopistojärjestelmässä. account.cpp-tiedosto sisältää luokan Account
 * toteutuksen.
 *
 * course.hh-tiedosto sisältää luokan Course, joka edustaa kurssia
 * yliopistojärjestelmässä. course.cpp-tiedosto sisältää luokan Course
 * toteutuksen.
 *
 * utils.hh-tiedosto sisältää luokan Utils, joka sisältää apufunktioita.
 * utils.cpp-tiedosto sisältää luokan Utils toteutuksen.
 *
 * Ohjelman käynnistyessä täytyy ensin luoda uusia kursseja ja käyttäjiä.
 * Ohjelma kysyy kurssin nimen, kurssikoodin, opintopisteiden määrän,
 * opiskelijat ja opettajat. Kunkin käyttäjätilin kohdalla
 * käyttäjän on annettava tilin koko nimi, sähköpostiosoite (vapaaehtoinen).
 * Jos sähköpostiosoitetta ei anneta, ohjelma generoi sellaisen tilille.
 *
 * Seuraavaksi on ilmoittauduttava kursseille. Mikäli käyttäjät suorittavat
 * kurssin, he saavat opintopisteitä. Käyttäjä voi myös valmistua yliopistosta.
 * Jos käyttäjä valmistuu, ei hän voi enää ilmottautua kursseille.
 *
 * Ohjelmalla on myös mahdollisuus tulostaa kurssien ja käyttäjätilien tiedot.
 * Käyttäjä voi tulostaa kaikkien kurssien ja käyttäjätilien tiedot tai tietyn
 * kurssin tai tilin tiedot.
 *
 * Lopuksi ohjelma lopetetaan, kun käyttäjä antaa lopetuskomennon.
 *
 *
 * Ohjelman kirjoittaja
 * Nimi: Enna Augustin
 * Opiskelijanumero: 50235634
 * Käyttäjätunnus: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 *
 */


#include "cli.hh"
#include "university.hh"


const std::string PROMPT = "Uni> ";


int main()
{
    University* university = new University("tuni.fi");
    Cli cli(university, PROMPT);
    while ( cli.exec() ){}

    delete university;
    return EXIT_SUCCESS;
}

