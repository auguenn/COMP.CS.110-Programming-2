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


#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>
#include <algorithm>

Company::Company()
{
}

Company::~Company()
{
    //std::cout << "Company destructor" << std::endl;

    // Deallocate staff
    for( std::map<std::string, Employee*>::iterator
             iter = all_staff_.begin();
             iter != all_staff_.end();
             ++iter )
        {
            delete iter->second;
        }

    // Deallocate projects
    for( std::map<std::string, Project*>::iterator
             iter = all_projects_.begin();
             iter != all_projects_.end();
             ++iter )
        {
            delete iter->second;
        }

}

Employee* Company::get_employee_by_id(const std::string& employee_id)
{
    if (current_staff_.find(employee_id) != current_staff_.end())
    {
        return current_staff_[employee_id];
    }

    return nullptr;
}


void Company::set_date(Params params)
{
    std::string day = params.at(0);
    std::string month = params.at(1);
    std::string year = params.at(2);
    if( not Utils::is_numeric(day, false) or
        not Utils::is_numeric(month, false) or
        not Utils::is_numeric(year, false) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.set(stoi(day), stoi(month), stoi(year));
    std::cout << "Date has been set to ";
    Utils::today.print();
    std::cout << std::endl;
}


void Company::advance_date(Params params)
{
    std::string amount = params.at(0);
    if( not Utils::is_numeric(amount, true) )
    {
        std::cout << NOT_NUMERIC << std::endl;
        return;
    }
    Utils::today.advance(stoi(amount));
    std::cout << "New date is ";
    Utils::today.print();
    std::cout << std::endl;
}


void Company::recruit(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);

    if( iter != current_staff_.end() )
    {
        std::cout << ALREADY_EXISTS << employee_id << std::endl;
        return;
    }

    iter = all_staff_.find(employee_id);
    if( iter != all_staff_.end() )
    {
        current_staff_.insert(*iter);
        std::cout << EMPLOYEE_RECRUITED << std::endl;
        return;
    }

    Employee* new_employee = new Employee(employee_id);
    all_staff_.insert({employee_id, new_employee});
    current_staff_.insert({employee_id, new_employee});
    std::cout << EMPLOYEE_RECRUITED << std::endl;
}


