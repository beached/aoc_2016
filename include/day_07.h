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

#include <daw/daw_algorithm.h>
#include <daw/daw_string_view.h>

namespace daw {
	namespace aoc_2016 {
		namespace day_07 {
			constexpr bool valid_sequence( daw::string_view sv ) noexcept {
				if( sv.size( ) < 4 ) {
					return false;
				}
				return sv[0] == sv[3] and sv[1] == sv[2] and sv[0] != sv[1];
			}

			constexpr bool all_unique( daw::string_view sv, daw::string_view const sv2 ) {
				while( sv.size( ) > 1U ) {
					if( sv.find( sv.front( ), 1 ) != daw::string_view::npos or
					    sv2.find( sv.front( ) ) != daw::string_view::npos ) {
						return false;
					}
					sv.remove_prefix( );
				}
				return true;
			}

			constexpr bool has_abba( daw::string_view sv ) noexcept {
				bool found = false;
				size_t pos = 0;
				while( ( sv.size( ) - pos ) >= 4 ) {
					if( valid_sequence( sv.substr( pos ) ) ) {
						found = true;
						break;
					}
					++pos;
				}
				if( not found ) {
					return false;
				}
				auto p0 = sv.substr( 0, pos );
				auto p1 = sv.substr( pos + 4 );
				return all_unique( p0, p1 ) and all_unique( p1, p0 );
			}

			constexpr daw::string_view next_ip( daw::string_view &sv ) {
				auto pos0 = sv.find( '[' );
				if( pos0 == daw::string_view::npos ) { 
					return {};
				}
				sv.remove_prefix( pos0 );
				if( sv.empty( ) ) {
					return {};
				}
				sv.remove_prefix( );
				if( sv.empty( ) ) {
					return {};
				}
				pos0 = sv.find( ']' );
				if( pos0 == daw::string_view::npos ) {
					return {};
				}
				auto result = sv.pop_front( pos0 );
				sv.remove_prefix( );
				return result;
			}
			constexpr bool is_valid_ipv7( daw::string_view sv ) noexcept {
				bool result = true;
				auto p = next_ip( sv );
				if( p.empty( ) ) { return false; }
				while( result and !p.empty( ) ) {
					result = !has_abba( p );
					p = next_ip( sv );
				}
				return result;
			}

			template<size_t N>
			constexpr size_t count_valid_ipv7( std::array<daw::string_view, N> arry ) noexcept {
				return daw::algorithm::accumulate( begin( arry ), end( arry ), 0ULL,
				                        []( size_t r, daw::string_view sv ) { return r + ( is_valid_ipv7( sv ) ? 1U : 0U ); } );
			}
		} // namespace day_07
	}   // namespace aoc_2016
} // namespace daw
