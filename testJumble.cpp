/* Assignment 3 - The Jumble Puzzle
 *
 * Testing file: testJumble.cpp
 * Student: Nathan Pacey	netid:18njp		Student Number:20153310		Class: CMPE320
 *
 */


/*
 * A testing class for your JumblePuzzle class and its exception. A few unit
 * tests are provided but you will need to add a few more.
 * The code also contains a simple function that allows you to play the game, and
 * another function that you can use to display the puzzle.  You should not need to
 * alter either of these supplied functions unless you wish to enhance them without
 * changing the way JumblePuzzle operates.
 *
 * If you wish to build a GUI interface for the puzzle, you may certainly do so, as
 * long as the unit tests are still carried out. *
 */

#include <string>
#include <iostream>
#include <ctime>
#include "jumble.h" //include the header file
using namespace std;

// Displays the puzzle to the screen.
// Row and column numbers are added to the display.
void showJumble(const charArrayPtr* jumble, const int size) {
	int i, j;
	cout << "\n  ";
	for (i = 0; i < size; i++)
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
	cout << endl;
	for (i = 0; i < size; i++) {
		if (i < 10)
			cout << " " << i << " ";
		else
			cout << i << " ";
		for (j = 0; j < size; j++)
			cout << jumble[i][j] << "  ";
		cout << endl;
	}
	cout << endl;
} // end showJumble

// How quickly can you find the hidden string?
void playGame() {
	string toHide;
	string difficultyString;
	int guessRow, guessCol;
	int start, finish;
	char guessDirection;

	cout << "Provide a string to hide in the puzzle, all lower case: ";
	cin >> toHide;
	cout << "\nChoose your difficultyString level: \"easy\", \"medium\" or \"hard\": ";
	cin >> difficultyString;

	JumblePuzzle* jp;
	try {
		jp = new JumblePuzzle(toHide, difficultyString);
	}
	catch (BadJumbleException& e) {
		cerr << e.what();
		return;
	}
	showJumble(jp->getJumble(), jp->getSize());
	start = static_cast<int>(time(nullptr));
	cout << "Enter row location: ";
	cin >> guessRow;
	cout << "Enter column location: ";
	cin >> guessCol;
	cout << "Enter directionChar (\"n\", \"e\", \"s\" or \"w\"): ";
	cin >> guessDirection;
	finish = static_cast<int>(time(nullptr));
	if (guessRow == jp->getRowPos() && guessCol == jp->getColPos() &&
		guessDirection == jp->getDirection())
		cout << "You found it!" << endl;
	else {
		cout << "Wrong location..." << endl;
		cout << "The location is row: " << jp->getRowPos() << " col: " << jp->getColPos()
			<< ", directionChar: " << jp->getDirection() << endl;
	}
	cout << "You took " << (finish - start) << " seconds." << endl;
	delete jp;
	jp = nullptr;
} // end playGame


