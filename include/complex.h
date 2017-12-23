
#ifndef ___COMPLEX_H_
#define ___COMPLEX_H_

#include <iostream>

template<typename T> class complex {
	typedef complex<T> complexT;
	
	public:
		complex<T>():
			re(0), im(0) {}
		complex<T>(T r):
			re(r), im(0) {}
		complex<T>(T r, T i):
			re(r), im(i) {}
		complex<T>(const complex<T>& o):
			re(o.re), im(o.im) {}
		
		/**
		 * Assignment.
		 */
		complexT& operator=(const complexT& rhs){
			re = rhs.re;
			im = rhs.im;
			return *this;
		}
		
		/**
		 * Arithmetic Addition.
		 */	
		friend const complexT operator+(const complexT& lhs, const complexT& rhs){
			return complexT(lhs) += rhs;
		}
		
		/**
		 * Negation (Two's Compliment).
		 */
		const complexT operator-() const{
			return complexT(-re, -im);
		}
		
		/**
		 * Arithmetic Subtraction.
		 */
		friend const complexT operator-(const complexT& lhs, const complexT& rhs){
			return complexT(lhs) -= rhs;
		}
		
		/**
		 * Arithmetic Multiplication.
		 */
		friend const complexT operator*(const complexT& lhs, const complexT& rhs){
			return complexT(lhs) *= rhs;
		}
		
		/**
		 * Arithmetic Division.
		 */
		friend const complexT operator/(const complexT& lhs, const complexT& rhs){
			return complexT(lhs) /= rhs;
		}
		
		/**
		 * Arithmetic Addition.
		 */	
		complexT& operator+=(const complexT& rhs){
			re += rhs.re;
			im += rhs.im;
			return *this;
		}
		
		/**
		 * Arithmetic Subtraction.
		 */
		complexT& operator-=(const complexT& rhs){
			re -= rhs.re;
			im -= rhs.im;
			return *this;
		}
		
		/**
		 * Arithmetic Multiplication.
		 */
		complexT& operator*=(const complexT& rhs){
			re = (re*rhs.re)-(im*rhs.im);
			im = (im*rhs.re)+(re*rhs.im);
			return *this;
		}
		
		/**
		 * Arithmetic Division.
		 */
		complexT& operator/=(const complexT& rhs){
			T den = (rhs.re*rhs.re)+(rhs.im*rhs.im);
			T re2 = ((re*rhs.re)+(im*rhs.im))/den;
			T im2 = ((im*rhs.re)-(re*rhs.im))/den;
			re = re2;
			im = im2;
		}
		
		/**
		 * Equality.
		 */
		friend bool operator==(const complexT& lhs, const complexT& rhs){
			return (lhs.re == rhs.re) && (lhs.im == rhs.im);
		}
		
		/**
		 * Inequality.
		 */
		friend bool operator!=(const complexT& lhs, const complexT& rhs){
			return !(lhs == rhs);
		}
		
		/**
		 * Stream Output.
		 */
		friend std::ostream& operator<<(std::ostream& os, const complexT& rhs){
			if(rhs.re){
				os << rhs.re;
				if(rhs.im > 0){
					os << "+";
				}
			}
			if(rhs.im){
				os << rhs.im << "i";
			}
			if(!rhs.re && !rhs.im){
				os << 0;
			}
			return os;
		}
		
		T real() const{
			return re;
		}
		
		T imag() const{
			return im;
		}
		
		complexT conj() const{
			return complexT(re, -im);
		}
		
	private:
		T re;
		T im;
};

#if __cplusplus >= 201103L
/**
 * Imaginary number literal.
 */
complex<unsigned long long> operator""_i(unsigned long long i){
	return complex<unsigned long long>(0, i);
}
#endif

#endif

