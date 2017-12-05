#include "pMT.h"
#include <cstring>
#include<stdlib.h>
pMT::pMT(int hashSelect)
/**
 * @brief
 * @param hashSelect a number corresponding to the hashfunction to use for this pMT
 * @return
 */
{
	myMerkle = new bTREE();
    selectedHash = hashSelect;
}

pMT::~pMT()
/**
 * @brief destructor
 * @return nada
 */
{
}

int pMT::insert(string vote, int time)
/**
 * @brief insert a vote and time into a leaf node of tree
 * @param vote - a string
 * @param time - an int representing the time
 * @return the number of operations needed to do the insert, -1 if out of memory
 */

{
    return myMerkle->insert(vote, time);
}

int pMT::find(string vote, int time, int hashSelect)
/**
 * @brief given a vote, timestamp, and hash function, does this vote exist in the tree?
 * @param vote, a string
 * @param time, an int
 * @param hashSelect, an int corresponding to the hash functions _1, _2, and _3
 * @return 0 if not found, else number of operations required to find the matching vote
 */
{
    string Hash;
    if(hashSelect<=1)
    {
        Hash = hash_1(vote);
    }
    else if(hashSelect==2)
    {
        Hash = hash_2(vote);
    }
    else if(hashSelect>=3)
    {
        Hash = hash_3(vote);
    }
    return myMerkle->find(Hash);

}

int pMT::findHash(string mhash)
/**
 * @brief does this hash exist in the tree?
 * @param mhash, a string to search for in the tree
 * @return 0 if not found, else number of opperations required to find the matching hash
 */
{
    return myMerkle->find(mhash);
}
//Created one to locate both data and hash
string pMT:: locate(string dathash)
{
    return myMerkle->locate(dathash);
}

//string pMT::locateData(string vote)
/**
 * @brief Function takes a hash of Vote and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param vote, the data to search for
 * @return sequence of L's and R's comprising the movement to the leaf node; else return a dot '.'
 */
//{
//}

//string pMT::locateHash(string mhash)
/**
 * @brief Function takes a hash and returns the sequence of (L)eft and (R)ight moves to get to that node starting from root.
 * @param mhash, the hash to search for
 * @return sequence of L's and R's comprising the movement to the hash node, ; else return a dot '.'
 */
//{
//}

// I could only come up with two hash functions myself

string pMT::hash_1(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
    char hashStr[32];
    char* str = new char[32];
    strcpy(str, key.c_str());
    unsigned int len = key.length();
    unsigned int seed = 4231;
    unsigned int hash = 0;
    unsigned int i    = 0;

    for (i = 0; i < len; ++str, ++i){
       hash = (hash * seed)*(hash*seed) + (*str) +(hash >> 10); 
    }
    itoa(hash, hashStr, 16);
    return hashStr;
	//hashStr is the hexadecimal hash 
}

string pMT::hash_2(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
	return "";
}

string pMT::hash_3(string key)
/**
 * @brief A function that takes in a key and returns a hash of that key using some custom function
 * @param key, a string
 * @return a hash of the key
 */
{
		unsigned int hash = 0xAAAAAAAA;
		unsigned int i = 0;
		int len = key.length();
		const char* str = key.c_str();
		for (i = 0; i < len; ++str, ++i)
		{
			hash ^= ((i & 1) == 0) ? (~(hash << 1) * (hash >> 5) ^(*str)) :
				(~((hash << 2) *((*str) + ~(hash >> 7))));
		}

		return std::to_string(hash);
}

bool operator ==(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if equal, false otherwise
 */
{
    if(lhs.myMerkle->rootNode->data == rhs.myMerkle->rootNode->data)
    {
        return true;
    }
    return false;
}

bool operator !=(const pMT& lhs, const pMT& rhs)
/**
 * @brief Comparison between two merkle trees
 * @param lhs, the left hand side of the equality statment
 * @param rhs, the right hand side of the equality statement
 * @return true if not equal, false otherwise
 */
{
    if(lhs == rhs)
    {
        return false;
    }
    return true;
}

pMT operator ^(const pMT& lhs, const pMT& rhs)
/**
 * @brief Where do two trees differ
 * @param lhs
 * @param rhs
 * @return a tree comprised of the right hand side tree nodes that are NOT different from the left
 */
{
    if((lhs==rhs) && (lhs.myMerkle->isRootNodeLeaf() == false) && (rhs.myMerkle->isRootNodeLeaf() == false))
    {
        return lhs;
    }
    else
    {
        pMT tmp(lhs.selectedHash);
        pMT tmp2(lhs.selectedHash);
        pMT LLpmt(lhs.selectedHash);
        LLpmt.myMerkle = lhs.myMerkle->getLeftTree();
        pMT LRpmt(lhs.selectedHash);
        LRpmt.myMerkle = lhs.myMerkle->getLeftTree();
        pMT RLpmt(lhs.selectedHash);
        RLpmt.myMerkle = lhs.myMerkle->getLeftTree();
        pMT RRpmt(lhs.selectedHash);
        RRpmt.myMerkle = lhs.myMerkle->getLeftTree();
        tmp = LLpmt^RLpmt;
        tmp2 = LRpmt^RRpmt;
        if(tmp!= NULL)
        {
            return tmp;
        }
        else if(tmp2!=NULL)
        {
            return tmp2;
        }
        else
        {
            return NULL;
        }
    }

}


//std::ostream& operator <<(std::ostream& out, const pMT& p)
///**
// * @brief Print out a tree
// * @param out
// * @param p
// * @return a tree to the screen
// */
//{
//}



std::ostream& operator <<(std::ostream& out, const pMT& p)
{
	std::string prefix;
	if (p.myMerkle->rootNode->isLeaf == true)
	{
		out << "-" << endl;
	}
	else
	{
		bTREE::displayLeft(out, p.myMerkle->lTree, "    ");
		
		out << "---" << p.myMerkle->rootNode->data << std::endl;

		bTREE::displayRight(out, p.myMerkle->rTree, "    ");
	}
	return out;
}

string pMT::hash_selected(string data)
{
	switch (selectedHash)
	{
		case 1: return hash_1(data);
		break;
		case 2: return hash_2(data);
		break;
		case 3: return hash_3(data);
		default:
		return hash_1(data);
	}
}

void pMT::rhash(bTREE *tree)
{
	int noOfSteps = 0;
	if((tree->lTree->lTree != NULL) && (tree->lTree->rTree != NULL))
	{
		rhash(tree->lTree);
		noOfSteps++;
	}

	if((tree->rTree->lTree != NULL) && (tree->rTree->rTree != NULL))
	{
		rhash(tree->rTree);
		noOfSteps++;
	}

	tree->rootNode->data = hash_selected(hash_selected(tree->lTree->rootNode->data) + hash_selected(tree->rTree->rootNode->data));
	noOfSteps++;
	//return number of Steps;
}

void pMT::update()
{
	rhash(myMerkle);
}
