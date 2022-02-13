#pragma once
#include <utility>


namespace ft
{
	template <typename T1, typename T2>
	struct pair
	{
		typedef T1 first_type;
		typedef T2 second_type;
		T1 first {};
		T2 second {};
		pair();
		pair(const pair&value){first = value.first; second = value.second;}
		pair(pair&&value){first = value.first; second = value.second;}
		pair(const std::pair<T1, T2> &stdPair): first(stdPair.first), second(stdPair.second){}
		constexpr pair( const T1& Val1, const T2& Val2) :first(Val1), second(Val2){}    
		pair& operator=(const pair& p) {first = p.first; second = p.second;}
		pair& operator=(pair&& p) noexcept {*this = p;}
		
		void swap(pair& p){
			T1 t1 = first;
			T2 t2 = second;
			
			first = p.first;
			second = p.second;
			
			p.first = t1;
			p.second = t2;
		}
		
		bool operator == (const pair & oth) const {return first == oth.first;}
		bool operator != (const pair & oth) const {return first != oth.first;}
		bool operator >= (const pair & oth) const {return first >= oth.first;}
		bool operator <= (const pair & oth) const {return first <= oth.first;}
		bool operator > (const pair & oth) const {return first > oth.first;}
		bool operator < (const pair & oth) const {return first < oth.first;}
	};    
} // namespace ft
