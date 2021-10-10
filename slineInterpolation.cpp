/*Побудувати лінійний сплайн для функції f(x) = sin(x) + x. Обчислити
наближені значення в точках х = -6.7, -5.5, -4.2, оцінити точність.*/

/*To build linear spline for function f(x) = sin(x) + x. Calculate
approximate values ​​at points x = -6.7, -5.5, -4.2, estimate the accuracy*/

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

using namespace std;

//function
double func(double x) {
	return sin(x) + x;
}

//output of vector values 
void print(vector<double> vec) {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}

//output of vector values for solved method
void print(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Solution in point: " << x[i] << " = " << vec[i] << endl;
	}
	cout << endl;
}

//output precision
void eps(vector<double> vec, vector<double> x) {
	for (int i = 0; i < vec.size(); i++) {
		cout << "Precision in point: " << x[i] << " = " << setw(10) << abs(abs(vec[i]) - abs(func(x[i]))) << endl;
	}
}

//Spline interpolation
void methodSplain(vector<double> _x, vector<double> _y, vector<double> x) {
	cout << endl << "____________Spline Interpolation____________" << endl;
	vector<double> a;
	vector<double> b;
	vector<double> result;
	for (int i = 0; i < _x.size() - 1; i++)
	{
		a.push_back((_y[i] - _y[i + 1]) / (_x[i] - _x[i + 1]));	
		b.push_back(_y[i] - (a[i] * _x[i]));			
		cout << "a( " << i << " ) = " << a[i] << endl;
		cout << "b( " << i << " ) = " << b[i] << endl << endl;
	}
	for (int i = 0; i < _x.size() - 1; i++) {
		for (int j = 0; j < _x.size() - 1; j++) {
			if (x[i] >= _x[j] && x[i] <= _x[j + 1]) {		
				result.push_back(a[i] * x[i] + b[i]);		
				j = _x.size() - 1;							
			}
		}
	}
	print(result, x);
	eps(result, x);
}

int main()
{
	double xTemp;
	double yTemp;
	vector<double> _x;
	vector<double> _y;
	vector<double> x;
	ifstream file("data.txt");
	while (!file.eof()) {
		file >> xTemp >> yTemp;
		_x.push_back(xTemp);
		_y.push_back(yTemp);
	}
	file.close();
	vector<double> newSplineX;
	ifstream fileEx3("splineInterpolation.txt");
	while (!fileEx3.eof()) {
		fileEx3 >> xTemp;
		newSplineX.push_back(xTemp);
	}
	fileEx3.close();
	cout << endl << "x: ";
	print(_x);
	cout << "y: ";
	print(_y);
	cout << "Dots: ";
	print(newSplineX);
	cout << endl;
	methodSplain(_x, _y, newSplineX);
}