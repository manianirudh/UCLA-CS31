//
//  array.cpp
//  project4
//
//  Created by Anirudh Mani on 11/1/18.
//  Copyright © 2018 Anirudh Mani. All rights reserved.
//

#include <iostream>
#include <string>
#include <cassert>
using namespace std;

/*
 method to append a string message to all values within an array
 */
int appendToAll(string a[],int n, string value){
    if(n < 0){
        return -1;
    }
    else{
        for(int i = 0; i < n; i++){
            a[i] = a[i] + value;//access string at an index and adds message
        }
        return n;
    }
}
/*
 method to find a target string within an array
 */
int lookup(const string a[],int n,string target){
    if(n < 0){
        return -1;
    }
    else{
        for(int i = 0; i < n; i++){
            if(a[i] == target){
                return i;//if target is found, the index of target is returned
            }
        }
    }
    return -1;//if target is not found, -1 is returned
}
/*
 finds the index of the alphabetically last string in the array
 */
int positionOfMax(const string a[], int n){
    if(n <= 0){
        return -1;
    }

    else{
        string alphaString = "";
        string currentString = "";
        int index = 0;
        for(int i = 0; i < n; i++){
            currentString = a[i];
            if(currentString > alphaString){ //checks if the currentString is alphabetically later
                alphaString = currentString;
                index = i;// only initializes if currentString is greater, so it will return smallest position if string found multiple times
                
            }
        }
    return index;//returns index of max
    }
}
/*
 rotates every elements one to the left starting at the position index
 */
int rotateLeft(string a[], int n, int pos){
    if(n <= 0 || pos < 0|| (n - pos) <= 0){
        return -1;
    }
    
    else{
        string tempString = a[pos];// holds the element at the position index of the array
        for(int i = pos; i < n-1; i++){ //starts at position index given by parameter
            a[i] = a[i+1]; //copies elements one over to the left
        }
        a[n-1] = tempString;//places string at given position to the last position in the array
        return pos;
    }
}

int countRuns(const string a[], int n){
    if(n < 0){
        return -1;
    }
    else if (n == 0){ //if n is 0 the number of runs is 0 because there are no elements
        return 0;
    }
    else{
        int countRuns = 1; //automatically initializes the number of runs to 1 because it there is >= 1 elements, there will be at least 1 run
        for(int i = 0; i < n - 1; i++){
            if(a[i] != a[i+1]){
                countRuns++;//if two consecutive elements are not the same, then the number of runs increases by 1
            }
        }
        return countRuns; //returns number of  runs
    }
}

int flip(string a[], int n){
    if(n < 0){
        return -1;
    }
    
    else{
        for(int i = 0; i < n/2; i++){ //it goes up to n/2 so that the array doesnt get switched twice
            string temp = "";
            temp = a[i];
            a[i] = a[n-1-i];
            a[n-1-i] = temp;
            /*
             the 4 lines of code above is used to switch two elements
             */
        }
    }
    
    return n;
}

int subsequence(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0 || (n1 - n2) < 0){
        return -1; // (n1 - n2) condition checks to make sure the subsequence array is smaller/equal size to sequence array
    }
    else if (n2 == 0){ //if the subsequence array is 0, then the start index is automatically 0
        return 0;
    }
    
    else{
        for(int j = 0; j < n1; j++){
            bool isSub = true; //boolean variable used as a flag for a subsequence, is reset to true after the if statement
            if(a1[j] == a2[0]){
                int startIndex = j; //variable that stores the possible startIndex of the subsequence
                int index = j; //index variable to move through sequence array
                for(int i = 0; i < n2; i++){
                    if(index >= n1 || a1[index] != a2[i] ){//checks to make sure the sequence array is not out of bounds with first if, checks if the the two elements are equal
                        isSub = false; //variable assigned to false so it breaks out of inner loop
                        break;
                    }
                    else{
                        index++; //index is incremented
                    }
                }
                if(isSub){
                    return startIndex; //if a full subsequence is found the startIndex is returned
                }
            }
        }
        return -1; //if no subsequences is found, the number -1 is returned
    }
}

