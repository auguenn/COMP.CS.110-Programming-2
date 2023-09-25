#include <cstdlib>
#include <iostream>
#include <vector>


// Prints the elements in the parameter vector ints.
void print_integers(const std::vector< int >& ints)
{
    for(auto elem : ints) {
        std::cout << elem << " ";
    }
    std::cout << std::endl;
}

// Reads as many integers as the parameter count indicates
// and stores them into the parameter vector ints.
void read_integers(std::vector< int >& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i) {
        std::cin >> new_integer;
        // TODO: Implement your solution here
        ints.push_back(new_integer);
    }
}

// TODO: Implement your solution here
bool same_values (std::vector< int > ints){
  for (int i = 0; i < ((int)ints.size()); ++i)
    {
      if (!(ints.at(0) == ints.at(i)))
        {
          return false;
        }
    }return true;
}

bool is_ordered_non_strict_ascending (std::vector< int >& ints) {
  for (int i = 0; i < ((int)ints.size()-1); ++i)
    {

      if (!(ints.at(i+1) >= ints.at(i)))
        {
          return false;
        }

    }return true;
}


bool is_arithmetic_series (std::vector< int >& ints) {
  for (int i = 0; i < ((int)ints.size()-1); ++i)
    {

      if ( !(ints.at(i+1) - ints.at(i) == ints.at(1) - ints.at(0)))
        {
          return false;
        }

    }
  return true;
}

bool is_geometric_series(std::vector< int >& ints)

{

    if (ints.size() == 1)
      {
        return true;
      }

    // Calculate ratio
    if (ints.at(0) == 0)
      {
         return false;
      }
    else
   {
    int ratio = ints[1] / (ints[0]);

    // Check the ratio of the remaining
    for (int i = 1; i < ((int) ints.size()); i++) {

     if ((ints[i] / (ints[i - 1])) != ratio) {
            return false;
        }
    }
    return true;
}
   }

std::vector<int>triple_integers(std::vector<int>& ints)
{
    std::vector<int> result;

        for (int num : ints) {
            result.push_back(num * 3);
        }

        return result;
}


int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    if(how_many <= 0) {
        return EXIT_FAILURE;
    }

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers)) {
        std::cout << "All the integers are the same" << std::endl;
    } else {
        std::cout << "All the integers are not the same" << std::endl;
    }

    if(is_ordered_non_strict_ascending(integers)) {
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    } else {
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;
    }

    if(is_arithmetic_series(integers)) {
        std::cout << "The integers form an arithmetic series" << std::endl;
    } else {
        std::cout << "The integers do not form an arithmetic series" << std::endl;
    }

    if(is_geometric_series(integers)) {
        std::cout << "The integers form a geometric series" << std::endl;
    } else {
        std::cout << "The integers do not form a geometric series" << std::endl;
    }

    std::vector<int> tripledNumbers = triple_integers(integers);
    std::cout << "Tripled values: ";
    print_integers(tripledNumbers);

    return EXIT_SUCCESS;
}

