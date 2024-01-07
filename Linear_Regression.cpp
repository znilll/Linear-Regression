
#include<iostream>
#include<fstream>

using namespace std;

ifstream rfile;

void read(int *, float [][2]);       // Reads data from file
void calc(int, double *, double *, float [][2]);  // Calculates slope and y-intercept
void write(double, double);     // Writes function of line of best fit to the screen

int main(){

    float coordinates[501][2];      // Creating 2D array to store (x, y) values
    int count = 0;      
    double slope, y_intercept;

    read(&count, coordinates);
    calc(count, &slope, &y_intercept, coordinates);
    write(slope, y_intercept);
    return 0;
}

void read(int *pcount, float arr[][2]){

    int i = 0;

    rfile.open("data.dat");

    if(!rfile){     // If there is an error opening data file, exit with 1.
        cout << "File couldn't opened!" << endl;
        exit(1);
    }

    while(!rfile.eof()){        // While end of file is not reached

        rfile >> arr[i][0] >> arr[i][1];    // Taking data into 2D array
        i++;        // Counting
    }

    if(i == 1){     // There is a line in the beginning of the emty .dat file and that makes i = 1.
        cout << "Dataset in the file is not valid or doesn't exist!" << endl;
        exit(2);
    }
    
    *pcount = i;    // Count in main will be i
    rfile.close();  // Closing data file
}

void calc(int count, double *pslope, double *py_intercept, float arr[][2]){
    double square_sum = 0, xy_sum = 0, x_sum = 0, y_sum = 0;

    for(int i = 0; i < count; i++){ // Calculating necessarry data for linear regression 
        square_sum += arr[i][0] * arr[i][0];
        xy_sum += arr[i][0] * arr[i][1];
        x_sum += arr[i][0];
        y_sum += arr[i][1];
    }

    *pslope = ((count * xy_sum) - (x_sum * y_sum))/ ((count * square_sum) - (x_sum * x_sum));   // Calculating slope
    *py_intercept = (y_sum - (*pslope * x_sum))/count;      // Calculating y-intercept
    
}

void write(double slope, double y_intercept){

    cout << "y = ax + b;" << endl;      // Writing results
    cout << "Slope (a) = " << slope << endl;
    cout << "Intercept (b) = " << y_intercept << endl << endl;
    cout << "Function of line of best fit for the given dataset is: " << endl;
    cout << "y = " << slope << "x  " << showpos << y_intercept << endl << endl;

}