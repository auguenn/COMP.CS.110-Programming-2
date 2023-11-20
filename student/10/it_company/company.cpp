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

    // TODO: Deallocate staff
    for( std::map<std::string, Employee*>::iterator
             iter = all_staff_.begin();
             iter != all_staff_.end();
             ++iter )
        {
            delete iter->second;
        }

    // TODO: Deallocate projects
    for( std::map<std::string, Project*>::iterator
             iter = all_projects_.begin();
             iter != all_projects_.end();
             ++iter )
        {
            delete iter->second;
        }

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
        std::cout << "None" << std::endl;
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
    // Checking if there already is or has been a project in company with the same name.
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
        // Lets create a new project for the new project and add it to company's
        // chronological register
        all_projects_in_order_.push_back(new_project);
        // Add project to current projects
        current_projects_.insert({project_id, new_project});
        std::cout << PROJECT_CREATED << std::endl;


}


void Company::close_project(Params params)
{
    std::string project_id = params.at(0);

    if (all_projects_.find(project_id) == all_projects_.end())
    {
        std::cout << CANT_FIND << project_id << std::endl;
        return;
    }

    Project* project_to_close = all_projects_[project_id];

    if (project_to_close->is_closed()) {
        std::cout << PROJECT_CLOSED << std::endl;
        return;
    }

    project_to_close->close_project(Utils::today);
    current_projects_.erase(project_id);
    std::cout << PROJECT_CLOSED << std::endl;
}


void Company::print_projects(Params)
{
    if( all_projects_in_order_.empty() )
    {
        std::cout << "None" << std::endl;
        return;
    }

    for(Project* project : all_projects_in_order_) {
        std::string id = project->get_id();
        project->print_date_info(id);
    }

}

void Company::add_requirement(Params params)
{


}



void Company::assign(Params params) {

}


void Company::print_project_info(Params params)
{

}

void Company::print_employee_info(Params params)
{

}

void Company::print_active_staff(Params)
{

}



bool Company::is_id_in_container(const std::string& id,
                                    const std::map<std::string, Project*>
                                    container) const
{
    if (container.find(id) == container.end())
    {
        std::cout << CANT_FIND << id << std::endl;
        return false;
    }
    return true;
}
