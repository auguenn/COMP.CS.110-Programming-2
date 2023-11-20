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

bool Project::is_employee_in_project(const std::shared_ptr<Employee>& employee) const {
    return std::find_if(assigned_staff_.begin(), assigned_staff_.end(), [&](const std::shared_ptr<Employee>& emp) {
        return emp == employee;
    }) != assigned_staff_.end();
}

std::vector<std::string> Project::update_employees_qualification()
{
    std::vector<std::string> unqualified_employees;
    for (auto it = assigned_staff_.begin(); it != assigned_staff_.end(); ) {
        if (!is_employee_qualified(**it)) {
            unqualified_employees.push_back((*it)->get_id());
            it = assigned_staff_.erase(it);
        } else {
            ++it;
        }
    }
    return unqualified_employees;
}

bool Project::add_requirement(const std::string& req)
{
    if (std::find(requirements_.begin(), requirements_.end(), req) != requirements_.end()) {
        return false; // Vaatimus on jo olemassa
    }
    requirements_.push_back(req);
    return true;
}

void Project::add_employee(const std::shared_ptr<Employee>& employee) {
    assigned_staff_.push_back(employee);
}

void Project::remove_employee(const std::shared_ptr<Employee>& employee)
{
    auto it = std::find(assigned_staff_.begin(), assigned_staff_.end(), employee);
    if (it != assigned_staff_.end()) {
        assigned_staff_.erase(it);
    }
}


std::vector<std::string> Project::get_requirements() const {
    return requirements_;
}
