#include "minint.h"
#include "cppcompat.h"
#include <cmath>

template<unsigned int W, unsigned int D, typename Sign=signed>
class qformat {
	private:
		typedef qformat<W, D, Sign> qformatT;
		
		template<unsigned int w, unsigned int d, typename s>
		struct _bits;
		template<unsigned int w, unsigned int d>
		struct _bits<w, d, signed> { enum { result = W+D+1 }; };
		template<unsigned int w, unsigned int d>
		struct _bits<w, d, unsigned> { enum { result = W+D }; };
		
		typedef typename minint_bits<_bits<W,D,Sign>::result>::DataType storageT;
		typedef typename minint_bits<(_bits<W,D,Sign>::result)*2>::DataType doubleT;
	
	public:
		qformat<W, D, Sign>():
			value(0) {}
		qformat<W, D, Sign>(unsigned int v):
			value(v << D) {}
		explicit qformat<W, D, Sign>(double v):
			value(std::round(v * smath<2,D>::pow)) {}
		qformat<W, D, Sign>(const qformat<W, D>& o):
			value(o.value) {}
			
		/**
		 * Covert to double.
		 */
		operator double(){
			return value * (1.0 / smath<2,D>::pow);
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
		const qformatT& operator=(const qformatT& rhs){
			value = rhs.value;
			return *this;
		}
		
		/**
		 * Arithmatic addition.
		 */
		friend const qformatT operator+(const qformatT& lhs, const qformatT& rhs){
			return qformatT(lhs) += rhs;
		}
		
		/**
		 * Arithmatic subtraction.
		 */
		friend const qformatT operator-(const qformatT& lhs, const qformatT& rhs){
			return qformatT(lhs) -= rhs;
		}
		
		/**
		 * Arithmatic multiplication.
		 */
		friend const qformatT operator*(const qformatT& lhs, const qformatT& rhs){
			return qformatT(lhs) *= rhs;
		}
		
		/**
		 * Arithmatic division.
		 */
		friend const qformatT operator/(const qformatT& lhs, const qformatT& rhs){
			return qformatT(lhs) /= rhs;
		}
		
		/**
		 * Arithmatic remainder.
		 */
		friend const qformatT operator%(const qformatT& lhs, const qformatT& rhs){
			return qformatT(lhs) %= rhs;
		}
		
		/**
		 * Assignment Addition.
		 */
		qformatT& operator+=(const qformatT& rhs){
			value += rhs.value;
			return *this;
		}
		
		/**
		 * Assignment Subtraction.
		 */
		qformatT& operator-=(const qformatT& rhs){
			value -= rhs.value;
			return *this;
		}
		
		/**
		 * Assignment Multiplication.
		 */
		qformatT& operator*=(const qformatT& rhs){
			value = ((value * rhs.value) + (1 << (D-1))) >> D;
			return *this;
		}
		
		/**
		 * Assignment Division.
		 */
		qformatT& operator/=(const qformatT& rhs){
			value = static_cast<storageT>((static_cast<doubleT>(value) << D) / rhs.value);
			return *this;
		}
		
		storageT bits(){
			return value;
		}
	
	private:
		storageT value;
};

typedef qformat<15,1, unsigned> UQ15_1;
typedef qformat<7,1, unsigned>  UQ7_1;
typedef qformat<3,12, signed> Q3_12;

static_assert(sizeof(UQ15_1) == 2, "sizeof(UQ15_1) incorrect");
static_assert(sizeof(UQ7_1) == 1, "sizeof(UQ7_1) incorrect");

