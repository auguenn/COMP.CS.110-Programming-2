/**
 * It-company
 *
Description:
 * The program implements a IT-company system that can be used for handling
 * project and employee data. The program has a list of commands to control
 * the company and things happening inside of it.
 * The program consists of classes Company, Project, Employee, Date, and Cli,
 * and the module Utils.
 *
 * At start, this program generates a company. After generating a new company,
 * the program asks for commands until user enters quit command. All the
 * commands are listed below.
 *
 * Employees are instances of the class Employee. Their info is stored in
 * separate STL-containers in the class Hospital. The program keeps track of
 * all of the previous and current employees as well as employees that are or
 * have been a part of a project. Employees can be identified by their names
 * that are/have to be given when recruiting new people to the company. An
 * employee can also be given skill that are stored in a container in the
 * Employee class.
 *
 * Projects are instances of the class Project. Projects have different names,
 * starting and ending dates. Starting and ending dates are instances of class
 * Date. The class Company uses the class Date when creating a new project. The
 * starting date is generated when the project is created and the ending date
 * generates when the project is closed. The class Company keep track of all
 * projects (both active and closed), current projects and it also has a
 * container that keep track of the order in which the projects have been
 * created. The project can also have skill requirements for the employees and
 * the requirements can be added all along the project's lifecycle.
 *
 * An employee can be assigned to projects. The success of the assignment
 * depends whether employee has at least one of the skills required in the
 * project. Also if the project gets more requirements when an employee has
 * already been assigned to the project the employee can be kicked out of the
 * project if they don't have at least one of the required skills.
 *
 * Command checking is done in Cli -class. Cli checks, if given input is known
 * and if there are correct amount of parameters given in the input. The module
 * Utils provides general functions used in the program.
 *
 * The functionalities of the commands are written in Company -class. The
 * Company -class is the main structure of the program, and it handles the
 * functionality and calls other classes when necessary to create a modular
 * program.
 *
 * Commands and describtion:
 * - QUIT : Terminates the program with the return value EXIT_SUCCESS. Does not
 *          print anything. The command takes no parameters, and if they are
 *          given, they will just be ignored.
 * - HELP : Prints all available commands and their acronyms and the describtion
 *          of the command.
 * - READ_FROM <file> : Reads commands from a file which name is given as a
 *          parameter <file>. If the file contains erronous commands it just
 *          ignores them and continues reading the file. If no file is found
 *          with the given name, an error message is printed.
 * - SET_DATE <dd> <mm> <yyyy> : Sets the date according to the given parameters
 *          of integer type. The date is in the form dd.mm.yyyy . If parameters
 *          are erronous,program prints an error message.
 * - ADVNACE_DATE <non-negative integer> : The command advances the current date
 *          with the given number of days ahead. If the parameter is erronous,
 *          the program prints an error message
 * - RECRUIT <id> : Adds a new employee to the company. Command needs one
 *          parameter that can be a name, to identify the new object of class
 *          Employee. If a staffmember with the given id already exists, the
 *          program prints an error message.
 * - LEAVE <id> - Removes (resigns) the given employee from the company. The
 *          command does not remove the employee from the projects they have
 *          worked in. If the given employee cannot be found prints an error
 *          message. After resign, the employee can be recruited again, and
 *          they have the skills added in the previous working period.
 * - ADD_SKILL <id> <skill> - Adds a new skill for an employee. If the employee
 *          already has the skill, nothing happens. An error message is
 *          printed, if the given employee cannot be found. It is not possible
 *          to add a skill for a resigned employee.
 * - PRINT_CURRENT_STAFF - Prints all current staff, i.e. employees recruited,
 *          but not resigned. Employees’ ids are listed in alphabetical order,
 *          one below another. If there is no staff in the company, the program
 *          prints None.
 * - CREATE_PROJECT <id> - Adds a new project in the company. The command
 *          requires id parameter that can be the name of the project. An error
 *          message is printed, if a project with the given id already exists.
 *          The error message is given for all projects already created, even
 *          if the project has been closed. Also the start date will be given
 *          for a new project. It is the current value of today variable of
 *          Utils module.
 * - CLOSE_PROJECT <id> - Closes a project. Closing means that an end date is
 *          set for the project. This date is the current value of today
 *          variable of Utils module. The data about the project is kept.
 *          It is possible to close a project several times and the re-close
 *          does nothing. A closed project cannot be re-created. If the given
 *          parameter is an unknown project, the program prints the error
 *          message.
 * - PRINT_PROJECTS - Prints all projects in the order, they have been created.
 *          From each project, its id and start date are printed. From a closed
 *          project, also the end date is printed. If there are no projects
 *          created yet, the command prints the text None.
 * - ADD_REQUIREMENT <id> <requirement> - Adds a new requirement for a project.
 *          If the project already has the requirement, nothing happens. An
 *          error message is printed, if the given project cannot be found. It
 *          is not possible to add requirements for a closed project. It is
 *          possible to add requirements for a project after employees have
 *          been assigned in it. If after adding requirements, the project has
 *          an employee that has no skills required in the project, the
 *          employee is taken away from the project.
 * - ASSIGN <employee id> <project id> - Assigns the given employee to work in
 *          the given project. The employee to be assigned must have at least
 *          one skill that can be found from the requirements of the project.
 *          If the project has no requirements, no skill requirements are
 *          expected from the employee, either. An employee cannot be assigned
 *          in a closed project. Re-assignment is not possible after a
 *          succesfull assignment. An error message can appear in three cases:
 *          the project is closed, the employee is missing a skill, or the
 *          employee is tried to assign again in the same project, where they
 *          have already assigned. If the employee or the project given as a
 *          parameter cannot be found, the program prints the error message.
 * - PRINT_PROJECT_INFO <id> - Prints information about the given project:
 *          start date, requirements, and staff. From a closed project, also
 *          the end date is printed. Requirements and employees are printed in
 *          alphabetical order, both of these in one line separated by a comma.
 *          If the project has no requirements or staff, the word None is
 *          printed instead. Above you can also the error message to be
 *          printed, if the given project cannot be found.
 * - PRINT_EMPLOYEE_INFO <id> - Prints information about an employee: their
 *          skills and projects in which they are working or have worked.
 *          Skills are listed in alphabetical order, all in same line,
 *          separated by a comma. Projects are listed, each in a line of its
 *          own, in the order in which the employee has been assigned in them.
 *          From each project, the start date is printed, and from closed
 *          projects also the end date is printed. If the employee has no
 *          skills or projects assigned, the word None is printed instead. If
 *          the given employee cannot be found, an error message is printed.
 *          The employee cannot be found if they have resigned.
 * - PRINT_ACTIVE_STAFF - The command prints active employees, i.e. those ones
 *          who are working or have worked in a project. Active employees are
 *          printed in alphabetical order based on their ids, each one in a
 *          line of their own. If the company has no active employees, the
 *          program prints None.
 *
 *
 *
 * Program author:
 * Name: Enna Augustin
 * Student number: 50235634
 * UserID: xxenau
 * E-Mail: enna.augustin@tuni.fi
 *
 *
 */

#include "cli.hh"
#include "company.hh"

const std::string PROMPT = "IT> ";

int main()
{
    Company* company = new Company();
    Cli cli(company, PROMPT);
    while( cli.exec() ){}

    delete company;
    return EXIT_SUCCESS;
}
