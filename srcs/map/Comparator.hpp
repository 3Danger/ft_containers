namespace ft
{
	template<typename T>
	struct less
	{
		bool operator()(const T &a, const T &b)
		{
			return a < b;
		}
	};
	template<typename T>
	struct greater
	{
		bool operator()(const T &a, const T &b)
		{
			return a > b;
		}
	};

} // namespace ft