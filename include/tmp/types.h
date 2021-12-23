/**
 * @file include/tmp/types.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_TYPES_H_
#define TMP_TYPES_H_

#include "tmp/cppcompat.h"

namespace tmp {

struct NIL {};

template<int A>
struct Int {
	typedef int type;
	enum { value = A };
};

static_assert((sizeof(Int<0>::value) == 4), "sizeof(Int) incorrect");

#if __cplusplus >= 201103L

template<bool A>
struct Bool {
	typedef bool type;
	enum : bool { value = A };
};

static_assert((sizeof(Bool<false>) == 1), "sizeof(Bool) incorrect");

template<long long A>
struct Long {
	typedef long long type;
	enum : long long { value = A };
};

static_assert((sizeof(Long<0>::value) == 8), "sizeof(Long) incorrect");

#else

template<bool A>
struct Bool {
	typedef bool type;
	enum { value = A };
};

#endif // __cplusplus >= 201103L

/**
 * Compares two types.
 * @tparam X First type.
 * @tparam Y Second type.
 *
 * @var result true if X and Y are the same type, false otherwise,
 */
template<typename X, typename Y>
struct Eq {
	enum { result = false };
};
template<typename X>
struct Eq<X, X> {
	enum { result = true };
};

/**
 * Conditional type.
 * @tparam COND Condition.
 * @tparam TRUE Type if COND is true.
 * @tparam FALSE Type if COND is false.
 */
template<bool COND, typename TRUE, typename FALSE>
struct If {};
template<typename TRUE, typename FALSE>
struct If<true, TRUE, FALSE> {
	typedef TRUE type;
};
template<typename TRUE, typename FALSE>
struct If<false, TRUE, FALSE> {
	typedef FALSE type;
};

/**
 * Larger of two types, by sizeof.
 * @tparam X First type.
 * @tparam Y Second type.
 */
template<typename X, typename Y>
struct Larger {
	typedef typename If<(sizeof(X) >= sizeof(Y)), X, Y>::type type;
};

/**
 * Smaller of two types, by sizeof.
 * @tparam X First type.
 * @tparam Y Second type.
 */
template<typename X, typename Y>
struct Smaller {
	typedef typename If<(sizeof(X) <= sizeof(Y)), X, Y>::type type;
};

} // namespace tmp

#endif // TMP_TYPES_H_
