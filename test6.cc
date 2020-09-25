#include <stdlib.h>   // rand, srand
#include <time.h>     // time
#include <algorithm>  // random_shuffle
#include <iostream>
#include <vector>

using namespace std;

#define U_INT unsigned int

void p_arr(vector<U_INT> &tb)
{
    for (int i = tb.size() - 1; i >= 0; i--)
        printf("%u, ", tb[i]);
    printf("\n--------------------\n");
}

int singleNumber(vector<U_INT> &nums, U_INT r)
{
    // N is the size of counter
    U_INT N = 32 - __builtin_clz(r + 1);
    // array of counters
    vector<U_INT> cnt_arr(N);

    for (size_t i = 0; i < nums.size(); i++) {
        // compute the value of all counter
        // x_j = x_j ^ (x_j-1 & x_j-2 & ... & x_0 & nums[i])
        for (int j = N - 1; j >= 0; j--) {
            U_INT tmp = nums[i];
            for (int z = j - 1; z >= 0; z--) {
                tmp &= cnt_arr[z];
            }
            cnt_arr[j] ^= tmp;
        }

        // compute the value of mask
        U_INT mask = 0xffffffff;
        U_INT one = 0x1;
        for (U_INT j = 0; j < N; j++) {
            if ((one & r) != 0)
                mask &= cnt_arr[j];
            else
                mask &= (~cnt_arr[j]);
            one = one << 1;
        }
        mask = ~mask;

        // bit-wise & mask
        for (int j = N - 1; j >= 0; j--) {
            cnt_arr[j] &= mask;
        }
    }
    return cnt_arr[0];
}

int main()
{
    // r is the num of times a number appears
    U_INT r = 7;

    vector<U_INT> vec;
    srand(time(NULL));

    // generate a number that appears r times
    U_INT num = rand() % 16;
    int times = r;
    while (times--) {
        vec.push_back(num);
    }

    // generate a number that appears one time
    U_INT ans = (num + 1000) % 16;
    vec.push_back(ans);

    // shuffle
    random_shuffle(vec.begin(), vec.end());

    // print
    p_arr(vec);

    cout << "res: " << singleNumber(vec, r) << endl;
    cout << "ans: " << ans << endl;
    return 0;
}
