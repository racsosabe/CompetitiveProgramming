#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;

int n;
int m;
char s[N];
vector<int> A, B, C;
vector<pair<int, int>> ans;

void solve(){
	int cntA = 0, cntB = 0, cntC = 0;
	for(int i = 1; i <= m; i++){
		if(s[i] == 'A') cntA++;
		if(s[i] == 'B') cntB++;
		if(s[i] == 'C') cntC++;
	}
	if(cntA - cntB + cntC < 0 or (cntA - cntB + cntC) & 1){
		puts("NO");
		return;
	}
	int Z = (cntA - cntB + cntC) / 2;
	int X = cntA - Z;
	int Y = cntC - Z;
	if(X < 0 or Y < 0){
		puts("NO");
		return;
	}
	for(int i = 1; i <= m; i++){
		if(s[i] == 'A') A.emplace_back(i);
		if(s[i] == 'B') B.emplace_back(i);
		if(s[i] == 'C') C.emplace_back(i);
	}
	int at = 0;
	for(int i = 0; i < Y; i++){
		while(at < C.size() and C[at] < B[i]) at++;
		if(at == C.size()){
			puts("NO");
			return;
		}
		ans.emplace_back(make_pair(B[i], C[at]));
		C[at++] = -1;
	}
	at = A.size() - 1;
	for(int i = B.size() - 1; i >= Y; i--){
		while(at >= 0 and B[i] < A[at]) at--;
		if(at == -1){
			puts("NO");
			return;
		}
		ans.emplace_back(make_pair(A[at], B[i]));
		A[at--] = -1;
	}
	at = 0;
	for(int i = 0; i < A.size(); i++){
		if(A[i] == -1) continue;
		while(at < C.size() and (C[at] == -1 or C[at] < A[i])) at++;
		if(at == C.size()){
			puts("NO");
			return;
		}
		ans.emplace_back(make_pair(A[i], C[at]));
		C[at] = -1;
	}
	if(ans.size() ^ n){
		puts("NO");
		return;
	}
	puts("YES");
	for(auto e : ans){
		printf("%d %d\n", e.first, e.second);
	}
}

int main(){
	scanf("%d", &n);
	m = n << 1;
	scanf("%s", s + 1);
	solve();
	return 0;
}
