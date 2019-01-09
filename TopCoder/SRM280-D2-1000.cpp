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

		- Interesting Brute Force problem.

		- Just brute force it with backtracking with 

		  special cases

		- Other way is with next_permutation as stated in

		  Contest analysis, which I think is a more 

		  elegant solution :D

		- Complexity: O(n^m), where m is numbers' size.
*/

class GroupingNumbers {
public:

	void backtracking(int pos, vector<int> &numbers, vector<int> &sums, vector<int> &sizes, int used, double &ans, int &n){
		int m = numbers.size();
		if(pos == m){
			if((used+1) == (1<<n)){
				double minimal = 1000000000000.0;
				double maximal = -1000000000000.0;
				double carry;
				for(int i=0; i<n; i++){
					carry = 1.0*sums[i]/sizes[i];
					minimal = min(minimal,carry);
					maximal = max(maximal,carry);
				}
				ans = min(ans,maximal-minimal);
			}
			return;
		}
		for(int i=0; i<n; i++){
			sums[i] += numbers[pos];
			sizes[i] += 1;
			backtracking(pos+1,numbers,sums,sizes,used|1<<i,ans,n);
			sums[i] -= numbers[pos];
			sizes[i] -= 1;
		}
	}

	double minRange(vector <int> numbers, int n) {
		vector<int> sums(n,0);
		vector<int> sizes(n,0);
		double ans = 1000000000000.0;
		int m = numbers.size();
		if(m == n){
			int minimal = 1000000000;
			int maximal = -1;
			for(int i=0; i<m; i++){
				maximal = max(maximal,numbers[i]);
				minimal = min(minimal,numbers[i]);
			}
			ans = maximal-minimal;
		}
		else{
			backtracking(0,numbers,sums,sizes,0,ans,n);
		}
		return ans;
	}
};
