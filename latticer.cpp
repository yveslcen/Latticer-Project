#include <bits/stdc++.h>
#define PB push_back
#define MP make_pair
using namespace std;

void valueErrorChecker(long double, bool, bool, bool);
void latticerRP();
void latticerCir();

int main() {
	cout << "Welcome to Latticer! "
	     << "Latticer is a tool for calculating lattices in and on Regular Polygon, Circle. " << endl
		 << endl << "Enter \"RP\" for Regular Polygon, "
		 << "\"Cir\" for Circle" << endl
		 << "Enter Code: ";
	string shapeCode;
	cin >> shapeCode;
	
	//Calculation Begin
	if (shapeCode == "RP" || shapeCode == "Rp" || shapeCode == "rp") {
		latticerRP();
	} else if (shapeCode == "CIR" || shapeCode == "Cir" || shapeCode == "cir") {
		latticerCir();
	} else {
		cout << "Error: \"" << shapeCode << "\" is an invalid code. " << endl;
		return 9;
	}
	return 0;
}

void valueErrorChecker(long double n, bool notNegative, bool notZero, bool greaterThanThree) {
	bool isError = false;
	if (notNegative && n < 0) isError = true;
	if (notZero && n == 0) isError = true;
	if (greaterThanThree && n < 3) isError = true;
	if (isError) {
		cout << "Error: value invalid. " << endl;
		exit(9);
	}
}

void latticerRP() {
	//Input Data
	cout << endl << "- - - - - - - - - - - - Data Input - - - - - - - - - - - -" << endl;
	int polygonSides;
	cout << "Warning, the Latticer can not yet process Concave Polygon. " << endl
		 << "All points entered should follow the sequence either to be clockwise or counterclockwise. " << endl << endl;
	cout << "How many sides does this Regular Polygon have: ";
	cin >> polygonSides;
	valueErrorChecker(polygonSides, true, true, true);
	vector< pair<long double, long double> > points(polygonSides);	
	cout << "Enter coordinate of the point. All inputs should follow the warning above" << endl;
	for (int i = 0; i < polygonSides; i++) {
		cout << "Point" << i + 1 << " x: ";
		cin >> points[i].first;
		cout << "Point" << i + 1 << " y: ";
		cin >> points[i].second;
		cout << endl;
	}
		
	//Calculation Begin
	int maxCoordinateX = points[0].first + 1, minCoordinateX = points[0].first - 1,
		maxCoordinateY = points[0].second + 1, minCoordinateY = points[0].second - 1;
	for (int i = 0; i < polygonSides; i++) {
		if (points[i].first > maxCoordinateX) maxCoordinateX = points[i].first + 1;
		if (points[i].first < minCoordinateX) minCoordinateX = points[i].first - 1;
		if (points[i].second > maxCoordinateY) maxCoordinateY = points[i].second + 1;
		if (points[i].second < minCoordinateY) minCoordinateY = points[i].second - 1;
	}
	/*int latticeQuantities = 0, */int countSidesApprove = 0;
	vector< pair<int, int> > lattices;
	for (int i = minCoordinateX; i <= maxCoordinateX; i++) {
		for (int j = minCoordinateY; j <= maxCoordinateY; j++) {
			for (int k = 0; k < polygonSides; k++) {
				//slope = 0
				if (points[k].second == points[(k + 1) % polygonSides].second) {
					if (points[k].second >= points[(k + 2) % polygonSides].second && 
						points[k].second >= j) countSidesApprove++;
					else if (points[k].second <= points[(k + 2) % polygonSides].second && 
						points[k].second <= j) countSidesApprove++;
				}
				//no slope
				else if (points[k].first == points[(k + 1) % polygonSides].first) {
					if (points[k].first >= points[(k + 2) % polygonSides].first && 
						points[k].first >= i) countSidesApprove++;
					else if (points[k].first <= points[(k + 2) % polygonSides].first && 
						points[k].first <= i) countSidesApprove++;
				}
				//normal slope, y = mx + n
				else {
					long double m = (points[(k + 1) % polygonSides].second - points[k].second) 
							   / (points[(k + 1) % polygonSides].first - points[k].first), 
						   n = points[k].second - m * points[k].first;
					if (points[(k + 2) % polygonSides].second >= m * 
						points[(k + 2) % polygonSides].first + n && 
						j >= m * i + n) countSidesApprove++;
					else if (points[(k + 2) % polygonSides].second <= m * 
							 points[(k + 2) % polygonSides].first + n && 
							 j <= m * i + n) countSidesApprove++;
				}
			}
			if (countSidesApprove == polygonSides) {
				lattices.PB(MP(i, j));
			}
			countSidesApprove = 0;
		}
	}

	//Output Lattices
	cout << "- - - - - - - - - - - - Result Output - - - - - - - - - - - -" << endl;
	for (int i = 0; i < lattices.size(); i++) {
		if (i == lattices.size() - 1) cout << "(" << lattices[i].first << ", " << lattices[i].second << ")" << endl;
		else cout << "(" << lattices[i].first << ", " << lattices[i].second << "), ";
	}
	if (lattices.size() == 1) cout << "There is totally 1 lattice in the Regular Polygon" << endl;
	else cout << "There are totally " << lattices.size() << " lattices in the Regular Polygon" << endl;
}

void latticerCir() {
	//Input Data
	cout << endl << "- - - - - - - - - - - - Data Input - - - - - - - - - - - -" << endl;
	pair<long double, long double> cirCentre;
	long double cirRadius;
	cout << "Enter coordinate x of the centre, x: ";
	cin >> cirCentre.first;
	valueErrorChecker(cirCentre.first, false, false, false);
	cout << "Enter coordinate y of the centre, y: ";
	cin >> cirCentre.second;
	valueErrorChecker(cirCentre.second, false, false, false);
	cout << "Enter the radius of the circle: ";
	cin >> cirRadius;
	valueErrorChecker(cirRadius, true, false, false);
	
	//Calculation Begin
	vector< pair<int, int> > lattices;
	for (int i = cirCentre.first - cirRadius - 1; i <= cirCentre.first + cirRadius + 1; i++) {
		for (int j = cirCentre.second - cirRadius - 1; j <= cirCentre.second + cirRadius + 1; j++) {
			if ((i - cirCentre.first) * (i - cirCentre.first) + 
				(j - cirCentre.second) * (j - cirCentre.second)
				<= cirRadius * cirRadius) {
				lattices.PB(MP(i, j));
			}
		}
	}
	
	//Output Lattices
	cout << "- - - - - - - - - - - - Result Output - - - - - - - - - - - -" << endl;
	for (int i = 0; i < lattices.size(); i++) {
		if (i == lattices.size() - 1) cout << "(" << lattices[i].first << ", " << lattices[i].second << ")" << endl;
		else cout << "(" << lattices[i].first << ", " << lattices[i].second << "), ";
	}
	if (lattices.size() == 1) cout << "There is totally 1 lattice in the Circle" << endl;
	else cout << "There are totally " << lattices.size() << " lattices in the Circle" << endl;
}