void Company::leave(Params params)
{
    std::string employee_id = params.at(0);
    std::map<std::string, Employee*>::const_iterator
            iter = current_staff_.find(employee_id);
    if( iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    current_staff_.erase(iter); // Employee still stays in all_staff_
    std::cout << EMPLOYEE_LEFT << std::endl;
}


void Company::add_skill(Params params)
{
    std::string employee_id = params.at(0);
    std::string skill_name = params.at(1);

    std::map<std::string, Employee*>::const_iterator
            staff_iter = current_staff_.find(employee_id);
    if( staff_iter == current_staff_.end() )
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    staff_iter->second->add_skill(skill_name);
    std::cout << SKILL_ADDED << employee_id << std::endl;
}



void Company::print_current_staff(Params)
{
    if( current_staff_.empty() )
    {
        std::cout << NONE << std::endl;
        return;
    }

    for( auto employee : current_staff_ )
    {
        employee.second->print_id("");
        std::cout << std::endl;
    }
}


void Company::create_project(Params params)
{
    const std::string& project_id = params.at(0);

    // Checking if there already is or has been a project in company with the
    // same name.
    if (all_projects_.find(project_id) != all_projects_.end())
    {
        std::cout << ALREADY_EXISTS << project_id << std::endl;
        return;
    }

    // If given project is a new project, create a new project object
    // and add it to the all_projects_ -container
    Project* new_project = nullptr;

    new_project = new Project(project_id, Utils::today);
    all_projects_.insert({project_id, new_project});

    // Add the project to company's chronological register
    all_projects_in_order_.push_back(new_project);

    // Add project to current projects
    current_projects_.insert({project_id, new_project});
    std::cout << PROJECT_CREATED << std::endl;

}


void Company::close_project(Params params)
{
    std::string project_id = params.at(0);

    // Checks if the project exists
    if (all_projects_.find(project_id) == all_projects_.end())
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project* project_to_close = nullptr;
    project_to_close = all_projects_[project_id];

    // If the project is already closed
    if (project_to_close->is_closed())
    {
        std::cout << PROJECT_CLOSED << std::endl;
        return;
    }


    // Set the ending date and close the project
    project_to_close->set_end_date_for_assigned_staff(Utils::today);
    project_to_close->close_project(Utils::today);
    current_projects_.erase(project_id);

    std::cout << PROJECT_CLOSED << std::endl;
}


void Company::print_projects(Params)
{
    // If there are no projects
    if( all_projects_in_order_.empty() )
    {
        std::cout << NONE << std::endl;
        return;
    }

    // Print the projects and their info
    for (Project* project : all_projects_in_order_)
    {
        std::string id = project->get_id();
        project->print_date_info(id);
    }

}


void Company::add_requirement(Params params)
{
    std::string project_id = params.at(0);
    std::string requirement = params.at(1);

    // Checks if the project exists and is not closed
    if (!is_id_in_container(project_id, all_projects_) ||
        !is_id_in_container(project_id, current_projects_))
    {
        return;
    }

    Project* project = nullptr;
    project = current_projects_.at(project_id);

    // Checks if the requirement already exists
    project->add_requirement(requirement);
    std::cout << REQUIREMENT_ADDED << project_id << std::endl;

}



void Company::assign(Params params)
{
    std::string staff_id = params.at(0);
    std::string project_id = params.at(1);

    // Check if the staff is in the company
    if (current_staff_.find(staff_id) == current_staff_.end())
    {
        std::cout << CANT_FIND << staff_id << std::endl;
        return;
    }

    // Check if the project exists
    if (!is_id_in_container(project_id, all_projects_))
    {
        return;
    }

    // Check if the project is closed
    if (current_projects_.find(project_id) == current_projects_.end())
    {
        std::cout << CANT_ASSIGN << staff_id << std::endl;
        return;
    }

    Project* project = nullptr;
    project = current_projects_.at(project_id);

    Employee* employee = nullptr;
    employee = get_employee_by_id(staff_id);

    // Check if the employee is already assigned to the project
    if (project->is_employee_in_project(staff_id))
    {
        std::cout << CANT_ASSIGN << staff_id << std::endl;
        return;
    }
    if (!project->get_requirements().empty())
    {
        bool has_required_skill = false;
        for (const auto& skill : employee->get_skills())
        {
            if (project->has_requirement(skill))
            {
                has_required_skill = true;
                break;
            }
        }
        if (!has_required_skill)
        {
            std::cout << CANT_ASSIGN << staff_id << std::endl;
            return;
        }
    }

    // Assign staff to the project
    project->add_employee(employee);
    all_active_staff_.insert(staff_id);

    // Initalize the starting date
    Date start_date;
    start_date = project->get_start_date();

    employee->add_project(project_id, start_date);

    std::cout << STAFF_ASSIGNED << project_id << std::endl;
}


void Company::print_project_info(Params params)
{
    std::string project_id = params.at(0);

    // Checks if the project exists
    if (all_projects_.find(project_id) == all_projects_.end())
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project* project = nullptr;
    project = all_projects_.at(project_id);

    project->print_date_info(project_id);
    std::cout << "** Requirements: ";
    project->print_requirements();

    std::cout << "** Staff: ";
    project->print_staff();
}


void Company::print_employee_info(Params params)
{
    std::string employee_id = params.at(0);

    Employee* employee = nullptr;
    employee = get_employee_by_id(employee_id);

    // If there is not the wanted employee
    if (employee == nullptr)
    {
        std::cout << CANT_FIND << employee_id << std::endl;
        return;
    }

    employee->print_skills();
    employee->print_projects();
}


void Company::print_active_staff(Params)
{
    // If there is no active staff
    if (all_active_staff_.empty())
    {
        std::cout << NONE << std::endl;
        return;
    }

    for (const auto& employee : all_active_staff_)
    {
        std::cout << employee << std::endl;
    }
}


bool Company::is_id_in_container(const std::string& id,
                                    const std::map<std::string, Project*>
                                                            container) const
{
    if (container.find(id) == container.end())
    {
        // If there is not the wanted id in the container
        std::cout << CANT_FIND << id << std::endl;
        return false;
    }

    // If the id is found
    return true;
}
