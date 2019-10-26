#include <algorithm>
#include <iostream>
#include <regex>
#include <string>
#include <vector>

#include <boost/algorithm/string.hpp>

int main()
{
    std::string tournament_name;
    std::getline(std::cin, tournament_name);

    struct teams_results_entry
    {
        unsigned wins;
        unsigned ties;
        unsigned losses;
        unsigned goals_scored;
        unsigned goals_against;

        teams_results_entry() : wins(), ties(), losses(), goals_scored(),
                        goals_against()
        {
        }
    };

    std::map<std::string, teams_results_entry> teams_results;
    size_t n_teams;
    std::cin >> n_teams;
    std::cin.ignore();
    for (size_t i = 0; i < n_teams; i++)
    {
        std::string team_name;
        std::getline(std::cin, team_name);
        teams_results[team_name];
    }

    size_t n_games;
    std::cin >> n_games;
    std::cin.ignore();
    // The regex captures (in the specified order):
    // 0: First team's name
    // 1: First team's goals
    // 2: Second team's goals
    // 3: Second team's name
    std::regex game_format("([^#@]{1,32})#(\\d+)@(\\d+)#([^#@]{1,32})");
    for (size_t i = 0; i < n_games; i++)
    {
        std::string temp;
        std::smatch matched_parts;
        std::getline(std::cin, temp);
        if (!(std::regex_match(temp, matched_parts, game_format)))
        {
            std::cerr << temp << " does not match the game entry format.\n"
                      << "Exiting..." << std::endl;
            return 1;
        }

        // The first match (matched_parts[0] is the entire string)
        std::string first_teamname = matched_parts[1].str();
        unsigned first_goals = std::stoul(matched_parts[2].str());
        unsigned second_goals = std::stoul(matched_parts[3].str());
        std::string second_teamname = matched_parts[4].str();

        int goals_difference_favour_first = first_goals - second_goals;

        auto& fe = teams_results.at(first_teamname);
        auto& se = teams_results.at(second_teamname);

        fe.goals_scored += first_goals;
        fe.goals_against += second_goals;
        se.goals_scored += second_goals;
        se.goals_against += first_goals;

        if (goals_difference_favour_first < 0)
        {
            fe.losses++;
            se.wins++;
        }
        else if (goals_difference_favour_first == 0)
        {
            fe.ties++;
            se.ties++;
        }
        else
        {
            fe.wins++;
            se.losses++;
        }
    }

    struct standings_entry
    {
        std::string name;
        unsigned games_played;
        unsigned wins;
        unsigned ties;
        unsigned losses;
        unsigned total_points;
        int goals_difference;
        unsigned goals_scored;
        unsigned goals_against;

        standings_entry(std::string name, unsigned games_played, unsigned wins,
                        unsigned ties, unsigned losses, unsigned total_points,
                        int goals_difference, unsigned goals_scored,
                        unsigned goals_against)
                       : name(name), games_played(games_played),
                         wins(wins), ties(ties), losses(losses),
                         total_points(total_points),
                         goals_difference(goals_difference),
                         goals_scored(goals_scored),
                         goals_against(goals_against)
        {
        }
    };

    std::vector<standings_entry> standings;
    std::transform(teams_results.begin(), teams_results.end(),
                   std::back_inserter(standings),
                   [](std::pair<std::string const, teams_results_entry> const& e){
                       return standings_entry(
                           e.first,
                           e.second.wins + e.second.ties + e.second.losses,
                           e.second.wins,
                           e.second.ties,
                           e.second.losses,
                           e.second.wins * 3 + e.second.ties * 1,
                           e.second.goals_scored - e.second.goals_against,
                           e.second.goals_scored,
                           e.second.goals_against);
                   });
    std::sort(standings.begin(), standings.end(),
              [](standings_entry const& l, standings_entry const& r){
                  if (l.total_points != r.total_points)
                  {
                      return l.total_points > r.total_points;
                  }
                  else if (l.wins != r.wins)
                  {
                      return l.wins > r.wins;
                  }
                  else if (l.goals_difference != r.goals_difference)
                  {
                        return l.goals_difference > r.goals_difference;
                    }
                  else if (l.goals_scored != r.goals_scored)
                  {
                      return l.goals_scored > r.goals_scored;
                  }
                  else if (l.games_played != r.games_played)
                  {
                      return l.games_played < r.games_played;
                  }
                  else
                  {
                      return boost::algorithm::to_lower_copy(l.name) >
                             boost::algorithm::to_lower_copy(r.name);
                  }
              });

    std::cout << tournament_name << std::endl;
    size_t cur_pos = 1;
    for (auto const& e : standings)
    {
        std::cout << cur_pos << ") " << e.name << " " << e.total_points
                  << "p, " << e.games_played << "g (" << e.wins << "-" << e.ties
                  << "-" << e.losses << "), " << e.goals_difference << "gd "
                  << "(" << e.goals_scored << "-" << e.goals_against << ")"
                  << std::endl;

        cur_pos++;
    }
}
