/* Nimi: Enna Augustin
* Opiskelijanumero: 50235634
* Käyttäjätunnus: xxenau
* E-Mail: enna.augustin@tuni.fi
*
*
* HUOM: Kohdat joissa kommentointi on englanniksi ovat valmiista koodipohjasta.
*
* */


#include "course.hh"
#include "university.hh"
#include <iostream>


Course::Course(const std::string& code, const std::string& name, int credits):
    course_code_(code), name_(name), credits_(credits)
{
}


Course::~Course()
{
}


void Course::print_info(bool print_new_line)
{
    std::cout << course_code_ << " : " << name_;
    if ( print_new_line )
    {
        std::cout << std::endl;
    }
}


void Course::print_long_info()
{
    std::cout << "* Course name: " << name_ << std::endl
              << "* Code: " << course_code_ << std::endl;
    print_staff();
}


void Course::print_staff()
{
    std::cout << "* Staff: " << std::endl;
    for (auto member : course_staff_ )
    {
        member->print();
    }
}


void Course::add_staff(Account *new_staff_member)
{
    // Checking if account is already a staff member
    for ( unsigned int i = 0; i < course_staff_.size(); ++i )
    {
        if ( course_staff_.at(i) == new_staff_member )
        {
            std::cout << STAFF_EXISTS << std::endl;
            return;
        }
    }

    course_staff_.push_back(new_staff_member);
    std::cout << STAFF_ADDED << std::endl;
}


const std::string Course::get_code() const
{
    return course_code_;
}


int Course::get_credits() const
{
    return credits_;
}


// Haetaan kurssin nimi
const std::string Course::get_name() const
{
    return name_;
}


bool Course::is_signed_up(Account *student)
{

    // Alustetaan current shared_ptr-muuttujaksi, joka osoittaa listan
    // ensimmäiseen elementtiin "top_".
    std::shared_ptr<Course_info> current = top_;

    while (current != nullptr) {
        // Tarkistetaan, onko nykyisen elementin käyttäjätili sama kuin
        // etsittävä "student".
        if (current->account == student) {
            return true;
        }

        // Siirrytään seuraavaan elementtiin "next".
        current = current->next;
    }
    return false;
}


void Course::add_student(Account *new_student)
{

    // Tarkistetaan onko opiskelija jo valmistunut.
        if (new_student->get_graduated()) {
            std::cout << ALREADY_GRADUATED << std::endl;
            return;
        }

    // Tarkistetaan onko opiskelija jo suorittanut kurssin.
    if (find(completed_courses_.begin(), completed_courses_.end(),
             new_student) != completed_courses_.end()) {
        std::cout << STUDENT_COMPLETED << std::endl;
        return;
    }

    // Tarkistaa onko opiskelija jo ilmottautunut kurssille.
    if (find(course_students_.begin(), course_students_.end(), new_student) !=
        course_students_.end()) {
        std::cout << STUDENT_EXISTS << std::endl;
        return;
    }

    // Lisätään opiskelijat kurssin tietueeseen.
    course_students_.push_back(new_student);
    std::shared_ptr<Course_info> new_data =
        std::make_shared<Course_info>(Course_info{new_student, top_});
    top_ = new_data;
    std::cout << SIGNED_UP << std::endl;
}


void Course::print_signups()
{
    // Tulostaa kaikki kurssille ilmottautuneet opiskelijat. Myös ne, jotka
    // ovat jo suorittaneet kurssin.
    for (auto student : course_students_) {
        student->print();
    }
}

void Course::complete_course(Account *student)
{

    // Tarkistetaan onko opiskelija ilmottautunut kurssille.
    if (!is_signed_up(student)) {
        std::cout << NO_SIGNUPS << std::endl;
        return;
    }

    // Lisätään opiskelija suoritettuihin kursseihin
    completed_courses_.push_back(student);

    // Poistetaan opiskelija kurssin tietueesta.´
    std::shared_ptr<Course_info> current = top_;
    std::shared_ptr<Course_info> previous = nullptr;

    while (current != nullptr) {
        if (current->account == student) {
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

    std::cout << COMPLETED << std::endl;
}
