#include <iostream>
#include <string>

using namespace std;


int main()
{
    cout << "How many numbers would you like to have? ";

    // Write your code here
    int numbers = 0;
    cin >> numbers;

    int i = 0;
    while (i < numbers) {
        ++i;
        if (i % 3 == 0 && i % 7 == 0) {
            cout << "zip boing" <<endl;
        }
        else if (i % 3 == 0) {
            cout << "zip" <<endl;
        }
        else if (i % 7 == 0) {
            cout << "boing" <<endl;
        }
        else {
        cout << i << endl;
        }

    }


    return 0;
}
