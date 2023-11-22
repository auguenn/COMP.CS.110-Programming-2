/* Class Project
 * ----------
 * COMP.CS.110 FALL 2023
 * ----------
 * Class for describing a project in an IT company.
 *
 * Note: Students need to implement almost all of this class by themselves.
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
    std::string get_id() const;
    std::vector<std::string> get_requirements();
    bool is_closed();
    void close_project(const Date& end);
    void add_employee(Employee* staff_id);
    // Print start and end dates. Param pre_text gets printed before the dates.
    void print_date_info(const std::string& pre_text) const;
    // Set the end date (Date class) for the care period.
    void set_end_date(const Date& end);
    void set_end_date_for_assigned_staff(const Date& end_date);


    bool is_employee_in_project(const std::string& employee);
    bool is_employee_qualified(const Employee& employee);
    bool add_requirement(const std::string& req);
    void remove_employee(const std::string& employee_id);
    std::set<Employee*> get_assigned_staff();

    std::vector<std::string> update_employees_qualification();

    Date get_start_date() const;
    Date get_end_date() const;

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

   std::set<Employee*> assigned_staff_;
   std::vector<std::string> requirements_;


};

#endif // PROJECT_HH
