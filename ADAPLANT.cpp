#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

struct MinStack{
	stack< pair<int, int> > S;
	void push(int x){
		if(S.empty()) S.emplace(make_pair(x, x));
		else S.emplace(make_pair(x, min(S.top().second, x)));
	}

	void pop(){
		S.pop();
	}

	int top(){
		return S.top().first;
	}

	bool empty(){
		return S.empty();
	}

	int getMin(){
		return S.empty() ? INT_MAX : S.top().second;
	}
};

struct MinQueue{
	MinStack in, out;

	void push(int x){
		in.push(x);
	}

	void pop(){
		if(out.empty()){
			while(!in.empty()){
				int x = in.top();
				out.push(x);
				in.pop();
			}
		}
		out.pop();
	}

	int getMin(){
		return min(in.getMin(), out.getMin());
	}
};

int n;
int k;
int a[N];

int main(){
	int t;
	scanf("%d", &t);
	while(t--){
		scanf("%d %d", &n, &k);
		k += 2;
		for(int i = 1; i <= n; i++) scanf("%d", a + i);
		int ans = -1;
		MinQueue Q1, Q2;
		for(int i = 1; i < k and i <= n; i++){
			Q1.push(a[i]);
			Q2.push(-a[i]);
		}
		for(int i = k; i <= n; i++){
			Q1.push(a[i]);
			Q2.push(-a[i]);
			if(i - k > 0){
				Q1.pop();
				Q2.pop();
			}
			ans = max(ans, -Q2.getMin() - Q1.getMin());
		}
		ans = max(ans, -Q2.getMin() - Q1.getMin());
		printf("%d\n", ans);
	}
	return 0;
}
