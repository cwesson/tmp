
#ifndef ___BIGINT_H__
#define ___BIGINT_H__

#include <iostream>
#include <limits>
#include <cstdint>
#include <cinttypes>
#include <string>
#include "cppcompat.h"

template<typename T>
class bigint {
	static_assert(std::numeric_limits<T>::is_integer, "bigint template is not integer");
	
	public:
		typedef bigint<T> bigintT;
		typedef bigint<bigintT> doubleintT;
		typedef T halfintT;
	
		enum {
			HALFSIZE = sizeof(T)*8,
			SIZE = HALFSIZE*2,
			DOUBLESIZE = SIZE*2
		};
	
		bigint():
			lo(0), hi(0) {}
		bigint(T n):
			lo(n), hi(0) {}
		bigint(T h, T l):
			lo(l), hi(h) {}
		bigint(const bigint<T>& o):
			lo(o.lo), hi(o.hi) {}
		
		/**
		 * Assignment.
		 */
		const bigintT& operator=(const bigintT& rhs){
			hi = rhs.hi;
			lo = rhs.lo;
			return *this;
		}
		
		/**
		 * Arithmatic addition.
		 */
		friend const bigintT operator+(const bigintT& lhs, const bigintT& rhs){
			return bigintT(lhs) += rhs;
		}
		
		/**
		 * Arithmatic negation (two's complement).
		 */
		const bigintT operator-() const{
			return (~(*this)) + bigintT(1);
		}
		
		/**
		 * Arithmatic subtraction.
		 */
		friend const bigintT operator-(const bigintT& lhs, const bigintT& rhs){
			return bigintT(lhs) -= rhs;
		}
		
		/**
		 * Arithmatic multiplication.
		 */
		friend const bigintT operator*(const bigintT& lhs, const bigintT& rhs){
			return bigintT(lhs) *= rhs;
		}
		
		/**
		 * Arithmatic division.
		 */
		friend const bigintT operator/(const bigintT& lhs, const bigintT& rhs){
			return bigintT(lhs) /= rhs;
		}
		
		/**
		 * Arithmatic remainder.
		 */
		friend const bigintT operator%(const bigintT& lhs, const bigintT& rhs){
			return bigintT(lhs) %= rhs;
		}
		
		/**
		 * Prefix increment.
		 */
		bigintT operator++(){
			(*this) += 1;
			return *this;
		}
		
		/**
		 * Postfix increment.
		 */
		bigintT operator++(int){
			bigintT ret(*this);
			++(*this);
			return ret;
		}
		
		/**
		 * Prefix decrement.
		 */
		bigintT operator--(){
			*this = (*this) - 1;
			 return *this;
		}
		
		/**
		 * Postfix decrement.
		 */
		bigintT operator--(int){
			bigintT ret(*this);
			--(*this);
			return ret;
		}
		
		/**
		 * Assignment Addition.
		 */
		bigintT& operator+=(const bigintT& rhs){
			hi = hi + rhs.hi;
			lo = lo + rhs.lo;
			if(lo < rhs.lo){
				++hi;
			}
			return *this;
		}
		
		/**
		 * Assignment Subtraction.
		 */
		bigintT& operator-=(const bigintT& rhs){
			return (*this) += (-rhs);
		}
		
		/**
		 * Assignment Multiplication.
		 */
		bigintT& operator*=(const bigintT& rhs){
			*this = doubleintT::mult(*this, rhs).low();
			return *this;
		}
		
		/**
		 * Assignment Division.
		 */
		bigintT& operator/=(const bigintT& rhs){
			*this = div(*this, rhs).quo;
			return *this;
		}
		
		/**
		 * Assignment Modulo.
		 */
		bigintT& operator%=(const bigintT& rhs){
			*this = div(*this, rhs).rem;
			return *this;
		}
		
		/**
		 * Assignment Bitwise AND.
		 */
		bigintT& operator&=(const bigintT& rhs){
			hi &= rhs.hi;
			lo &= rhs.lo;
			return *this;
		}
		
		/**
		 * Assignment Bitwise OR.
		 */
		bigintT& operator|=(const bigintT& rhs){
			hi |= rhs.hi;
			lo |= rhs.lo;
			return *this;
		}
		
		/**
		 * Assignment Bitwise XOR.
		 */
		bigintT& operator^=(const bigintT& rhs){
			hi ^= rhs.hi;
			lo ^= rhs.lo;
			return *this;
		}
		
		/**
		 * Assignment Left Shift.
		 */
		const bigintT& operator<<=(unsigned int rhs){
			*this = (*this) << rhs;
			return *this;
		}
		
		/**
		 * Assignment Right Shift.
		 */
		const bigintT& operator>>=(unsigned int rhs){
			*this = (*this) >> rhs;
			return *this;
		}
		
