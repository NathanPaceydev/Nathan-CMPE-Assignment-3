/* Assignment 3 - The Jumble Puzzle
 *
 * Header file: jumble.h
 * Student: Nathan Pacey	netid:18njp		Student Number:20153310		Class: CMPE320
 *
 */


#pragma once // only include header once *
#include <vector>
#include <string>
#include <exception>
using namespace std;


typedef char* charArrayPtr; // variable pointing to the char array for heap

// if the user does not enter the defined strings for each question throw exception
class BadJumbleException {
public:
    BadJumbleException(const string &message);
    string &what();

private:
    string message; // error message
};


class JumblePuzzle {

public:
    // jumble puzzle class, initializes attributes and throws exception for bad input
    JumblePuzzle(const string &givenString, const string &difficultyString); 

    // sets size attribute using the size of the given word return the size of the puzzle
    const int &setPuzzleSize();

    // basic getters to return attributes
    int getSize() const;
    char getDirection() const;
    int getRowPos() const;
    int getColPos() const;

    // Getter Method to create a copy of the jumble puzzle heap and return the copy
    charArrayPtr* getJumble() const;

    // Copy constructor
    JumblePuzzle(const JumblePuzzle &newPuzzle);

    // Destructor (deleting constructor)
    ~JumblePuzzle();

    // Overloading the Assignment Operator '=' for JubblePuzzle Object
    JumblePuzzle& operator=(const JumblePuzzle&);

private:

    // initalize the attribute variables
    string givenString;
    string difficultyString;
    int sizeInt;
    char directionChar;

    // initalize puzzle char heap
    charArrayPtr* jumblePuzzle;

    // directions options
    char directionsCharArray[4] = {'n','e','s','w'}; //populate it with given dirs

    // Method to create a puzzle without the given word
    charArrayPtr *generateRandomPuzzle(const int &sizeInt);

    // Method to create the puzzle including the hidden word
    charArrayPtr *createPuzzle();

    // randomly generated indecies for the hidden word
    int rowIndexInt;
    int colIndexInt;

};




