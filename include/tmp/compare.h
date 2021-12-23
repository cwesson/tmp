/**
 * @file include/tmp/compare.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_COMPARE_H_
#define TMP_COMPARE_H_

namespace tmp {

template<typename T>
class compare_chaining{
	public:
		virtual ~compare_chaining() {}
		
		operator bool() const {
			return result;
		}
		
		template<typename U>
		const compare_chaining<U> operator<(const U& rhs) const {
			if(result){
				return compare_chaining<U>(rhs, (lhs < rhs));
			}
			return compare_chaining<U>(rhs, false);
		}
		
		template<typename U>
		const compare_chaining<U> operator<=(const U& rhs) const {
			if(result){
				return compare_chaining<U>(rhs, (lhs <= rhs));
			}
			return compare_chaining<U>(rhs, false);
		}
		
		template<typename U>
		const compare_chaining<U> operator>(const U& rhs) const {
			if(result){
				return compare_chaining<U>(rhs, (lhs > rhs));
			}
			return compare_chaining<U>(rhs, false);
		}
		
		template<typename U>
		const compare_chaining<U> operator>=(const U& rhs) const {
			if(result){
				return compare_chaining<U>(rhs, (lhs >= rhs));
			}
			return compare_chaining<U>(rhs, false);
		}
		
		template<typename U>
		const compare_chaining<U> operator==(const U& rhs) const {
			if(result){
				return compare_chaining<U>(rhs, (lhs == rhs));
			}
			return compare_chaining<U>(rhs, false);
		}
		
		template<typename U>
		const compare_chaining<U> operator!=(const U& rhs) const {
			if(result){
				return compare_chaining<U>(rhs, (lhs != rhs));
			}
			return compare_chaining<U>(rhs, false);
		}
	
	private:
		compare_chaining(const T& lhs) :
			lhs(lhs),
			result(true)
		{}

		compare_chaining(const T& lhs, bool res) :
			lhs(lhs),
			result(res)
		{}
		
		const T& lhs;
		const bool result;
		
		template<typename U> friend class compare_chaining;
		friend class compare;
};

class compare {
	public:
		compare() {}

		template<typename T>
		const compare_chaining<T> operator<<(const T& first) const {
			return compare_chaining<T>(first);
		}
};

} // namespace tmp

#endif // TMP_COMPARE_H_
