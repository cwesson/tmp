/**
 * @file include/tmp/list.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_LIST_H_
#define TMP_LIST_H_

#include "tmp/types.h"
#include "tmp/assert.h"

namespace tmp {

template<typename H, typename T=NIL>
struct List {
	typedef H head;
	typedef T tail;
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
 * @tparam N Index into the List.
 *
 * @var result The Nth element of List L.
 */
template<typename L, int N>
struct Nth {
	enum { result = Nth<typename L::tail, N-1>::result };
};
template<typename L>
struct Nth<L, 0> {
	enum { result = L::head::value };
};

/**
 * Calculates the Nth type in a List.
 * @tparam L List to find element in.
 * @tparam N Index into the List.
 *
 * @var type The Nth element of List L.
 */
template<typename L, unsigned long long N>
struct NthType {
	typedef typename NthType<typename L::tail, N-1>::type type;
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
	typedef typename Assert<Includes<L, F>::result>::check fail;
	//static_assert(Includes<L, F>::result, "L does not include F");
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
	enum { result = L::head::value + static_cast<typename L::head::type>(Sum<typename L::tail>::result) };
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
	enum { result = L::head::value * static_cast<typename L::head::type>(Product<typename L::tail>::result) };
};
template<>
struct Product<NIL> {
	enum { result = 1 };
};

} // namespace tmp

#endif // TMP_LIST_H_
