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

#include <array>
#include <iostream>

#include <daw/daw_string_view.h>

#include "day_01.h"

namespace daw::aoc_2016::day_01 {
	static constexpr daw::basic_string_view problem_input =
	  "L1,L5,R1,R3,L4,L5,R5,R1,L2,L2,L3,R4,L2,R3,R1,L2,R5,R3,"
	  "L4,R4,L3,R3,R3,L2,R1,L3,R2,L1,R4,L2,R4,L4,R5,L3,R1,R1,"
	  "L1,L3,L2,R1,R3,R2,L1,R4,L4,R2,L189,L4,R5,R3,L1,R47,R4,"
	  "R1,R3,L3,L3,L2,R70,L1,R4,R185,R5,L4,L5,R4,L1,L4,R5,L3,"
	  "R2,R3,L5,L3,R5,L1,R5,L4,R1,R2,L2,L5,L2,R4,L3,R5,R1,L5,"
	  "L4,L3,R4,L3,L4,L1,L5,L5,R5,L5,L2,L1,L2,L4,L1,L2,R3,R1,"
	  "R1,L2,L5,R2,L3,L5,L4,L2,L1,L2,R3,L1,L4,R3,R3,L2,R5,L1,"
	  "L3,L3,L3,L5,R5,R1,R2,L3,L2,R4,R1,R1,R3,R4,R3,L3,R3,L5,"
	  "R2,L2,R4,R5,L4,L3,L1,L5,L1,R1,R2,L1,R3,R4,R5,R2,R3,L2,"
	  "L1,L5";

}

int main( ) {
	constexpr auto day_01_p0 =
	  daw::aoc_2016::day_01::calc_dist( daw::aoc_2016::day_01::problem_input );
	std::cout << "Answer p0: " << day_01_p0 << '\n';

	auto day_01_p1 = daw::aoc_2016::day_01::calc_dup_dist(
	  daw::aoc_2016::day_01::problem_input );
	std::cout << "Answer p1: " << day_01_p1 << '\n';
}
