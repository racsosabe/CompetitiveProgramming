#include<bits/stdc++.h>
using namespace::std;

/*
	Author: Racso Galvan

	Idea:

	- Observation ad-hoc problem.

	- Let's say that A is 1 and B is 2, by the transformation moves we can check

	  that the sum of digits modulo 3 remains the same as the original.

	- First, notice that the moves can be reverted, so there exists a sequence
	
	  A -> BB and BB -> A (B -> AA and AA -> B)

	- So we can always transform every non-empty string into A, AA or AAA, which

	  are 1, 2 and 0 modulo 3 respectively. (This can be done since we can do B -> AA
	  
	  or BB -> A and then take AAA until we have one of those final strings).

	- Complexity: O(n + m + q), where n is the length of S and m is the length of T.
*/

const int N = 100000 + 5;

int n;
int q;
char s[N];
int ac[2][N];

void process(int id){
	scanf("%s", s);
	n = strlen(s);
	for(int i = 1; i <= n; i++){
		int val = s[i - 1] - 'A' + 1;
		ac[id][i] = ac[id][i - 1] + val;
		if(ac[id][i] >= 3) ac[id][i] -= 3;
	}
}

int query(int id, int l, int r){
	return (ac[id][r] + 3 - ac[id][l - 1]) % 3;
}

int main(){
	for(int i = 0; i < 2; i++) process(i);
	scanf("%d", &q);
	while(q--){
		int l1, r1, l2, r2;
		scanf("%d %d %d %d", &l1, &r1, &l2, &r2);
		puts(query(0, l1, r1) == query(1, l2, r2) ? "YES" : "NO");
	}
	return 0;
}
