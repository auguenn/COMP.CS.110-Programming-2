#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
#include <vector>
#include <set>
using namespace std;

using split_string = vector<string> ;

split_string split(const string &line,
                               const char sep,
                               bool ignore_empty = false)
{
  vector<string> parts = {};
  string part = "";

  for(char c : line)
    {
      // checking separate or not
      if(c == sep)
        {
          //checking empty
          if (!(part.empty() &&  ignore_empty))
            {
              parts.push_back(part);
            }
          part.clear();
        }
      else{
          part = part + c;
        }
    }
  parts.push_back(part);
  return parts;
}

void print_word_data (pair<string , set<int>> const &word  )
{
  uint total_row_number = word.second.size();
  cout << word.first << ' ' << total_row_number << ':';

  for(set<int>::iterator iter = word.second.begin();
      iter != word.second.end();
      iter++)
    {
        cout << ' ' << *iter;

      //  checking if last row number
        if(++iter != word.second.end())
          {
            cout << ',';

          }
        iter--;
    }
     cout << endl;
}

int main()
{
  //gettig filename

  cout << "Input file: ";

  string filename;
  getline(cin, filename);

  //try opening
  ifstream file(filename);


  if (!file)
    {
      cout << "Error! The file "<<filename
           <<" cannot be opened."
           <<endl;
      return EXIT_FAILURE;
    }

  //Looping through file and saving values
  map<string, set<int>> words;
  string line;
  vector <string> lineWords;
  vector <string>::iterator words_iter;
  uint line_counter = 1;

  while (getline(file, line))
    {
      lineWords = split(line,' ',true);

      words_iter = lineWords.begin();
      while(words_iter != lineWords.end())
        {
          // checking word in the data
          if(words.find(*words_iter) == words.end())
            {
              words.insert({*words_iter, {}});
            }

          words.at(*words_iter).insert(line_counter);
          ++words_iter;
        }
      ++line_counter;
    }
  for (pair<string , set<int>> const &word_data : words)
    {
      print_word_data(word_data);
    }

}
