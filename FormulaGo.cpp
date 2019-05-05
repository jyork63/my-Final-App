#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

void mainMenu(); //main menu function
void searchFormulas(); //search function
void formulas(); //list function
void aboutFormulaGo(); //description of formulaGo
void contactUs(); //contact info
void displayFormulaInfo(int, bool); //function to display the corresdponding formula and variable meaning to the formula name chosen
void newScreen(); //prints 50 blank lines to look like a new screen
void goBack(); //returns to the main menu

fstream formulaNamefile; //file containing names of formulas
fstream formulafile; //file containing the formulas
fstream variableMeaningfile; //file containing the meaning for the variables in the formulas

int main()
{
	mainMenu();
	return 0;
}

void mainMenu() //main menu function
{
	int choice1 = 0; //main menu input variable

	cout << setw(24) << "FormulaGo" << endl << endl
			 << endl << endl;

	cout << setw(30) << "1.) Search Formulas" << endl << endl
			 << setw(26) << "2.) Formulas" << endl << endl
			 << setw(30) << "3.) About FormulaGo" << endl << endl
			 << setw(27) << "4.) Contact Us" << endl;

	while (choice1 < 5)
	{
		cin >> choice1; //Use 1 for Search Formulas, 2 for Formulas, 3 for About Formulas, and 4 for Contact Us
		switch (choice1)
		{
			case 1: searchFormulas();
					 		break;

			case 2: formulas();
					 		break;

			case 3: aboutFormulaGo();
					 		break;

			case 4: contactUs();
						  break;

			default: exit(0); //closing the app
		}
	}
}

void searchFormulas() //To search for the formula you want
{
	int i;
	bool search = true;
	string formulaSearch; //input for search prompt
	string tempFormulaName; //temp holding spot for formula names coming from the file
	string formulaNameArray[31]; //array to contain the formula names

	formulaNamefile.open("FormulaName.txt");

	newScreen();

	for(i = 0; i < 31; i++) //Putting the file into an array
	{
		getline(formulaNamefile, tempFormulaName);
		formulaNameArray[i] = tempFormulaName + "\n";
	}

	cout << "(enter back to return to main menu) search: ";
	while(formulaSearch == "")
  {
		getline (cin,formulaSearch); //search input
  }
  formulaSearch += "\n";

	for (i = 0; i < 31; i++)
	{
		if (formulaSearch == formulaNameArray[i]) //searching
		{
			formulaNamefile.close();
  		displayFormulaInfo(i, search);
  		break;
		}
		else if (formulaSearch != formulaNameArray[i] && i == 30) //validation
		{
			cout << "Invalid formula, please try again. Make sure spelling is correct! enter 'back' to return to main menu.";
			
			formulaNamefile.close();
			searchFormulas();
		}
		else if (formulaSearch == "back\n") //return to main menu
		{
			formulaNamefile.close();
			newScreen();
			mainMenu();
		}
	}
	formulaNamefile.close();
}

void formulas() //Lists formulas and you choose one
{
	int formulaNum = 0; //input for the desired formula
	bool formula = false;
	string tempFormulaName2; //temp holding spot for formula names
	string formulaNameArray2[31]; //array to contain the formula names

	formulaNamefile.open("FormulaName.txt");

	newScreen();

	for(int a = 0; a < 31; a++) //Putting the file into an array
	{
		getline(formulaNamefile, tempFormulaName2);
		formulaNameArray2[a] = tempFormulaName2 + "\n";
	}

	for(int a = 0; a < 31; a++) //displaying the formula names
	{
		cout << a + 1 << ".) " << formulaNameArray2[a];
	}

  formulaNamefile.close();

	cin >> formulaNum;
	displayFormulaInfo(formulaNum, formula);
}

