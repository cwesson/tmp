
#include "smath.h"
#include <cstdint>

/**
 * Integer type of minimum size to store the given value.
 * @tparam bits Number of bits needing to be stored.
 *
 * @var DataType Type of minimum size.
 */
template<unsigned long long bits, typename sign=unsigned>
struct minint_bits {
	enum {
		Value = bits / 8,
		Check = Value * 8,
		Result = bits > Check ? Value + 1 : Value
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
			>>>>>>>>> DataTypes;
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
			>>>>>>>>> DataTypes;
	};
	typedef typename NthType<typename types<bits, sign>::DataTypes, Result>::type DataType;
};

template<>
struct minint_bits<1> {
	enum {
		bits = 1,
		Result = 1
	};
	typedef uint8_t DataType;
};

template<>
struct minint_bits<0> {
};


/**
 * Integer type of minimum size to store the given value.
 * @tparam max Maximum value needing to be stored.
 *
 * @var DataType Type of minimum size.
 */
template<unsigned long long max>
struct minint {
	enum {
		bits = (minint<smath<max, 1>::shr>::bits + 1),
		Result = minint_bits<bits>::Result
	};
	
	typedef typename minint_bits<bits>::DataType DataType;
};

template<>
struct minint<1> {
	enum {
		bits = 1,
		Result = 1
	};
	typedef uint8_t DataType;
};

template<>
struct minint<0> {
};

static_assert(sizeof(minint<1>::DataType) == 1);
static_assert(sizeof(minint<255>::DataType) == 1);
static_assert(sizeof(minint<256>::DataType) == 2);
static_assert(sizeof(minint<65535>::DataType) == 2);
static_assert(sizeof(minint<65536>::DataType) == 4);
static_assert(sizeof(minint<4294967295>::DataType) == 4);
static_assert(sizeof(minint<4294967296>::DataType) == 8);

