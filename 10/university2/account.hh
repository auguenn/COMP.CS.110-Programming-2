/* Luokka: Account
 * --------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet
 * -------------
 * Luokka, joka edustaa opiskelijaa tai henkilökunnan jäsentä yliopistojärjsetelmässä.
 *
 * --------------
 * Nimi: Enna Augustin
 * Opiskelijanumero: 50235634
 * Käyttäjätunnus: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 *
 * HUOM: kohdat, joissa englanninkielinen kommentointi on valmiista
 * koodipohjasta.
 *
 * */


#ifndef ACCOUNT_HH
#define ACCOUNT_HH

#include <string>
#include <vector>
#include <algorithm>
#include <memory>



class Course;

// Tietue yksittäisen käyttäjän tietojen tallentamiseksi
struct Accounts_info {
    Course *course_;
    std::shared_ptr<Accounts_info> next;
};


const std::string NO_SIGNUPS = "No signups found on this course.";
const std::string SIGNED_UP = "Signed up on the course.";
const std::string COMPLETED = "Course completed.";
const std::string GRADUATED = "Graduated, all courses completed.";


class Account
{
public:
    /**
     * @brief Account constructor
     * @param full_name as "firstname lastname"
     * @param account_number
     * @param duplicates tells the number of full namesakes
     * @param university_suffix is the e-mail suffix e.g. "tuni.fi"
     */
    Account(const std::string& full_name, int account_number, int duplicates,
            const std::string& university_suffix);

    /**
     * @brief Account destructor
     */
    ~Account();

    /**
     * @brief print account info on one line
     */
    void print() const;


    /**
     * @brief get_email
     * @return email linked to this account
     */
    std::string get_email() const;


    /**
     * @brief get_full_name
     * @return full name of this account
     */
    std::string get_full_name() const;


    /**
     * @brief get_account_number
     * @return account number linked to this account
     */
    int get_account_number() const;


    /**
     * @brief add_course
     * @param course
     * Lisää kurssi opiskelijan tällä hetkellä suorittamien kurssien listaan ja
     * tietueeseen.
     */
    void add_course(Course *course);


    /**
     * @brief remove_course
     * @param course
     * Lisää kurssin suoritettujen kurssien listaan sekä poistaa sen kurssien
     * tietueesta.
     */
    void remove_course(Course *course);


    /**
     * @brief print_current
     * Tulostaa opiskelijan tällä hetkellä opiskelemat kurssit.
     */
    void print_current(std::shared_ptr<Accounts_info> top) const;


    /**
     * @brief print_completed
     * Tulostaa opiskelijan suorittamat kurssit.
     */
    void print_completed() const;


    /**
     * @brief print_study_state
     * Tulostaa opintojen tilan eli sen mitä kursseja opiskelija tällä hetkellä
     * käy, mitä käy nyt ja kuinka monta opintopistettä on suoritettu.
     *
     */
    void print_study_state() const;


    /**
     * @brief graduate
     * Asettaa gratuated_ attribuutin todeksi, jos opiskelija on suorittanut
     * kaikki kurssit. Jos opiskelija ei ole suoritanut kaikkia kursseja
     * muutetaan kaikki meneillään olevat kurssit suoritetuiksi.
     */
     void graduate();


     /**
      * @brief get_graduated
      * @return Tosi jos opiskelija on valmistunut, muussa tapauksessa epätosi.
      */
     bool get_graduated() const;



private:
    std::string full_name_;
    std::string last_name_;
    std::string first_name_;
    std::string email_;
    const int account_number_;


    // graduated_ on tosi jos opiskelija on suorittanut kaikki kurssit.
    // Muuten se on epätosi.
    bool graduated_ = false;

    // vektori, joka sisältää kurssit, joille opiskelija on ilmottautunut
    std::vector<Course *> courses_;

    // vektori, joka sisältää opiskelija  suoritttamat kurssit
    std::vector<Course *> completed_courses_;

    // Osoitin, joka osoittaa käyttäjätilien tietueen kärkeen.
    std::shared_ptr<Accounts_info> top_;
};

#endif // ACCOUNT_HH


