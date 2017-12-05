#pragma once
#include <string>
#include <queue>
using namespace std;

class bTREE
{
    struct treeNode{
        
        string data="";
        int time;
		bool isLeaf;
    };

private:


public:
    bTREE();
    ~bTREE();
    
    treeNode* rootNode;
	bTREE * lTree;
	bTREE * rTree;
    queue<bTREE*> myQueue=queue<bTREE*>();
	int myQueueSize = 0;
	
    int dataInserted();
    int numberOfNodes();
    bTREE* getLeftTree() const;
    bTREE* getRightTree() const;
    bool isRootNodeLeaf() const
    {
        return rootNode->isLeaf;
    }
    int insert(string, int);

    int find(string);

    string locate(string);


    friend bool operator==(const bTREE& lhs, const bTREE& rhs);
    friend bool operator!=(const bTREE& lhs, const bTREE& rhs);

    friend std::ostream& operator<<(std::ostream& out, const bTREE& p);

    static void displayLeft( std::ostream & outfile,
      bTREE * subtree, std::string prefix );

    static void displayRight( std::ostream & outfile,
      bTREE * subtree, std::string prefix );

};

