#include <stdlib.h>  // rand, srand
#include <time.h>    // time
#include <cassert>
#include <fstream>
#include <iostream>
#include <vector>
#include "jemalloc/cpucycles.h"
#include "jemalloc/div.h"

using namespace std;

// according to div.h the maximum value is as follow
#define FAST_DIV_MAX ((uint64_t)(1) << 32) - 1

int main()
{
    srand(time(NULL));
    size_t N = 10000;  // size of test case

    vector<uint64_t> arr;
    vector<uint64_t> fastdiv_res;
    vector<uint64_t> nordiv_res;

    // generate n
    while (N--) {
        arr.push_back(rand() % FAST_DIV_MAX);
    }

    for (size_t i = 0; i < arr.size(); i++) {
        uint64_t start, finish;  // cycle counter

        uint64_t n = arr[i];
        uint64_t d = rand() % FAST_DIV_MAX;

        div_info_t DIV;
        div_init(&DIV, d);

        // compute
        start = cpucycles();
        uint64_t res1 = div_compute(&DIV, n);
        finish = cpucycles();

        // store result
        fastdiv_res.push_back(finish - start);

        // compute
        start = cpucycles();
        uint64_t res2 = n / d;
        finish = cpucycles();

        // store result
        nordiv_res.push_back(finish - start);

        if (res1 != res2)
            cout << "Error (n=" << n << ", d=" << d << " res=" << res1
                 << " res2=" << res2 << endl;
    }

    ofstream fastdiv_fs;
    fastdiv_fs.open("div.data");
    for (size_t i = 0; i < fastdiv_res.size(); i++) {
        fastdiv_fs << i << " " << fastdiv_res[i] << " " << nordiv_res[i]
                   << endl;
    }
    fastdiv_fs.close();
}
