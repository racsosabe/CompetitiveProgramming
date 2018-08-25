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
		- Easy Meet in the Middle problem.

		- First, let's assume that we sell everything we already have, thus
		  having a initial amount of money and value.
		
		- If initial value is greater or equal than K, return 0. Else, we do the following

		- Just notice that we can split the total group of postmarks in 2 groups
		  So we can brute force those groups and have them stored by a pair (value,price)
	  	  Now, we see that for a pair (x,y) we can use any pair (a,b) such that
		  x+a >= k

		  Which means that we only need to get the position of the minimal a in
		  the second group, our best choice is the one that has minimum price.

		- Also, if we have a greater x, then our a will be smaller in consequence, 
		  so there we use two pointers for both groups and since we need minimum
		  we mantain it for the second group.
	  	
		- Complexity: O(n2^{n/2})

*/

class CollectingPostmarks {
public:
	int amountOfMoney(vector <int> prices, vector <int> have, vector <int> values, int K) {
		typedef pair<int,int> ii;
		int act_money = 0;
		int val = 0;
		int n = prices.size();
		for(int i=0; i<int(have.size()); i++){
			act_money += prices[have[i]];
			val += values[have[i]];
		}
		if(val >= K) return 0;
		vector<ii> part1, part2;
		int m = n/2;
		int p = n - m;
		for(int mask=0; mask<1<<m; mask++){
			int act_val = 0;
			int act_price = 0;
			for(int i=0; i<m; i++){
				if((mask>>i)&1){
					act_val += values[i];
					act_price += prices[i];
				}
			}
			part1.push_back(make_pair(act_val,act_price));
		}
		for(int mask=0; mask<1<<p; mask++){
			int act_val = 0;
			int act_price = 0;
			for(int i=0; i<p; i++){
				if((mask>>i)&1){
					act_val += values[i+m];
					act_price += prices[i+m];
				}
			}
			part2.push_back(make_pair(act_val,act_price));
		}
		sort(part1.begin(),part1.end());
		sort(part2.begin(),part2.end());
		int ans = -1;
		int pos1 = 0, pos2 = (1<<p)-1;
		int act_min = -1;
		while(pos1 < (1<<m)){
			while(pos2 >= 0 and part1[pos1].first + part2[pos2].first >= K){
				act_min = act_min==-1?part2[pos2].second:min(act_min,part2[pos2].second);
				pos2--;
			}
			if(act_min > -1){
				ans = ans==-1?max(act_min+part1[pos1].second-act_money,0):min(ans,max(act_min+part1[pos1].second-act_money,0));
			}
			pos1++;
		}
		return ans;
	}
};
