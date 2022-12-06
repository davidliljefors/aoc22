#include "Common.h"

namespace d5 {

struct command
{
	i32 amount{};
	i32 from{};
	i32 to{};
};

auto parse_command(std::string_view line) -> command {
	const auto numbers = line 
		| views::split(' ')
		| views::drop(1)
		| views::stride(2) 
		| views::transform([](auto subrange) { return subrange | ranges::to_vector; })
		| ranges::to_vector;

	return { 
		.amount = to_int<i32>(numbers.at(0)), 
		.from = to_int<i32>(numbers.at(1))-1,
		.to = to_int<i32>(numbers.at(2))-1 
	};
}

using Piles = std::array<std::vector<char>, 9>;

void run_command_9000(command com, Piles& piles)
{
	for (i32 i = 0; i < com.amount; ++i)
	{
		const auto val = piles.at(com.from).back();
		piles.at(com.from).pop_back();
		piles.at(com.to).push_back(val);
	}
}

void run_command_9001(command com, Piles& piles)
{
	auto& source = piles.at(com.from);
	auto& dest = piles.at(com.to);

	std::copy(
		source.end() - com.amount,
		source.end(),
		std::back_inserter(dest)
	);

	source.resize(source.size() - com.amount);
}

std::string write_top_crates(Piles const& piles)
{
	std::string top_crates;
	for (auto& pile : piles)
	{
		top_crates.push_back(pile.back());
	}
	return top_crates;
}

Piles parse_piles(std::vector<std::string> input)
{
	Piles piles;

	const auto size = ranges::size(input);
	const auto crates = input | views::take_exactly(size - 1);
	
	for (auto crate : crates)
	{
		auto elems = crate
			| views::drop(1)
			| views::stride(4)
			| views::enumerate;

		for (auto pair : elems)
		{
			if (std::isalpha(pair.second))
			{
				piles.at(pair.first).push_back(pair.second);
			}
		}
	}

	for (auto& pile : piles)
	{
		ranges::reverse(pile);
	}

	return piles;
}

std::string part1()
{
	const std::vector<std::string> lines = read_lines("input/day5.txt");
	auto parts = lines 
		| views::split("") 
		| views::transform([](auto subrange) { return subrange | ranges::to_vector; }) 
		| ranges::to_vector;
	
	auto piles = parse_piles( parts.at(0) );
	const auto commands = parts.at(1) | views::transform(parse_command);

	for (auto c : commands)
	{
		run_command_9000(c, piles);
	}

	return write_top_crates(piles);
}

std::string part2()
{
	const std::vector<std::string> lines = read_lines("input/day5.txt");
	auto parts = lines 
		| views::split("")
		| views::transform([](auto subrange) { return subrange | ranges::to_vector; })
		| ranges::to_vector;

	auto piles = parse_piles(parts.at(0));
	const auto commands = parts.at(1) | views::transform(parse_command);

	for (auto c : commands)
	{
		run_command_9001(c, piles);
	}

	return write_top_crates(piles);
}

}

int main()
{
	fmt::print("Day 5 part 1 {}\n", d5::part1());
	fmt::print("Day 5 part 2 {}\n", d5::part2());

	return 0;
};