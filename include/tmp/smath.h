/**
 * @file include/tmp/smath.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_SMATH_H_
#define TMP_SMATH_H_

#include "cppcompat.h"
#include "tmp/assert.h"

namespace tmp {

/**
 * Calculates n to the power of x at compile time.
 * @tparam n
 * @tparam x
 *
 * @var value n^x
 */
template<unsigned long long n, unsigned long long x>
struct static_pow {
	enum { value = n * static_pow<n, x-1>::value };
};
template<unsigned long long n>
struct static_pow<n, 0> {
	enum { value = 1 };
};

static_assert((static_pow<2,16>::value == 65536), "static_pow test failed");

/**
 * Calculates n factorial at compile time.
 * @tparam n
 *
 * @var value n!
 */
template<unsigned long long n>
struct static_factorial {
	enum { value = n * static_factorial<n-1>::value };
};
template<>
struct static_factorial<0> {
	enum { value = 1 };
};

static_assert((static_factorial<12>::value == 479001600), "static_factorial test failed");

/**
 * Calculates binary artithmatic at compile time.
 * @tparam a Left-hand side argument.
 * @tparam b Right-hand side argument.
 *
 * @var max The greater of a and b.
 * @var min The lesser of a and b.
 * @var log Calculates log_b(a) rounded down.  When b is 2 or less, calculates log2(a) rounded up.
 */
template<long long a, long long b=0>
struct smath {
	enum {
		sum        = (a + b),
		difference = (a - b),
		product    = (a * b),
		quotient   = (a / b),
		remainder  = (a % b),
		add        = (a + b),
		sub        = (a - b),
		mul        = (a * b),
		div        = (a / b),
		mod        = (a % b),
		max        = ((a > b) ? a : b),
		min        = ((a < b) ? a : b),
		shl        = (a << b),
		shr        = (a >> b),
		binor      = (a | b),
		binand     = (a & b),
		binxor     = (a ^ b),
		pow        = (a * smath<a, b-1>::pow),
		log        = (smath<a, 0>::log / (b <= 2 ? 1 : smath<b, 0>::log)),
	};
};
template<long long a>
struct smath<a, 0> {
	enum {
		sum        = a,
		difference = a,
		product    = 0,
		//quotient = Divide by zero error,
		//remainder= Divide by zero error,
		add        = a,
		sub        = a,
		mul        = 0,
		//div      = Divide by zero error,
		//mod      = Divide by zero error,
		max        = ((a > 0) ? a : 0),
		min        = ((a < 0) ? a : 0),
		shl        = a,
		shr        = a,
		binor      = a,
		binand     = 0,
		binxor     = a,
		pow        = 1,
		log        = ((a > 1) ? (1 + smath<(a >> 1), 0>::log) : 1),
	};
};
template<>
struct smath<0, 0> {
	enum {
		sum        = 0,
		difference = 0,
		product    = 0,
		//quotient = Divide by zero error,
		//remainder= Divide by zero error,
		add        = 0,
		sub        = 0,
		mul        = 0,
		//div      = Divide by zero error,
		//mod      = Divide by zero error,
		max        = 0,
		min        = 0,
		shl        = 0,
		shr        = 0,
		binor      = 0,
		binand     = 0,
		binxor     = 0,
		pow        = 1,
		log        = 1,
	};
};

static_assert((smath<20, 3>::sum        ==   23), "smath::sum test failed");
static_assert((smath<20, 3>::difference ==   17), "smath::difference test failed");
static_assert((smath<20, 3>::product    ==   60), "smath::product test failed");
static_assert((smath<20, 3>::quotient   ==    6), "smath::quotient test failed");
static_assert((smath<20, 3>::remainder  ==    2), "smath::quotient test failed");
static_assert((smath<20, 3>::max        ==   20), "smath::max test failed");
static_assert((smath<20, 3>::min        ==    3), "smath::min test failed");
static_assert((smath<20, 3>::shl        ==  160), "smath::shl test failed");
static_assert((smath<20, 3>::shr        ==    2), "smath::shr test failed");
static_assert((smath<20, 3>::binor      ==   23), "smath::binor test failed");
static_assert((smath<20, 3>::binand     ==    0), "smath::binand test failed");
static_assert((smath<20, 3>::binxor     ==   23), "smath::binxor test failed");
static_assert((smath<20, 3>::pow        == 8000), "smath::pow test failed");
static_assert((smath<20, 3>::log        ==    2), "smath::log test failed");

} // namespace tmp

#endif // TMP_SMATH_H_
