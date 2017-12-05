#include <stdio.h>
#include "pMT.h"
#include <vector>
#include <fstream>
#include<string>
#include <iostream>
#include <sstream>
using namespace std;

void promptAndFillInVariables(vector<string>& votes, vector<int>& timeStamps, int& noOfVotes)
{
    string filename;
    string temp;
	string vote1;
	int timestamp = 0;
    cout<<"What's the file name: ";
    cin>>filename;
	ifstream myfile;
    myfile.open(filename);
	int index = 0;
	if (myfile.is_open())
	{
		while (getline(myfile, temp))
		{
            
			if (index > 0 )
			{
				istringstream iss(temp);
				iss >> vote1 >> timestamp;
				int pos = vote1.find(":");
				if (pos!=std::string::npos)
				{
				    string vote = vote1.substr(0,pos);
				    votes.push_back(vote);
                    timeStamps.push_back(timestamp);
                    noOfVotes++;
				}
			}
			index++;
		}

	}
	else{
        cout<<"Error opening file. Check filename."<<endl;
	}
}
int main(int argc, char **argv)
{
    vector<string> votes;
    vector<int> timeStamps;
    int NumVotes = 0;
    promptAndFillInVariables(votes, timeStamps, NumVotes);
    pMT theMerkleTree(1);
    while((theMerkleTree.getQueueLength())*2<=NumVotes) 
    {
        theMerkleTree.insert("a", 0);
    }
    for(int i = 0; i<NumVotes; i++)
    {
        theMerkleTree.insert(votes[i],timeStamps[i]);
    }
    theMerkleTree.update();
	cout << theMerkleTree << endl;
	cout << "The rootNode hash is: " << theMerkleTree.getMerkle()->rootNode->data << endl;
	
	vector<string> votes1;
	vector<int> timeStamps1;
	int noOfVotes1 = 0;
    promptAndFillInVariables(votes1, timeStamps1, noOfVotes1);
    pMT merkleTree1(1);
	while ((merkleTree1.getQueueLength()) * 2 <= noOfVotes1) 
	{
		merkleTree1.insert("a", 0);
	}
	for (int i = 0; i<noOfVotes1; i++)
	{
		merkleTree1.insert(votes1[i], timeStamps1[i]);
	}
	merkleTree1.update();
	vector<string> votes2;
	vector<int> timeStamps2;
	int noOfVotes2 = 0;
    promptAndFillInVariables(votes2, timeStamps2, noOfVotes2);
    pMT merkleTree2(1);
	while ((merkleTree2.getQueueLength()) * 2 <= noOfVotes2) 
	{
		merkleTree2.insert("a", 0);
	}
	for (int i = 0; i<noOfVotes2; i++)
	{
		merkleTree2.insert(votes2[i], timeStamps2[i]);
	}
	merkleTree2.update();

    if(merkleTree1 == merkleTree2)
    {
        cout<<"Check!"<<endl;
    }
    else
    {
        cout<<"Not VCheck"<<endl;
    }
    return 0;
}
