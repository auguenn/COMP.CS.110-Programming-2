#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using NET = std::unordered_map<std::string, std::vector<std::string>>;

std::vector<std::string> split(const std::string& s,
                               const char delimiter,
                               bool ignore_empty = false)
{
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter) + 1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}


void store(std::string const &id1, std::string const &id2, NET &network)
 {

       // is person in network?

     if(network.find(id1) == network.end())
       {
          network.insert({id1, {}});
       }

     if(network.find(id2) == network.end())
       {
          network.insert({id2, {}});
       }

       network.at(id1).push_back(id2);
 }


 void print(std::string const &id, std::string const dots, NET const &network)
{
  // trivial case of no followers

  std::vector<std::string> followers = network.at(id);
  std::cout << dots << id <<std::endl;

  if(followers.empty())
      return;

  for(std::string const &i : followers)
    {
      print(i, dots + "..", network);
    }
}

int count(std::string const &id, NET const &network)
{
  // trivial case of no followers
  std::vector<std::string> followers = network.at(id);

  int n = 0;

  for (std::string const &i : followers)
    {
      n++;
      n += count (i, network);
    }
  return n;

}

int depth(std::string const &id, NET const &network)
{
  // trivial case of no followers
  std::vector<std::string> followers = network.at(id);

  int d_max = 0;

  for (const std::string &f : followers)
    {
      int d = depth(f, network);
      if (d > d_max)
        d_max = d;
    }

  return d_max + 1;

}



int main()
{
    // TODO: Implement the datastructure here


    NET network;

    while(true)
    {
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        // Allowing empty inputs
        if(parts.size() == 0)
        {
            continue;
        }

        std::string command = parts.at(0);

        if(command == "S" or command == "s")
        {
            if(parts.size() != 3)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            store (id1, id2, network);



        }
        else if(command == "P" or command == "p")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            print(id, "", network);
        }
        else if(command == "C" or command == "c")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

           std::cout << count (id, network) << std::endl;

        }
        else if(command == "D" or command == "d")
        {
            if(parts.size() != 2)
            {
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            std:: cout << depth (id, network) << std::endl;

        }
        else if(command == "Q" or command == "q")
        {
           return EXIT_SUCCESS;
        }
        else
        {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
