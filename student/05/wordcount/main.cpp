#include <iostream>
#include <sstream>
#include <fstream>
#include <map>
using namespace std;

int main()
{
    string input_file="";
    cout<< "Input file: " ;
    cin >> input_file ;
    ifstream input(input_file);

    if ( !input ) {
        cout << "Error! The file "<< input_file << " cannot be opened." <<endl;
        return EXIT_FAILURE;
    }
    multimap<string, int>  words;

        //string word;

        for(int lines=1;input;lines++){
            string buf;
            getline( input, buf);
            istringstream i( buf );
            if(i){
                string line;
                while(i>>line){
                    if (line != ""){
                        words.insert( pair<string,int>( line, lines ));
                    }

                }
            }
        }

        input.close();

        multimap< string, int>::iterator it1;
        multimap< string, int>::iterator it2;

        for ( it1 = words.begin(); it1 != words.end(); )
        {
            it2 = words.upper_bound( (*it1).first );
            string s="";
            cout << (*it1).first << " " <<words.count((*it1).first)<< ": "  ;

            for ( ; it1 != it2; it1++ )
            {
                s+=to_string((*it1).second) + ", ";

            }
            for(unsigned int i=3;i<s.length();i++){
                if(s[0]==s[3]) s.erase(1,3);
                else if(s[6]==s[3]) s.erase(4,6);
                else if(i%3==0){
                    if(s[i]==s[i-3]) {
                        s.erase(i-2,i);
                    }
                }
            }
            cout<< s.substr(0,s.length()-2);
            cout << endl;
        }

}
