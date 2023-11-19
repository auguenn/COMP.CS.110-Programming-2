#include "project.hh"
#include <iostream>

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
