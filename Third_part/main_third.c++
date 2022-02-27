#include <iostream>
#include <string>
#include <vector>
#include <math.h>

using namespace std;

int matrixSize;
int powerOfTen = 3; // for base truncting
double epsilonLength;

struct Point {
	int X, Y;
};

struct Triangle {
	Point A, B, C;
	double base;
	string intersection = " ";
};

struct Parameters {
	double k1 = -1.0, k2 = -1.0, 
		b1 = -1.0, b2 = -1.0, xCrossPoint = -1.0, yCrossPoint = -1.0;
};

bool isEqualSideTriangle(Triangle& triangle);
bool isPresent(Triangle& currentTriangle, vector<Triangle>& trianglesArray);
void calculateParameters(Point p1, Point p2, Point p3, Point p4, Parameters parameter);
bool isIntersected(Point p1, Point p2, Point p3, Point p4);
int isIntersected(Triangle& currentTriangle, vector<Triangle>& trianglesArray);
void outputTriangle(Triangle triangle);

bool isEqualSideTriangle(Triangle& triangle) {

	int dX, dY;
	double lengthAB, lengthBC, lengthCA;
	
	// AB:
	dX = abs(triangle.A.X - triangle.B.X);
	dY = abs(triangle.A.Y - triangle.B.Y);
	lengthAB = sqrt(dX * dX + dY * dY);

	// BC:
	dX = abs(triangle.B.X - triangle.C.X);
	dY = abs(triangle.B.Y - triangle.C.Y);
	lengthBC = sqrt(dX * dX + dY * dY);

	// CA:
	dX = abs(triangle.C.X - triangle.A.X);
	dY = abs(triangle.C.Y - triangle.A.Y);
	lengthCA = sqrt(dX * dX + dY * dY);
	
	if (abs(lengthAB - lengthBC) < epsilonLength 
		&& abs(lengthBC - lengthCA) < epsilonLength
		&& lengthAB != 0) {

		// average length of base:
		triangle.base = round((lengthAB + lengthBC + lengthCA) / 3.0 * pow(10.0, powerOfTen)) / pow(10.0, powerOfTen);
		return true;
	}

	else {

		return false;
	}
}

bool isPresent(Triangle& currentTriangle, vector<Triangle>& trianglesArray) {
	if (trianglesArray.size() > 0) {

		for (auto& foundTriangle : trianglesArray) {

			if (currentTriangle.base == foundTriangle.base) {

				return true;
			}

			else if ((currentTriangle.A.X == foundTriangle.A.X) && (currentTriangle.A.Y == foundTriangle.A.Y) // point A comparison
				|| (currentTriangle.A.X == foundTriangle.B.X) && (currentTriangle.A.Y == foundTriangle.B.Y)
				|| (currentTriangle.A.X == foundTriangle.C.X) && (currentTriangle.A.Y == foundTriangle.C.Y)
				|| (currentTriangle.B.X == foundTriangle.A.X) && (currentTriangle.B.Y == foundTriangle.A.Y) // point B comparison
				|| (currentTriangle.B.X == foundTriangle.B.X) && (currentTriangle.B.Y == foundTriangle.B.Y)
				|| (currentTriangle.B.X == foundTriangle.C.X) && (currentTriangle.B.Y == foundTriangle.C.Y)
				|| (currentTriangle.C.X == foundTriangle.A.X) && (currentTriangle.C.Y == foundTriangle.A.Y) // point C comparison
				|| (currentTriangle.C.X == foundTriangle.B.X) && (currentTriangle.C.Y == foundTriangle.B.Y)
				|| (currentTriangle.C.X == foundTriangle.C.X) && (currentTriangle.C.Y == foundTriangle.C.Y)) {

				return true;
			}
		}

		return false;
	}
	else {

		return false;
	}
}

