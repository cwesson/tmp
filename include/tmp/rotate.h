/**
 * @file include/tmp/rotate.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_ROTATE_H_
#define TMP_ROTATE_H_

namespace tmp {

template<typename T> T rol(T num, unsigned int shift){
	return (num<<shift) | ((num>>(sizeof(T)*8)-shift));
}

template<typename T> T ror(T num, unsigned int shift){
	return (num>>shift) | ((num<<(sizeof(T)*8)-shift));
}

} //namespace tmp

#endif // TMP_ROTATE_H_
