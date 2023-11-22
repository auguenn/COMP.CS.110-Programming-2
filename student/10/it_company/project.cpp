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

void Project::set_end_date(const Date &end)
{
    end_ = end;
}

void Project::set_end_date_for_assigned_staff(const Date& end_date) {
    for (Employee* employee : assigned_staff_) {
        employee->end_project(id_, end_date);
    }
}

void Project::add_employee(Employee* staff_member)
{
    assigned_staff_.insert(staff_member);
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

std::vector<std::string> Project::get_requirements() {
    return requirements_;
}

std::set<Employee*> Project::get_assigned_staff() {
    return assigned_staff_;
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



/*bool Project::is_employee_in_project(const std::string& employee) {
    if( assigned_staff_.find(employee) == assigned_staff_.end()) {
       return false;
    }
   return true;
}

bool Project::is_employee_qualified(const Employee& employee) {
    if (requirements_.empty()) {
        return true;
    }
    int req_count = 0;

    while (req_count != 0) {
        for (const auto& req : requirements_) {
            if (!employee.has_skill(req)) {
                return false;
            }
            req_count += 1;
        }
    }


    return true;
}

void Project::add_employee(Employee& employee) {
    if (is_employee_qualified(employee)) {
        assigned_staff_.insert(employee.get_id());
    }
}*/

/*void Project::remove_employee(const std::string& employee_id) {
    assigned_staff_.rem(employee_id);
}
*/


bool Project::add_requirement(const std::string& req)
{
    if (std::find(requirements_.begin(), requirements_.end(), req) != requirements_.end()) {
        return false; // Vaatimus on jo olemassa
    }
    //update_employees_qualification();
    requirements_.push_back(req);

    return true;
}

Date Project::get_start_date() const {
       return start_;
   }

Date Project::get_end_date() const {
       return end_;
   }

