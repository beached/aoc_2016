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
#include <cstdint>
#include <numeric>

#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2016 {
		namespace day_07 {
			constexpr bool valid_sequence( daw::string_view sv ) noexcept {
				if( sv.size( ) < 4 ) {
					return false;
				}
				return sv[0] == sv[3] and sv[1] == sv[2] and sv[0] != sv[1] and
				       sv[2] != sv[3];
			}

			constexpr bool is_palindrome( daw::string_view sv ) noexcept {
				while( sv.size( ) >= 4 ) {
					if( valid_sequence( sv ) ) {
						return true;
					}
					sv.remove_prefix( );
				}
				return false;
			}

			constexpr size_t is_valid_ipv7( daw::string_view part0,
			                                daw::string_view part1,
			                                daw::string_view part2 ) noexcept {
				auto const p0 = is_palindrome( part0 );
				auto const p1 = is_palindrome( part1 );
				auto const p2 = is_palindrome( part2 );
				return !p1 and ( p0 or p2 ) ? 1U : 0U;
			}

			constexpr size_t count_valid_ipv7( daw::string_view sv ) noexcept {
				size_t result = 0;
				while( !sv.empty( ) ) {
					auto p0 = sv.pop_front( "[" );
					sv.remove_prefix( );
					auto p1 = sv.pop_front( "]" );
					sv.remove_prefix( );
					auto p2 = sv.substr( 0, sv.find( '[' ) );
					result += is_valid_ipv7( p0, p1, p2 );
				}
				return result;
			}

			template<size_t N>
			constexpr size_t
			count_valid_ipv7( std::array<daw::string_view, N> arry ) noexcept {
				return std::accumulate( begin( arry ), end( arry ), 0ULL,
				                        []( size_t r, daw::string_view sv ) {
					                        return r + count_valid_ipv7( sv );
				                        } );
			}
		} // namespace daw_07
	}   // namespace aoc_2016
} // namespace daw
