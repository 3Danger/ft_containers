//
// Created by Rasul on 14.01.2022.
//

#ifndef CONTAINERYYY_SFINAE_H
#define CONTAINERYYY_SFINAE_H

#include <iterator>

namespace ft {
//* ENABLE IF
	template<bool, typename T>
	struct enable_if {
	};
	template<typename T>
	struct enable_if<true, T> {
		typedef T type;
	};

	template<typename T, typename U>
	struct is_same{static const bool value = false;};

	template <typename T>
	struct is_same<T, T>{static const bool value = true;};

	template <typename iterator_category>
	struct is_random_access_iterator{
		static const bool value = is_same<iterator_category, std::random_access_iterator_tag>::value;
	};
	template <typename iterator_category>
	struct is_input_iterator{
		static const bool value = is_same<iterator_category, std::input_iterator_tag>::value;
	};
	template <typename iterator_category>
	struct is_forward_iteraor{
		static const bool value = is_same<iterator_category, std::forward_iterator_tag>::value;
	};
	template <typename iterator_category>
	struct is_bidirectional_iterator{
		static const bool value = is_same<iterator_category, std::bidirectional_iterator_tag>::value;
	};


// is integer
	template<typename T>
	struct is_integer {
		static const bool value = false;
	};
	template<>
	struct is_integer<int> {
		static const bool value = true;
	};
	template<>
	struct is_integer<unsigned int> {
		static const bool value = true;
	};
	template<>
	struct is_integer<char> {
		static const bool value = true;
	};
	template<>
	struct is_integer<unsigned char> {
		static const bool value = true;
	};
	template<>
	struct is_integer<long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<unsigned long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<long long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<unsigned long long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const int> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const unsigned int> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const char> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const unsigned char> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const unsigned long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const long long> {
		static const bool value = true;
	};
	template<>
	struct is_integer<const unsigned long long> {
		static const bool value = true;
	};


// is floating num
	template<typename T>
	struct is_float {
		static const bool value = false;
	};
	template<>
	struct is_float<float> {
		static const bool value = true;
	};
	template<>
	struct is_float<double> {
		static const bool value = true;
	};
	template<>
	struct is_float<long double> {
		static const bool value = true;
	};
	template<>
	struct is_float<const float> {
		static const bool value = true;
	};
	template<>
	struct is_float<const double> {
		static const bool value = true;
	};
	template<>
	struct is_float<const long double> {
		static const bool value = true;
	};

//	template <typename T>
//	struct is_arithmetic_iterator

}




#endif //CONTAINERYYY_SFINAE_H
