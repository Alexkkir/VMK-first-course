#include <bits/stdc++.h>
using namespace std;

const unsigned PRIMARY = 73;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);

    string str;
    cin >> str;
    unsigned size = str.size();

    vector<unsigned> ptab(size, 1);
    for(unsigned i = 1; i < size; ++i)
        ptab[i] = ptab[i-1]*PRIMARY;

    vector<unsigned> htab(size+1, 0);
    for (unsigned i = 1; i <= size; i++)
        htab[i] = htab[i-1] + (str[i-1]-'A'+1)*ptab[i-1];

    for(unsigned len = 1; len < size + 1; ++len) {
        unsigned curr = 0;
        unsigned hs2 = htab[curr + len] - htab[curr];
        unsigned hs1 = hs2;
        bool equel = false;
        while(hs1 == hs2) {
            if(size - curr < len) {
                equel = true;
                break;
            }
            hs1 = hs2 * ptab[len];
            curr += len;
            if(size - curr < len) {
                unsigned l = size - curr;
                hs1 = htab[curr - len + l] - htab[curr - len];
                hs1 *= ptab[len];
                hs2 = htab[curr + l] - htab[curr];
            }
            else
                hs2 = htab[curr + len] - htab[curr];
        }

        if(equel) {
            cout << len;
            break;
        }

    }

    return 0;
}