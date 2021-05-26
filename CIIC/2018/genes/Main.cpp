#include "genes.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <cassert>
#include <cstdlib>


using namespace std;

#define forn(i,n) for(int i=0;i<(int)(n);i++)

map<pair<int,int>,int> testCaseCosts;
vector<long long> testCaseIndexes;

int testCaseT;
long long testCaseTotalCost = 0;

long long measureBacteria(int gene1, int gene2)
{
    if (gene1 < 1 || gene1 > testCaseT ||
	gene2 < 1 || gene2 > testCaseT)
    {
	cerr << "Out of range genes (" << gene1 << "," << gene2 << ")" << endl;
	exit(0);
    }
    pair<int,int> p(gene1,gene2);
    if (testCaseCosts.find(p) == testCaseCosts.end())
    {
	cerr << "Impossible to produce bacteria (" << gene1 << "," << gene2 << ")" << endl;
	exit(0);
    }
    testCaseTotalCost += testCaseCosts[p];
    return testCaseIndexes[gene1-1] + testCaseIndexes[gene2-1];
}

void report(int K, int *kinds, long long *values)
{
    cout << "Reported kinds: " << K << endl;
    cout << "kind\tvalue" << endl;
    forn(i,K)
    {
       cout << kinds[i] << '\t' << values[i] << endl;
    }
}

int main()
{
    // INPUT:
    // T C
    // g1 g2 cost  [C lines like this]
    // [A line with T integers, the productivity indexes]
    cin >> testCaseT;
    int C; cin >> C;
    vector<int> gene1(C), gene2(C), cost(C);
    forn(i,C)
    {
	cin >> gene1[i] >> gene2[i] >> cost[i];
	testCaseCosts[make_pair(gene1[i],gene2[i])] = cost[i];
	testCaseCosts[make_pair(gene2[i],gene1[i])] = cost[i];
    }

    testCaseIndexes.resize(testCaseT);
    forn(i,testCaseT) cin >> testCaseIndexes[i];
    tryScience(testCaseT, C, cost.data(), gene1.data(), gene2.data());

    cout << "The total cost was: " << testCaseTotalCost << endl;
}
