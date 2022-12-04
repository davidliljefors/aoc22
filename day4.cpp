#include "Common.h"

namespace d4 {

using Range = std::pair<int, int>;

auto parse_line(std::string_view s) -> std::pair<Range, Range>
{
	auto parse_pair = [](std::string_view pair) -> Range
	{
		auto [first, second] = split_at(pair, '-');
		return { to_int<i32>(first), to_int<i32>(second) };
	};

	auto [first, second] = split_at(s, ',');
	return { parse_pair(first), parse_pair(second) };
}

auto is_range_in_range(std::pair<Range, Range> ranges) -> bool
{
	const auto test = [](Range left, Range right)
	{
		auto const& [leftMin, leftMax] = left;
		auto const& [rightMin, rightMax] = right;

		return leftMin >= rightMin
			&& leftMax <= rightMax;
	};

	auto const& [left, right] = ranges;
	return test(left, right) || test(right, left);
}

auto is_range_overlap(std::pair<Range, Range> ranges) -> bool
{
	auto const& [left, right] = ranges;
	auto const& [leftMin, leftMax] = left;
	auto const& [rightMin, rightMax] = right;

	return leftMax >= rightMin
	   && rightMax >= leftMin;
}

i32 part1()
{
	const std::vector<std::string> lines = ReadLines("input/day4.txt");
	return ranges::count_if(lines, is_range_in_range, parse_line);
}

i32 part2()
{
	const std::vector<std::string> lines = ReadLines("input/day4.txt");
	return ranges::count_if(lines, is_range_overlap, parse_line);
}

}

int main()
{
	fmt::print("Day 4 part 1 {}\n", d4::part1());
	fmt::print("Day 4 part 2 {}\n", d4::part2());

	return 0;
};