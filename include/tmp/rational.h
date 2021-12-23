
#ifndef TMP_RATIONAL_H_
#define TMP_RATIONAL_H_

#include <iostream>
#include <limits>
#include "cppcompat.h"

template<typename T> class rational {
	static_assert(std::numeric_limits<T>::is_integer, "rational template is not integer");
	
	typedef rational<T> rationalT;
	
	public:
		rational():
			nu(0), de(1) {}
		rational(T n):
			nu(n), de(1) {}
		rational(T n, T d):
			nu(n), de(d) { reduce(); }
		rational(const rational& o):
			nu(o.nu), de(o.de) { reduce(); }
		
		/**
		 * Assignment.
		 */
		rationalT& operator=(const rationalT& rhs){
			nu = rhs.nu;
			de = rhs.de;
			reduce();
			return *this;
		}
		
		/**
		 * Arithmetic Addition.
		 */	
		friend const rationalT operator+(const rationalT& lhs, const rationalT& rhs){
			return rationalT(lhs) += rhs;
		}
		
		/**
		 * Negation (Two's Compliment).
		 */
		const rationalT operator-() const{
			return rationalT(-nu, de);
		}
		
		/**
		 * Arithmetic Subtraction.
		 */
		friend const rationalT operator-(const rationalT& lhs, const rationalT& rhs){
			return rationalT(lhs) -= rhs;
		}
		
		/**
		 * Arithmetic Multiplication.
		 */
		friend const rationalT operator*(const rationalT& lhs, const rationalT& rhs){
			return rationalT(lhs) *= rhs;
		}
		
		/**
		 * Arithmetic Division.
		 */
		friend const rationalT operator/(const rationalT& lhs, const rationalT& rhs){
			return rationalT(lhs) /= rhs;
		}
		
		/**
		 * Assignment Addition.
		 */	
		rationalT& operator+=(const rationalT& rhs){
			nu = (nu*rhs.de)+(de*rhs.nu);
			de = de*rhs.de;
			reduce();
			return *this;
		}
		
		/**
		 * Assignment Subtraction.
		 */
		rationalT& operator-=(const rationalT& rhs){
			nu = (nu*rhs.de)-(de*rhs.nu);
			de = de*rhs.de;
			reduce();
			return *this;
		}
		
		/**
		 * Assignment Multiplication.
		 */
		rationalT& operator*=(const rationalT& rhs){
			nu = nu*rhs.nu;
			de = de*rhs.de;
			reduce();
			return *this;
		}
		
		/**
		 * Assignment Division.
		 */
		rationalT& operator/=(const rationalT& rhs){
			nu = nu*rhs.de;
			de = de*rhs.nu;
			reduce();
			return *this;
		}
		
		/**
		 * Equality.
		 */
		friend bool operator==(const rationalT& lhs, const rationalT& rhs){
			return (lhs.nu == rhs.nu) && (lhs.de == rhs.de);
		}
		
		/**
		 * Inequality.
		 */
		friend bool operator!=(const rationalT& lhs, const rationalT& rhs){
			return !(lhs == rhs);
		}
		
		/**
		 * Stream Output.
		 */
		friend std::ostream& operator<<(std::ostream& os, const rationalT& rhs){
			os << rhs.nu;
			if(rhs.de != 1){
				os << "/" << rhs.de;
			}
			return os;
		}
	
	private:
		T nu;
		T de;
		
		void reduce(){
			T g = gcd(nu, de);
			nu = nu / g;
			de = de / g;
		}
		
		T gcd(T a, T b){
			if(a == 0){
				return b;
			}else if(b == 0){
				return a;
			}
			
			if(a < 0){
				a = -a;
			}
			if(b < 0){
				b = -b;
			}
			
			if(a == b){
				return a;
			}else if(a > b){
				return gcd(a-b, b);
			}else{
				return gcd(a, b-a);
			}
		}
};

#endif // TMP_RATIONAL_H_
