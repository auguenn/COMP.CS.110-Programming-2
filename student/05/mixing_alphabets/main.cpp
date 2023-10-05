#include <iostream>
#include <string>
#include <algorithm>
#include <random>

int main()
{
    // This is a random number generator that should be given as parameter to the
    // function of the algorithm library to shuffle letters
    std::minstd_rand generator;

    std::cout << "Enter some text. Quit by entering the word \"END\"." << std::endl;
    std::string word;

    while (std::cin >> word)
    {
        if (word == "END")
        {
            return EXIT_SUCCESS;
        }

        // TODO: implement your solution here
        std::string y= word.substr(1,word.length()-2);
        shuffle (y.begin(),y.end(),generator);
        if(word.length()==1) {
            word=word[0];
        }
        else {
            word= word[0] + y + word[word.length()-1];
        }
	
        std::cout << word << std::endl;
    }
}
