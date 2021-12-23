/**
 * @file include/tmp/minint.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_MININT_H_
#define TMP_MININT_H_

#include "tmp/list.h"
#include "tmp/smath.h"
#include "tmp/cppcompat.h"
#include <stdint.h>

namespace tmp {

/**
 * Integer type of minimum size to store the given value.
 * @tparam BITS Number of BITS needing to be stored.
 *
 * @var type Type of minimum size.
 */
template<unsigned long long BITS, typename SIGN=unsigned>
struct minint_bits {
	enum {
		Bytes = BITS / 8,
		Check = Bytes * 8,
		result = BITS > Check ? Bytes + 1 : Bytes
	};
	
	template<unsigned long long b, typename s>
	struct types;
	template<unsigned long long b>
	struct types<b, signed>{
		// List of minimum type to store index-number of bytes
		typedef List<int8_t,  // 0
				List<int8_t,  // 1
				List<int16_t, // 2
				List<int32_t, // 3
				List<int32_t, // 4
				List<int64_t, // 5
				List<int64_t, // 6
				List<int64_t, // 7
				List<int64_t, // 8
				NIL
			> > > > > > > > > DataTypes;
	};
	template<unsigned long long b>
	struct types<b, unsigned>{
		// List of minimum type to store index-number of bytes
		typedef List<uint8_t,  // 0
				List<uint8_t,  // 1
				List<uint16_t, // 2
				List<uint32_t, // 3
				List<uint32_t, // 4
				List<uint64_t, // 5
				List<uint64_t, // 6
				List<uint64_t, // 7
				List<uint64_t, // 8
				NIL
			> > > > > > > > > DataTypes;
	};

	typedef typename NthType<typename types<BITS, SIGN>::DataTypes, result>::type type;
};

template<>
struct minint_bits<1> {
	enum {
		result = 1
	};
	typedef uint8_t type;
};

template<>
struct minint_bits<0> {
};


/**
 * Integer type of minimum size to store the given value.
 * @tparam max Maximum value needing to be stored.
 *
 * @var type Type of minimum size.
 */
template<unsigned long long max>
struct minint {
	enum {
		bits = (minint<smath<max, 1>::shr>::bits + 1),
		result = minint_bits<bits>::result
	};
	
	typedef typename minint_bits<bits>::type type;
};

template<>
struct minint<1> {
	enum {
		bits = 1,
		result = 1
	};
	typedef uint8_t type;
};

template<>
struct minint<0> {
};

static_assert(sizeof(minint<1>::type) == 1, "sizeof(minint<1>) is incorrect");
static_assert(sizeof(minint<255>::type) == 1, "sizeof(minint<255>) is incorrect");
static_assert(sizeof(minint<256>::type) == 2, "sizeof(minint<256>) is incorrect");
static_assert(sizeof(minint<65535>::type) == 2, "sizeof(minint<65535>) is incorrect");
static_assert(sizeof(minint<65536>::type) == 4, "sizeof(minint<65536>) is incorrect");
static_assert(sizeof(minint<4294967295>::type) == 4, "sizeof(minint<4294967295>) is incorrect");
static_assert(sizeof(minint<4294967296>::type) == 8, "sizeof(minint<4294967296>) is incorrect");

} // namespace tmp

#endif // TMP_MININT_H_
