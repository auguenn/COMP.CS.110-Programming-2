#include <iostream>

using namespace std;

int main()
{
    int number = 0;
    cout << "Enter a positive number: ";
    cin >> number;

    if (number <= 0) {
        cout << "Only positive numbers accepted" << endl;
        }
    else {
        int j=1;
            for (int i = j; i * i <= number; i++)
              {
                if (number % i == 0)
                  {
                  j = i;
                  }
              }
            cout << number << " = " << j << " * " << number / j << endl;
            }

    return 0;
}
