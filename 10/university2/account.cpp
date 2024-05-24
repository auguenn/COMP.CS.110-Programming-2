/* Nimi: Enna Augustin
* Opiskelijanumero: 50235634
* Käyttäjätunnus: xxenau
* E-Mail: enna.augustin@tuni.fi
*
* HUOM: kohdat, joissa on englanninkielinen
* kommentointi ovat valmiista koodipohjasta.
* */


#include "account.hh"
#include "utils.hh"
#include "course.hh"
#include <iostream>


Account::Account(const std::string& full_name, int account_number,
                 int duplicates, const std::string& university_suffix):
    full_name_(full_name),
    last_name_(""),
    first_name_(""),
    account_number_(account_number)
{
    std::vector<std::string> name = Utils::split(full_name_, ' ');
    last_name_ = name.back();
    first_name_ = name.front();

    // Constructing e-mail address
    email_ = Utils::to_lower(first_name_);
    email_ += ".";
    if ( duplicates > 0 )
    {
        email_ += std::to_string(duplicates);
        email_ += ".";
    }
    email_ += Utils::to_lower(last_name_);
    email_ += "@";
    email_ += university_suffix;
}


Account::~Account()
{
}


void Account::print() const
{
    std::cout << account_number_ << ": "
              << first_name_ << " "
              << last_name_  << ", "
              << email_ << std::endl;
}


std::string Account::get_email() const
{
    return email_;
}


std::string Account::get_full_name() const
{
    return full_name_;
}

int Account::get_account_number() const
{
    return account_number_;
}


void Account::add_course(Course *course)
{
    // Tarkistaa onko opiskelija jo valmistunut
    if (graduated_) {
        return;
    }

    // Tarkistaa onko kurssi jo lisätty opiskelijalle
    if (find(courses_.begin(), courses_.end(), course) != courses_.end()) {
        return;
    }

    // Lisää kurssi käyttäjän tietueeseen
    std::shared_ptr<Accounts_info> new_data =
    std::make_shared<Accounts_info>(Accounts_info{course, top_});
    top_ = new_data;
    courses_.push_back(course);
}


void Account::remove_course(Course *course)
{
    // Tarkistaa onko opiskelija jo valmistunut
    if (graduated_) {
        return;
    }

    // Tarkistaa onko kurssi jo poistettu
    if (find(courses_.begin(), courses_.end(), course) == courses_.end()) {
        return;
    }

    // Poistaa kurssin käyttäjältä
    courses_.erase(remove(courses_.begin(), courses_.end(), course),
                   courses_.end());

    // Lisää kurssin suoritettuihin kursseihin
    completed_courses_.push_back(course);


    // Poistaa kurssin käyttäjän tietueesta
    std::shared_ptr<Accounts_info> current = top_;
    std::shared_ptr<Accounts_info> previous = nullptr;

    while (current != nullptr) {
        if (current->course_ == course) {
            if (previous == nullptr) {
                top_ = current->next;
            } else {
                previous->next = current->next;
            }
            break;
        }
        previous = current;
        current = current->next;
    }
}


void Account::print_current(std::shared_ptr<Accounts_info> current) const
{
    if (current == nullptr) {
        return;
    }

    // Tulostaa tällä hetkellä suoritettavat kurssit.
    print_current(current->next);
    std::cout << current->course_->get_code() << " : "
         << current->course_->get_name() << std::endl;
}


void Account::print_completed() const
{
    int credits = 0;

    // Tulostaa suoritetut kurssit niiden suoritusjärjestyksessä.
    for (auto it = completed_courses_.begin(); it != completed_courses_.end();
         ++it) {
        std::cout << (*it)->get_code() << " : " <<
                     (*it)->get_name() << std::endl;
        credits += (*it)->get_credits();
    }

    std::cout << "Total credits: " << credits << std::endl;
}


void Account::print_study_state() const
{
    // Tulostaa tämänhetkiset kurssit siinä järjestyksessä kuin niille on
    // ilmottauduttu.
    std::cout << "Current:" << std::endl;
    std::shared_ptr<Accounts_info> current = top_;
    print_current(top_);

    // Tulostaa suoritetut kurssit siinä järjestyksessä kuin ne olivat
    // suoritettu sekä suoritettujen opintopisteiden kokonaismäärän.
    std::cout << "Completed:" << std::endl;
    print_completed();
}


// Merkitsee käyttäjän valmistuneeksi
bool Account::get_graduated() const
{
    return graduated_;
}


void Account::graduate()
{

    graduated_ = true;

    std::cout << GRADUATED << std::endl;

    // säilyttää suoritetut kurssit väliaikaisesti
    std::vector<Course *> temporary_completed_courses;

    // Merkitsee kaikki käyttäjän tietueessa olevat suorittamattomat kurssit
    // suoritetuiksi ja lisää ne suoritettujen kurssien vektoriin.
    std::shared_ptr<Accounts_info> current = top_;
    std::shared_ptr<Accounts_info> previous = nullptr;

    while (current != nullptr) {

        temporary_completed_courses.push_back(current->course_);

        if (previous == nullptr) {
            top_ = current->next;
        } else {
            previous->next = current->next;
        }

        previous = current;
        current = current->next;
    }

    // kääntää kurssit suoritusjärjestykseen
    reverse(temporary_completed_courses.begin(),
            temporary_completed_courses.end());

    // asettaa suoritetut kurssit listaan oikeaan järjestykseen
    for (auto it = temporary_completed_courses.begin();
         it != temporary_completed_courses.end(); ++it) {
        completed_courses_.push_back(*it);
    }

    // Tyhjentää kurssien tiedot
    top_ = nullptr;
}

