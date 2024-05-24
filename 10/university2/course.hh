/* Luokka: Course
 * -------------
 * COMP.CS.110 Ohjelmointi 2: Rakenteet
 * -------------
 * Luokka, joka edustaa yksittäistä kurssia. Kurssi koostuu nimestä,
 * kurssikoodista, henkilökunnasta sekä opiskelijoista.
 *
 *
 * --------------
 * Nimi: Enna Augustin
* Opiskelijanumero: 50235634
* Käyttäjätunnus: xxenau
* E-Mail: enna.augustin@tuni.fi
*
*
* HUOM: Kohdat, joissa on englanninkielinen kommentointi ovat valmiista
* koodipohjasta.
*
* */

#ifndef COURSE_HH
#define COURSE_HH

#include "account.hh"
#include <iostream>
#include <memory>
#include <string>
#include <vector>


const std::string STUDENT_ADDED = "A new student has been added.";
const std::string STAFF_ADDED = "A new staff member has been added.";
const std::string STAFF_EXISTS = "Error: Staff member already added on this course.";
const std::string STUDENT_EXISTS = "Error: Student already added on this course.";
const std::string STUDENT_COMPLETED = "Error: Student already completed this course.";


// Tietue yksittäisen kurssin tietojen tallentamiseksi.
struct Course_info {
    Account *account;
    std::shared_ptr<Course_info> next;
};


class Course {
public:
    /**
     * @brief Course
     * @param code unique code for the course, used as id
     * @param name
     * @param credits
     */
    Course( const std::string& code, const std::string& name, int credits = 5);


    /**
     * @brief Course destructor
     */
    ~Course();


    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, pring also a newline
     * at the end.
     */
    void print_info(bool print_new_line);


    /**
     * @brief print_long_info
     * Print longer course info with staff.
     */
    void print_long_info();


    /**
     * @brief print_staff
     * Print all staff of the course.
     */
    void print_staff();


    /**
     * @brief add staff
     * @param new_staff
     * Add a staff member to course.
     */
    void add_staff(Account* new_staff_member);


    /**
     * @brief get_code
     * @return the course code.
     */
    const std::string get_code() const;


    /**
     * @brief get_credits
     * @return the amount of credits this course is valued.
     */
    int get_credits() const;


    /**
     * @brief get_name
     * @return kurssin nimi
     */
     const std::string get_name() const;



    /**
     * @brief add_student
     * Lisää opiskelijan kurssille
     */
    void add_student(Account *new_student);



    /**
     * @is_signed_up
     * @param student
     * @return tosi, jos opiskelija on ilmottautunut kurssille.
     */
    bool is_signed_up(Account *student);


    /**
     * @brief print_signups
     * Tulostaa kaikki kurssille ilmottautuneet opiskelijat.
     */
    void print_signups();


    /**
     * @brief complete_course
     * @param student
     * Merkitsee opiskelijan suorittaman kurssin suoritetuksi.
     */
    void complete_course(Account *student);



private:
    std::string course_code_;
    std::string name_;
    int credits_;
    std::vector<Account*> course_staff_;


    // osoitin ensimmäiseen elementtiin listassa, joka sisältää opiskelijoita,
    // jotka ovat ilmoittautuneet kurssille, mutta eivät ole vielä
    // suorittaneet sitä.
    std::shared_ptr<Course_info> top_;

    // vektori, joka sisältää kaikki kurssille ilmottautuneet opiskelijat.
    // Myös ne jotka ovat jo suorittaneet sen.
    std::vector<Account *> course_students_;

    // vektori, joka sisältää kurssin suorittaneet opiskelijat.
    std::vector<Account *> completed_courses_;
};

#endif // COURSE_HH


