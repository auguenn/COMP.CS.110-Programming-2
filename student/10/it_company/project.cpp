#include "project.hh"
#include <iostream>
#include <algorithm>

Project::Project(const std::string& id, const std::string& start):
    id_(id), start_(start)
{
    is_closed_ = false;

}

Project::Project(const std::string& id, const Date &start):
    id_(id), start_(start)
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

bool Project::is_closed()
{
    return is_closed_;
}

void Project::close_project(const Date& end)
{
    end_ = end;
    is_closed_ = true;
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


bool Project::is_employee_qualified(const Employee& employee)
{
    for (const auto& req : requirements_) {
        if (!employee.has_skill(req)) {
            return false;
        }
    }
    return true;
}

bool Project::is_employee_in_project(const std::string employee) {
    if( assigned_staff_.find(employee) == assigned_staff_.end()) {
       return false;
    }
   return true;
}



bool Project::add_requirement(const std::string& req)
{
    if (std::find(requirements_.begin(), requirements_.end(), req) != requirements_.end()) {
        return false; // Vaatimus on jo olemassa
    }
    requirements_.push_back(req);
    return true;
}

void Project::add_employee(const std::string employee) {
    assigned_staff_.insert(employee);
}


std::vector<std::string> Project::get_requirements() const {
    return requirements_;
}
