#include <thread>
#include <chrono>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

using namespace std;

#define ROUNDS 100

void my_function()
{
	for (int i = 0; i < 100; i++)
	{
		cout << "round number " << i << endl;
	}
}

void write_to_csv(int rows, int durs[], double deviations[], double avg, double std_dev)
{
	// Create csv file
	ofstream myfile("statistics.csv");
	string wr_str;
	// Write to csv line by line
	for (int row = 0; row < rows; row++)
	{
		// Convert row and duration to string
		wr_str = to_string(row + 1) + "," + to_string(durs[row]) + "," + to_string(deviations[row]) + "\n";
		// Write to csv
		myfile << wr_str;
	}
	// Convert avg and std_dev to string
	wr_str = "avg and std_dev," + to_string(avg) + "," + to_string(std_dev) + "\n";
	// Write to csv
	myfile << wr_str;
}


void main()
{
	int durs[ROUNDS];					// array of duration each round
	double deviations[ROUNDS];			// array of deviation of each round
	double avg;							// average of durs
	double std_dev;						// standard deviation

	avg = 0;
	// Calculate duration of each round
	for (int i = 0; i < ROUNDS; i++)
	{
		// Start point
		auto start = chrono::high_resolution_clock::now();
		// Call your function here
		my_function();
		// End point
		auto stop = chrono::high_resolution_clock::now();
		// Calculate duration in miliseconds
		auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
		// Convert duration to integer
		durs[i] = duration.count();
		avg = avg + durs[i];
	}
	avg = avg / ROUNDS;
	// Calculate standard deviation
	std_dev = 0;
	for (int i = 0; i < ROUNDS; i++)
	{
		deviations[i] = durs[i] - avg;
		std_dev += pow(deviations[i], 2);
	}
	std_dev /= ROUNDS;
	std_dev = pow(std_dev, 0.5);
	// Write to CSV
	write_to_csv(ROUNDS, durs, deviations, avg, std_dev);
}