/**
 * @file include/tmp/assert.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_ASSERT_H_
#define TMP_ASSERT_H_

#include "types.h"

namespace tmp {

/**
 * Fails compilation if the condition is false.
 * @tparam Cond Condition to check.
 */
template<bool Cond, typename T=NIL>
struct Assert {
	typedef typename T::fail check;
};
template<>
struct Assert<true> {
	typedef void check;
};

} // namespace tmp

#endif // TMP_ASSERT_H_
