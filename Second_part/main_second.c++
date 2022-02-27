#include <iostream>
#include <string>
#include <time.h>

const int rowsNumber = 8;
const int columnsNumber = 8;
const int coordinatesNumber = 2;

struct Сoordinates {
	int x, y;
};

Сoordinates coord;

using namespace std;

void menuOutput();
bool isLetter(char coord);
bool isDigit(char coord);
int getCoordinates();
void detectPath(int** array);
void outputFrame();
void outputArray(int** array);

void menuOutput() {
	cout << "Practical task num.2 IKBO-03-21 Nasevich V.V.\n"
		"Variant num.19.\n\nMenu:\n"
		"1)Enter '1' to enter queen coordinates.\n"
		"2)Enter '2' to output the current chessboard.\n"
		"\nEnter '0' to exit the programm.\n";
}

bool isLetter(char coord) {
	return (int('a') <= int(coord) && int(coord) <= int('h')) ? true : false;
}

bool isDigit(char coord) {
	return (int('1') <= int(coord) && int(coord) <= int('9')) ? true : false;
}

int getCoordinates() {
	string coordinate;
	cin >> coordinate;
	if (coordinate.length() == coordinatesNumber) {
		if (isLetter(coordinate[0]) && isDigit(coordinate[1])) {
			coord.x = abs(rowsNumber - 1 - int(coordinate[1]) + int('1'));
			coord.y = int(coordinate[0]) - int('a');
			return 1;
		}
		else if (isLetter(coordinate[1]) && isDigit(coordinate[0])) {
			coord.x = abs(rowsNumber - 1 - int(coordinate[0]) + int('1'));
			coord.y = int(coordinate[1]) - int('a');
			return 1;
		}
		else {
			return 0;
		}
	}
	else {
		return 0;
	}
}

void detectPath(int** array) {
	for (int row = 0; row < rowsNumber; row++) {
		for (int column = 0; column < columnsNumber; column++) {
			if ((row - column == coord.x - coord.y) || (row + column == coord.x + coord.y)) {
				array[row][column] = 1;
			}
			else if (row == coord.x || column == coord.y) {
				array[row][column] = 1;
			}
			else {
				array[row][column] = 0;
			}
		}
	}
}

void outputFrame() {
	cout << "  ";
	for (size_t i = int('a'); i <= int('h'); i++) {
		cout << char(i) << " ";
	}
	cout << endl;
}

void outputArray(int** array) {
	int counter = rowsNumber;
	cout << endl;
	for (size_t i = 0; i < rowsNumber; i++) {
		if (i == 0) {
			outputFrame();
		}
		for (size_t j = 0; j < columnsNumber; j++) {
			if (j == 0) {
				cout << counter << " " << array[i][j] << " ";
			}
			else if (j == columnsNumber - 1) {
				cout << array[i][j] << " " << counter << endl;
				counter--;
			}
			else {
				cout << array[i][j] << " ";
			}
		}
		if (i == rowsNumber - 1) {
			outputFrame();
		}
	}
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	int** chessBoard = new int* [rowsNumber];
	for (int i = 0; i < rowsNumber; i++)
		chessBoard[i] = new int[columnsNumber];
	int chooseTask = 0;
	menuOutput();
	cout << "\nYour choice is:\n";
	cin >> chooseTask;
	while (chooseTask != 0) {
		switch (chooseTask) {
		case 1: {
			cout << "\nEnter the queen coordinats:\n";
			if (!getCoordinates()) {
				cout << "\nCoordinates were entered incorrectly. Try again.\n";
				cin.clear();
				cin.ignore(numeric_limits<streamsize>::max(), '\n');
				break;
			}
			break;
		}
		case 2: {
			detectPath(chessBoard);
			chessBoard[coord.x][coord.y] = 8;
			outputArray(chessBoard);
			break;
		}
		default:
			cout << "\nIncorrect number. Try again.\n";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			break;
		}
		cout << endl;
		system("pause");
		system("cls");
		menuOutput();
		cout << "\nYour next choice is:\n";
		cin >> chooseTask;
	}
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	return 0;
}