		/**
		 * Equality.
		 */
		friend bool operator==(const bigintT& lhs, const bigintT& rhs){
			return (lhs.hi == rhs.hi) && (lhs.lo == rhs.lo);
		}
		
		/**
		 * Inequality.
		 */
		friend bool operator!=(const bigintT& lhs, const bigintT& rhs){
			return !(lhs == rhs);
		}
		
		/**
		 * Less than.
		 */
		friend bool operator<(const bigintT& lhs, const bigintT& rhs){
			return (lhs.hi < rhs.hi) || (lhs.hi == rhs.hi && lhs.lo < rhs.lo);
		}
		
		/**
		 * Greater than.
		 */
		friend bool operator>(const bigintT& lhs, const bigintT& rhs){
			return (lhs.hi > rhs.hi) || (lhs.hi == rhs.hi && lhs.lo > rhs.lo);
		}
		
		/**
		 * Less than or equal.
		 */
		friend bool operator<=(const bigintT& lhs, const bigintT& rhs){
			return (lhs == rhs) || (lhs < rhs);
		}
		
		/**
		 * Greater than or equal.
		 */
		friend bool operator>=(const bigintT& lhs, const bigintT& rhs){
			return (lhs == rhs) || (lhs > rhs);
		}
		
		/**
		 * Logical NOT
		 */
		bool operator!() const{
			return (hi == 0) && (lo == 0);
		}
		
		/**
		 * Left bit shift.
		 */
		const bigintT operator<<(unsigned long int shift) const{
			if(shift >= HALFSIZE){
				return bigintT((lo<<(shift-HALFSIZE)), 0);
			}else{
				return bigintT(((hi<<shift) | (lo>>(HALFSIZE-shift))), (lo<<shift));
			}
		}
		
		/**
		 * Right bit shift.
		 */
		const bigintT operator>>(unsigned long int shift) const{
			if(shift >= HALFSIZE){
				return bigintT(0, (hi>>(shift-HALFSIZE)));
			}else{
				return bigintT((hi>>shift), ((lo>>shift) | (hi<<(HALFSIZE-shift))));
			}
		}
		
		/**
		 * Bitwise OR.
		 */
		const bigintT operator|(const bigintT& rhs) const{
			return bigintT(*this) |= rhs;
		}
		
		/**
		 * Bitwise AND.
		 */
		const bigintT operator&(const bigintT& rhs) const{
			return bigintT(*this) &= rhs;
		}
		
		/**
		 * Bitwise XOR.
		 */
		const bigintT operator^(const bigintT& rhs) const{
			return bigintT(*this) ^= rhs;
		}
		
		/**
		 * Bitwise NOT (one's complement).
		 */
		const bigintT operator~() const{
			return bigintT(~hi, ~lo);
		}
		
		/**
		 * Conversion to bool.
		 * Used by boolean operators.
		 */
		explicit operator bool(){
			return (lo != halfintT(0)) || (hi != halfintT(0));
		}
		
		/**
		 * Hexidecimal notation.
		 */
		std::string hex() const;
		
		/**
		 * Stream Output.
		 */
		friend std::ostream& operator<<(std::ostream& os, const bigintT& rhs){
			os << rhs.hex();
			return os;
		}
		
		/**
		 * Get the lower half of the number.
		 * @return Lower half of the number
		 */
		halfintT low() const{
			return lo;
		}
		
		/**
		 * Get the upper half of the number.
		 * @return upper half of the number
		 */
		halfintT high() const{
			return hi;
		}
		
		
		/**
		 * Multiply a and b with carry.
		 * @param a First number.
		 * @param b Seconf number.
		 * @return Result including carry.
		 */
		static bigintT mult(const halfintT& a, const halfintT& b);
		
		typedef struct {
			bigintT quo;
			bigintT rem;
		} div_result;
		
		/**
		 * Divide a and b.
		 * @param a First number.
		 * @param b Seconf number.
		 * @return Result.
		 */
		static div_result div(const bigintT& a, const bigintT& b){
			div_result res = {0, 0};
	
			for(long long i = (sizeof(bigintT)*8)-1; i >= 0; --i){
				res.rem <<= 1;
				res.rem |= ((a >> i) & bigintT(0x1));
				if(res.rem >= b){
					res.rem -= b;
					res.quo |= (bigintT(0x1) << i);
				}
			}
	
			return res;
		}
		
	private:
		halfintT lo;
		halfintT hi;
};

template<typename T>
std::string bigint<T>::hex() const{
	char buff[HALFSIZE/2 + 1] = {0};
	snprintf(&buff[0], sizeof(buff), "%s%s", hi.hex().c_str(), lo.hex().c_str());
	return std::string(&buff[0]);
}

