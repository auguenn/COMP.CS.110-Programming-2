#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";

    // Write your code here
    double temperature = 0;
    cin >> temperature;

    double temperature_in_fahrenhite = (temperature*1.8)+32;
    cout << temperature << " degrees Celsius is " << temperature_in_fahrenhite << " degrees Fahrenheit" <<endl;

    double temperature_in_celsius = (temperature-32)/1.8;
    cout << temperature << " degrees Fahrenheit is " << temperature_in_celsius << " degrees Celsius" <<endl;

    return 0;
}
