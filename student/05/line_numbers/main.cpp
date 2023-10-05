#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string input = "";
    string output = "";

    cout << "Input file: ";
    cin >> input;

    cout<< "Output file: ";
    cin >> output;

    ifstream input_olio(input);

    if ( not input_olio ) {
        cout << "Error! The file " << input <<" cannot be opened." << endl;
        return EXIT_FAILURE;
    }
    else {
        ofstream output_olio(output);
        int x=1;
        string line;

        while(getline(input_olio, line)){
            output_olio << x <<" "<<line<<endl;
            x++;
        }

        input_olio.close();
        output_olio.close();
        return EXIT_SUCCESS;
    }

    return EXIT_SUCCESS;
}
