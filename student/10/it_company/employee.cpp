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

void Employee::add_skill(const std::string& skill)
{
    skills_.insert(skill);
}

std::vector<std::string> Employee::get_projects() const
{
    std::vector<std::string> result;
    for( std::map<std::string, DateRange>::const_iterator
         iter = projects_.begin();
         iter != projects_.end();
         ++iter )
    {
        result.push_back(iter->first);
    }
    return result;
}

std::set<std::string> Employee::get_skills() const {
    return skills_;
}

void Employee::add_project(const std::string& name,
                          Date start)
{
    DateRange date;
        date.start_date = start;
        date.end_date = Date(); // Alustetaan päättöpäivämäärä tyhjäksi

        if (projects_.find(name) != projects_.end()) {
            projects_.at(name) = date;
        } else {
            projects_.insert({name, date});
        }
}

void Employee::end_project(const std::string& name, Date end) {
    if (projects_.find(name) != projects_.end()) {
         projects_.at(name).end_date = end; // Päivitetään päättöpäivämäärä
     } else {
         DateRange date;
         date.start_date = Date();
         date.end_date = end;
         projects_.insert({name, date});
     }

}

void Employee::remove_project(const std::string& name)
{
    projects_.erase(name);
}

bool Employee::has_skill(const std::string &skill) const
{
    for( std::string skill_item : skills_ )
    {
        if( skill_item == skill )
        {
            return true;
        }
    }
    return false;
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
        std::cout << "None" << std::endl;
        return;
    }

    std::set<std::string>::const_iterator iter = skills_.begin();
    std::cout << *iter; // Printing the first one
    ++iter;
    while( iter != skills_.end() )
    {
        std::cout << ", " << *iter; // Printing the rest
        ++iter;
    }
    std::cout << std::endl;
}

void Employee::print_projects(const std::string& pre_text) const {


    if (projects_.empty()) {
        std::cout << "Projects: None" << std::endl;
        return;
    }

    std::cout << pre_text << std::endl;
    for( std::map<std::string, DateRange>::const_iterator
             iter = projects_.begin();
             iter != projects_.end();
             ++iter )

        { std::string name = "";

          name = iter->first;
          DateRange dates = iter->second;
          std::string start = dates.start_date.to_string();
          std::string end = dates.end_date.to_string();

          if (end == "0.0.0") {
              std::cout << "** " << name << " : "
                        << start << " - "
                        << std::endl;
          } else {
              std::cout
                        << "** " << name << " : "
                        << start << " - "
                        << end << std::endl;
          }



        }

}


bool Employee::operator<(const Employee &rhs) const
{
    return id_ < rhs.id_;
}