void calculateParameters(Point p1, Point p2, Point p3, Point p4, Parameters parameter) {

	// tangent calculation (according to definition):
	parameter.k1 = (p1.X - p2.X != 0) ? (p1.Y - p2.Y) / (p1.X - p2.X) : -1;
	parameter.k2 = (p3.X - p4.X != 0) ? (p3.Y - p4.Y) / (p3.X - p4.X) : -1;

	// parameter b calculation:
	parameter.b1 = p1.Y - parameter.k1 * p1.X;
	parameter.b2 = p3.Y - parameter.k2 * p3.X;

	// abscissa of the point of the lines intersection:
	parameter.xCrossPoint = 
		(parameter.k1 - parameter.k2 != 0) ? (parameter.b2 - parameter.b1) / (parameter.k1 - parameter.k2) : -1;
}

bool isIntersected(Point p1, Point p2, Point p3, Point p4) {

	if (p2.X < p1.X) {

		Point tmp = p1;
		p1 = p2;
		p2 = tmp;
	}

	if (p4.X < p3.X) {

		Point tmp = p3;
		p3 = p4;
		p4 = tmp;
	}

	// if there is a potential intersection interval:
	if (p2.X >= p3.X) {

		// if both segments are vertical and have equal X coord (special case):
		if (p1.X == p2.X && p3.X == p4.X && p1.X == p3.X) {

			// if both segments have common Y coordinate:
			if (!((max(p1.Y, p2.Y) < min(p3.Y, p4.Y))
				|| (min(p1.Y, p2.Y) > max(p3.Y, p4.Y)))) {
	
				return true;
			}

			else {

				return false;
			}
		}

		// if one segment is vertical (special case): 
		else if (p1.X == p2.X || p3.X == p4.X) {

			Parameters parameter;

			// if 1st segment is vertical
			if (p1.X == p2.X) {

				calculateParameters(p1, p2, p3, p4, parameter);
				parameter.xCrossPoint = p1.X;
				parameter.yCrossPoint = 
					parameter.k2 * parameter.xCrossPoint + parameter.b2;

				if (p3.X <= parameter.xCrossPoint && p4.X >= parameter.xCrossPoint
					&& min(p1.Y, p2.Y) <= parameter.yCrossPoint
					&& max(p1.Y, p2.Y) >= parameter.yCrossPoint) {

					return true;
				}

				else {

					return false;
				}
			}
			// if 2nd segment is vertical
			else if (p3.X == p4.X) {

				calculateParameters(p1, p2, p3, p4, parameter);
				parameter.xCrossPoint = p3.X;
				parameter.yCrossPoint = 
					parameter.k1 * parameter.xCrossPoint + parameter.b1;

				if (p1.X <= parameter.xCrossPoint && p2.X >= parameter.xCrossPoint
					&& min(p3.Y, p4.Y) <= parameter.yCrossPoint
					&& max(p3.Y, p4.Y) >= parameter.yCrossPoint) {

					return true;
				}

				else {

					return false;
				}
			}
		}

		// if both segments are non-vertical (general case):
		else {

			Parameters parameter;
			calculateParameters(p1, p2, p3, p4, parameter);

			// if xCrossPoint is included in the intersection of 
			// the projections of both segments on the x-axis:
			if (!(parameter.xCrossPoint < max(p1.X, p3.X)
				|| parameter.xCrossPoint > min(p2.X, p4.X))) {

				return true;
			}

			else {

				return false;
			}
		}
	}

	else {

		return false;
	}
}

