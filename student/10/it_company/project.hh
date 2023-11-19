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

    bool is_closed();

    void close_project(const Date& end);

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
};

#endif // PROJECT_HH
