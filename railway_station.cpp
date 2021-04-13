// Determine number of platforms at a station
//

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int count_num_platforms(vector<vector<double>> &train_schedule); 

int main()
{
	
	vector<vector<double>> train_schedule = { {8,10},
											  {8.5,13.5},
											  {9,12},
											  {10,11},
											  {15,15.45},
											  {14.5, 15.45},
											  {19,20},
											  {21,22}}; //arrival in first column and departure in second, correct answer is 3
	

	/*
	vector<vector<double>> train_schedule = { {0.0,0.0},
											  {9.0,0.0},
		        							  {-9,0.0} }; //bogus schedule, correct answer is 0
				*/							  
	
   	/*
	vector<vector<double>> train_schedule = { {9.0,10.0},
											  {10.0,11.0},
											  {11.0,12.0} }; //no overlap, correct answer is 1
		*/									  

	/*
	 vector<vector<double>> train_schedule = { {5.0,5.5},
											   {5.0,5.5},
											   {5.0,5.5},
											   {5.0,5.5}}; //all trains arrive at the same time, correct answer is 4
	*/																					


	cout << "Number of platforms: " << count_num_platforms(train_schedule)<<"\n"; 


}

void print_mat(const vector<vector<double>>& mat){

	// Display elements of matrix
	for (int i = 0; i < mat.size(); i++)
	{
		for (int j = 0; j < mat[0].size(); j++)
			cout << mat[i][j] << " ";
		cout << endl;
	}
}

bool time_entry_is_valid(double t1, double t2) 
{
	return t1 > 0.0 && t1 < 24.0 && 
		   t2 > 0.0 && t2 < 24.0 && 
		   (t2 - t1 > 0.0);
}

int count_num_platforms(vector<vector<double>> &train_schedule)
{

	bool platform_found = 0; 

	vector<double> platform_departure; //vector of platforms

	//sort train schedule by the first column, arrival time
	sort(train_schedule.begin(), train_schedule.end(), [](const vector<double>& v1, const vector<double>& v2){ return v1 < v2; });

	cout << "Train schedule sorted by arrival time: \n";
	print_mat(train_schedule);
	
	//assign the first platform to the first train and record the time of departure
	if (time_entry_is_valid(train_schedule[0][0], train_schedule[0][1]))
	{ 
		platform_departure.push_back(train_schedule[0][1]); 
	}
	
	//Loop over train schedule by arrival time and keep track of next departure 
	for (int i = 1; i < train_schedule.size(); i++) 
	{
		platform_found = false; 

		if (time_entry_is_valid(train_schedule[i][0], train_schedule[i][1]))
		{
			//loop through platform departure times and assign arriving train to first "free" platform, 
			// i.e one with departure time prior to this train's arrival time
			for (int j = 0; j < platform_departure.size(); j++) 
			{
				if (train_schedule[i][0] >= platform_departure[j]) { //greater than equal to assumes trains are sharply on time! next run should assume some time delta
					platform_departure[j] = train_schedule[i][1];
					platform_found = true;
					break;
				}
			}
			if (!platform_found) //if no platform was available, build a new one
			{
				platform_departure.push_back(train_schedule[i][1]);
			}

		}
			   
	}
	//Count the number of platforms after all the arriving trains are assigned to platforms
	return platform_departure.size();
}