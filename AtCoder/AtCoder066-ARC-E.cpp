#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- DP problem.

	- We want to maximize the sum of the values multiplied by their final signs

	  after putting some parentheses.

	- Observation 1: If we fix the number of parentheses put after a negative sign

	  in the previous positions, we can get the final sign that the i-th value

	  will have.

	- Observation 2: Each time we put a paretheses, we are inverting the sign once

	  for the next values. Since inverting 3 times is the same as inverting once

	  the optimal answer only needs a maximum depth of 2 for the parentheses.

	- If we simulate the process using DP, we can solve it fast enough.

	- Complexity: O(n)
*/

const int N = 100000 + 5;

int n;
int a[N];
char op[N];
bool vis[N][4];
long long memo[N][4];

bool isOp(char c){ return c == '+' or c == '-';}

int sgn(int par){ return par ? 1 : -1;}

long long DP(int pos, int par){
	if(pos == n) return 0;
	if(vis[pos][par]) return memo[pos][par];
	long long ans = LLONG_MIN;
	if(op[pos] == '+'){
		ans = a[pos] * sgn(par ^ 1) + DP(pos + 1, par);
		if(par) ans = max(ans, a[pos] * sgn(par ^ 1) + DP(pos + 1, par - 1));
	}
	else{
		if(par + 1 <= 2){
			ans = max(ans, a[pos] * sgn(par) + DP(pos + 1, par + 1));
		}
		ans = max(ans, a[pos] * sgn(par) + DP(pos + 1, par));
		if(par){
			ans = max(ans, a[pos] * sgn(par) + DP(pos + 1, par - 1));
		}
	}
	vis[pos][par] = true;
	return memo[pos][par] = ans;
}

int main(){
	scanf("%d", &n);
	scanf("%d", &a[0]);
	op[0] = '+';
	for(int i = 1; i < n; i++){
		char c = getchar();
		while(!isOp(c)) c = getchar();
		scanf("%d", &a[i]);
		op[i] = c;
	}
	printf("%lld\n", DP(0, 0));
	return 0;
}
