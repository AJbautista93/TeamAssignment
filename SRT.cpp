#include<iostream>
#include<cstdlib>
#include<string>
#include<cmath>
#include<vector>
#include<algorithm>

using namespace std;
struct Stimulatedess {
	char name;
	float arrTime;
	float expRunTime;
	int priority;
} Stimulated[20];

void Sort(struct Stimulatedess* Stimulated)
{
	float temp = 0.0;
	for (int i = 0; i < 20; i++)
	{
		for (int j = i + 1; j < 20; j++)
		{
			if (Stimulated[j].arrTime < Stimulated[i].arrTime)
			{
				temp = Stimulated[i].arrTime;
				Stimulated[i].arrTime = Stimulated[j].arrTime;
				Stimulated[j].arrTime = temp;
			}
		}
	}
	cout << "Sorted contents of the ready queue>>\n";
	for (int i = 0; i < 20; i++) {
		cout << "Name: " << Stimulated[i].name
			<< " Arrival time: " << Stimulated[i].arrTime
			<< " Expected run time: " << Stimulated[i].expRunTime
			<< " Priority: " << Stimulated[i].priority << endl;
	}
}

void DisplayStatistics(struct Stimulatedess* Stimulated)
{
	float LExit = 0.0;
	vector<float> TurnAroundTime, WaitTimeT;
	int unexe, totalT;
	int time = 0;
	cout << "Timeline for the Algorithm: ";
	for (int i = 0; i < 20; i++) {
		if (time > 99) {
			unexe = 20 - i;
			break;
		}
		while (time < Stimulated[i].arrTime) {
			cout << "-";
			time++;
		}
		for (int j = 0; j < ceil(Stimulated[i].expRunTime); j++) {
			cout << Stimulated[i].name;
		}
		TurnAroundTime.push_back(time + Stimulated[i].expRunTime - Stimulated[i].arrTime);
		WaitTimeT.push_back(time - Stimulated[i].arrTime);
		time += ceil(Stimulated[i].expRunTime);
		LExit = Stimulated[i].expRunTime;
	}
	totalT = time - ceil(LExit) + LExit - Stimulated[0].arrTime;
	while (time < 100) {
		cout << "-";
		time++;
	}
	cout << endl;
	float TS = 0, WS = 0;
	for (int i = 0; i < TurnAroundTime.size(); i++) {
		TS += TurnAroundTime[i];
		WS += WaitTimeT[i];
	}
	cout << "Average TurnAround Time is " << TS / 20.0 << " Quanta"
		<< "\nAverage WaitTime is " << WS / 20.0 << " Quanta"
		<< "\nNumber of Processes in the ready queue that never ran are " << unexe
		<< "\nThroughput of the algorithm per 100 quanta: " << (20 - unexe) * 100 / totalT << endl << endl;
}


void Algorithm()
{
	char name = 'A';
	//float LExit = 0;
	for (int i = 0; i < 20; i++) {
		Stimulated[i].name = name + i;
		Stimulated[i].arrTime = static_cast <float> (rand()) / static_cast <float> (RAND_MAX / 99);
		Stimulated[i].expRunTime = 0.1 + static_cast <float> (rand()) / (static_cast <float> (RAND_MAX / (10 - 0.1)));
		Stimulated[i].priority = rand() % (4 + 1 - 1) + 1;
	}
	Sort(Stimulated);
	DisplayStatistics(Stimulated);
}

int main()
{
	srand(0);
	for (int i = 0; i < 5; i++)
	{
		cout << "Process Number:" << i + 1 << endl;
		Algorithm();
	}
	return 0;
}