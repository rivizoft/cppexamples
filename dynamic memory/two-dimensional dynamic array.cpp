/* 
This is the implementation of a dynamic two-dimensional array 
using a loop
*/

#include <iostream>

using namespace std;

double average_value(double *arr[], int strokes, int columns);

int main()
{
	int strokes;
	int columns;

	cout << "Enter strokes: ";
	cin >> strokes;
	cout << endl;
	cout << "Enter columns: ";
	cin >> columns;

	/* START to create two-dimensional array */
	double **school = new double* [strokes];
	for (int i = 0; i < strokes; i++)
	{
		school[i] = new double[columns];
	}
	/* END two-dimensional array*/

	/* START to write value down in an array */
	for (int i = 0; i < strokes; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			cout << "Enter the value: ";
			cin >> school[i][j];
			cout << endl;
		}
	}
	/* END to wite down value in an array */

	cout << "The average value is: ";
	cout << average_value(school, strokes, columns);

	return 0;
}

/* Function which find average value */
double average_value(double *arr[], int strokes, int columns)
{
	double sum = 0;
	for (int i = 0; i < strokes; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			sum += arr[i][j];
		}
	}

	return sum / (strokes * columns);
}