
#ifndef ___CPPCOMPAT_H_
#define ___CPPCOMPAT_H_

#if __cplusplus < 201103L

#define constexpr const

#define explicit

/**
 * Compile boolean assertion.  This will cause a compile error
 * if condition is false.
 * @param condition Boolean statement.
 * @param msg Ignored.  Included for compatibility with C++11.
 */
#define static_assert(condition, msg) typedef int __static_assert__[(condition) ? 0 : -1];

#endif

#endif

