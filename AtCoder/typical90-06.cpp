#include<bits/stdc++.h>
using namespace::std;

const int N = 100000 + 5;

int n;
int k;
char s[N];

void solve(){
	set< pair<char, int> > S;
	for(int i = 0; i + k < n; i++){
		S.emplace(make_pair(s[i], i));
	}
	int pos = 0;
	for(int i = n - k; i < n; i++){
		S.emplace(make_pair(s[i], i));
		pair<char, int> cur = *S.begin();
		putchar(cur.first);
		while(pos <= cur.second){
			S.erase(make_pair(s[pos], pos));
			pos += 1;
		}
	}
	putchar('\n');
}

int main(){
	scanf("%d %d", &n, &k);
	scanf("%s", s);
	solve();
	return 0;
}
