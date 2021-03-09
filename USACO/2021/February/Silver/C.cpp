#include<bits/stdc++.h>
using namespace::std;

const int N = 500 + 5;

int n;
int cur[N];
int a[N][N];
int carry[N];
int cur_min[N];

int add(int l, int r){
	int res = (r - l + 1) * (r - l + 2) / 2;
	int last_one = l - 1;
	for(int i = l; i <= r; i++){
		if(carry[i] == 1){
			int len = i - last_one - 1;
			res -= len * (len + 1) / 2;
			last_one = i;
		}
	}
	int len = r - last_one;
	res -= len * (len + 1) / 2;
	return res;
}

long long solve(){
	long long ans = 0LL;
	for(int c1 = 1; c1 <= n; c1++){
		for(int i = 1; i <= n; i++) cur_min[i] = 250;
		for(int c2 = c1; c2 <= n; c2++){
			for(int i = 1; i <= n; i++){
				cur_min[i] = min(cur_min[i], a[i][c2]);
				int val = cur_min[i];
				if(val > 100) carry[i] = 0;
				else if(val == 100) carry[i] = 1;
				else carry[i] = 2;
			}
			int L = 1, R;
			while(L <= n){
				while(L <= n and carry[L] == 2) L += 1;
				if(L > n) break;
				R = L;
				while(R <= n and carry[R] < 2) R += 1;
				ans += add(L, R - 1);
				L = R;
			}
		}
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 1; i <= n; i++){
		for(int j = 1; j <= n; j++){
			scanf("%d", &a[i][j]);
		}
	}
	printf("%lld\n", solve());
	return 0;
}