void displayFormulaInfo(int num1, bool searchOrFormula) //function to display selected formula info
{
	char pickAnother; //variable to pick another formula

	string tempFormula; //temp holding spot for the formulas
	string tempVariableMeaning; //temp holding spot for the variable meanings
	string tempFormulaName3; //temp holding spot for the formula name

	string formulaArray[31]; //array to contain the formulas
	string variableMeaningArray[31]; //array to contain the variable meanings
	string formulaNameArray3[31]; //array to contain the formula names

	formulafile.open("Formulas.txt");
	variableMeaningfile.open("VariableMeaning.txt");
	formulaNamefile.open("FormulaName.txt");
	
	for(int a = 0; a < 31; a++) //Putting the files into arrays
	{
		getline(formulafile, tempFormula);
		formulaArray[a] = tempFormula + "\n";

		getline(variableMeaningfile, tempVariableMeaning);
		variableMeaningArray[a] = tempVariableMeaning + "\n";

		getline(formulaNamefile, tempFormulaName3);
		formulaNameArray3[a] = tempFormulaName3 + "\n";
	}
	
	while (num1 >= 0 && num1 < 999)
	{
		if (num1 >= 0 && num1 <= 31)
		{
			if (searchOrFormula == false) //displays correct info for formulas choice
			{
				newScreen();
				cout << formulaNameArray3[num1 - 1] << endl; //display selected formula name
				cout << formulaArray[num1 - 1] << endl; //display selected formula
				cout << variableMeaningArray[num1 - 1]; //display variable meanings
				break;
			}
			else if (searchOrFormula == true) //displays correct info for search choice
			{
				newScreen();
				cout << formulaNameArray3[num1] << endl; //display selected formula name
				cout << formulaArray[num1] << endl; //display selected formula
				cout << variableMeaningArray[num1]; //display variable meanings
				break;
			}
		}
		else if (num1 < 1 || num1 > 31)
		{
			cout << "Error: Try again." << endl;
			break;
		}
	}

	cout << endl << "Do you want to find another formula? (Y or N)" << endl;
	cin >> pickAnother; //y for yes, n for no, p to exit app

	switch (pickAnother)
	{
		case 'Y':
		case 'y':	formulafile.close();
							variableMeaningfile.close();
							formulaNamefile.close();
							if (searchOrFormula == false) //to return to formula function
							{
								formulas();
							}
							else //to return to search function
							{
								searchFormulas();
							}
							break;
	
		case 'N':
		case 'n':	formulafile.close();
							variableMeaningfile.close();
							formulaNamefile.close();
							newScreen();
							mainMenu();
							break;
		case 'p':
		case 'P':	exit(0);
							break;
	}

	formulafile.close();
	variableMeaningfile.close();
	formulaNamefile.close();
}

void aboutFormulaGo() //function for description of FormulaGo
{
	newScreen();

	cout << "FormulaGo is an app designed to help students so "
			 << "that they can have a multitude of formulas ready "
			 <<	"for them at their fingertips. Formulas "
			 <<	"will range from basic mathatical formulas to "
			 << "complex Calculus ones! With FormulaGo you can "
			 << "search for a formula and it will display the "
			 << "formula you want along with what each variable "
			 << "is for. Or you can have a list of all the "
			 << "formulas be shown and then select the desired "
			 << "formula from there." << endl << endl;
	cout << setw(30) << "Return to main menu (Y or N)" << endl;

	goBack();
}

void contactUs() //function for contact info
{
	newScreen();

	cout << setw(26) << "Contact Info"
			 << endl << endl;
	cout << "Email: s0483030@student.rockvalleycollege.edu"
			 << endl << endl
			 << "Phone: (815)555-5555"
			 << endl;
	cout << setw(30) << "Return to main menu (Y or N)" << endl;

	goBack();
}

void newScreen() //function to "make a new screen"
{
	for (int i = 0; i < 50; i++) //Like its a new screen
	{
		cout << endl;
	}
}

void goBack()
{
	char goBack = 'q';

	while (goBack != 'y' || goBack != 'Y')
	{
		cin >> goBack; //enter Y or y to go back to the main menu

		switch (goBack)
		{
			case 'Y':
			case 'y': newScreen();
								mainMenu();
								break;
	
			case 'N': 
			case 'n': exit(0);
								break;
		}
	}
}
