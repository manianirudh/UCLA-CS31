//
//  main.cpp
//  project5
//
//  Created by Anirudh Mani on 11/7/18.
//  Copyright © 2018 Anirudh Mani. All rights reserved.
//

#include <iostream>
using namespace std;
#include <cstring>
#include <cassert>

const int MAX_WORD_LENGTH = 20;


/*
 this helper function is called in order to "remove" an element from the array if called
 */
void eliminate(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns, int pos){
    for(int i = pos; i < nPatterns-1; i++){
        separation[i] = separation[i+1];
        strcpy(word1[i], word1[i+1]);
        strcpy(word2[i], word2[i+1]);
        
    }
}
/*
 this method takes in 3 arrays and removes the incorrect element rows, and then returns the correct value of nPatterns
 */
int makeProper(char word1[][MAX_WORD_LENGTH+1], char word2[][MAX_WORD_LENGTH+1], int separation[], int nPatterns){
    if (nPatterns < 0){
        return 0;
    }
    /*
     makes every every alphabet character in word1 and word2 lowercase
     */
    for(int i = 0; i < nPatterns; i++){
        for (int j = 0; j < MAX_WORD_LENGTH; j++) {
            word1[i][j] = tolower(word1[i][j]);
            word2[i][j] = tolower(word2[i][j]);
        }
    }
    /*
     removes the pattern if the seperation value is negative
     */
    for(int k = 0; k < nPatterns; k++){
        if(separation[k] < 0){
            eliminate(word1, word2, separation, nPatterns, k);
            nPatterns--;
            k--; //does this to make sure it removes two negative values in a row
        }
    }
    /*
     removes the incorrect rows in word 1 (if a word contains a non-alpha)
     */
    
    for(int i = 0; i < nPatterns; i++){
        for(int j = 0; j < strlen(word1[i]); j++){
            if ((!isalpha(word1[i][j]) && word1[i][j] != '\0')){
                eliminate(word1, word2, separation, nPatterns, i);
                nPatterns--;
                i--; //makes sure not to skip two incorrect words
                break;//breaks out of inner for loops to go to next index
            }
        }
    }
    /*
     removes empty strings in word1
     */
    for(int i = 0; i < nPatterns; i++){
        if(strlen(word1[i]) == 0){
            eliminate(word1, word2, separation, nPatterns, i);
            nPatterns--;
            i--;//makes sure to not skip two empty string in a row
        }
    }
    /*
     removes empty strings in word2
    */
    for(int i = 0; i < nPatterns; i++){
        if(strlen(word2[i]) == 0){
            eliminate(word1, word2, separation, nPatterns, i);
            nPatterns--;
            i--;//makes sure to not skip two empty string in a row
        }
    }
    /*
     removes the incorrect rows in word 2 (if a word contains a non-alpha)
     */
    for(int i = 0; i < nPatterns; i++){
        for(int j = 0; j < strlen(word2[i]); j++){
            if ((!isalpha(word2[i][j]) && word2[i][j] != '\0')){
                eliminate(word1, word2, separation, nPatterns, i);
                nPatterns--;
                i--; //makes sure not to skip two incorrect words
                break;//breaks out of inner for loops to go to next index
            }
        }
    }
    
    
    /*
     removes repeated words
     */
    for (int i = 0; i < nPatterns; i++) {
        for(int j = i+ 1; j < nPatterns; j++){
            if((strcmp(word1[i], word2[j]) == 0 && strcmp(word1[j], word2[i]) == 0) || (strcmp(word1[i], word1[j]) == 0 && strcmp(word2[j], word2[i]) == 0) ){
                if(separation[i] >= separation[j]){
                    eliminate(word1, word2, separation, nPatterns, j);//removes row j
                    nPatterns--;
                    j--;//decrements j to check the rest of the nPatterns if the same pattern exists
                    
                }
                else{
                    eliminate(word1, word2, separation, nPatterns, i);
                    nPatterns--;
                    i--;//resets to the previous row so not to skip any repeated element
                    j = nPatterns;//breaks out of nest for loop
                    break;//breaks out of the if statement
                    
                }
                
            }
        }
    }
    
    
    return nPatterns;
}

