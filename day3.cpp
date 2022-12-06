
#include "Common.h"

namespace d3 {

const auto split_string_half = [](std::string const& s)
{
	const auto half_size = s.size() / 2;
	return std::vector{
		s.substr(0, half_size),
		s.substr(half_size, std::string::npos)
	};
};


auto get_common_item(std::vector<std::string> backpacks)
{
	std::string prev = backpacks.at(0);
	ranges::sort(prev);
	std::string next;

	for (auto& s : backpacks | views::tail)
	{
		next.clear();
		ranges::sort(s);
		ranges::set_intersection(prev, s, std::back_inserter(next));
		std::swap(prev, next);
	}

	return prev.at(0);
};

const auto to_priority = [](char c)
{
	if (c >= 'a' && c <= 'z')
	{
		return c - 'a' + 1;
	}
	if (c >= 'A' && c <= 'Z')
	{
		return c - 'A' + 27;
	}

	throw std::runtime_error("err");
};

i32 part1()
{
	const std::vector<std::string> lines = read_lines("input/day3.txt");

	auto range = lines
		| views::transform(split_string_half)
		| views::transform(get_common_item)
		| views::transform(to_priority);

	return ranges::accumulate(range, 0);
}

i32 part2()
{
	const std::vector<std::string> lines = read_lines("input/day3.txt");

	auto range = lines
		| views::chunk(3)
		| views::transform([](auto r) { return ranges::to_vector(r); })
		| views::transform(get_common_item)
		| views::transform(to_priority);

	return ranges::accumulate(range, 0);
}

}

//int main()
//{
//	fmt::print( "Day 3 part 1 {}\n", d3::part1() );
//	fmt::print( "Day 3 part 2 {}\n", d3::part2() );
//
//	return 0;
//};