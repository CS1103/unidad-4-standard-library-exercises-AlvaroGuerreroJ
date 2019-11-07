#include <iostream>
#include <map>
#include <optional>
#include <regex>
#include <string>
#include <utility>

bool is_project_name(std::string const& s);
bool is_student_id(std::string const& s);

int main()
{
    // The number of students in each project
    std::map<std::string, unsigned> projects_counts;
    // Map each student to the project he joined. If the student is invalidated
    // for joining multiple projects, it does not have value (as in an default
    // constructed `optional`).
    std::map<std::string, std::optional<std::string>> student_project;

    std::string temp;
    std::getline(std::cin, temp);

    if (!is_project_name(temp))
    {
        // Must start with a project name
        std::cerr << temp << " is not a project name.\nExiting..." << std::endl;
        return 1;
    }
    std::string cur_project = temp;
    projects_counts[cur_project] = 0;

    while (std::getline(std::cin, temp) && temp != "1")
    {
        if (is_project_name(temp))
        {
            cur_project = temp;
            projects_counts[cur_project] = 0;
        }
        else if (is_student_id(temp))
        {
            if (student_project.count(temp) == 0)
            {
                student_project[temp] = cur_project;
                projects_counts[cur_project]++;
            }
            else if (student_project[temp].has_value() &&
                     student_project[temp].value() != cur_project)
            {
                projects_counts[student_project[temp].value()]--;
                student_project[temp].reset();
            }
        }
        else
        {
            std::cerr << temp << " is not a project name or student_id.\n"
                      << "Exiting..." << std::endl;
        }
    }

    using entry = std::pair<std::string, unsigned>;
    std::vector<entry> final_project_counts(projects_counts.begin(),
                                            projects_counts.end());

    std::sort(final_project_counts.begin(), final_project_counts.end(),
              [](entry const& l, entry const& r) {
                  return l.second >= r.second;
              });

    for (auto const& p : final_project_counts)
    {
        std::cout << p.first << " " << p.second << std::endl;
    }
}

bool is_project_name(std::string const& s)
{
    std::regex project_name("[A-Z ]+");
    return std::regex_match(s, project_name);
}

bool is_student_id(std::string const& s)
{
    std::regex student_id("[a-zA-Z][a-zA-Z0-9]*");
    return std::regex_match(s, student_id);
}
