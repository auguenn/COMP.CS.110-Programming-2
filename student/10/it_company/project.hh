/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing a project in an IT company.
 *
 * Program author:
 * Name: Enna Augustin
 * Student number: 50235634
 * UserID: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 * */

#ifndef PROJECT_HH
#define PROJECT_HH


#include "employee.hh"
#include "date.hh"
#include "utils.hh"
#include <string>
#include <memory>
#include <set>

const std::string NOT_QUALIFIED = "Not qualified any more: ";


class Project
{
public:
    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as string ddmmyyyy)
     */
    Project(const std::string& id, const std::string& start);

    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as Date object)
     */
    Project(const std::string& id, const Date& start);

    /**
     * @brief Project destructor
     */
    ~Project();

    // More public methods

    /**
     * @brief : Gets the project's id
     * @param : None
     * @return : Id as string
     */
    std::string get_id() const;


    /**
     * @brief : Gets the project's requirements
     * @param : None
     * @return : Project's requirements in alphabetical order as a vector
     */
    std::vector<std::string> get_requirements();


    /**
     * @brief : Gets the staff assigned to the project
     * @param : None
     * @return : The assigned employees as a set
     */
    std::set<Employee*> get_assigned_staff();


    /**
     * @brief : Gets the project's starting date
     * @param : None
     * @return : Starting date as a Date object
     */
    Date get_start_date() const;


    /**
     * @brief Checks if the project is closed
     * @param : None
     * @return : A truth value whether the project is closed or not
     */
    bool is_closed();


    /**
     * @brief Closes the project
     * @param : The ending date as a referenced Date object
     * @return : None
     */
    void close_project(const Date& end);

    /**
     * @brief Checks if the project has the requirement
     * @param : Skill (=requirement) as a referenced string
     * @return : Truth value whether the project has the requirement
     */
    bool has_requirement(const std::string& skill);


    /**
     * @brief Project constructor
     * @param : id
     * @param : start (given as Date object)
     */
    void add_requirement(const std::string& req);


    /**
     * @brief Adds a employee to the project
     * @param : Staff_id as a Employee pointer
     * @return : None
     */
    void add_employee(Employee* staff_id);


    /**
     * @brief : Checks if the employee is assigned to the project
     * @param : Employee name as a referenced string
     * @return : Truth value whether the employee is assigned to the project or
     *           not
     */
    bool is_employee_in_project(const std::string& employee);


    /**
     * @brief : Set the end date (Date class) for the project when the project
     *          is closed.
     * @param : Ending date as a referenced Date object
     * @return: None
     */
    void set_end_date_for_assigned_staff(const Date& end_date);


    /**
     * @brief : Print start and end dates. Param pre_text gets printed before
     *          the dates.
     * @param : Pre_text to be printed before the information given as a
     *          referenced string
     * @return : None
     */
    void print_date_info(const std::string& pre_text) const;


    /**
     * @brief : Print the project's requirements
     * @param :  None
     * @return : None
     */
    void print_requirements() const;


    /**
     * @brief : Print the project's staff
     * @param : None
     * @return : None
     */
    void print_staff() const;



private:
    /**
     * @brief obvious attributes
     */
    std::string id_; // Can be a name or any other identifier
    Date start_;
    Date end_;

    // More attributes and private methods

    // A boolean attribute to check if the period is closed or not
    bool is_closed_;

   // Container for staff assigned to the project
   std::set<Employee*> assigned_staff_;

   // Container for projects requirements
   std::vector<std::string> requirements_;


};

#endif // PROJECT_HH
