// This program will calculate the amount of money that will be in a savings account after it has
// been deposited for a number of months. This will use multiple functions and get input from a file.

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

unsigned int readData(ifstream&, double&, double&, int&);  // Function prototype for reading in the present value, interest rate and # of months.
double futureValue(double, double, int);  // Function prototype for calculating the future value.
void displayResults(ofstream&, double, double, double, int );  // Function prototype for writing the values to the output file.

    // Main function.
int main()
{
        // Declare variables.
    double futureVal ;  // To hold the amount of money that will be obtained in the future after receiving interest.
    double interestRate ;  // To hold the rate at which the deposited money will increase each month.
    int months;  // To hold the number of months that the deposited money will be left in the savings account.
    double presentValue;  // To hold the amount of money to deposit today.
    int returnValue = 1;  // For determining whether valid or invalid values were gotten from the file, or end of file has been reached.
    string iFileName;  // To hold the name of the input file.
    ifstream inputFile;  // To hold the input file object.
    ofstream outputFile; // To hold the output file object.

        // Ask the user to enter the name of the input file.
    cout << "Enter input file name";
    cin >> iFileName;
    cout << endl;

        // Open the input file.
    inputFile.open(iFileName);

        // If the input file did not open write out an error message and stop processing.
    if (!inputFile)
    {
        cout << "File \"" << iFileName << "\" could not be opened" << endl;
        exit(0);
    }

        // Open the output file.
    outputFile.open("output.xls");

        // If the open failed close the input file, display an error message and stop processing.
    if (!outputFile)
    {
        cout << "File \"output.xls\" could not be opened" << endl;
        exit(0);
    }

        // Write the headings to the output file.
    outputFile << "Future Value\tPresent Value\tMonthly Interest\tMonths" << endl;

        // Check if the end of file for the input file has not been reached.
    while (returnValue != 0)
    {
            // Call the function for reading in the present value, interest rate and number of months, store the value it returns.
            // Pass the input file by reference so that the program can continue reading from where it left off.
        returnValue = readData (inputFile, presentValue, interestRate, months);

            // If the input is valid calculate the future value and display the results.
        if (returnValue == 1)
        {
                // Call the function for calculating the future value.
                // Convert the monthly interest rate to a percentage.
            futureVal = futureValue (presentValue, interestRate / 100, months);

                // Call the function for writing the results to the output file.
                // Pass the output file by reference so that the program can continue writing from where it left off.
            displayResults (outputFile, futureVal, presentValue, interestRate, months);
        }

            // If the input is not valid display the data and an error message.
        else if (returnValue == 2)
        {
                // Set the desired output formatting for numbers.
            cout << setprecision(2) << fixed << showpoint;

            cout << presentValue << " ";

            // Set the desired output formatting for numbers.
            cout << setprecision(3) << fixed << showpoint;

            cout << interestRate << " ";

                // Set the desired output formatting for numbers.
            cout << setprecision(0);

            cout << months << endl;
            cout << "One or more of the above values are not greater than zero" << endl;
        }
    }


        // Close the input and output files.
    inputFile.close();
    outputFile.close();

    return 0;
}

    // Function for reading in the present value, interest rate and number of months.
unsigned int readData (ifstream& inputFile, double& presentValue, double& interestRate, int& months)
{
        // Read and store the data gotten from the file.
    if (inputFile >> presentValue >> interestRate >> months)
    {
            // If every read data is valid, return '1' to the calling function.
        if ((presentValue > 0.0 ) && (interestRate > 0.0) && (months > 0))
            return 1;

            // If any of the data is invalid, return '2' to the calling function.
        else
            return 2;
    }

        // If end of file has been reached, return '0' to the calling function.
    else
        return 0;
}

    // Function for calculating the future value.
double futureValue (double presentValue, double interestRate, int months)
{
        // Return the future value to the calling function.
    return( presentValue * pow ((1 + interestRate), months) );
}

    // Function for writing the values to the output file.
void displayResults (ofstream& outputFile, double futureVal, double presentValue, double interestRate, int months)
{
        // Set the desired output formatting for numbers.
    outputFile << setprecision(2) << fixed << showpoint;

    outputFile << futureVal << "\t" << presentValue << "\t";

        // Set the desired output formatting for numbers.
    outputFile << setprecision(3) << fixed << showpoint;

    outputFile << interestRate << "\t";

        // Set the desired output formatting for numbers.
    outputFile << setprecision(0);

    outputFile << months << endl;
}
