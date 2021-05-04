#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int a[N];
int ft[N];
int last[N];

void update(int pos, int val){
	pos++;
	while(pos <= n){
		ft[pos] += val;
		pos += (-pos) & pos;
	}
}

int getSum(int pos){
	int res = 0;
	pos++;
	while(pos > 0){
		res += ft[pos];
		pos &= pos - 1;
	}
	return res;
}

long long solve(){
	memset(last, -1, sizeof last);
	int cnt = 0;
	long long ans = 0;
	for(int i = 0; i < n; i++){
		int l = last[a[i]];
		ans += cnt - getSum(l);
		if(last[a[i]] == -1){
			cnt += 1;
			last[a[i]] = i;
			update(i, 1);
		}
		else{
			update(last[a[i]], -1);
			update(i, 1);
			last[a[i]] = i;
		}
	}
	return ans;
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; i++) scanf("%d", a + i);
	printf("%lld\n", solve());
	return 0;
}
