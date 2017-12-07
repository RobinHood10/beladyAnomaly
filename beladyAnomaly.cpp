#include <iostream>
#include <queue>
#include <cstdlib>
#include <ctime>	// for srand
#include <vector>
#include <random>	//needed?
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

std::vector<int> hundredFrames(std::vector<int> sequence)
{
	std::vector<int> pageFaultArray(100);
	for (int i=1;i<101;i++)	//for frame set
	{
		int pageFaults=0;
		std::queue<int> pagesInMemory;
		for(int ref=0;ref<1000;ref++)	//for page in sequence
		{
			if(!seek(pagesInMemory, sequence[ref])) 	//page not found in Memory
			{
				pagesInMemory.push(sequence[ref]);
				if(pagesInMemory.size()>i)
					pagesInMemory.pop();
				pageFaults++;
			}
		}
		//store page faults for that number of frames
		pageFaultArray[i]=pageFaults;
	}
	return pageFaultArray;

}

int main()
{
	std::srand((unsigned)time(0));
	int anomalies = 0;
	for (int i=0;i<100;i++)	//i=number of sequence
	{
		std::vector<int> sequence = getSequence();
		std::vector<int> result = hundredFrames(sequence);
		//go through result vector looking for anomalies
		for (int frame=2;frame<101;frame++)
		{
			if (result[frame]>result[frame-1])
			{
			//anomaly detected!
			anomalies++;
			std::cout<<"Anomaly Detected!";
			std::cout<<"Sequence: "<<i<<std::endl;
			std::cout<<result[frame-1]<<" page faults at "<<frame-1<<" frames.\n";
			std::cout<<result[frame]<<" page faults at "<<frame<<" frames.\n";
			}
		}

	}
	std::cout<<"\nAnomaly detected "<<anomalies<<" times."<<std::endl;

	return 0;
}
