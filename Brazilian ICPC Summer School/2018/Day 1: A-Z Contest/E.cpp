#include<bits/stdc++.h>
using namespace::std;

int n;

void backtracking(int val, int limit, vector<int> &v){
	if(val == 0){
		printf("%d", v[0]);
		for(int i = 1; i < v.size(); i++){
			printf("+%d", v[i]);
		}
		putchar('\n');
	}
	for(int i = min(val, limit); i >= 1; i--){
		v.emplace_back(i);
		backtracking(val - i, i, v);
		v.pop_back();
	}
}

int main(){
	scanf("%d", &n);
	vector<int> v;
	backtracking(n, n, v);
	return 0;
}
