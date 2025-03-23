#include <iostream>
#include <vector>

int main()
{
    std::cout << "hello world";

    std::vector<int> a;
    a.push_back(3);

    for(int e : a )
    {
        std::cout << e;
    }
}