int differ(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    else{
        if(n1 > n2){
            for(int i = 0; i < n2; i++){
                if(a1[i] != a2[i]){
                    return i; //returns index where the two arrays differ
                }
            }
            return n2;//if everything is the same returns the smaller array
        }
        else{
            for(int i = 0; i < n1; i++){
                if(a1[i] != a2[i]){
                    return i; //returns index where the two arrays differ
                }
            }
            return n1;//if everything is the same returns the smaller array
        /*
         two conditionals used to check which n value (n1 or n2) to return if no difference is found
         */
        }
    }
}

int lookupAny(const string a1[], int n1, const string a2[], int n2){
    if(n1 < 0 || n2 < 0){
        return -1;
    }
    else if (n1 == 0 && n2 == 0){ //if both sizes are 0 the index returned is 0
        return 0;
    }
    else{
        for(int i = 0; i < n1; i++){
            for(int j = 0; j < n2; j++){
                if(a1[i] == a2[j]){
                    return i;// returns index of element in a1 that is same as a2
                }
            }
        }
    }
    return -1; //if there is no similar  element
}

int divide(string a[],int n, string divider){
    int counter = 0;
    
    if(n < 0){
        return -1;
    }
    else{
        for(int k = 0; k < n; k++){
            if (a[k] < divider){
                counter++;//counts up number of elements less than divider
            }
        }
        
        for(int i = 0; i < n; i++){
            if(a[i] > divider){
                int j = i + 1;//if there is an element that is greater, the rest of the loop is iterated through
                while(j < n){
                    if(a[j] <= divider){ //if a lower element is found, the two elements are switched
                        string temp = a[i];
                        a[i] = a[j];
                        a[j] = temp;
                        j = n;//uses this to exit the while loop
                    }
                    else{
                        j++;
                    }
                }
            }
        }
        return counter;
        
        
    }
}



