#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>	// for srand
#include <vector>
#include <random>
#include <algorithm>


std::vector<int> getSequence(int length = 1000)
{
	std::vector<int> pageSequence;
	for(int i=0; i<length; i++)
	{
		pageSequence.push_back(std::rand()%250);
	}
	return pageSequence;
}

bool seek(std::queue<int> q, int target)
{
//returns true if target is found in queue
	while(!q.empty())
	{
	if(q.front()==target)
		return true;
	else
		q.pop();
	}
	return false;
}

int hundredFrames(int n, std::vector<int> sequence)
{
	int anomalies = 0;
	int oldFaults = 0;
	std::vector<int> pageFaultArray(100);
	for (int i=1;i<101;i++)	//for frame set
	{
		int pageFaults=0;
		std::vector<int> seekArray(250, 0);
		std::queue<int> pagesInMemory;
		for(int ref=0;ref<1000;ref++)	//for page in sequence
		{
			if(!seekArray[sequence[ref]])	//page not found
			//if(!seek(pagesInMemory, sequence[ref])) 	//page not found in Memory
			{
				pagesInMemory.push(sequence[ref]);
				seekArray[sequence[ref]]=1;
				if(pagesInMemory.size()>i)
				{
					int p=pagesInMemory.front();
					seekArray[p]=0;
					pagesInMemory.pop();
				}
				pageFaults++;
			}
		}
		//store page faults for that number of frames
		pageFaultArray[i]=pageFaults;
//		if (i!=1 && pageFaultArray[i]>pageFaultArray[i-1])
		if(pageFaults>oldFaults && oldFaults !=0)
		{
			//anomaly detected!
			anomalies++;
			std::cout<<"\nAnomaly Detected!";
			std::cout<<"  Sequence: "<<n<<std::endl;
			std::cout<<oldFaults<<" page faults at "<<i-1<<" frames.\n";
			std::cout<<pageFaults<<" page faults at "<<i<<" frames.\n";
		}
		oldFaults = pageFaults;
		pageFaults = 0;
	}
	//std::cout<<"\nAnomaly detected "<<anomalies<<" times."<<std::endl;
	return anomalies;
}

int main()
{
	std::srand((unsigned)time(0));
	int totalAnomalies=0;
	for (int i=0;i<100;i++)	//i=number of sequence
	{
		std::vector<int> sequence = getSequence();
		totalAnomalies+=hundredFrames(i, sequence);
	}
	std::cout<<"\nAnomaly detected "<<totalAnomalies<<" times.";
	return 0;
}
