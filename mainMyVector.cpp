#include <iostream>
#include "vector.hpp"
#include <vector>

int main(){
    typedef ft::vector<int>::iterator           t_iter;
    typedef ft::vector<int>::reverce_iterator   t_riter;


    ft::vector<int> vec;
    std::vector<int> svec;
    for(size_t i = 0; i < 10; i++)
        vec.push_back(i);
    
    t_iter beg = vec.begin();
    t_iter end = vec.end();
    t_riter rbeg = vec.rbegin();
    t_riter rend = vec.rend();

    while(rbeg != rend)
        std::cout << *rbeg++ << ", " << std::endl;
    std::cout << std::endl;

    while(beg != end)
        std::cout << *beg++ << ", " << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;
    std::cout << std::endl;

    svec.resize(15);
    std::copy(vec.begin(), vec.end(), svec.begin());
    std::cout << *svec.begin() << std::endl;

}