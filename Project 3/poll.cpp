//
//  main.cpp
//  project3
//
//  Created by Anirudh Mani on 10/22/18.
//  Copyright © 2018 Anirudh Mani. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;
/*
 this is a helper method that checks if the statecode passed is valid
 */

bool isValidUppercaseStateCode(string stateCode)
{
    const string codes =
    "AL.AK.AZ.AR.CA.CO.CT.DE.FL.GA.HI.ID.IL.IN.IA.KS.KY."
    "LA.ME.MD.MA.MI.MN.MS.MO.MT.NE.NV.NH.NJ.NM.NY.NC.ND."
    "OH.OK.OR.PA.RI.SC.SD.TN.TX.UT.VT.VA.WA.WV.WI.WY";
    return (stateCode.size() == 2  &&
            stateCode.find('.') == string::npos  &&  // no '.' in stateCode
            codes.find(stateCode) != string::npos);  // match found
}
/*
 this is a helper function that checks if the string pollD passed meets the poll data rules
 pollData is this case is a substring of a pollData that only includes one state forecast
*/

bool isValidChecker(string pollD){
    int x = 0;
    string stateCode = "";
    int digitCounter = 0;
    
    if(!isalpha(pollD[x])){
        return false;
    }
    while(isalpha(pollD[x])){
        stateCode += pollD[x];
        x++;
    }
    if(!isValidUppercaseStateCode(stateCode)){
        return false;
    }
    else{
        while (x != pollD.size()){
            if(!isdigit(pollD[x])){
                return false;
            }
            while(isdigit(pollD[x])){
                digitCounter ++;
                x++;
                
                if(digitCounter > 2){
                    return false;
                }
            }
            if(!isalpha(pollD[x])){
                return false;
            }
            x++;
            digitCounter = 0;
        }
    }
    return true;
}

/*
 function to check if an entire pollData string is valid
 */
bool hasProperSyntax(string pollData){
    string stateCode = "";
    bool hasProper = true;
    int commaCounter = 0;
    int startIndex = 0;
    int endIndex = 0;
    string upperPollData = "";
    
    //code to count how many commas are in pollData
    for(int i = 0; i != pollData.size(); i++){
        if(pollData[i] == ','){
            commaCounter++;
        }
    }
    //code to convert everything to uppercase (if possible)
    for (int j = 0; j != pollData.size(); j++){
        upperPollData += toupper(pollData[j]);
    }
    //code to return true for an empty string
    if (upperPollData.length() == 0){
        return true;
    }
    
    //if statement to check for proper syntax given only 1 state within a statecode (no commas)
    if (commaCounter == 0){
        hasProper = isValidChecker(upperPollData);
    }
    //control flow to check proper syntax for every single state forecast
    else{
        upperPollData += ","; //adds a comma at the end of the temporary string
        for(int j = startIndex; j != upperPollData.size(); j++){
            if(upperPollData[j] == ','){
                endIndex = j;// sets endIndex to the index of j
                int length = endIndex - startIndex; //determines length of a state forecast
                hasProper = isValidChecker(upperPollData.substr(startIndex,length)); //checks if state forecast has proper syntax
                if(hasProper == false){
                  return false; //automatically returns false if forecast does not have proper syntax
                }
                startIndex = endIndex + 1; //reassigns startIndex to after comma
            }
        }
    }
    return hasProper;
}
/*
 function to set correct amount of tallySeats based on character passed in
 */
int tallySeats(string pollData, char party, int& seatTally){
    //for loop to change lowercase letters in poll case
    for (int j = 0; j != pollData.size(); j++){
        pollData[j] = toupper(pollData[j]);
    }
    
    party = toupper(party); //converts party character to upper case
    
    //control flow to check if pollData has proper syntax
    if (!hasProperSyntax(pollData)){
        return 1;
    }
    //control flow to check if party character is an alphabet
    else if(!isalpha(party)){
        return 2;
    }
    //control flow to check if pollData size is 2 or 0, in which case seatTally will be set to 0
    else if(pollData.size() == 2 || pollData.size() == 0){
        seatTally = 0;
        return 0;
    }
    //control flow to tally the number of seats for a given party
    else{
        seatTally = 0;
        for(int i = 2; i != pollData.size(); i++){
            if(pollData[i] == party){
                if(isdigit(pollData[i - 2])){
                    seatTally += ((pollData[i - 2] - '0') * 10) + ((pollData[i - 1] - '0') * 1);
                }
                
                else if (isdigit(pollData[i - 1])){
                    seatTally += (pollData[i - 1] - '0') * 1;
                }
            }
        }
        return 0;
    }
}

int main(){
    int seatTally = 0;
    assert(hasProperSyntax("TX")); //tests if statecode function works
    assert(hasProperSyntax("tX")); //tests to make sure capitalization occurs
    assert(hasProperSyntax("Tx20R")); //tests to see if isValidChecker works
    assert(hasProperSyntax("TX1D21R")); //tests to see if isValidChecker works for multiple parties
    assert(hasProperSyntax("+TX1D") == false); //tests to see if isValidChecker properly handles characters
    assert(hasProperSyntax("YY") == false); //tests if statecode functions returns false correctly
    assert(hasProperSyntax("TX9R17D1I,Ny,CA3d5r4D,UT4R"));//tests if hasProperSyntax works for multiple commas
    assert(hasProperSyntax("ut3r00456D") == false); //tests if it returns false for size > 2 of number
    assert(hasProperSyntax("Ny9D,Vt*3,NJ3r") == false); //tests if hasProperSyntax properly returns false if syntax is wrong
    assert(hasProperSyntax("MA9D,UT4R")  &&  hasProperSyntax("KS4R,MA9D"));//given by Smallberg to check if commas work
    assert(hasProperSyntax("MA9D,,UT4R") == hasProperSyntax("KS4R,,MA9D"));
    assert((tallySeats(" ", 'R', seatTally) == 1));//checks to see if hasProperSyntax properly called in tallySeats
    assert((tallySeats("CA99D", '2', seatTally) == 2));//checks to see if tallySeats properly returns if party character not an alphabet
    assert((tallySeats("", 'R', seatTally) == 0) && seatTally==0);//checks to see if tallySeats works for empty string
    assert((tallySeats("VT", 'D', seatTally) == 0) && seatTally==0);//checks to see if tallySeats works for just state code
    assert((tallySeats("MA1d", 'D', seatTally) == 0) && seatTally==1);//checks to see if tallySeats properly tallies for one state forecast
    assert((tallySeats("TN87R", 'R', seatTally) == 0) && seatTally==87);//checks to see if tallySeats proerly tallies for 2 digits
    assert((tallySeats("NY1D33R", 'R', seatTally) == 0) && seatTally==33);//checks to see if tallySeats properly tallies with a forecast of multiple parties
    assert((tallySeats("NY12R,MA34R", 'R', seatTally) == 0) && seatTally==46);//checks to see if tallySeats properly tallies with
    assert((tallySeats("TX9R17D1I,Ny,CA3d5r4D,KS4K", 'K', seatTally) == 0) && seatTally==4);//checks to see if tallySeats properly avoids error if statecode and party are the same
    cerr << "PASS";
}




