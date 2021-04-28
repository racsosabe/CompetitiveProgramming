#include<bits/stdc++.h>
using namespace::std;

const int N = 25;

int n;
char s[N];

void print(){
	for(int i = 0; i < n; i++) putchar(s[i]);
	putchar('\n');
}

void backtracking(int pos, int sum){
	if(pos == n){
		if(sum == 0) print();
		return;
	}
	s[pos] = '(';
	backtracking(pos + 1, sum + 1);
	if(sum > 0){
		s[pos] = ')';
		backtracking(pos + 1, sum - 1);
	}
}

int main(){
	scanf("%d", &n);
	if(n % 2 == 0) backtracking(0, 0);
	return 0;
}
