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
    std::vector<std::string> update_employees_qualification();
    std::vector<std::string> get_requirements();

    bool is_closed();
    void close_project(const Date& end);
    // Print start and end dates. Param pre_text gets printed before the dates.
    void print_date_info(const std::string& pre_text) const;
    void add_employee(Employee& staff_id);
    bool is_employee_in_project(const std::string& employee);
    bool is_employee_qualified(const Employee& employee);
    bool add_requirement(const std::string& req);
    std::set<std::string> get_assigned_staff();


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

   std::set<std::string> assigned_staff_;
   std::vector<std::string> requirements_;


};

#endif // PROJECT_HH
