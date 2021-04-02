#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Notice that if we arrive to position x with a distance of D, we will have

	  2 possibilities:

	  1) Turn a_x to keep the distance (Alice doesn't move)

	  2) Turn a_x to decrease the distance, thus, making D' = some value in [0, D - 1]

	- This can be reduced to mantain D in the range [0, D] so that we can ensure

	  that Alice won't reach the goal after that.

	- Let's denote B_i as the minimum possible D-value with which we can arrive to

	  position i and Alice won't reach the goal, then we can define it recursively:

	  1) If B_(i + 1) <= floor(a_i / 2), then this means that if we arrive with

	     D = B_(i + 1) to position i, it won't be affected by a_i, thus this is

	     the minimum valid value.

	  2) Otherwise, we will want to arrive to position (i + 1) with value B_(i + 1)

	     thus, we will have B_i = B_(i + 1) + a_i.

	- Finally, we can just check if B_(i + 1) <= A_(i - 1) to know wheter we can

	  change a_i in order to make that Alice doesn't reach the goal.

	- Complexity: O(n + q)

*/

const int N = 500000 + 5;

int n;
int D;
int q;
int a[N];
long long prefix[N];
long long minvalid[N];

void preprocess(){
	prefix[0] = D;
	for(int i = 1; i <= n; i++){
		prefix[i] = min(prefix[i - 1], abs(prefix[i - 1] - a[i]));
	}
	minvalid[n + 1] = 1;
	for(int i = n; i >= 1; i--){
		if(minvalid[i + 1] <= a[i] / 2) minvalid[i] = minvalid[i + 1];
		else minvalid[i] = minvalid[i + 1] + a[i];
	}
}

bool solve(int x){
	return minvalid[x + 1] <= prefix[x - 1];
}

int main(){
	scanf("%d %d", &n, &D);
	for(int i = 1; i <= n; i++){
		scanf("%d", a + i);
	}
	preprocess();
	scanf("%d", &q);
	for(int i = 1; i <= q; i++){
		int x;
		scanf("%d", &x);
		puts(solve(x) ? "YES" : "NO");
	}
	return 0;
}
