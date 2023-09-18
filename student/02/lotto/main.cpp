#include <iostream>

using namespace std;

unsigned long int factorial(unsigned long int n)
{
    if (n > 0) {
        return n * factorial(n - 1);
       }
    else {
            return 1;
        }
}

unsigned long int count_possibility(unsigned long int& total, unsigned long int& drawn)
{
    unsigned long int a = 1;
    unsigned long int b = 1;
    unsigned long int c = 1;

    a = factorial(total);
    b = factorial(drawn);
    c = factorial(total-drawn);

    unsigned long int possibility = 1;
    possibility = a/(c*b);

    return possibility;
}

int main()
{
    unsigned long int total = 0;
    cout << "Enter the total number of lottery balls: ";
    cin >> total;

    unsigned long int drawn = 0;
    cout << "Enter the number of drawn balls: ";
    cin >> drawn;

   if (total < 0 || drawn < 0) {
       cout << "The number of balls must be a positive number." <<endl;
   }
   else  if ( drawn > total )
     {
       cout << "The maximum number of drawn balls is the total amount of balls." << endl;
     }
    else if ( drawn == total )
      {
        cout << "The probability of guessing all "<< drawn <<" balls correctly is 1/1" << endl;
      }
   else {
       cout <<"The probability of guessing all " << drawn << " balls correctly is 1/" << count_possibility(total, drawn) <<endl;
   }
    return 0;
}
