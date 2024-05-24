/* Nimi: Enna Augustin
* Opiskelijanumero: 50235634
* Käyttäjätunnus: xxenau
* E-Mail: enna.augustin@tuni.fi
*
*
* HUOM: Kohdat, joissa on englanninkielinen kommentointi ovat valmiista
* koodipohjasta.
*
* */


#include "university.hh"
#include <iostream>
#include <string>

University::University(const std::string& email_suffix):
    running_number_(111111), email_suffix_(email_suffix)
{
}

University::~University()
{
    for ( auto course : courses_ )
    {
        delete course.second;
    }

    for ( auto account : accounts_ )
    {
        delete account.second;
    }
}

void University::new_course(Params params)
{
    std::string code = params.at(0);
    std::string name = params.at(1);

    if ( courses_.find(code) != courses_.end() )
    {
        std::cout << ALREADY_EXISTS << std::endl;
        return;
    }
    else
    {
        std::cout << NEW_COURSE << std::endl;
    }

    Course* n_course = new Course(code, name);
    courses_.insert({n_course->get_code(), n_course});
}

void University::print_courses(Params)
{
    for ( auto course : courses_ )
    {
        course.second->print_info(true);
    }
}

void University::print_course(Params params)
{
    std::string code = params.at(0);

    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }

    courses_.at(code)->print_long_info();
}

void University::new_account(Params params)
{
    std::string full_name = params.at(0);

    int num = 0;
    for ( std::map<int, Account*>::iterator iter = accounts_.begin();
          iter != accounts_.end();
          ++iter )
    {
        if ( iter->second->get_full_name() == full_name )
        {
            std::string email = iter->second->get_email();
            num = Utils::numeric_part(email);
            if(num == 0)
            {
                ++num;
            }
            ++num;
        }
    }

    int account_number = running_number_++;
    Account* n_account = new Account(full_name, account_number, num,
                                     email_suffix_);
    accounts_.insert({account_number, n_account});
    std::cout << NEW_ACCOUNT << std::endl;
    n_account->print();
}

void University::print_accounts(Params)
{
    for ( auto account : accounts_ )
    {
        account.second->print();
    }
}

void University::print_account(Params params)
{
    int account = std::stoi(params.at(0));

    std::map<int, Account*>::iterator iter = accounts_.find(account);

    if ( iter == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }
    iter->second->print();
}

void University::add_staff(Params params)
{
    std::string code = params.at(0);
    int account = std::stoi(params.at(1));

    if ( courses_.find(code) == courses_.end() )
    {
        std::cout << CANT_FIND << code << std::endl;
        return;
    }
    if ( accounts_.find(account) == accounts_.end() )
    {
        std::cout << CANT_FIND << account << std::endl;
        return;
    }

    courses_.at(code)->add_staff(accounts_.at(account));
}


// Tarkistetaan että käyttäjä on olemassa
bool University::check_account_exists(int account) const {
    if (accounts_.find(account) == accounts_.end()) {
        std::cout << CANT_FIND << account << std::endl;
        return false;
    }
    return true;
}

// Tarkistetaan että kurssi on olemassa.
bool University::check_course_exists(std::string code) const {
    if (courses_.find(code) == courses_.end()) {
        std::cout << CANT_FIND << code << std::endl;
        return false;
    }
    return true;
}


void University::sign_up(Params params)
{
    std::string code = params.at(0);
    int account = stoi(params.at(1));

    // Tarkistetaan että kurssi ja käyttäjä ovat olemassa
    if (!check_course_exists(code) || !check_account_exists(account)) {
        return;
    }

    // Lisätään käyttäjä kurssin ilmottautuneisiin.
    courses_.at(code)->add_student(accounts_.at(account));

    // Lisätään kurssi käyttäjän ilmottautumisiin.
    accounts_.at(account)->add_course(courses_.at(code));
}


void University::complete(Params params)
{
    std::string code = params.at(0);
    int account = stoi(params.at(1));

    // Tarkistetaan että kurssi ja käyttäjä ovat olemassa
    if (!check_course_exists(code) || !check_account_exists(account)) {
        return;
    }

    // Merkitään kurssi suoritetuksi käyttäjälle.
    courses_.at(code)->complete_course(accounts_.at(account));

    // Poistetaan kurssi käyttäjän suoritettavissa olevista kursseista.
    accounts_.at(account)->remove_course(courses_.at(code));

}


void University::print_signups(Params params)
{
    std::string code = params.at(0);

    // Tarkistetaan onko kurssi olemassa.
    if (!check_course_exists(code)) {
        return;
    }

    // Tulostetaan kurssille ilmottautuneiden opiskelijoiden tiedot.
    courses_.at(code)->print_signups();

}


void University::print_completed(Params params)
{
    int account = stoi(params.at(0));

    // Tarkista onko käyttäjä olemassa.
    if (!check_account_exists(account)) {
        return;
    }

    // Tulosta suoritetut kurssit
    accounts_.at(account)->print_completed();
}


void University::print_study_state(Params params)
{
    int account = stoi(params.at(0));

    // Tarkista onko käyttäjä olemassa.
    if (!check_account_exists(account)) {
        return;
    }

    // Tulosta opintojen tila
    accounts_.at(account)->print_study_state();

}


void University::graduate(Params params)
{
    int account = stoi(params.at(0));

    // Tarkista onko käyttäjä olemassa.
    if (!check_account_exists(account)) {
        return;
    }

    // Merkitse opiskelija valmistuneeksi
    accounts_.at(account)->graduate();


}
