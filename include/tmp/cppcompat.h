/**
 * @file include/tmp/cppcompat.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_CPPCOMPAT_H_
#define TMP_CPPCOMPAT_H_

#if __cplusplus < 201103L

#define constexpr const

#define explicit

/**
 * Compile boolean assertion.  This will cause a compile error
 * if condition is false.
 * @param condition Boolean statement.
 * @param msg Ignored.  Included for compatibility with C++11.
 */
#define static_assert(condition, msg) typedef int __static_assert__[(condition) ? 1 : -1];

#endif // __cplusplus < 201103L

#endif // TMP_CPPCOMPAT_H_
