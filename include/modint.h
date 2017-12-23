
#include "minint.h"

template<unsigned long long MOD>
class modint {
	public:
		typedef modint<MOD> modintT;
		typedef typename minint<MOD>::DataType storageT;
		
		modint<MOD>():
			value(0) {}
		modint<MOD>(unsigned long long v):
			value(v % MOD) {}
		modint<MOD>(const modint<MOD>& o):
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
		friend std::ostream& operator<<(std::ostream& os, const modintT& rhs){
			os << static_cast<unsigned long long>(rhs.value);
			return os;
		}
	
	private:
		storageT value;
};

