/**
 * @file lfsr.h
 * Linear Feedback Shift Register (LFSR) template.
 * @author Conlan Wesson
 */

#pragma once

#include <iostream>
#include "minint.h"

namespace lfsr {

/**
 * Bitmask consisting of N ones.
 * @tparam N Number of bits set.
 */
template<unsigned int N>
struct _lfsr_mask {
	enum {
		value = (1 << (N-1)) | _lfsr_mask<N-1>::value, ///< Value of the bitmask.
	};
};

template<>
struct _lfsr_mask<0> {
	enum {
		value = 0,
	};
};

/**
 * LFSR feedback calculator.
 * @tparam SIZE Size of the LFSR in bits.
 * @tparam TAPS Bit positions to use.
 */
template<unsigned int SIZE, unsigned int... TAPS>
struct _lfsr_feed {};

/**
 * Linear Feedback Shift Register (LFSR).
 * @tparam SIZE Size of the LFSR in bits.
 * @tparam TAPS Bit positions to use.
 */
template<unsigned int SIZE, unsigned int... TAPS>
class LFSR {
	public:
		typedef typename minint_bits<SIZE>::DataType state_t;
		static_assert(sizeof(state_t)*8 >= SIZE);

		/**
		 * LFSR constructor.
		 * @param init Initial state of the LFSR.
		 */
		LFSR(unsigned int init) : _state(init & _lfsr_mask<SIZE>::value) {}

		/**
		 * LFSR copy constructor.
		 * @param other Original LFSR.
		 */
		LFSR(const LFSR& other) = default;

		/**
		 * Assignment operator.
		 * @param other Original LFSR.
		 */
		LFSR& operator=(const LFSR& other) = default;

		/**
		 * Assignment operator.
		 */
		explicit operator unsigned int(){
			return _state;
		}

		/**
		 * Assignment operator.
		 */
		explicit operator bool(){
			return (_state & 1);
		}

		/**
		 * Prefix increment.
		 * Shift the LFSR once.
		 * @return The new LSB.
		 */
		unsigned int operator++(){
			state_t fb = feedback();
			_state = ((_state >> 1) | (fb << (SIZE-1)));
			return **this;
		}

		/**
		 * Postfix increment.
		 * Shift the LFSR once.
		 * @return The old LSB.
		 */
		unsigned int operator++(int){
			unsigned int ret = **this;
			++(*this);
			return ret;
		}

		/**
		 * Shift assignment operator.
		 * @param shift Shift amount.
		 */
		void operator>>=(unsigned int shift){
			for( ; shift > 0; --shift){
				++(*this);
			}
		}

		/**
		 * Shift operator.
		 * @param shift Shift amount.
		 * @return New LFSR.
		 */
		LFSR operator>>(unsigned int shift){
			LFSR ret(*this);
			ret >>= shift;
			return ret;
		}

		/**
		 * Dereference.
		 * @return The current LSB.
		 */
		unsigned int operator*(){
			return (_state & 1);
		}

		unsigned int state(){
			return _state;
		}

	private:
		state_t _state;

		unsigned int feedback(){
			return _lfsr_feed<SIZE, TAPS...>::feedback(_state) & 1;
		}
};

template<unsigned int SIZE, unsigned int T, unsigned int... TAPS>
struct _lfsr_feed<SIZE, T, TAPS...> {
	/**
	 * Calculate LFSR feedback.
	 * @param state Current state of the LFSR.
	 * @return Feedback value, should AND with 1 to get the bit.
	 */
	static unsigned int feedback(typename LFSR<SIZE, T, TAPS...>::state_t state){
		return (state >> (SIZE-T)) ^ _lfsr_feed<SIZE, TAPS...>::feedback(state);
	}
};

template<unsigned int SIZE, unsigned int T>
struct _lfsr_feed<SIZE, T> {
	static unsigned int feedback(typename LFSR<SIZE, T>::state_t state){
		return (state >> (SIZE-T));
	}
};

}
