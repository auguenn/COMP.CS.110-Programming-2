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

#include "project.hh"
#include <iostream>
#include <algorithm>


Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start), end_()
{
    is_closed_ = false;

}


Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start), end_()
{
    is_closed_ = false;
}


Project::~Project()
{
    //std::cout << "Project " << id_ << " destructed." << std::endl;
}


std::string Project::get_id() const
{
    return id_;
}


std::vector<std::string> Project::get_requirements()
{
    // Sort the requirements in aphabetical order
    std::sort(requirements_.begin(), requirements_.end());
    return requirements_;
}


std::set<Employee*> Project::get_assigned_staff()
{
    return assigned_staff_;
}


Date Project::get_start_date() const
{
       return start_;
}


bool Project::is_closed()
{
    return is_closed_;
}


void Project::close_project(const Date& end)
{
    end_ = end;
    // Set the boolean to true
    is_closed_ = true;
}


bool Project::has_requirement(const std::string& skill)
{
    return std::find(requirements_.begin(), requirements_.end(), skill)
                                                        != requirements_.end();
}


void Project::add_requirement(const std::string& req)
{
    // Check if the requirement exists
    if (std::find(requirements_.begin(), requirements_.end(), req) !=
                                                    requirements_.end())
    {
        return;
    }

    // Add requirement to the project
    requirements_.push_back(req);

    // Check if the new requirement has caused an employee to be kicked out of
    // the project
    if (!assigned_staff_.empty()) {
        for (auto it = assigned_staff_.begin(); it != assigned_staff_.end();)
        {
            bool has_required_skill = false;
            // Initialize a pointer
            Employee* employee = *it;

            // Check if the employee is assigned to the project
            if (!employee->is_assigned_to_project(id_))
            {
                ++it;
                continue;
            }

            // Check if the employee has at least one of the required skills
            for (const auto& skill : employee->get_skills())
            {
                if (has_requirement(skill))
                {
                    has_required_skill = true;
                    break;
                }
            }

            if (!has_required_skill)
            {
                std::cout << NOT_QUALIFIED << employee->get_id() << std::endl;
                // Remove the employee from the assigned staff
                it = assigned_staff_.erase(it);
            }
            else
            {
                ++it;
            }
        }
    }
}


void Project::add_employee(Employee* staff_member)
{
    assigned_staff_.insert(staff_member);
}


bool Project::is_employee_in_project(const std::string& employee)
{
    for (const auto& emp : assigned_staff_)
    {
            if (emp->get_id() == employee)
            {
                return true;
            }
        }

        return false;
}


void Project::set_end_date_for_assigned_staff(const Date& end_date)
{
    for (Employee* employee : assigned_staff_)
    {
        employee->end_project(id_, end_date);
    }
}


void Project::print_date_info(const std::string& pre_text) const
{
    std::cout << pre_text << " : ";
    start_.print();
    std::cout << " - ";

    // Checking if the project has ended. If ended, print ending date.
    if (not end_.is_default())
    {
        end_.print();
    }

    std::cout << std::endl;
}

