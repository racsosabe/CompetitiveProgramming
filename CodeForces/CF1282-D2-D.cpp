#include<bits/stdc++.h>
using namespace::std;

int ask(string s) {
	printf("%s\n", s.c_str());
	fflush(stdout);
	int x;
	scanf("%d", &x);
	if(x == 0 or x == -1) exit(0);
	return x;
}

int main() {
	int r1 = ask(string(300, 'a'));
	int r2 = ask(string(300, 'b'));
	int n = 600 - r1 - r2;
	string s(n, 'a');
	int b = r1 - 300 + n;
	int last = b;
	for(int i = 0; i + 1 < n; i++) {
		string cur = s;
		cur[i] = 'b';
		int dis = ask(cur);
		if(dis < last) {
			s = cur;
			last = dis;
		}
	}
	if(last) s.back() = 'b';
	int res = ask(s);
	assert(false);
	return 0;
}
