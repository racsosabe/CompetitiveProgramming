#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racsó Galván

	Idea:

	- Just maintain 26 sets such that the set S[c] contains all the positions in which

	  character c appears.

	- We can answer to the queries by iterating over the 26 possible characters, using

	  a lower_bound on l and if the corresponding value exists, check if its not

	  greater than r.

	- Complexity: O(qElogn + nlogn), where E = 26

*/

const int N = 500000 + 5;
const int E = 26;

int n;
int q;
int a[N];
char s[N];
set<int> S[E];

void init(){
	for(int i = 1; i <= n; i++){
		a[i] = s[i] - 'a';
		S[s[i] - 'a'].emplace(i);
	}
}

void update(int i, int c){
	S[a[i]].erase(i);
	S[c].emplace(i);
	a[i] = c;
}

int solve(int l, int r){
	int res = 0;
	for(int i = 0; i < E; i++){
		if(S[i].empty()) continue;
		set<int>::iterator it = S[i].lower_bound(l);
		if(it != S[i].end() and *it <= r) res++;
	}
	return res;
}

int main(){
	scanf("%d", &n);
	scanf("%s", s + 1);
	init();
	scanf("%d", &q);
	while(q--){
		int op;
		scanf("%d", &op);
		if(op == 1){
			int i;
			char c;
			scanf("%d", &i);
			c = getchar();
			while(!isalpha(c)) c = getchar();
			update(i, c - 'a');
		}
		else{
			int l, r;
			scanf("%d %d", &l, &r);
			printf("%d\n", solve(l, r));
		}
	}
	return 0;
}
