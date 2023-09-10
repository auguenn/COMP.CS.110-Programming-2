#include <iostream>
#include <cmath>
using namespace std;

int main()
{
    cout << "Enter a number: ";
    int value = 0;
    cin >> value;
    int cube = 0;
    if (value != 0) {
        cube = pow(value, 3.0);
        if (cube / value / value == value) {
            cout << "The cube of " << value << " is " << cube << "." << endl;
        }
        else {
            cout << "Error! The cube of " << value << " is not " << cube << "." << endl;

        }
    }
    else {
        cout << "The cube of 0 is 0." << endl;
    }
}