// Add unit tests to this function.  A few unit tests are provided to test your copy constructor,
// your assignment overloading and aliasing.  You need to write some more tests before these ones.
// Test the public members only ("Black Box Testing").  Test to make sure that exceptions are
// thrown when they should be, that the puzzle is the correct size and is formed properly, and
// that the accessors return what they should.  You can add these unit tests as you develop your
// code ("TDD") and comment out the supplied tests until you are ready for them.
void testJumble() {

	// Test copy constructor for proper operation
	cout << "Testing copy constructor:" << endl;
	// While debugging, you can use capital letters to make the hidden string easier to locate
	JumblePuzzle jp1("HELLO", "easy");
	showJumble(jp1.getJumble(), jp1.getSize());
	JumblePuzzle jp2(jp1);
	cout << "Should look the same:" << endl;
	showJumble(jp2.getJumble(), jp2.getSize());

	// Test aliasing from copy constructor
	charArrayPtr* puzzle = jp2.getJumble();
	int sz = jp2.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '.';
	cout << "Dotted diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 1:" << endl;
	showJumble(jp1.getJumble(), sz);
	cout << "Should be same as original 2:" << endl;
	showJumble(jp2.getJumble(), sz);

	// Test assignment operator for proper operation
	cout << "Testing assignment operator:" << endl;
	JumblePuzzle jp3("BYE", "easy");
	showJumble(jp3.getJumble(), jp3.getSize());
	JumblePuzzle jp4 = jp3;
	cout << "Should look the same:" << endl;
	showJumble(jp4.getJumble(), jp4.getSize());

	// Test aliasing from assignment operator
	puzzle = jp4.getJumble();
	sz = jp4.getSize();
	for (int i = 0; i < sz; i++)
		puzzle[i][i] = '*';
	cout << "Star diagonal:" << endl;
	showJumble(puzzle, sz);
	cout << "Should be same as original 3:" << endl;
	showJumble(jp3.getJumble(), sz);
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);

	// Test self-assignment
	// This shows as a "bug", which it should do.  However, you should still
	// be able to build and run your program.
	jp4 = jp4;
	cout << "Should be same as original 4:" << endl;
	showJumble(jp4.getJumble(), sz);

	// Test for a memory leak.
	// This is a pretty slow test and it may be that the limit of the loop
	// will not be large enough to show a memory leak, especially if you have
	// quite a bit of RAM.  In my tests I found that with about 4.0 GB free this
	// test would cause a memory leak failure when loop Limit was 1,000,000.
	// Start with a loop limit of 100 or 1000 and increase it by a factor of 10.
	// The other way to see a memory leak failure is to have task manager show your
	// memory consumption as the program runs.  If it keeps climbing - you have a problem,
	// even if you don't run out of memory.
	// Of course you won't get a memory leak error if you are using the heap properly,
	// and the program will terminate normally!
	int loopLimit = 1000;
	for (int i = 0; i < loopLimit; i++)
		JumblePuzzle jp("HIDDENWORD", "hard");
	cout << "\nPassed memory leak test!" << endl;

    // ************************ New added Unit Tests Below *******************************************
	cout << "\n **** Start of Custom Test Cases ****" << endl;

	/* Testing Assignment Operator
	* by calling an instance of jp5 and setting it equal to the predefined jpl1
	*/
    JumblePuzzle jp5 = jp1; // assignment jp5 -> jp1
	cout << "\n\nTesting the assignment operator by comparing attributes of jp5 to jp1 after setting jp5 = jp1" << endl;

	// Testing Size attribute
    if (jp1.getSize() == jp5.getSize()) {
		cout << "\nPassed getSize() test!" << endl;
	} else {
		cout << "\nFailed getSize() test!" << endl;
	}

	// Testing the Direction attribute
	if (jp1.getDirection() == jp5.getDirection()) {
		cout << "\nPassed getDirection() test!" << endl;
	} else {
		cout << "\nFailed getDirection() test!" << endl;
	}

	// Testing the Row Value attribute
	if (jp1.getRowPos() == jp5.getRowPos()) {
		cout << "\nPassed getRowPos() test!" << endl;
	} else {
		cout << "\nFailed getRowPos() test!" << endl;
	}

	// Testing the Col Value attribute
	if (jp1.getColPos() == jp5.getColPos()) {
		cout << "\nPassed getColPos() test!" << endl;
	} else {
		cout << "\nFailed getColPos() test!" << endl;
	}

	/* Testing the Copy Constructor Attributes 
	* by calling an instance of jp6 and passing it jp1, then comparing the attributes 
	*/ 
	JumblePuzzle jp6(jp2); // initalizing object
	cout << "\n\nTesting the copy constructor by comparing attributes after instantiating jp6(jp2)" << endl;

	// Testing Size attribute
	if (jp2.getSize() == jp6.getSize()) {
		cout << "\nPassed getSize() test!" << endl;
	} else {
		cout << "\nFailed getSize() test!" << endl;
	}

	// Testing the Direction attribute
	if (jp2.getDirection() == jp6.getDirection()) {
		cout << "\nPassed getDirection() test!" << endl;
	} else {
		cout << "\nFailed getDirection() test!" << endl;
	}

	// Testing the Row Value attribute
	if (jp2.getRowPos() == jp6.getRowPos()) {
		cout << "\nPassed getRowPos() test!" << endl;
	} else {
		cout << "\nFailed getRowPos() test!" << endl;
	}

	// Testing the Col Value attribute
	if (jp2.getColPos() == jp6.getColPos()) {
		cout << "\nPassed getColPos() test!" << endl;
	} else {
		cout << "\nFailed getColPos() test!" << endl;
	}

    // ************* End of Added Test Cases *************************************

} // end testJumble 


int main() {
	// Note if you just want top see test cases or play the game comment out the calls
	testJumble();

	// Make sure your class works before you play the game!
	cout << "\n\n\t\t\t\tPlay the Game Now!\n" << endl;
	playGame();

	return 0;
} // end main

