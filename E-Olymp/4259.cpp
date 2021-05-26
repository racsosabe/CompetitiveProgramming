#include<bits/stdc++.h>
using namespace::std;

int n;
stack< pair<int, int> > S;

void push(int x){
	if(S.empty()) S.emplace(make_pair(x, x));
	else S.emplace(make_pair(x, min(S.top().second, x)));
}

void pop(){
	S.pop();
}

int getMin(){
	return S.top().second;
}

int main(){
	scanf("%d", &n);
	int op;
	for(int i = 0; i < n; i++){
		scanf("%d", &op);
		if(op == 1){
			int x;
			scanf("%d", &x);
			push(x);
		}
		else if(op == 2){
			pop();
		}
		else{
			printf("%d\n", getMin());
		}
	}
	return 0;
}
