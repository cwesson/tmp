/**
 * @file include/tmp/tmath.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_TMATH_H_
#define TMP_TMATH_H_

namespace tmp {

#if __cplusplus >= 201402L

template<typename T> constexpr T PI;
template<> constexpr int    PI<int>    = 3;
template<> constexpr double PI<double> = 3.141592653589793;
template<> constexpr float  PI<float>  = 3.14159265;

#endif

/**
 * Calculates the max of a and b.
 * @param a
 * @param b
 * @return The greater of a and b.
 */
template<typename T>
T max(T a, T b){
	return (a > b) ? a : b;
}

/**
 * Calculates the min of a and b.
 * @param a
 * @param b
 * @return The lesser of a and b.
 */
template<typename T>
T min(T a, T b){
	return (a < b) ? a : b;
}

#if __cplusplus >= 201103L

/**
 * Calculates the maximum of args.
 * @param args List of arguments to calculate the maxmimum of.
 * @return The greatest from args.
 */
template<typename T, typename... Args>
T max(T x, Args... args){
	return max(x, max(args...));
}

/**
 * Calculates the minimum of args.
 * @param args List of arguments to calculate the minimum of.
 * @return The least from args.
 */
template<typename T, typename... Args>
T min(T x, Args... args){
	return min(x, min(args...));
}

/**
 * Calculates the sum of all arguments.
 * @param Args List of arguments to calculate summation of.
 * @return The summation of all arguments.
 */
template<typename T>
T sum(T x){
	return x;
}
template<typename T, typename... Args>
T sum(T x, Args... args){
	return x + sum(args...);
}

/**
 * Calculates the product of all arguments.
 * @param Args List of arguments to calculate product of.
 * @return The product of all arguments.
 */
template<typename T>
T product(T x){
	return x;
}
template<typename T, typename... Args>
T product(T x, Args... args){
	return x * product(args...);
}

#endif // __cplusplus >= 201103L

} // namespace tmp

#endif // TMP_TMATH_H_
