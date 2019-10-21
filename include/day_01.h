// The MIT License (MIT)
//
// Copyright (c) 2019 Darrell Wright
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and / or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#pragma once

#include <array>
#include <cassert>
#include <cstddef>
#include <cstdint>
#include <numeric>
#include <optional>
#include <tuple>
#include <utility>

#include <daw/daw_algorithm.h>
#include <daw/daw_cxmath.h>
#include <daw/daw_parser_helper_sv.h>
#include <daw/daw_string_split_range.h>
#include <daw/daw_string_view.h>

namespace daw::aoc_2016::day_01 {
	template<typename Number>
	constexpr Number abs( Number n ) noexcept {
		if( n < 0 ) {
			return -n;
		}
		return n;
	}

	enum Directions { North, South, East, West };

	struct Movement {
		int x;
		int y;
		Directions left;
		Directions right;
	};

	static inline constexpr std::array move_table = {
	  Movement{0, 1, West, East}, Movement{0, -1, East, West},
	  Movement{1, 0, North, South}, Movement{-1, 0, South, North}};

	template<typename CharT, typename Traits, ptrdiff_t Extent>
	constexpr int32_t
	calc_dist( daw::basic_string_view<CharT, Traits, Extent> sv ) {
		int32_t pos_x = 0;
		int32_t pos_y = 0;
		Directions cur_dir = North;

		for( auto inst : daw::string_split_range<char>( sv, "," ) ) {
			switch( inst.front( ) ) {
			case 'R':
				cur_dir = move_table[cur_dir].right;
				break;
			case 'L':
				cur_dir = move_table[cur_dir].left;
				break;
			}
			auto const how_far =
			  daw::parser::parse_unsigned_int<int>( inst.substr( 1 ) );
			pos_x += move_table[cur_dir].x * how_far;
			pos_y += move_table[cur_dir].y * how_far;
		}

		return abs( pos_x ) + abs( pos_y );
	}

	template<size_t arry_dim>
	constexpr size_t coord( int32_t x, int32_t y ) {
		// 0,0 is at arry_dim/2, arry_dim/2
		x += static_cast<int32_t>( arry_dim / 2 );
		y += static_cast<int32_t>( arry_dim / 2 );
		assert( x >= 0 );
		assert( y >= 0 );
		return static_cast<size_t>( ( y * static_cast<int32_t>( arry_dim / 2 ) ) +
		                            x );
	};

	template<int32_t X0, int32_t X1, int32_t Y0, int32_t Y1>
	struct Grid {
		static_assert( X0 < X1 );
		static_assert( Y0 < Y1 );
		static constexpr int32_t min_x = X0;
		static constexpr int32_t max_x = X1;
		static constexpr int32_t min_y = Y0;
		static constexpr int32_t max_y = Y1;
		static constexpr int32_t width = max_x - min_x;
		static constexpr int32_t height = max_y - min_y;
		static_assert( width >= 2 );
		static_assert( height >= 2 );
		std::array<bool, width * height> grid{};

		constexpr Grid( ) noexcept = default;

		constexpr static size_t coord( int32_t x, int32_t y ) noexcept {
			auto pos = ( y - Y0 ) * width + ( x - X0 );
			assert( pos >= 0 );
			return static_cast<size_t>( pos );
		}

		constexpr bool &operator( )( int32_t x, int32_t y ) noexcept {
			return grid[coord( x, y )];
		}

		constexpr bool const &operator( )( int32_t x, int32_t y ) const noexcept {
			return grid[coord( x, y )];
		}
	};

	template<typename Grid>
	void show_array( Grid const &visited ) {
		for( auto x = visited.min_x; x < visited.max_x; ++x ) {
			for( auto y = visited.min_y; y < visited.max_y; ++y ) {
				if( visited( x, y ) ) {
					std::cout << '#';
				} else {
					std::cout << "·";
				}
			}
			std::cout << '\n';
		}
	}

	template<typename CharT, typename Traits, ptrdiff_t Extent>
	int32_t calc_dup_dist( daw::basic_string_view<CharT, Traits, Extent> sv ) {
		static_assert( Extent >= 0 );
		int32_t pos_x = 0;
		int32_t pos_y = 0;
		Directions cur_dir = North;

		constexpr int32_t arry_dim = static_cast<int32_t>( Extent );
		auto visited = Grid<( -arry_dim ), arry_dim, -arry_dim, arry_dim>( );
		visited( 0, 0 ) = true;

		for( auto inst : daw::string_split_range<char>( sv, "," ) ) {
			switch( inst.front( ) ) {
			case 'R':
				cur_dir = move_table[cur_dir].right;
				break;
			case 'L':
				cur_dir = move_table[cur_dir].left;
				break;
			}
			auto how_far = daw::parser::parse_unsigned_int<int>( inst.substr( 1 ) );
			if( move_table[cur_dir].x == 0 ) {
				// move along y
				while( how_far-- > 0 ) {
					pos_y += move_table[cur_dir].y;
					if( visited( pos_x, pos_y ) ) {
						show_array( visited );
						return abs( pos_x ) + abs( pos_y );
					}
					visited( pos_x, pos_y ) = true;
				}
			} else {
				// move along x
				while( how_far-- > 0 ) {
					pos_x += move_table[cur_dir].x;
					if( visited( pos_x, pos_y ) ) {
						show_array( visited );
						return abs( pos_x ) + abs( pos_y );
					}
					visited( pos_x, pos_y ) = true;
				}
			}
		}
		show_array( visited );
		std::abort( );
	}
} // namespace daw::aoc_2016::day_01
