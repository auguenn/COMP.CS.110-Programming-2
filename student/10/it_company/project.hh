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
    Date get_start_date() const;
    Date get_end_date() const;
    std::vector<std::string> get_requirements() const;
    std::string get_id() const;

    bool is_closed();
    bool is_employee_qualified(const Employee& employee);
    bool add_requirement(const std::string& req);

    void close_project(const Date& end);
    void remove_employee(const std::shared_ptr<Employee>& employee);
    std::vector<std::string> update_employees_qualification();
    bool is_employee_in_project(const std::shared_ptr<Employee>& employee) const;
    void add_employee(const std::shared_ptr<Employee>& employee) ;

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

    std::vector<std::shared_ptr<Employee>> assigned_staff_;
    std::vector<std::string> requirements_;


};

#endif // PROJECT_HH
