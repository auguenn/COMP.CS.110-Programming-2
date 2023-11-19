#include "company.hh"
#include "utils.hh"
#include <iostream>
#include <set>

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
    for (auto& project_pair : all_projects_)
       {
           for (auto& project_ptr : project_pair.second)
           {
               // Käytä std::unique_ptr:ia varatun muistin vapauttamiseen
               project_ptr.reset(); // Vapauta muisti automaattisesti, kun unique_ptr tuhoutuu
           }
       }
       all_projects_.clear();

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
    if (params.empty()) {
        std::cout << "Error: Missing project ID." << std::endl;
        return;
    }

    const std::string& project_id = params[0];
    if (all_projects_.count(project_id) > 0) {
        std::cout << ALREADY_EXISTS << project_id << std::endl;
        return;
    }

    auto new_project = std::make_shared<Project>(project_id, Utils::today);
    all_projects_[project_id].push_back(new_project);
    std::cout << PROJECT_CREATED << std::endl;
}

void Company::close_project(Params params)
{

}

void Company::print_projects(Params)
{
    if(all_projects_.empty())
     {
         std::cout << "None" << std::endl;
         return;
     }

     for (const auto& project_pair : all_projects_)
     {
         const std::string& project_id = project_pair.first;
         const std::vector<std::shared_ptr<Project>>& projects = project_pair.second;

         for (const auto& project : projects)
         {
             std::cout << project_id << " : ";
             project->get_start_date().print(); // Tulosta aloituspäivämäärä

             if (project->is_closed())
             {
                 std::cout << " - ";
                 project->get_end_date().print(); // Tulosta sulkemispäivämäärä
             }

             std::cout << std::endl;
         }
     }
}

void Company::add_requirement(Params params)
{

}

void Company::assign(Params params)
{

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
