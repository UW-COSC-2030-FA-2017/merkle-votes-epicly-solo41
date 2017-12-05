#include "bTREE.h"
#include <vector>
#include <iostream>
using namespace std;

//look at descriptions in pMT.h for guidance on what you might need for these function to actually do
bTREE::bTREE()
{
	rootNode = new treeNode();
	rootNode->data = "";
	rootNode->time = 0;
	rootNode->isLeaf = true;
	lTree = NULL;
	rTree = NULL;
    myQueue.push(this);
	myQueueSize++;
}

bTREE::~bTREE(){
	delete rootNode;
}

int bTREE::dataInserted()
{
	int numData = 0;
	if (rootNode == NULL){
		numData= 0;
	}
	else if (rootNode->isLeaf == true){
		numData = 1;
	}
	else{
		numData = lTree->dataInserted() + rTree->dataInserted();
	}
	return numData;
}

int bTREE::numberOfNodes(){
	int numNodes = 0;
	if (rootNode == NULL)
	{
		numNodes = 0;
	}
	else if (lTree->rootNode == NULL && rTree->rootNode == NULL)
	{
		numNodes = 1;
	}
	else
	{
		numNodes = 1 + lTree->numberOfNodes() + rTree->numberOfNodes();
	}
	return numNodes;
}


bTREE* bTREE::getLeftTree() const
{
    return lTree;
}
bTREE* bTREE::getRightTree() const
{
    return rTree;
}

int bTREE::insert(string data1, int time1)
{
	static int noOfSteps = 0;
	bool insert = false;
	bTREE * newTree = new bTREE();
	treeNode* newNode = new treeNode();
	newNode->data = data1;
	newNode->time = time1;
	newNode->isLeaf = true;
	newTree->rootNode = newNode;
	newTree->lTree = NULL;
	newTree->rTree = NULL;

	if (rootNode == NULL){
		rootNode = newNode;
		myQueue.push(newTree);
		myQueueSize++;
		noOfSteps++;
		insert = true;
	}

	else if(myQueue.front()->lTree == NULL) {
		myQueue.front()->lTree = newTree;
		myQueue.push(newTree);
		myQueueSize++;
		noOfSteps+=2;
		rootNode->isLeaf = false;
		insert = true;
		
	}

	else if (myQueue.front()->rTree == NULL)
	{
		myQueue.front()->rTree = newTree;
		myQueue.push(newTree);
		myQueueSize++;
		myQueue.pop();
		myQueueSize--;
		noOfSteps +=3;
		rootNode->isLeaf = false;
		insert = true;
		
	}
	if(insert)
	{
		
		return noOfSteps;
	}
	return 0;
}

int bTREE::find(string x)
{
    static bool found = false;
    static int steps= 0;
    if((rootNode->data != x) && (rootNode->isLeaf == false))
    {
        steps = 1 + rTree->find(x)+lTree->find(x);
    }
    else
    {
       steps ++;
       found = true;
    }
    if(found)
    {
        return steps;
    }
    return 0;
}

string bTREE::locate(string x)
{
    static string directions;
	cout << "test:" << find(x) << endl;
    if(find(x)==0)
    {
        directions = ".";
    }
    else
    {
        if((rootNode->data == x) && (rootNode->isLeaf == false))
        {
            directions = directions+(" ");
        }
		else if((lTree->find(x) > 0) && (rootNode->isLeaf == false)){
                directions = directions + "L";
                lTree->locate(x);
            }
		else if ((rTree->find(x)) > 0 && (rootNode->isLeaf == false))
		{
			directions = directions + "R";
			rTree->locate(x);
		}
    }
    return directions;
}

bool operator ==(const bTREE& lhs, const bTREE& rhs)
{
    if(lhs != rhs)
    {
        return false;
    }
    return true;
}

bool operator!=(const bTREE & lhs, const bTREE & rhs)
{
    static bool not_equality = false;
    if(lhs.rootNode->data != rhs.rootNode->data)
    {
        not_equality = true;
    }
    else if((lhs.lTree != rhs.lTree) || (lhs.rTree != rhs.rTree))
    {
        not_equality = true;
    }
    return not_equality;
}

void
   bTREE:: displayLeft( std::ostream & outfile,
   bTREE * subtree, std::string prefix )
{
   if( subtree == NULL )
   {
      outfile << prefix + "/" << endl;
   }
   else
   {
      displayLeft( outfile, subtree->lTree, prefix + "     " );
	  outfile << prefix + "\\---" << subtree->rootNode->data << std::endl;
      displayRight( outfile, subtree->rTree, prefix + "|    " );
   }
}


void
   bTREE:: displayRight( std::ostream & outfile,
   bTREE * subtree, std::string prefix )
{
   if( subtree == NULL )
   {
      outfile << prefix + " " << std::endl;
   }
   else
   {
      displayLeft( outfile, subtree->lTree, prefix + "|    " );
      
	  outfile << prefix + "  " << subtree->rootNode->data << std::endl;
      displayRight( outfile, subtree->rTree, prefix + "     " );
   }
}


std::ostream& operator <<(std::ostream& out, const bTREE* p)
{
   std::string prefix;
   if( p->rootNode->isLeaf == true)
   {
      out << "- " << endl;
   }
   else
   {
      bTREE::displayLeft( out, p->lTree, "    " );
	  out << " " << p->rootNode->data << std::endl;

      bTREE::displayRight( out, p->rTree, "    " );
   }
   return out;
}

