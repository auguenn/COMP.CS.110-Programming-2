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

Date Project::get_start_date() const
{
    return start_;
}

Date Project::get_end_date() const
{
    return end_;
}

bool Project::is_closed()
{
    return is_closed_;
}

void Project::close_project(const Date& end) {
    end_ = end;
    is_closed_ = true;
}

bool Project::is_employee_qualified(const Employee& employee) {
    for (const auto& req : requirements_) {
        if (!employee.has_skill(req)) {
            return false;
        }
    }
    return true;
}

bool Project::is_employee_in_project(const std::shared_ptr<Employee>& employee) const {
    return std::find(assigned_staff_.begin(), assigned_staff_.end(), employee) != assigned_staff_.end();
}

std::vector<std::string> Project::update_employees_qualification() {
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

bool Project::add_requirement(const std::string& req) {
    if (std::find(requirements_.begin(), requirements_.end(), req) != requirements_.end()) {
        return false; // Vaatimus on jo olemassa
    }
    requirements_.push_back(req);
    return true;
}

void Project::remove_employee(const std::shared_ptr<Employee>& employee) {
    auto it = std::find(assigned_staff_.begin(), assigned_staff_.end(), employee);
    if (it != assigned_staff_.end()) {
        assigned_staff_.erase(it);
    }
}
