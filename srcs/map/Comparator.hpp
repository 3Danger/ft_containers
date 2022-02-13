namespace ft
{
	template<typename T>
	struct less
	{
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;
		bool operator()(const T &a, const T &b)
		{
			return a < b;
		}
	};
	template<typename T>
	struct greater
	{
		typedef bool result_type;
		typedef T first_argument_type;
		typedef T second_argument_type;
		bool operator()(const T &a, const T &b)
		{
			return a > b;
		}
	};

} // namespace ft