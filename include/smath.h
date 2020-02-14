
#ifndef ___SMATH_H_
#define ___SMATH_H_

#include "cppcompat.h"

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
 */
template<long long a, long long b>
struct smath {
	enum {
		sum        = (a + b),
		difference = (a - b),
		product    = (a * b),
		quotient   = (a / b),
		remainder  = (a % b),
		max        = ((a > b) ? a : b),
		min        = ((a < b) ? a : b),
		shl        = (a << b),
		shr        = (a >> b),
		binor      = (a | b),
		binand     = (a & b),
		binxor     = (a ^ b),
		pow        = (a * smath<a, b-1>::pow),
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
		max        = ((a > 0) ? a : 0),
		min        = ((a < 0) ? a : 0),
		shl        = a,
		shr        = a,
		binor      = a,
		binand     = 0,
		binxor     = a,
		pow        = 1,
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

template<int a>
struct Int {
	enum { value = a };
};

struct NIL {};

template<typename H, typename T=NIL>
struct List {
	typedef H head;
	typedef T tail;
};

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
 * Calculates the length of a List.
 * @tparam L List to calculate the length of.
 *
 * @var result Length of List L.
 */
template<typename L>
struct Length {
	enum { result = 1 + Length<typename L::tail>::result };
};
template<>
struct Length<NIL> {
	enum { result = 0 };
};

/**
 * Calculates the Nth element of a List.
 * @tparam L List to find element in.
 * @tparam n Index into the List.
 *
 * @var result The Nth element of List L.
 */
template<typename L, int n>
struct Nth {
	enum { result = Nth<typename L::tail, n-1>::result };
};
template<typename L>
struct Nth<L, 0> {
	enum { result = L::head::value };
};

/**
 * Calculates the Nth type in a List.
 * @tparam L List to find element in.
 * @tparam n Index into the List.
 *
 * @var type The Nth element of List L.
 */
template<typename L, unsigned long long n>
struct NthType {
	typedef typename NthType<typename L::tail, n-1>::type type;
};
template<typename L>
struct NthType<L, 0> {
	typedef typename L::head type;
};

/**
 * Determines if an element exists in a List.
 * @tparam L List to find element in.
 * @tparam F Element to find in the List.
 *
 * @var result true if List L contains element F, false otherwise.
 */
template<typename L, typename F>
struct Includes {
	enum { result = Eq<typename L::head, F>::result ? true : Includes<typename L::tail, F>::result };
};
template<typename F>
struct Includes<NIL, F> {
	enum { result = false };
};

/**
 * Fails compilation if the condition is false.
 * @tparam cond Condition to check.
 */
template<bool cond, typename T=NIL>
struct Assert {
	typedef typename T::fail check;
};
template<>
struct Assert<true> {
	typedef void check;
};

template<typename L, typename F>
struct _Find {
	enum { result = Eq<typename L::head, F>::result ? 0 : 1 + _Find<typename L::tail, F>::result };
};
template<typename F>
struct _Find<NIL, F> {
	enum { result = 0 };
};

/**
 * Determines the index of an element in a List.
 * @tparam L List to find element in.
 * @tparam F Element to find in the List.
 *
 * @var result The index of F in L
 */
template<typename L, typename F>
struct Find {
	//typedef typename Assert<Includes<L, F>::result>::check fail;
	static_assert(Includes<L, F>::result, "L does not include F");
	enum { result = _Find<L, F>::result };
};

/**
 * Calculates the sum of all elements in a List.
 * @tparam L List to calculate the sum of.
 *
 * @var result The sum of all elements in List L.
 */
template<typename L>
struct Sum {
	enum { result = L::head::value + Sum<typename L::tail>::result };
};
template<>
struct Sum<NIL> {
	enum { result = 0 };
};

/**
 * Calculates the product of all elements in a List.
 * @tparam L List to calculate the product of.
 *
 * @var result The product of all elements in List L.
 */
template<typename L>
struct Product {
	enum { result = L::head::value * Product<typename L::tail>::result };
};
template<>
struct Product<NIL> {
	enum { result = 1 };
};

#endif

