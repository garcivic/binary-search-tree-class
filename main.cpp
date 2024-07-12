#include <cmath>
#include <iostream>
#include <iomanip>
#include <set>
#include <vector>

//Files we are testing -------------------------------------------------------
#include "includes/bst/bst.h"
#include "includes/bst_functions/bst_functions.h"

int random(int low, int high)
{
  //call srand in main if you want better random numbers.
  return static_cast<int>(low + (rand() % static_cast<int>((high - low + 1))));
}
bool basic_random_test(bool debug = true)
{
    return true;
}
bool basic_test_bst(bool debug = false)
{
    return true;
}
int main()
{
    int test_index = 0;
    bool test_results[] = { basic_random_test(), basic_test_bst()};
    for (auto& result : test_results)
    {
        if (!result)
            std::cout << "\nTEST:" << test_index << " FAILED.\n";
        test_index++;
    }
    return 0;
}