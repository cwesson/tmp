#include "minint.h"
#include "cppcompat.h"
#include <cmath>

template<unsigned int W, unsigned int D, typename S=unsigned>
class qformat {
	private:
		typedef qformat<W, D> qformatT;
		typedef typename minint_bits<W+D>::DataType storageT;
		typedef typename minint_bits<(W+D)*2>::DataType doubleT;
	
	public:
		qformat<W, D>():
			value(0) {}
		qformat<W, D>(unsigned int v):
			value(v << D) {}
		explicit qformat<W, D>(double v):
			value(std::round(v * smath<2,D>::pow)) {}
		qformat<W, D>(const qformat<W, D>& o):
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

typedef qformat<15,1> Q15_1;
typedef qformat<3,13> Q3_13;
typedef qformat<7,1>  Q7_1;

static_assert(sizeof(Q15_1) == 2, "sizeof(Q15_1) incorrect");
static_assert(sizeof(Q7_1) == 1, "sizeof(Q7_1) incorrect");