int main() {

    string zero[0] = {};
// append to all
    string nflTeams[4] = {"niners","raiders","patriots","chiefs"};
    //general case to check if method works
    assert(appendToAll(nflTeams, 4, "!!") == 4 && nflTeams[0] == "niners!!" && nflTeams[1] == "raiders!!" && nflTeams[2] == "patriots!!" && nflTeams[3] == "chiefs!!");
    
    //edge case
    assert(appendToAll(zero, 0, "!!") == 0); //zero case
    assert(appendToAll(nflTeams, -1, "!!") == -1); //less than zero case
    
// lookup
    string n[6] = {"hari", "ravi" , "harsh", "sahen", "hari", "hArI"};
    assert(lookup(n, 6, "sahen") == 3);
    assert(lookup(n, 6, "hari") == 0);
    assert(lookup(zero, 0, "hari") == -1);
    assert(lookup(n, 6, "HaRi") == -1);
    assert(lookup(n, -1, "harsh") == -1);

//position of max
    string x[4] = {"green", "yellow", "red", "blue"};
    string x1[6] = {"green", "blue", "red", "yellow", "yellow", "orange"};
    assert(positionOfMax(x, 4) == 1);
    assert(positionOfMax(x1, 6) == 3);
    assert(positionOfMax(zero, 0) == -1);
    assert(positionOfMax(x1, -3) == -1);
    
//    rotate to left
    string teams[4] = {"niners","raiders","patriots","chiefs"};
    
    assert(rotateLeft(teams, 4, 3) == 3 && teams[0] == "niners" && teams[1] == "raiders" && teams[2] == "patriots" && teams[3] == "chiefs");
    assert(rotateLeft(teams, 4, 0) == 0 && teams[0] == "raiders" && teams[1] == "patriots" && teams[2] == "chiefs" && teams[3] == "niners");
    assert(rotateLeft(teams, 4, -1) == -1);
    assert(rotateLeft(teams, -1, -3) == -1);
    assert(rotateLeft(teams, 4, 6) == -1);
    assert(rotateLeft(zero, 0, 1) == -1);

//    countRuns
    string s[5] = {"ted", "ted", "bill", "bill", "bill"};
    string s1[3] = {"ted", "ted" , "ted"};
    string s2[6] = {"ted", "tEd", "teD", "TEd", "tED", "TED"};
    assert(countRuns(s, 5) == 2);
    assert(countRuns(s1, 3) == 1);
    assert(countRuns(s2, 6) == 6);
    assert(countRuns(zero, 0) == 0);
    assert(countRuns(s, -4) == -1);

//    flip
    string fl[4] = {"a", "b", "c", "d"};
    string fli[4] = {"a", "b", "c", "d"};
    assert(flip(fl, 3) == 3 && fl[0] == "c" && fl[1] == "b" && fl[2] == "a" && fl[3] == "d");
    assert(flip(fli, 4) == 4 && fli[0] == "d" && fli[1] == "c" && fli[2] == "b" && fli[3] == "a");
    assert(flip(zero, 0) == 0);
    assert(flip(fl, -3) == -1);

//    differ
    string nba[4] = {"lakers","celtics","warriors","rockets"};
    string nTeams[2] = {"lakers", "jazz"};
    string nbaTeams[7] = {"lakers","celtics","warriors","rockets", "jazz", "pelicans", "knicks"};
    assert(differ(nba, 4, nTeams, 2) == 1);
    assert(differ(nba, 4, zero, 0) == 0);
    assert(differ(nba, -1, nba, 4) == -1);
    assert(differ(nba, 4, nTeams, -2) == -1);
    assert(differ(nba, 4, nbaTeams, 7) == 4);
    assert(differ(nbaTeams, 7, nba, 4) == 4);
    assert(differ(zero, 0, nTeams, 4) == 0);
    
//    subsequence
    
    string arr[6] = {"a", "b", "c", "d", "e", "f"};
    string arr1[7] = {"a","b", "c", "e", "b", "c", "e"};
    string arr2[3] = {"b", "c", "d"};
    string arr3[4] = {"d", "e", "f", "g"};
    
    assert(subsequence(arr, 3, arr1, 3) == 0);
    assert(subsequence(arr, 6, zero, 0) == 0);
    assert(subsequence(arr, 6, arr3, 3) == 3);
    assert(subsequence(zero, 0, arr2, 3) == -1);
    assert(subsequence(arr, 6, arr2, 7) == -1);
    assert(subsequence(arr, -1, arr2, 7) == -1);
    assert(subsequence(arr2, -2, arr1, 3) == -1);
    assert(subsequence(arr1, 7, arr2, 3) == -1);
    assert(subsequence(arr, 6, arr3, 4) == -1);
    
//    lookup any
    string l[4] = {"b", "c", "d", "e"};
    string k[3] = {"f", "g", "c"};
    
    assert(lookupAny(l, 4, k, 3) == 1);
    assert(lookupAny(k, 3 , l, 4) == 2);
    assert(lookupAny(l, 4, k, 2) == -1);
    assert(lookupAny(zero, 0, k, 3) == -1);
    assert(lookupAny(zero, 0, k, 0) == 0);
    assert(lookupAny(l, -1, k, 3) == -1);
    assert(lookupAny(l, 4, k, -2) == -1);
    
//    divide
    string u[5] = {"q", "w", "f", "h", "p"};
    
    assert(divide(zero, 0, "ted") == 0);
    assert(divide(u, -1, "h") == -1);
    assert(divide(u, 5, "a") == 0);
    assert(divide(u, 5, "z") == 5);
    assert(divide(u, 5, "l") == 2);
    assert(divide(u, 5, "r") == 4);
    
    cerr << "PASS";
}
