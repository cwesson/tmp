/**
 * @file include/tmp/fixed.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_FIXED_H_
#define TMP_FIXED_H_

#include "tmp/minint.h"
#include "tmp/cppcompat.h"
#include <cmath>

namespace tmp {

template<unsigned int W, unsigned int D, typename SIGN=signed>
class fixed {
	private:
		typedef fixed<W, D, SIGN> fixedT;
		
		template<unsigned int w, unsigned int d, typename s>
		struct _bits;
		template<unsigned int w, unsigned int d>
		struct _bits<w, d, signed> {
			enum {
				result = w+d+1,
				issigned = 1,
			};
		};
		template<unsigned int w, unsigned int d>
		struct _bits<w, d, unsigned> {
			enum {
				result = w+d,
				issigned = 0,
			};
		};
		
		typedef typename minint_bits<_bits<W,D,SIGN>::result, SIGN>::type storageT;
		typedef typename minint_bits<(_bits<W,D,SIGN>::result)*2, SIGN>::type doubleT;

		enum {
			mask = (1 << _bits<W,D,SIGN>::result) - 1,
			dmask = (1 << D) - 1,
		};
	
	public:
		fixed():
			value(0) {}
		
		fixed(storageT v):
			value(v << D)
		{
			normalize();
		}
		
		explicit fixed(double v):
			value(static_cast<storageT>(round(v * static_cast<double>(smath<2,D>::pow))))
		{
			normalize();
		}
		
		fixed(const fixed& o):
			value(o.value)
		{
			normalize();
		}
		
		template<unsigned int X, unsigned int E>
		fixed(const fixed<X, E, SIGN>& o) {
			typedef typename Larger<typename fixed<X, E, SIGN>::storageT, storageT>::type conversionT;

			conversionT v = o.value;
			value = (((v >> E) << D) | (
				((D > E) ? (v << (D-E)) : (v >> (E-D))) & dmask
			));

			normalize();
		}
			
		/**
		 * Covert to double.
		 */
		operator double(){
			return value * (1.0 / static_cast<double>(smath<2,D>::pow));
		}
		
		/**
		 * Covert to int.
		 */
		operator int(){
			return value >> D;
		}
			
		/**
		 * Assignment.
		 */
		const fixedT& operator=(const fixedT& rhs){
			value = rhs.value;
			return *this;
		}
		
		/**
		 * Arithmatic addition.
		 */
		friend fixedT operator+(const fixedT& lhs, const fixedT& rhs){
			return fixedT(lhs) += rhs;
		}
		
		/**
		 * Arithmatic subtraction.
		 */
		friend fixedT operator-(const fixedT& lhs, const fixedT& rhs){
			return fixedT(lhs) -= rhs;
		}
		
		/**
		 * Arithmatic multiplication.
		 */
		friend fixedT operator*(const fixedT& lhs, const fixedT& rhs){
			return fixedT(lhs) *= rhs;
		}
		
		/**
		 * Arithmatic division.
		 */
		friend fixedT operator/(const fixedT& lhs, const fixedT& rhs){
			return fixedT(lhs) /= rhs;
		}
		
		/**
		 * Arithmatic remainder.
		 */
		friend fixedT operator%(const fixedT& lhs, const fixedT& rhs){
			return fixedT(lhs) %= rhs;
		}
		
		/**
		 * Assignment Addition.
		 */
		fixedT& operator+=(const fixedT& rhs){
			value += rhs.value;
			return *this;
		}
		
		/**
		 * Assignment Subtraction.
		 */
		fixedT& operator-=(const fixedT& rhs){
			value -= rhs.value;
			return *this;
		}
		
		/**
		 * Assignment Multiplication.
		 */
		fixedT& operator*=(const fixedT& rhs){
			value = ((value * rhs.value) + (1 << (D-1))) >> D;
			return *this;
		}
		
		/**
		 * Assignment Division.
		 */
		fixedT& operator/=(const fixedT& rhs){
			value = static_cast<storageT>((static_cast<doubleT>(value) << D) / rhs.value);
			return *this;
		}
		
		storageT bits(){
			return value;
		}
	
	private:
		storageT value;

		void normalize() {
			if(!_bits<W,D,SIGN>::issigned){
				value &= mask;
			}
		}

		template<unsigned int X, unsigned int E, typename T> friend class fixed;
};

typedef fixed<15,1, unsigned> UQ15_1;
typedef fixed<7,1, unsigned>  UQ7_1;
typedef fixed<3,12, signed> Q3_12;
typedef fixed<3,12, unsigned> UQ3_12;

static_assert(sizeof(UQ15_1) == 2, "sizeof(UQ15_1) incorrect");
static_assert(sizeof(UQ7_1) == 1, "sizeof(UQ7_1) incorrect");

} // namespace tmp

#endif // TMP_FIXED_H_