template<>
std::string bigint<uint64_t>::hex() const;

template<typename T>
bigint<T> bigint<T>::mult(const halfintT& a, const halfintT& b){
	typedef typename halfintT::halfintT qintT;
	/*
						ah al
					x bh bl
	-------------------------
				ahbl+alblc albl
	ahbh+albhc  albh
	-------------------------
	*/
	const qintT ah = a.high();
	const qintT al = a.low();
	const qintT bh = b.high();
	const qintT bl = b.low();

	const halfintT albl = halfintT::mult(al, bl);
	const qintT alblc = albl.high();
	const qintT alblp = albl.low();
	const halfintT ahbl = halfintT::mult(ah, bl) + alblc;
	const qintT ahblc = ahbl.high();
	const qintT ahblp = ahbl.low();
	const halfintT albh = halfintT::mult(al, bh);
	const qintT albhc = albh.high();
	const qintT albhp = albh.low();
	const halfintT ahbh = halfintT::mult(ah, bh) + albhc;
	const halfintT i = ((halfintT)ahblp + (halfintT)albhp);
	const qintT ih = i.high();
	const qintT il = i.low();

	const bigintT ret(
		ahbh + ahblc + ih,
		((halfintT)il << HALFSIZE) | alblp
	);

	return ret;
}

template<>
bigint<uint64_t> bigint<uint64_t>::mult(const uint64_t& a, const uint64_t& b);

namespace std {
	template<typename T>
	class numeric_limits<bigint<T> > {
		public:
			static constexpr bool is_specialized = true;
			static constexpr bool is_signed = numeric_limits<T>::is_signed;
			static constexpr bool is_integer = numeric_limits<T>::is_integer;
			static constexpr bool is_exact = numeric_limits<T>::is_exact;
			static constexpr bool has_infinity = false;
			static constexpr bool has_quiet_NaN = false;
			static constexpr bool has_signaling_NaN = false;
			static constexpr bool has_denorm = false;
			static constexpr bool has_denorm_loss = false;
			static constexpr bool round_style = numeric_limits<T>::round_style;
			static constexpr bool is_iec559 = false;
			static constexpr bool is_bounded = numeric_limits<T>::is_bounded;
			static constexpr bool is_modulo = numeric_limits<T>::is_modulo;
			static constexpr int digits = 8*sizeof(T)*2;
			static constexpr int digits10 = numeric_limits<bigint<T> >::digits * 0.30103;
			static constexpr int max_digits10 = 0;
			static constexpr int radix = numeric_limits<T>::radix;
			static constexpr int min_exponent = 0;
			static constexpr int min_exponent10 = 0;
			static constexpr int max_exponent = 0;
			static constexpr int max_exponent10 = 0;
			static constexpr bool traps = numeric_limits<T>::traps;
			static constexpr bool tinyness_before = false;
			static bigint<T> min() { return bigint<T>(0); }
			static bigint<T> lowest() { return bigint<T>(0); }
			static bigint<T> max() { return bigint<T>(numeric_limits<T>::max(), numeric_limits<T>::max()); }
			static bigint<T> epsilon() { return bigint<T>(0); }
			static bigint<T> round_error() { return bigint<T>(0); }
			static bigint<T> infinity() { return bigint<T>(0); }
			static bigint<T> quiet_NaN() { return bigint<T>(0); }
			static bigint<T> signaling_NaN() { return bigint<T>(0); }
			static bigint<T> denorm_min() { return bigint<T>(0); }
	};
}

typedef bigint<uint64_t> uint128;
typedef bigint<uint128> uint256;
typedef bigint<uint256> uint512;
typedef bigint<uint512> uint1024;
typedef bigint<uint1024> uint2048;
typedef bigint<uint2048> uint4096;
typedef bigint<uint4096> uint8192;
typedef bigint<uint8192> uint16384;
typedef bigint<uint16384> uint32768;

static_assert(sizeof(uint128) == 128/8, "sizeof(uint256) incorrect");
static_assert(sizeof(uint256) == 256/8, "sizeof(uint256) incorrect");
static_assert(sizeof(uint512) == 512/8, "sizeof(uint512) incorrect");
static_assert(sizeof(uint1024) == 1024/8, "sizeof(uint1024) incorrect");
static_assert(sizeof(uint2048) == 2048/8, "sizeof(uint2048) incorrect");
static_assert(sizeof(uint4096) == 4096/8, "sizeof(uint4096) incorrect");
static_assert(sizeof(uint8192) == 8192/8, "sizeof(uint8192) incorrect");
static_assert(sizeof(uint16384) == 16384/8, "sizeof(uint16384) incorrect");
static_assert(sizeof(uint32768) == 32768/8, "sizeof(uint32768) incorrect");

#endif

