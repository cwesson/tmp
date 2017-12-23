
#ifndef ___MATRIX_H_
#define ___MATRIX_H_

#if __cplusplus >= 201103L
#include <initializer_list>
#endif

template<unsigned int ROWS, unsigned int COLS, typename T=int>
class matrix {
	typedef matrix<ROWS, COLS, T> matrixT;

	public:
		matrix<ROWS, COLS, T>(){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] = T(0);
				}
			}
		}
		matrix<ROWS, COLS, T>(T d[ROWS][COLS]){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] = d[r][c];
				}
			}
		}
		matrix<ROWS, COLS, T>(T d[ROWS*COLS]){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] = d[(r*COLS) + c];
				}
			}
		}
		matrix<ROWS, COLS, T>(const matrixT& o){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] = o.data[r][c];
				}
			}
		}
#if __cplusplus >= 201103L
		matrix<ROWS, COLS, T>(std::initializer_list<T> d){
			const T* dd = d.begin();
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] = *dd;
					++dd;
				}
			}
		}
#endif
		
		/**
		 * Assignment.
		 */
		matrixT& operator=(const matrixT& rhs){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] = rhs.data[r][c];
				}
			}
			return *this;
		}
		
		/**
		 * Matrix Addition.
		 */
		const matrixT operator+(const matrixT& rhs) const{
			return matrixT(*this) += rhs;
		}
		
		/**
		 * Matrix subtraction.
		 */
		const matrixT operator-(const matrixT& rhs) const{
			return matrixT(*this) -= rhs;
		}
		
		/**
		 * Matrix multiplication.
		 */
		template<unsigned int P>
		friend const matrix<ROWS, P, T> operator*(const matrixT& lhs, const matrix<COLS, P, T>& rhs){
			matrix<ROWS, P, T> ret;
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < P; ++c){
					T sum(0);
					for(unsigned int m = 0; m < COLS; ++m){
						sum += lhs.data[r][m] * rhs[m][c];
					}
					ret[r][c] = sum;
				}
			}
			return ret;
		}
		
		/**
		 * Arithmetic Multiplication.
		 */
		friend const matrixT operator*(T lhs, const matrixT& rhs){
			return matrixT(rhs) *= lhs;
		}
		
		/**
		 * Arithmetic Multiplication.
		 */
		const matrixT operator*(T rhs) const{
			return matrixT(*this) *= rhs;
		}
		
		/**
		 * Matrix Division.
		 */
		friend const matrixT operator/(const matrixT& lhs, const matrixT& rhs){
			return matrixT(lhs) /= rhs;
		}
		
		/**
		 * Arithmetic Division.
		 */
		const matrixT operator/(T rhs) const{
			return matrixT(*this) /= rhs;
		}
		
		/**
		 * Assignment Addition.
		 */
		matrixT& operator+=(const matrixT& rhs){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] += rhs.data[r][c];
				}
			}
			return *this;
		}
		
		/**
		 * Assignment Subtraction.
		 */
		matrixT& operator-=(const matrixT& rhs){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] -= rhs.data[r][c];
				}
			}
			return *this;
		}
		
		/**
		 * Assignment Multiplication.
		 */
		matrixT& operator*=(T rhs){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] *= rhs;
				}
			}
			return *this;
		}
		
		/**
		 * Assignment Division.
		 */
		matrixT& operator/=(T rhs){
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					data[r][c] /= rhs;
				}
			}
			return *this;
		}
		
		/**
		 * Equality.
		 */
		bool operator==(const matrixT& rhs) const{
			for(unsigned int r = 0; r < ROWS; ++r){
				for(unsigned int c = 0; c < COLS; ++c){
					if(data[r][c] != rhs.data[r][c]){
						return false;
					}
				}
			}
			return true;
		}
		
		/**
		 * Inequality.
		 */
		bool operator!=(const matrixT& rhs) const{
			return !(*this == rhs);
		}
	
	private:
		/**
		 * Row helper class.
		 * Allows use of double array operator.
		 */
		class row {
			public:
				/**
				 * Array index.
				 */
				T& operator[](unsigned int c){
					return rowdata[c];
				}
				
				/**
				 * Array index.
				 */
				const T& operator[](unsigned int c) const{
					return rowdata[c];
				}
				
			private:
				T rowdata[COLS];
		};
		
		row data[ROWS];
		
	public:
		/**
		 * Array index.
		 */
		row& operator[](unsigned int r){
			return data[r];
		}
		
		/**
		 * Array index.
		 */
		const row& operator[](unsigned int r) const{
			return data[r];
		}
};

template<unsigned int COLS, typename T>
matrix<1, COLS, T> operator,(matrix<1, COLS-1, T> a, T b){
	matrix<1, COLS, T> d;
	for(unsigned int i = 0; i < COLS-1; ++i){
		d[i] = a[i];
	}
	d[COLS-1] = b;
	return d;
}

template<typename T>
matrix<1, 2, T> operator,(T a, T b){
	T ret[2] = {a, b};
	return ret;
}

#endif