int isIntersected(Triangle& currentTriangle, vector<Triangle>& trianglesArray) {

	for (auto& foundTriangle : trianglesArray) {

		// for AB:
		if (isIntersected(currentTriangle.A, currentTriangle.B, foundTriangle.A, foundTriangle.B)) {
			
			currentTriangle.intersection = "is intersected";
			return 1;
		}

		if (isIntersected(currentTriangle.A, currentTriangle.B, foundTriangle.B, foundTriangle.C)) {

			currentTriangle.intersection = "is intersected";
			return 1;
		}

		if (isIntersected(currentTriangle.A, currentTriangle.B, foundTriangle.C, foundTriangle.A)) {

			currentTriangle.intersection = "is intersected";
			return 1;
		}

		// for BC:
		if (isIntersected(currentTriangle.B, currentTriangle.C, foundTriangle.A, foundTriangle.B)) {
			
			currentTriangle.intersection = "is intersected";
			return 1;
		}

		if (isIntersected(currentTriangle.B, currentTriangle.C, foundTriangle.B, foundTriangle.C)) {

			currentTriangle.intersection = "is intersected";
			return 1;
		}

		if (isIntersected(currentTriangle.B, currentTriangle.C, foundTriangle.C, foundTriangle.A)) {

			currentTriangle.intersection = "is intersected";
			return 1;
		}

		// for CA:
		if (isIntersected(currentTriangle.C, currentTriangle.A, foundTriangle.A, foundTriangle.B)) {
			
			currentTriangle.intersection = "is intersected";
			return 1;
		}

		if (isIntersected(currentTriangle.C, currentTriangle.A, foundTriangle.B, foundTriangle.C)) {

			currentTriangle.intersection = "is intersected";
			return 1;
		}

		if (isIntersected(currentTriangle.C, currentTriangle.A, foundTriangle.C, foundTriangle.A)) {

			currentTriangle.intersection = "is intersected";
			return 1;
		}
	}

	// if there is no intersection:
	currentTriangle.intersection = "is not intersected";
	return 0;
}

void outputTriangle(Triangle triangle) {
	cout << "\nTriangle with base " << triangle.base 
		<< " and coordinates (" << triangle.A.X << ", " 
		<< triangle.A.Y << ") (" << triangle.B.X << ", " 
		<< triangle.B.Y << ") (" << triangle.C.X << ", " 
		<< triangle.C.Y << ") " << triangle.intersection << ".";
}

int main() {

	setlocale(LC_ALL, "Russian");
	vector<Point> dotsArray;
	vector<Triangle> trianglesArray;

	cout << "Enter the size of a square matrix ('0' to end the programm):\n";
	cin >> matrixSize;
	cout << "\nEnter base length comprarison accuracy('0.2' is recommended) or '0' to end the programm:\n";
	cin >> epsilonLength;
	cout << endl;

	while (matrixSize > 0 && epsilonLength > 0) {

		int counter = 0;
		for (size_t x = 1; x <= matrixSize; x++) {

			for (size_t y = 1; y <= matrixSize; y++) {

				dotsArray.resize(dotsArray.size() + 1);
				dotsArray[counter].X = x;
				dotsArray[counter].Y = y;
				counter++;
			}
		}

		trianglesArray.clear();

		for (size_t i = 0; i < dotsArray.size(); i++) {

			for (size_t j = i; j < dotsArray.size(); j++) {

				for (size_t k = j; k < dotsArray.size(); k++) {

					Triangle triangle;
					triangle.A = dotsArray[i];
					triangle.B = dotsArray[j];
					triangle.C = dotsArray[k];

					if (!isEqualSideTriangle(triangle)) {

						continue;
					}

					if (isPresent(triangle, trianglesArray)) {
						
						continue;
					}

					trianglesArray.push_back(triangle);
				}
			}
		}

		cout << "The total amount of suitable triangles is " 
			<< trianglesArray.size() << ".\n";

		if (trianglesArray.size() > 0) {

			cout << "\nThe examples of suitable triangles:\n";

			for (auto& triangle : trianglesArray) {

				isIntersected(triangle, trianglesArray);
				outputTriangle(triangle);
			}
		}

		cout << endl;
		system("pause");
		system("cls");

		cout << "Enter the size of a square matrix ('0' to end the programm):\n";
		cin >> matrixSize;
		cout << "\nEnter base length comprarison accuracy('0.2' is recommended) or '0' to end the programm:\n";
		cin >> epsilonLength;
		cout << endl;
	}

	return 0;
}