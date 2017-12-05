 #pragma once

#include "bTREE.h"
#include <string>
using namespace std;
class pMT
{
private:
    int selectedHash;
    bTREE *myMerkle;

    string hash_1(string);
    string hash_2(string);
    string hash_3(string);

public:
    pMT(int);
    ~pMT();

    bTREE* getMerkle() const
    {
        return myMerkle;
    }
	int getQueueLength() const
	{
		return myMerkle->myQueueSize;
	}
    int insert(string s, int i);
    int find(string, int, int);
    int findHash(string x);


    string locate(string x);

    friend bool operator==(const pMT& lhs, const pMT& rhs);

    friend bool operator!=(const pMT& lhs, const pMT& rhs);

    friend pMT operator^(const pMT& lhs, const pMT& rhs);

    friend std::ostream& operator<<(std::ostream& out, const pMT& p);


    void update();

    void rhash(bTREE *tree);

    string hash_selected(string data);
};

