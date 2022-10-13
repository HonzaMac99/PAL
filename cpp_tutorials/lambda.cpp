#include <iostream>
#include <vector>
#include <algorithm>

int main(int argc, char* argv[])
{
    int d = 7, e = 3;
    std::vector<int> v{2, 3, 7, 14, 23};
    
    // lambda functions: [cc](p){fd}
    // to pass all variables to lambda, use:
    //  pass by value     ... [=](...){...}
    //  pass by reference ... [&](...){...}
    std::for_each(v.begin(), v.end(), [&d, &e](int x){
        std::cout << "var d = " << d << " ,e = " << e << std::endl;
        std::string is_div = (x%d == 0) ? "" : "not ";
        std::cout << " -> " << x << " is " << is_div << "divisible by " << d << std::endl;
    });
    return 0;
}
