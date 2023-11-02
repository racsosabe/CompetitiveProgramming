#include<bits/stdc++.h>
using namespace::std;

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

const int N = 100000 + 5;

int n;
int k;
int h[N];
MinQueue Q1, Q2;

int check(int x){
	int maxi = -min(Q1.getMin(), -x);
	int mini = min(Q2.getMin(), x);
	return maxi - mini;
}

void solve(){
	vector< pair<int, int> > ans;
	int pos = 1;
	for(int i = 1; i <= n; i++){
		while(pos <= n and check(h[pos]) <= k){
			Q1.push(-h[pos]);
			Q2.push(h[pos]);
			pos += 1;
		}
		if(ans.empty() or ans[0].second - ans[0].first + 1 < pos - i){
			ans.clear();
			ans.emplace_back(make_pair(i, pos - 1));
		}
		else if(ans[0].second - ans[0].first + 1 == pos - i){
			ans.emplace_back(make_pair(i, pos - 1));
		}
		Q1.pop();
		Q2.pop();
	}
	printf("%d %d\n", ans[0].second - ans[0].first + 1, (int)ans.size());
	for(auto e : ans){
		printf("%d %d\n", e.first, e.second);
	}
}

int main(){
	scanf("%d %d", &n, &k);
	for(int i = 1; i <= n; i++) scanf("%d", h + i);
	solve();
	return 0;
}
