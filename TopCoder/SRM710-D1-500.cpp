#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
	Author: Racso Galvan

	Idea:
		- Interesting Game Theory problem.

		- Consider instawins first:

		  1) XOR of all stones is 0, then we can take the

		     magic one and keep the victory condition.

		  2) All piles have 1 stone, then we can take the

		     magic one and change or keep victory condition

		     according to parity.

		- Now consider restrictive scenarios:

		  1) If max(a[i]) >= 2 and XOR isn't 0 then we can't 
		  
		     take magic stone since both Normal and Misere Nim 
		     
		     winning conditions fulfill, thus we will lose.

		- With all the above, now what to do?

		  We are left with a situation in which XOR != 0 and

		  max(a[i]) >= 2 so we are not willing to take magic

		  stone. So, we just want to know who will take it.

		- Let's notice that now if a player makes a move so

		  that any instawin condition fulfills then it will

		  lose. Now we can analyze the game just with the

		  n piles and in a Misere game in which losing conditions

		  are the instawins.

		- The left is stated as in cgy4ever's blog about the round

		  in gilcu3's sub-comment.

		- Complexity: O(n)
*/

class MagicNim {
public:
	string findWinner(vector <int> a) {
		int n = a.size();
		int maximo = 0;
		int XOR = 0;
		for(int i=0; i<n; i++){
			maximo = max(maximo,a[i]);
			XOR ^= a[i];
		}
		if(XOR == 0 or maximo == 1){
			return "Alice";
		}
		int maximomisere = 0;
		for(int i=0; i<n; i++){
			maximomisere = max(maximomisere,(a[i]>>1));
		}
		int mirrormove = XOR&1;
		XOR >>= 1;
		if(maximomisere >= 2 and XOR == 0){
			if(mirrormove) return "Bob";
			else return "Alice";
		}
		if(maximomisere == 1 and XOR == 1){
			if(mirrormove) return "Alice";
			else return "Bob";
		}
		return "Alice";
	}
};
