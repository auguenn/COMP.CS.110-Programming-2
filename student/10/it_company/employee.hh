/* Class Employee
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing an employee in an IT company.
 *
 * Program author:
 * Name: Enna Augustin
 * Student number: 50235634
 * UserID: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 * */


#ifndef EMPLOYEE_HH
#define EMPLOYEE_HH

#include "date.hh"
#include <string>
#include <set>
#include <map>
#include <vector>

const std::string NONE = "None";


class Employee
{
public:
    /**
     * @brief Employee default constructor
     */
    Employee();

    /**
     * @brief Employee constructor
     * @param id
     */
    Employee(const std::string& id);



    /**
     * @brief Employee constructor (not in use)
     * @param id
     * @param date_of_birth
     */
    Employee(const std::string& id, const std::string& date_of_birth);

    /**
     * @brief Employee destructor
     */
    ~Employee();


    /**
     * @brief get_id
     * @return employee's id
     */
    std::string get_id() const;


    /**
     * @brief Gets the employee's skills
     * @param : None
     * @return A set of the employee's skills
     */
    std::set<std::string> get_skills() const;


    /**
     * @brief : Adds a skill for an employee
     * @param : skill (name)
     * @return: None
     */
    void add_skill(const std::string& skill);


    /**
     * @brief : Adds a project for an employee
     * @param : project (name)
     * @param : Starting date
     * @return : None
     */
    void add_project(const std::string& name, Date start);


    /**
     * @brief : Ends a project for an employee (sets the ending date)
     * @param : Project (name)
     * @param : Ending date
     * @return : None
     */
    void end_project(const std::string& name, Date end);


    /**
     * @brief : Checks if the employee is assigned to the project
     * @param : Project (project_id) as a referenced string
     * @return : Truth value whether the employee is assigned to the project
     */
    bool is_assigned_to_project(const std::string& project_id) const;


    /**
     * @brief print_id
     * @param pre_text
     * Prints employee's id, before that prints the pre_text
     */
    void print_id(const std::string& pre_text) const;


    /**
     * @brief print_skills
     * Prints employee's skills, all skills in one line, separated by a comma,
     * if the employee has no skills, prints "None"
     */
    void print_skills() const;


    /**
     * @brief : Prints the project info (name, starting date, ending date)
     * @param : None
     * @return : None
     */
    void print_projects() const;


    /**
     * @brief operator<
     * @param : rhs
     * Comparison based on id_'s, enables forming a set of Employee objects
     */
    bool operator<(const Employee& rhs) const;



private:
    /**
     * @brief obvious attributes
     */
    std::string id_;               // Can be a name or any other identifier
    Date date_of_birth_;           // Not actually needed

    std::set<std::string> skills_; // IT skills


    // A struct to save the date information for an employee's projects
    struct DateRange {
        Date start_date;
        Date end_date;
    };

    // A container to save the employee's projects
    std::map<std::string, DateRange> projects_;

};

#endif // EMPLOYEE_HH
