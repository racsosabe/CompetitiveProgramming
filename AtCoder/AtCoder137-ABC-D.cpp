#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Notice that if we want to consider taking some job (A, B) then we will need to

	  do it in a day X <= M - A to be able to earn its reward (otherwise it makes no sense 

	  to take the job)

	- Now, we can iterate over the days i = M to 0 and add each job that can be done

	  until i-th day, out of all these jobs we can take the one that has the greatest

	  reward (if it exists)

	- Complexity O(m + nlogn)

*/

const int N = 100000 + 5;

int n;
int m;
vector<int> ending_here[N];

int main() {
	scanf("%d %d", &n, &m);
	for(int i = 0; i < n; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		if(m >= a) ending_here[m - a].emplace_back(b);
	}
	int res = 0;
	priority_queue<int> Q;
	for(int i = m; i >= 0; i--) {
		for(auto x : ending_here[i]) Q.emplace(x);
		if(!Q.empty()) {
			res += Q.top(); Q.pop();
		}
	}
	printf("%d\n", res);
	return 0;
}
