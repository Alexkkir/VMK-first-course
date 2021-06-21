#include <iostream>
#include <unordered_set>
#include <set>

using namespace  std;
using std::unordered_set;
using std::set;

int main() {
    set<long long> nums;

    long long p1, p2, p3, n;
    scanf("%lld%lld%lld%lld", &p1, &p2, &p3, &n);

    nums = {1, p1, p2, p3};

    auto index = 0;
    for (auto elem : nums) {
        index++;
//        printf("i: %lld elem: %lld\n", index, elem);
        if (index == n) {
            printf("%lld", elem);
            return 0;
        }
        else {
            nums.insert(elem * p1);
            nums.insert(elem * p2);
            nums.insert(elem * p3);
        }
    }
    return 0;
}
