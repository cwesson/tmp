/**
 * @file include/tmp/modint.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_MODINT_H_
#define TMP_MODINT_H_

#include "tmp/minint.h"

namespace tmp {

template<unsigned long long MOD>
class modint {
	public:
		typedef modint<MOD> modintT;
		typedef typename minint<MOD>::type storageT;
		
		modint():
			value(0) {}
		modint(unsigned long long v):
			value(v % MOD) {}
		modint(const modint& o):
			value(o.value) {}
		
		/**
		 * Assignment.
		 */
		const modintT& operator=(const modintT& rhs){
			value = rhs.value;
			return *this;
		}
		
		/**
		 * Arithmatic addition.
		 */
		friend const modintT operator+(const modintT& lhs, const modintT& rhs){
			return modintT(lhs) += rhs;
		}
		
		/**
		 * Arithmatic subtraction.
		 */
		friend const modintT operator-(const modintT& lhs, const modintT& rhs){
			return modintT(lhs) -= rhs;
		}
		
		/**
		 * Arithmatic multiplication.
		 */
		friend const modintT operator*(const modintT& lhs, const modintT& rhs){
			return modintT(lhs) *= rhs;
		}
		
		/**
		 * Arithmatic division.
		 */
		friend const modintT operator/(const modintT& lhs, const modintT& rhs){
			return modintT(lhs) /= rhs;
		}
		
		/**
		 * Arithmatic remainder.
		 */
		friend const modintT operator%(const modintT& lhs, const modintT& rhs){
			return modintT(lhs) %= rhs;
		}
		
		/**
		 * Prefix increment.
		 */
		modintT operator++(){
			(*this) += 1;
			return *this;
		}
		
		/**
		 * Postfix increment.
		 */
		modintT operator++(int){
			modintT ret(*this);
			++(*this);
			return ret;
		}
		
		/**
		 * Prefix decrement.
		 */
		modintT operator--(){
			*this = (*this) - 1;
			 return *this;
		}
		
		/**
		 * Postfix decrement.
		 */
		modintT operator--(int){
			modintT ret(*this);
			--(*this);
			return ret;
		}
		
		/**
		 * Assignment Addition.
		 */
		modintT& operator+=(const modintT& rhs){
			value = (value + rhs.value) % MOD;
			return *this;
		}
		
		/**
		 * Assignment Subtraction.
		 */
		modintT& operator-=(const modintT& rhs){
			value = (value - rhs.value) % MOD;
			return *this;
		}
		
		/**
		 * Assignment Multiplication.
		 */
		modintT& operator*=(const modintT& rhs){
			value = (value * rhs.value) % MOD;
			return *this;
		}
		
		/**
		 * Assignment Division.
		 */
		modintT& operator/=(const modintT& rhs){
			value = (value / rhs.value) % MOD;
			return *this;
		}
		
		/**
		 * Assignment Modulo.
		 */
		modintT& operator%=(const modintT& rhs){
			value = (value % rhs.value) % MOD;
			return *this;
		}
		
		/**
		 * Equality.
		 */
		friend bool operator==(const modintT& lhs, const modintT& rhs){
			return lhs.value == rhs.value;
		}
		
		/**
		 * Inequality.
		 */
		friend bool operator!=(const modintT& lhs, const modintT& rhs){
			return !(lhs == rhs);
		}
		
		/**
		 * Less than.
		 */
		friend bool operator<(const modintT& lhs, const modintT& rhs){
			return lhs.value < rhs.value;
		}
		
		/**
		 * Greater than.
		 */
		friend bool operator>(const modintT& lhs, const modintT& rhs){
			return lhs.value > rhs.value;
		}
		
		/**
		 * Less than or equal.
		 */
		friend bool operator<=(const modintT& lhs, const modintT& rhs){
			return lhs.value <= rhs.value;
		}
		
		/**
		 * Greater than or equal.
		 */
		friend bool operator>=(const modintT& lhs, const modintT& rhs){
			return lhs.value >= rhs.value;
		}
		
		/**
		 * Logical NOT
		 */
		bool operator!() const{
			return value == 0;
		}
		
		/**
		 * Stream Output.
		 */
		template<unsigned long long M>
		friend std::ostream& operator<<(std::ostream& os, const modint<M>& rhs);
	
	private:
		storageT value;
};

/**
 * Stream Output.
 */
template<unsigned long long MOD>
std::ostream& operator<<(std::ostream& os, const modint<MOD>& rhs){
	os << rhs.value;
	return os;
}

} // namespace tmp

#endif // TMP_MODINT_H_
