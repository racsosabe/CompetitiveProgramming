#include<bits/stdc++.h>
using namespace::std;

const int N = 200000 + 5;
const int E = 62;

int n;
int q;
char s[N];
int st[4 * N];
int cnt[E][4 * N];

int get(char c){
	if(isdigit(c)) return c - '0';
	return 10 + (c <= 'Z' ? c - 'A' : 26 + c - 'a');
}

void build(int pos = 1, int l = 1, int r = n){
	if(l == r){
		st[pos] = 1;
		cnt[get(s[l])][pos] += 1;
		return;
	}
	int mi = (l + r) / 2;
	build(2 * pos, l, mi);
	build(2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
	for(int i = 0; i < E; i++) cnt[i][pos] = cnt[i][2 * pos] + cnt[i][2 * pos + 1];
}

void update(int x, int y, int z, int pos = 1, int l = 1, int r = n){
	if(y < l or r < x or x > y) return;
	if(cnt[z][pos] == 0) return;
	if(l == r){
		cnt[z][pos] = 0;
		st[pos] = 0;
		return;
	}
	int mi = (l + r) / 2;
	update(x, y, z, 2 * pos, l, mi);
	update(x, y, z, 2 * pos + 1, mi + 1, r);
	st[pos] = st[2 * pos] + st[2 * pos + 1];
	for(int i = 0; i < E; i++) cnt[i][pos] = cnt[i][2 * pos] + cnt[i][2 * pos + 1];
}

int query(int x, int pos = 1, int l = 1, int r = n){
	if(l == r) return st[pos];
	int mi = (l + r) / 2;
	if(x <= mi) return query(x, 2 * pos, l, mi);
	else return query(x, 2 * pos + 1, mi + 1, r);
}

int getPos(int k, int pos = 1, int l = 1, int r = n){
	if(l == r) return l;
	int mi = (l + r) / 2;
	if(st[2 * pos] >= k) return getPos(k, 2 * pos, l, mi);
	return getPos(k - st[2 * pos], 2 * pos + 1, mi + 1, r);
}

int main(){
	scanf("%d %d", &n, &q);
	scanf("%s", s + 1);
	build();
	int l, r;
	while(q--){
		scanf("%d %d", &l, &r);
		char c = getchar();
		while(!isalpha(c) and !isdigit(c)) c = getchar();
		l = getPos(l);
		r = getPos(r);
		int x = get(c);
		update(l, r, x);
	}
	for(int i = 1; i <= n; i++){
		if(query(i)) putchar(s[i]);
	}
	putchar('\n');
	return 0;
}
