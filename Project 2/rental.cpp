//
//  rental.cpp
//  project2
//
//  Created by Anirudh Mani on 10/10/18.
//  Copyright © 2018 Anirudh Mani. All rights reserved.
//

#include <iostream>
using namespace std;

int main() {
    int startOdometer;
    int endOdometer;
    int rentalDays;
    string customerName;
    string luxuryCar;
    int month;
    double rentalCharge = 0;
    
    cout << "Odometer at start: ";
    cin >> startOdometer;
    if(startOdometer < 0){
        cout << "---" << endl;
        cout << "The starting odometer reading must be nonnegative.";
        exit(0);
    }//If statement to check starting odometer is correct values
    
    cout << "Odometer at end: ";
    cin >> endOdometer;
    int milesTraveled = endOdometer - startOdometer;
    if (milesTraveled < 0){
        cout << "---" << endl;
        cout << "The final odometer reading must be at least as large as the starting reading.";
        exit(0);
    }//If statement to check ending odometer > starting odometer
    
    cout << "Rental days: ";
    cin >> rentalDays;
    
    if (rentalDays < 0){
        cout << "---" << endl;
        cout << "The number of rental days must be positive.";
        exit(0);
    }//If statement to check rental days is greater than 0
    
    cin.ignore(10000, '\n');
    cout << "Customer name: ";
    getline(cin, customerName);
    if (customerName == ""){
        cout << "---" << endl;
        cout << "You must enter a customer name.";
        exit(0);
    }//If statement to check if name is empty string
    
    cout << "Luxury car? (y/n): ";
    cin >> luxuryCar;
    if (!(luxuryCar == "y" || luxuryCar == "n")){
        cout << "---" << endl;
        cout << "You must enter y or n.";
        exit(0);
    }//If statement to check if luxury car status is yes or no
    
    cout << "Month (1=Jan, 2=Feb, etc.): ";
    cin >> month;
    if (month < 1 || month > 12){
        cout << "---" << endl;
        cout << "The month number must be in the range 1 through 12.";
        exit(0);
    }//If statgement to check if month is within range
    
    if(luxuryCar == "y"){
        rentalCharge += 61 * rentalDays;
    }
    else{
        rentalCharge += 33 * rentalDays;
    }
    
    if (milesTraveled <= 100){
        rentalCharge += 0.27 * milesTraveled;
    }
    else if (milesTraveled <= 400){
        if (month > 3 && month < 12){
            rentalCharge += 0.21 * (milesTraveled - 100) + (100 * 0.27);
        }
        else {
            rentalCharge += 0.27 * milesTraveled;
        }
    }
    else if (milesTraveled > 400){
        if (month > 3 && month < 12){
            rentalCharge += (0.19 * (milesTraveled - 400)) + (0.21 * 300) + (0.27 * 100);
        }
        else{
            rentalCharge += (0.19 * (milesTraveled - 400)) + (0.27 * 400);
        }
    }
    
    cout.setf(ios::fixed);
    cout.precision(2);
    cout <<"---" << endl;
    cout << "The rental charge for " << customerName << " is $" << rentalCharge;
    
}

