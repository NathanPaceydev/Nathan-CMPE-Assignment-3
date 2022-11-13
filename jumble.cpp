/* Assignment 3 - The Jumble Puzzle
 *
 * Implementation file: jumble.cpp
 * Student: Nathan Pacey	netid:18njp		Student Number:20153310		Class: CMPE320
 * 
 */


// include standard libs *
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "jumble.h"

// ################ EXCEPTION CLASS ##################################
// Exception class for any incorrect inputs
BadJumbleException::BadJumbleException(const string &message) : message(message) {}
string& BadJumbleException::what(){ 
    return message; 
}


// ################ JUMBLEPUZZLE CLASS ################################
// given a string (hidden word) and a difficulty string check set the attributes of the puzzle. Throw exception for bad input
JumblePuzzle::JumblePuzzle(const string &givenString, const string &difficultyString) {
    // throw exception if the user did not input a word between 3 and 10 characters
    if (givenString.length() < 3 || givenString.length() > 10) {
        throw BadJumbleException("\nNot a valid Word Inputted: \nEnter a word with between 3 and 10 lowercase characters\n");
    }

    // make sure the word does not contain numbers or capitals
    // ****** NOTE that I DID NOT checked for capital letters and number inputs since the intructions DID NOT SPECIFY IF THE PROGRAM SHOULD THROW AN EXCEPTION FOR CAPS **************
    for (int i = 0; i < givenString.length(); i++) { 
        if (isdigit(givenString[i])) { //throw exception if a number
            throw BadJumbleException("\nNot a valid Word Inputted: \nEnter a word with between 3 and 10 lowercase characters\n");
        }
    }

    std::vector<std::string> difficulties{ "easy", "medium", "hard"}; //str vector for the difficultyString options

    // check if the input is one of the difficultyString options
    bool isValidDifficulty = (std::find(std::begin(difficulties), std::end(difficulties), difficultyString) != std::end(difficulties));

    // throw exception if the difficulties is not in the allowable options
    if (!isValidDifficulty) {
        throw BadJumbleException("\nError Difficulty level must be: \"easy\", \"medium\" or \"hard\" in lowercase only");
    }

    // if the user inputted correct values set the object attributes
    this->difficultyString = difficultyString;
    this->givenString = givenString;
    this->sizeInt = setPuzzleSize(); // set the size of the outputted puzzle calling the setPuzzleSize() method
    this->jumblePuzzle = createPuzzle();  // Set the puzzle to output to the createPuzzle() method

} //end JumblePuzzle::JumblePuzzle


// ############################## SETTERS ########################################
// using the size of the given word return the size of the puzzle
const int &JumblePuzzle::setPuzzleSize() {
    // if the user selects easy multiply the given word by 2
    if (difficultyString == "easy") { 
        return 2 * givenString.length();
    } 
    // if the user selects medium multiply the given word by 2
    if (difficultyString == "medium") { 
        return 3 * givenString.length(); 
    }
    // if the user selects hard multiply the given word by 2
    if (difficultyString == "hard") {
        return 4 * givenString.length();
    }

    return 0;
}


// ################################ GETTERS #####################################
int JumblePuzzle::getSize() const {
    return this->sizeInt;
}

char JumblePuzzle::getDirection() const {
    return this->directionChar;
}

int JumblePuzzle::getRowPos() const {
    return this->rowIndexInt;
}

int JumblePuzzle::getColPos() const {
    return this->colIndexInt;
}


// Getter Method to create a copy of the jumble puzzle heap and return the copy
charArrayPtr *JumblePuzzle::getJumble() const{
    charArrayPtr *newJumblePuzzle = new char*[sizeInt]; //create a new puzzle

    // populate the new puzzle
    for (int i = 0; i < sizeInt; i++) {
        newJumblePuzzle[i] = new char[sizeInt]; //populate the heap

        for (int j = 0; j < sizeInt; j++) {
            newJumblePuzzle[i][j] = jumblePuzzle[i][j];
        }
    }
    return newJumblePuzzle;
}


// #################### Methods to Create the puzzle ######################################
// Method to create a puzzle without the given word
charArrayPtr *JumblePuzzle::generateRandomPuzzle(const int &sizeInt) {
    srand(time(NULL)); // set random seed to generate random numbers

    charArrayPtr* randomPuzzle = new charArrayPtr[sizeInt];

    for (int i = 0; i < sizeInt; ++i) { //iterate through rows
        randomPuzzle[i] = new char[sizeInt]; // set heap

        for (int j = 0; j < sizeInt; j++) { // iterate through cols
            randomPuzzle[i][j] = 'a' + rand() % 26; // set random lowercase char a->z
        }
    }
    return randomPuzzle;
}


