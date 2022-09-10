// flash.cpp : Flashcard Application for GCU Programming Class.
// By: Bryan Ensign

#include  // random_shuffle
#include   // iterator
#include  // cout, cin, endl

#include "Flashcards.h"
#include "Word.h"
#include "flashcards.txt"

using namespace std;

int main( /* int argc, char* argv[] */) {

	char choice; // Choice of what character inputted
	string filename;
	bool quit = false; // If the file does not boot then application stops

	Flashcards cards; // This will call the flash card

	do {
		cout << "Main Menu:" << endl; // This will ask for the main menu
		cout << "**********" << endl;
		cout << "  1) Import flashcards" << endl;  // This will import the list of flashcards
		cout << "  2) Export flashcards" << endl; // This will export the list of flashcards 
		cout << "  3) Clear" << endl; // This will display clear the line
		cout << "  4) Study" << endl; // This will display the study prompt
		cout << "Please enter your selection ('q' to quit): "; // This will allow the user to select the flashcards or quit the program
		cin >> choice; // This poses the user with a choice

		switch (choice) { // This will switch to the next card
		case 'q': // Pressing q provides this result
			quit = true; // Quits on switch
			break;

		case '1':
			cout << "Enter a filename: "; // This will ask for a file name to select the data
			cin >> filename;
			cout << "Loading " << filename << "... "; // This will load the data and show the output
			try {
				cards.import(flashcards.txt); // This will import the flashcard via file name request
			}
			catch (char* errmsg) {
				cout << "FAILED - " << errmsg << endl << endl; // If there are errors this will display
				continue;
			}
			cout << "SUCCESS" << endl; // If the cards are access correctly this will be displayed
			break;

		case '2':
			cout << "Enter a filename: "; // This will access the card display
			cin >> filename;
			cout << "Export to " << filename << "..."; // This should allow you to save the vile with a name you choose
			if (!cards.empty()) {
				try {
					cards.export(flashcards.txt); // This will continue to display new cards 
				} 
				catch (char* errmsg) {
					cout << "FAILED - " << errmsg << endl; // If there are errors this will display
					continue;
				}
				cout << "SUCCESS" << endl; // If the cards are access correctly this will be displayed
			}
			else {
				cout << "FAILED - "; // This will report erros 
				cout << "No flashcards have been loaded yet." << endl; // Error message if the cards do not load correctly
			}

			break;

		case '3':
			cout << "Clear flashcards...SUCCESS" << endl; // This will start over a new process and allow a new beginning
			cards.clear(); // This will clear the card selection
			break;

		case '4':
			if (!cards.empty()) {
				cout << "study mode" << endl; // This will allow the user to cycle through and learn the data by repeating
				random_shuffle(cards.begin(), cards.end()); // This will shuffle the cards and cycle through them randomly for studying
				Flashcards::iterator itr = cards.begin();
				while (itr != cards.end()) { 
					cout << endl;
					cout << (**itr).getName() << endl;
					cout << "'n' for next & 'd' for definition: "; // This will move to the next card and define the card section
					cin >> choice;
					switch (choice) {
					case 'n':
						//This might drop to the next one
						break;

					case 'd':
					{
						cout << (**itr).getPartOfSpeech() << ". " // This may call letters or allow verbal from windows
							<< (**itr).getDefinition() << endl;
						vector examples = (**itr).getExamples(); // This is the location of examples on the page
						vector::iterator examples_itr = examples.begin();
						while (examples_itr != examples.end()) { // This is whare examples variable
							cout << " - " << (*examples_itr) << endl; // This will count the examples
							examples_itr++;
						}
						break;
					}
					itr++;
				}
			}
			else {
				cout << "No flashcards have been loaded yet." << endl; // Error reporting no flashcards line
			}
			break;

		default:
			cout << "Invalid command. Retry again." << endl; // Error reporting and gives the user the ability to start over again
			break;
		}
		cout << endl;
	} while (!quit); // This will exit
	return 0; // This will stop
}