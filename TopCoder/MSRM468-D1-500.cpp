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
		- DP with memory compression problem.

		- First of all, let's use an array memo[n][k] to denote the minimum
		  
		  cost to reach city n using exactly k flights. Also denote pref[i]

		  as the sum of flight times from city 0 to i.

		- Then, our recurrence will be the following if our last choice was a flight

		  memo[n][k] = min(pref[n] - pref[i] + memo[i][k-1]) = pref[n] + min(memo[i][k-1] - pref[i]) for i < n

		  Now, if our last choice was to use a road, then we simply use

		  memo[n][k] = road[n-1] + memo[n-1][k]

		- Constraint 1: ML is just 64MB. We can't use a DS for minimum.

		  Observation: We need the function f(x,k) = memo[x][k-1] - pref[x]

		  for all previous x possible, so we can store that value in a single 

		  variable.

		  Thus, we can use an array of size (k+1) to store the minimum so far

		  for each k of f(x,k).

		- Warning 1: Don't update the values directly for each position, we must

		  use another array to store the new values and then minimize the

		  global one.

		- Constraint 2: ML is STILL 64MB. memo[MAXN][MAXK] is MLE. 

		  Observation: We only need the former value of memo[n-1][k] for the

		  road choice, so we can use an array of 2 x (k+1).

		- Warning 2: Remember to clear the values of the current row you'll use.

		- Complexity: O(nk)

*/

class RoadOrFlightHard {
public:

	long long minTime(int n, int roadFirst, int roadProd, int roadAdd, int roadMod, int flightFirst, int flightProd, int flightAdd, int flightMod, int k) {
		vector< vector<long long> > memo(2,vector<long long>(k+1,1LL<<62));
		vector<int> flights(n);
		vector<int> roads(n);
		vector<long long> ft(k+1,1LL<<62);
		flights[0] = flightFirst % flightMod;
		roads[0] = roadFirst % roadMod;
		for(int i=1; i<n; i++){
			flights[i] = (1LL * flights[i-1] * flightProd + flightAdd) % flightMod;
			roads[i] = (1LL * roads[i-1] * roadProd + roadAdd) % roadMod;
		}
		vector<long long> pref(n+1);
		pref[0] = 0LL;
		for(int i=1; i<=n; i++){
			pref[i] = pref[i-1] + flights[i-1];
		}
		memo[0][0] = 0LL;
		ft[0] = 0LL;
		for(int i=1; i<=n; i++){
			int pos = (i & 1);
			int last = pos ^ 1;
			for(int j=0; j<=k; j++) memo[pos][j] = 1LL<<62;
			memo[pos][0] = memo[last][0] + roads[i-1];
			vector<long long> actft(k+1);
			actft[0] = memo[pos][0] - pref[i];
			for(int j = 1; j <= k; j++){
				memo[pos][j] = memo[last][j] + roads[i-1];
				memo[pos][j] = min(memo[pos][j], pref[i] + ft[j-1]);
				actft[j] = memo[pos][j] - pref[i];
			}
			for(int j=0; j<=k; j++) ft[j] = min(ft[j], actft[j]);
		}
		long long ans = 1LL<<61;
		for(int i=0; i<=k; i++) ans = min(ans,memo[n&1][i]);
		return ans;
	}
};