// Method to create the puzzle including the hidden word
charArrayPtr* JumblePuzzle::createPuzzle() {
    charArrayPtr* completePuzzle = generateRandomPuzzle(sizeInt); // call the functio to generate a puzzle with no word

    // initalize vars
    bool puzzleCompleteFlag = false;
    int row;
    int col;

    srand(time(NULL)); // set random seed to generate random numbers


    // place the hidden word using random directions and indexes
    while (!puzzleCompleteFlag) {
        // get random dir, row and col
        directionChar = directionsCharArray[rand() % 4];
        rowIndexInt = rand() % (sizeInt);
        colIndexInt = rand() % (sizeInt);

        // set the puzzle row & col attributes based on the indexes
        row = this->rowIndexInt;
        col = this->colIndexInt;

        // if the random dir is up
        if ((directionChar == 'n')&&((int(row) - int(givenString.length()) + 1) > -1)) { //make sure that the indecies allow the word to be placed up
            // populate the puzzle until the whole word is placed
            for (int i = 0; i < givenString.length(); ++i) {
                if ((row - i) < 0) break;

                else if (i < (givenString.length() - 1)) {
                    completePuzzle[row - i][col] = givenString.at(i);
                }
                else {
                    completePuzzle[row - i][col] = givenString.at(i);
                    puzzleCompleteFlag = true;
                }
            }
        }

        // if the random dir is right
        else if ((directionChar == 'e')&&((int(col) + int(givenString.length())) < sizeInt - 1)) { //make sure that the indecies allow the word to be placed right
            // populate the puzzle until the whole word is placed
            for (int i = 0; i < givenString.length(); ++i) {
                if ((col + i) > sizeInt - 1) break;

                else if (i < (givenString.length() - 1)) {
                    completePuzzle[row][col + i] = givenString.at(i);
                    
                }
                else { 
                    completePuzzle[row][col + i] = givenString.at(i); 
                    puzzleCompleteFlag = true;
                }
            }
        }

        // if the random dir is down
        else if ((directionChar == 's') && (int(row) + int(givenString.length()) < sizeInt - 1)) { //make sure that the indecies allow the word to be placed down
            // populate the puzzle until the whole word is placed
            for (int i = 0; i < givenString.length(); ++i) {
                if ((row + i) > sizeInt - 1) break;

                else if (i < (givenString.length() - 1)) {
                    completePuzzle[row + i][col] = givenString.at(i);
                }
                else { 
                    completePuzzle[row + i][col] = givenString.at(i); 
                    puzzleCompleteFlag = true;
                }
            }
        }

        // if the random dir is left
        else if ((directionChar == 'w') && ((int(col) - int(givenString.length()) + 1) > -1)) { //make sure that the indecies allow the word to be placed left
            // populate the puzzle until the whole word is placed
            for (int i = 0; i < givenString.length(); ++i) {
                if ((col - i) < 0) break;

                else if (i < (givenString.length() - 1)) {
                    completePuzzle[row][col - i] = givenString.at(i);
                }
                else {
                    completePuzzle[row][col - i] = givenString.at(i);
                    puzzleCompleteFlag = true;
                }
            }
        }

    }//end while

    return completePuzzle;
}//end JumblePuzzle::createPuzzle()


//############## CONSTRUTOR & DESTRUCTOR ###############################
// Copy constructor
JumblePuzzle::JumblePuzzle(const JumblePuzzle &newPuzzle) {
    // call getters to set attributes
    sizeInt = newPuzzle.getSize();
    directionChar = newPuzzle.getDirection();
    rowIndexInt = newPuzzle.getRowPos();
    colIndexInt = newPuzzle.getColPos();

    // make new instance of jubble puzzle heap
    charArrayPtr* existingPuzzle = newPuzzle.getJumble();
    jumblePuzzle = new charArrayPtr[this->sizeInt];

    // populate the puzzle
    for (int i=0; i<sizeInt; ++i){
        jumblePuzzle[i] = new char[sizeInt]; //populate heaap

        for (int j=0; j<sizeInt; ++j){
            jumblePuzzle[i][j] = existingPuzzle[i][j]; //populate puzzle
        }
    }
}


// Destructor (deleting constructor)
JumblePuzzle::~JumblePuzzle() {
    // iterate through each element and free the memory (delete it)
    for (int i=0; i<this->sizeInt; ++i) {
        delete[] jumblePuzzle[i];
        jumblePuzzle[i] = nullptr;
    }
    // delete the whole object
    delete[] jumblePuzzle;
    jumblePuzzle = nullptr;
}


// ################ OPERATOR OVERLOADING ##########################
// Overloading the Assignment Operator '=' for JubblePuzzle Object
JumblePuzzle &JumblePuzzle::operator=(const JumblePuzzle &comparePuzzle) {
    if (this != &comparePuzzle) {     // if current puzzle object is not equal to passed in puzzle

        // declare / set attributes by calling getters
        sizeInt = comparePuzzle.getSize();
        directionChar = comparePuzzle.getDirection();
        rowIndexInt = comparePuzzle.getRowPos();
        colIndexInt = comparePuzzle.getColPos();
        
        // make new instance of jubble puzzle heap by calling getJumble()
        charArrayPtr *existingPuzzle = comparePuzzle.getJumble();
        jumblePuzzle = new charArrayPtr[sizeInt];

        // iterate through each element and free the memory (delete it)
        for (int a = 0; a < sizeInt; ++a) {
            delete[] jumblePuzzle[a];
        }
        delete[] jumblePuzzle; // delete the whole object

        // populate the puzzle
        for (int i=0; i<sizeInt; ++i){
            jumblePuzzle[i] = new char[sizeInt]; //populate heaap

            for (int j=0; j<sizeInt; ++j){
                jumblePuzzle[i][j] = existingPuzzle[i][j];  //populate puzzle
            }
        }
    }

    return *this;
}// end &JumblePuzzle::operator=()