const int DOCUMENT_MAX_LENGTH = 250;

int rate(const char document[], const char word1[][MAX_WORD_LENGTH+1], const char word2[][MAX_WORD_LENGTH+1], const int separation[], int nPatterns){
    
    /*
     for loop to automatically return value for negative nPatterns
     */
    if (nPatterns < 0){
       nPatterns = 0;
    }
    
    int counter = 0;
    
    /*
        this for loop converts all charaacters in the document array into lowercase
    */
    char fixedDocument[DOCUMENT_MAX_LENGTH+1];
    int index = 0;
    for(int i = 0; document[i] != '\0'; i++){
        fixedDocument[i] = tolower(document[i]);
        index = i;//holds the current element to be used outside
    }
    fixedDocument[index+1] = '\0';//sets the last index in fixedDocument to the 0 byte
    
    /*
     this loop is to remove all characters that are not spaces or alphabets
    */
    for (int i = 0; i != strlen(fixedDocument); i++) {
        if(fixedDocument[i] != ' ' && !isalpha(fixedDocument[i])){
            for(int j = i; j < strlen(fixedDocument); j++){
                fixedDocument[j] = fixedDocument[j+1];
            }
            i--;
        }
    }
    
    /*
     this loop is to remove extra spaces (ie if there are 3 spaces in a row it would remove the 2 extra ones)
    */
    for (int i = 0; i != strlen(fixedDocument) - 1; i++) {
        if(fixedDocument[i] == ' ' && fixedDocument[i+1] == ' '){
            for(int j = i; j < strlen(fixedDocument); j++){
                fixedDocument[j] = fixedDocument[j+1];
            }
            i--;//makes sure to not skip two spaces in a row
        }
    }
    
//    for(int i = 0; i < strlen(fixedDocument); i++){
//        cout << fixedDocument[i];
//    }
//    cout << endl;
    
    /*
     this loop counts the number of spaces
    */
    int numSpaces = 0;
    for(int i = 0; i != strlen(fixedDocument); i++){
        if(fixedDocument[i] == ' '){
            numSpaces++;
        }
    }
    
    
    int NUMBER_OF_ROWS = numSpaces + 1;//number of rows is 1 plus the number of spaces (becuz first word may not have a space before)
    
    char wordsOfDocument[DOCUMENT_MAX_LENGTH+1][DOCUMENT_MAX_LENGTH+1];//initalizes the array for the words in document
    int rowIndex = 0;
    int columnIndex = 0;
    
    /*
     loads the 2d array with words of the document
    */
    for(int i = 0; i != strlen(fixedDocument); i++){
        if(fixedDocument[i] != ' '){
            wordsOfDocument[rowIndex][columnIndex] = fixedDocument[i];//loads character to 2d array
            columnIndex++;//moves to next column in row
        }
        else if(fixedDocument[i] == ' '){
            wordsOfDocument[rowIndex][columnIndex] = '\0';//makes the last value a zero byte
            rowIndex++; //moves down to the next row
            columnIndex = 0; //resets column to 0 so it starts at the same thing
        }
    }
    
//    for(int i = 0; i < NUMBER_OF_ROWS; i++){
//        cout << wordsOfDocument[i] << endl;
//    }
//    cout << endl;
    
    /*
     method to calculate the rating of the document
    */
    for(int j = 0; j < nPatterns; j++){
//        cout << "index j is : " << j << endl;
        for(int i = 0; i < NUMBER_OF_ROWS; i++){
//            cout << "index i is: " << i << endl;
            if(strcmp(wordsOfDocument[i], word1[j]) == 0){
                int sep = 1;
                while((sep <= separation[j] + 1) && (i+sep) < NUMBER_OF_ROWS){
                    if(strcmp(wordsOfDocument[i+sep], word2[j]) == 0){
//                        cout << "PATTERN FOUND (FOREWARDS)" << endl;
//                        cout << "word1 is: " << wordsOfDocument[i] << endl;
//                        cout << "word2 is: " << wordsOfDocument[i+sep] << endl;
                        counter++; //increments rating
                        i = NUMBER_OF_ROWS; //breaks out of nested for loop
                        break; //breaks out of while loop
                    }
                    else{
                        sep++;//if word not found, increment position
                    }
                }
            }
            if(strcmp(wordsOfDocument[i], word2[j]) == 0){
                int sep = 1;
                while((sep <= separation[j] + 1) && (i+sep) < NUMBER_OF_ROWS){
                    if(strcmp(wordsOfDocument[i+sep], word1[j]) == 0){
//                        cout << "PATTERN FOUND (BACKWARDS)" << endl;
//                        cout << "word2 is: " << wordsOfDocument[i] << endl;
//                        cout << "word1 is: " << wordsOfDocument[i+sep] << endl;
                        counter++; //increments rating
                        i = NUMBER_OF_ROWS; //breaks out of nested for loop
                        break; //breaks out of while loop
                    }
                    else{
                        sep++;//if word not found, increment position
                    }
                }
            }
        }
    }
    

    /*
     clears every row in the 2d array for the next call
     */
    for(int i = 0; i < DOCUMENT_MAX_LENGTH+1; i++){
        for(int j = 0; j < DOCUMENT_MAX_LENGTH+1; j++)
        wordsOfDocument[i][j] = '\0';//sets every since element to the zero byte
    }
    
    return counter;//returns the rating
}

