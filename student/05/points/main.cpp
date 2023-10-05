#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <sstream>
#include <set>
#include <vector>
using namespace std;

int main()
{
    string input_file="";
    multimap<string,int> x;
    string name="",score="";
    int int_score;
    set<string> key_set;
    vector<string> key_vector;
    vector<int> sum;


    cout<< "Input file: " ;
    cin >> input_file ;
    ifstream input_file_object(input_file);
    if(input_file_object){
        string line;

        while(getline(input_file_object, line)){
            stringstream ss(line);
            getline(ss,name,':');
            getline(ss,score,':');
            int_score=stoi(score);

            x.insert(make_pair(name,int_score));
            key_set.insert(name);
            key_vector.assign(key_set.begin(),key_set.end());

            for(unsigned int i=0;i<key_vector.size();i++){
                sum.push_back(0);
            }

        }
        for (auto itr = x.begin(); itr != x.end(); itr++) {
            for (unsigned int i=0;i<key_vector.size();i++) {
                if (itr -> first == key_vector[i]) {
                    //cout << key_vector[i] << "  " << itr -> second << endl;
                    sum[i]+=   itr -> second;
                }
            }
        }
        cout<< "Final scores: " <<endl;
        for(unsigned int i=0;i<key_vector.size();i++){
            cout<<key_vector[i]<<": "<<sum[i]<<endl;
        }

    }
    else{

        cout << "Error! The file "<< input_file << " cannot be opened." <<endl;
        return EXIT_FAILURE;
    }
    input_file_object.close();
}
