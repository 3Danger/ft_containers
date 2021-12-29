#include <iostream>
#include <stack>
#include <deque>

int main(){
	std::stack<int> st;

	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	std::cout << st.top() << std::endl;
	st.pop();
	std::cout << st.top() << std::endl;
}