/*
 helper function to print out a cstring array
 */
void printCString(char arr[][MAX_WORD_LENGTH+1], int n){
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}

/*
 helper function to print out the separation array
 */
void printSeparation (int arr[], int n){
    for (int i = 0; i < n; i++){
        cout << arr[i] << " ";
    }
    cout << endl;
}



int main() {
    char test1w1[][MAX_WORD_LENGTH+1] = {
        "scientist","deranged", "nefarious", "have"
    };
    char test1w2[][MAX_WORD_LENGTH+1] = {
        "mad", "robot","plot", "happiness"
    };
    int test1dig[] = {
        -1,-3,0,12
    };
    assert(makeProper(test1w1,test1w2,test1dig,4) ==2); //checks to see if it removes negative separations

    char test2w1[][MAX_WORD_LENGTH+1] = {
        "scientist","half-deranged", "nefar1ous", "almost-have"
    };
    char test2w2[][MAX_WORD_LENGTH+1] = {
        "mad", "robot",    "plot",      "happiness"
    };
    int test2dig[] = {
        1, 3, 0, 12
    };
    assert(makeProper(test2w1, test2w2, test2dig, 4) == 1); //checks to see if it removes improper words in w1

    char test3w1[][MAX_WORD_LENGTH+1] = {
        "scientist","deranged", "nefarious", "have"
    };
    char test3w2[][MAX_WORD_LENGTH+1] = {
        "mad!!!","robot","345","happiness"
    };
    int test3dig[] = {
        1, 3, 0, 12
    };
    assert(makeProper(test3w1, test3w2, test3dig, 4) == 2); //checks to see if it removes improper words in w2

    char test4w1[][MAX_WORD_LENGTH+1] = {
        "scientist","d3ranged", "nefarious", "have", "good", "pointers", "mad"
    };
    char test4w2[][MAX_WORD_LENGTH+1] = {
        "mad!!!", "robot",    "345",      "happiness", "life", "d3ath", "scientist"
    };
    int test4dig[] = {
        1, 3, 0, 12,-30, 2, 5
    };

    assert(makeProper(test4w1, test4w2, test4dig, 7) == 2); //checks if the removal works for all 3 cases without errors

    char test5w1[][MAX_WORD_LENGTH+1] = {
        "scientist","deranged", "nefarious", "mad"
    };
    char test5w2[][MAX_WORD_LENGTH+1] = {
        "mad", "robot",    "plot",      "scientist"
    };
    int test5dig[] = {
        1, 3, 0, 12
    };
    assert(makeProper(test5w1, test5w2, test5dig, 4) == 3); //checks to see if it removes pattern found but switched

    char test6w1[][MAX_WORD_LENGTH+1] = {
        "scientist","deranged", "nefarious", "mad", "deranged"
    };
    char test6w2[][MAX_WORD_LENGTH+1] = {
        "mad", "robot",    "plot",      "life", "robot"
    };
    int test6dig[] = {
        1, 3, 0, 12, 5
    };
    assert(makeProper(test6w1, test6w2, test6dig, 5) == 4); //checks to see if it removes exact pattern found

    char test7w1[][MAX_WORD_LENGTH+1] = {
        "scientist","scientist", "m3d", "mad", "mad"
    };
    char test7w2[][MAX_WORD_LENGTH+1] = {
        "mad", "mad",    "scientist",      "scientist", "scientist"
    };
    int test7dig[] = {
        1, 3, 0, 12, 5
    };
    assert(makeProper(test7w1, test7w2, test7dig, 5) == 1); //checks to see if it removes pattern found multiple times

    char test8w1[][MAX_WORD_LENGTH+1] = {"mad", "deranged", "NEFARIOUS", "half-witted", "robot", "plot", "have", "NeFaRiOuS"};
    char test8w2[][MAX_WORD_LENGTH+1] = {"scientist", "robot", "PLOT", "assistant", "deranged", "Nefarious", "mad", "pLoT"};
    int test8dig[] = {-1,3,0,2,1,0,12,0};

    assert(makeProper(test8w1, test8w2, test8dig, 8) == 3);

    char test9w1[][MAX_WORD_LENGTH+1] = {
        "scientist","", "m3d", "mad", "world"
    };
    char test9w2[][MAX_WORD_LENGTH+1] = {
        "mad", "mad",    "",      "professor", "scientist"
    };
    int test9dig[] = {
        1, 3, 0, -12, 5
    };
    assert(makeProper(test9w1, test9w2, test9dig, 5) == 2); //checks to see if it removes empty string properly (in both w1 and w2)
    assert(makeProper(test9w1, test9w2, test9dig, -4) == 0);// checks for negative nPatterns passed in


    const int RATE1_NRULES = 5;
    char rate1w1[RATE1_NRULES][MAX_WORD_LENGTH+1] = {
        "mad",       "deranged", "nefarious", "life" , "life"
    };
    char rate1w2[RATE1_NRULES][MAX_WORD_LENGTH+1] = {
        "scientist", "robot",    "plot",      "good" ,  "life"
    };
    int rate1dist[RATE1_NRULES] = {
        1,           3,          0,           0     , 4
    };
    assert(rate("The mad UCLA scientist unleashed a deranged evil giant robot.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 2); //checks to see if it can calculate the pattern correctly
    assert(rate("The mad UCLA scientist unleashed    a deranged robot.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 2); //checks to see if it removes extra spaces properly
    assert(rate("** 2018 **",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 0);//checks to see if it properly removes incorrect characters
    assert(rate("  That plot: NEFARIOUS!",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 1); //checks to see if it works checking from behind
    assert(rate("deranged deranged robot deranged robot robot",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 1);//checks to make sure it only find a pattern once
    assert(rate("That scientist said two mad scientists suffer from deranged-robot fever.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 0);//checks to make sure there's no false positive
    assert(rate("life is life.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 1);//checks to make sure it doesn't check for the same pattern again, even if in different row
    assert(rate("this life is the good life.",
                rate1w1, rate1w2, rate1dist, RATE1_NRULES) == 2);//checks to see if it can move past old patterns while having the same word in word1
    assert(rate("this life is the good life.",
           rate1w1, rate1w2, rate1dist, -4) == 0);//checks to see if it works for negative nPattern values
    assert(rate("this life is the good life.",
                rate1w1, rate1w2, rate1dist, 0) == 0);//checks to see if it works for an nPattern value of 0
    
    

    cerr << "ALL TESTS PASSED";

}

