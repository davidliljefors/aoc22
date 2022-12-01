#pragma once

#include <string>
#include <fstream>
#include <filesystem>

#include <range/v3/all.hpp>
#include <fmt/core.h>

#include "ops.h"

namespace views = ranges::views;

using u64 = std::uint64_t;
using i64 = std::int64_t;
using u32 = std::uint32_t;
using i32 = std::int32_t;

inline std::string ReadFile( std::string const& path )
{
	std::string content;

	if( std::filesystem::exists(path) )
	{
		std::fstream is( path, std::ios::in | std::ios::binary | std::ios::ate );
		const auto data_size = is.tellg();
		content.resize( data_size );
		is.seekg( 0, std::ios::beg );
		is.read( content.data(), data_size );

	}

	return content;
}

inline std::vector<std::string> ReadLines( std::string const& path )
{
	const std::string file = ReadFile( path );

	auto lines = views::split( file, '\n' ) | views::transform( []( auto range ) {
		auto c = range | views::common;
		const std::string s{ c.begin(), c.end() };
		return s;
	} );

	return ranges::to<std::vector>( lines );
}