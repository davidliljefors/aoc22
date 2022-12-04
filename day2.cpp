
#include "Common.h"

namespace d2 {

constexpr i32 Win = 6;
constexpr i32 Draw = 3;

const auto score_fn1 = [](std::string const& s)
{
	const i32 opponent = s.at(0) - 'A' + 1;
	const i32 player = s.at(2) - 'X' + 1;

	const auto diff = player - opponent;
	if (diff == 0)
	{
		return player + Draw;
	}
	if (diff == 1 || diff == -2)
	{
		return player + Win;
	}
	return player;
};

const auto score_fn2 = [](std::string const& s)
{
	enum class outcomes : char {
		Lose = 'X',
		Draw = 'Y',
		Win = 'Z'
	};

	const i32 opponent = s.at(0) - 'A';
	const outcomes outcome = outcomes(s.at(2));

	if (outcome == outcomes::Lose)
	{
		const auto player = positive_modulo(opponent - 1, 3) + 1;
		return player;
	}
	if (outcome == outcomes::Draw)
	{
		const auto player = opponent + 1;
		return player + Draw;
	}
	if (outcome == outcomes::Win)
	{
		const auto player = positive_modulo(opponent + 1, 3) + 1;
		return player + Win;
	}

	return 0;
};

i32 part1()
{
	const std::vector<std::string> lines = ReadLines("input/day2.txt");
	return ranges::accumulate(lines, 0, ops::plus, score_fn1);
}

i32 part2()
{
	const std::vector<std::string> lines = ReadLines("input/day2.txt");
	return ranges::accumulate(lines, 0, ops::plus, score_fn2);
}

}

//int main()
//{
//
//	fmt::print( "Day 2 part 1 {}\n", d2::part1() );
//	fmt::print( "Day 2 part 2 {}\n", d2::part2() );
//
//	return 0;
//};