#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
	Author: Racso Galvan

	Idea: 
		- DP + Simulation problem

		- Just notice that we will choose at most D different creatures

		  so we can just simulate for each type how many creatures we have

		  trained so far and get the maximum sum possible.

		- Complexity: O(n^2 * D^2)

*/

class CreatureTraining {
public:
	int n;
	vector<int> Q;
	vector<int> P;
	bool vis[55][101][101];
	long long memo[55][101][101];

	long long DP(int pos, int left, int used){
		if(pos == n-1){
			return 1LL * P[pos] * Q[pos];
		}
		if(vis[pos][left][used]) return memo[pos][left][used];
		long long ans = DP(pos+1,left,0) + 1LL * P[pos] * (Q[pos] - used);
		if(used + 1 <= Q[pos]){
			for(int i = pos+1; i < n and i - pos <= left; i++){
				long long cand = P[i] + DP(pos,left - (i - pos), used+1);
				if(ans < cand){
					ans = cand;
				}
			}
		}
		vis[pos][left][used] = true;
		return memo[pos][left][used] = ans;
	}

	long long maximumPower(vector <int> count, vector <int> power, int D) {
		n = power.size();
		Q = count;
		P = power;
		return DP(0,D,0);
	}
};
