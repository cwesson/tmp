
#ifndef __ROTATE_H_
#define __ROTATE_H_

template<typename T> T rol(T num, unsigned int shift){
	return (num<<shift) | ((num>>(sizeof(T)*8)-shift));
}

template<typename T> T ror(T num, unsigned int shift){
	return (num>>shift) | ((num<<(sizeof(T)*8)-shift));
}


#endif

