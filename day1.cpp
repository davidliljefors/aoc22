
#include "Common.h"

namespace d1 {

auto to_int = [](std::string const& s) { return std::stoi(s); };

i32 part1()
{
	const std::vector<std::string> lines = ReadLines("input/day1.txt");

	auto range = lines
		| views::split("")
		| views::transform([](auto subrange) { return ranges::accumulate(subrange, 0, ops::plus, to_int); });

	return ranges::max(range);
}

i32 part2()
{
	const std::vector<std::string> lines = ReadLines("input/day1.txt");

	auto range = lines
		| views::split("")
		| views::transform([](auto subrange) { return ranges::accumulate(subrange, 0, ops::plus, to_int); });

	std::vector<int> top3;
	top3.resize(3);

	ranges::partial_sort_copy(range, top3, std::greater{});

	return ranges::accumulate(top3, 0);
}

}

//int main()
//{
//	
//	fmt::print( "Day 1 part 1 {}\n", d1::part1() );
//	fmt::print( "Day 1 part 2 {}\n", d1::part2() );
//
//	return 0;
//}