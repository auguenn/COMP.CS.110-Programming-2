/* IT-company
 *
 *
 * Program author:
 * Name: Enna Augustin
 * Student number: 50235634
 * UserID: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
*/

#include "employee.hh"
#include <iostream>
#include <map>

Employee::Employee()
{
}

Employee::Employee(const std::string &id):
    id_(id)
{
    date_of_birth_ = Date();
}

Employee::Employee(const std::string& id, const std::string& date_of_birth):
    id_(id), date_of_birth_(date_of_birth)
{
}

Employee::~Employee()
{
    //std::cout << "Employee " << id_ << " destructed." << std::endl;
}


std::string Employee::get_id() const
{
    return id_;
}


std::set<std::string> Employee::get_skills() const
{
    return skills_;
}


void Employee::add_skill(const std::string& skill)
{
    skills_.insert(skill);
}


void Employee::add_project(const std::string& name, Date start)
{
    DateRange date = {};

    date.start_date = start;

    // Initializing the end date as empty
    date.end_date = Date();

    // Checking if the project name exists in the map
    if (projects_.find(name) != projects_.end())
    {
        // If the project exists, update its date range
        projects_.at(name) = date;
    }
    else
    {
        // If the project doesn't exist, insert it into the map
        projects_.insert({name, date});
    }
}


void Employee::end_project(const std::string& name, Date end)
{
    // Check if the project name exists in the map
    if (projects_.find(name) != projects_.end())
    {
        // Update the end date
        projects_.at(name).end_date = end;
     }
    else
    {
        // If the project doesn't exist, create a new DateRange and insert it
        // into the map
        DateRange date = {};
        date.start_date = Date();
        date.end_date = end;
        projects_.insert({name, date});
     }

}


bool Employee::is_assigned_to_project(const std::string& project_id) const
{
    return projects_.find(project_id) != projects_.end();
}


void Employee::print_id(const std::string& pre_text) const
{
    std::cout << pre_text << id_;
    //date_of_birth_.print();
    //std::cout << std::endl;
}


void Employee::print_skills() const
{
    std::cout << "Skills: ";
    if( skills_.empty() )
    {
        std::cout << NONE << std::endl;
        return;
    }

    std::set<std::string>::const_iterator iter = skills_.begin();
    // Printing the first one
    std::cout << *iter;
    ++iter;
    while( iter != skills_.end() )
    {
        // Printing the rest
        std::cout << ", " << *iter;
        ++iter;
    }
    std::cout << std::endl;
}


void Employee::print_projects() const
{
    if (projects_.empty())
    {
        std::cout << "Projects: " << NONE << std::endl;
        return;
    }

    std::cout << "Projects: " << std::endl;

    // Going throuh the projects' info
    for( std::map<std::string, DateRange>::const_iterator
             iter = projects_.begin();
             iter != projects_.end();
             ++iter )
    {
        std::string name = "";
        std::string start = "";
        std::string end = "";

        DateRange dates = iter->second;
        name = iter->first;

        // Change the dates to strings
        start = dates.start_date.to_string();
        end = dates.end_date.to_string();

        // If the project is not closed yet
        if (end == "0.0.0")
        {
            std::cout << "** " << name << " : "
                      << start << " - "
                      << std::endl;
        }
        // If the project has ended
        else
        {
              std::cout << "** " << name << " : "
                        << start << " - "
                        << end << std::endl;
        }
    }
}


bool Employee::operator<(const Employee &rhs) const
{
    return id_ < rhs.id_;
}
