/**
 * @file include/tmp/oneof.h
 * @author Conlan Wesson
 * @copyright (c) 2025, Conlan Wesson
 */

#ifndef TMP_ONEOF_H_
#define TMP_ONEOF_H_

#include <type_traits>

namespace tmp {

/**
 * Helper for oneof.
 * @warning Do not use this directly, use oneof.
 */
template<typename T, typename... S>
class _oneof {
	public:
		_oneof() {
		}

		~_oneof() {
		}
		
		void destroy(unsigned int index){
			if(index == 0){
				obj.~T();
			}else{
				others.destroy(index-1);
			}
		}

		template<typename A>
		A* as(unsigned int index){
			if constexpr(std::is_same<T, A>::value){
				if(index == 0){
					return &obj;
				}else{
					return nullptr;
				}
			}else{
				return others.template as<A>(index-1);
			}
		}

		template<typename A>
		bool is(unsigned int index){
			if constexpr(std::is_same<T, A>::value){
				return (index == 0);
			}else{
				return others.template is<A>(index-1);
			}
		}

		template<typename A>
		unsigned int set(const A& ins, unsigned int index){
			if constexpr(std::is_same<T, A>::value){
				obj = ins;
				return index+1;
			}else{
				return others.template set<A>(ins, index+1);
			}
		}
		
		template<typename A, typename... ARGS>
		unsigned int make(ARGS... args, unsigned int index){
			if constexpr(std::is_same<T, A>::value){
				new (&obj) T(args...); // this is bad, don't do this, but in this case it allows constructing the object in-place
				return index+1;
			}else{
				return others.template make<A, ARGS...>(args..., index+1);
			}
		}

	private:
		union {
			T obj;
			_oneof<S...> others;
		};
};

template<>
class _oneof<void> {
	public:
		void destroy(unsigned int index){
			(void)index;
		}
};

/**
 * Helper for is_oneof.
 * @warning Do not use this directly, use is_oneof.
 */
template<typename A, typename T, typename... S>
struct _is_oneof {
	enum { value = std::is_same<T, A>::value || _is_oneof<A, S...>::value };
};

template<typename A>
struct _is_oneof<A, void> {
	enum { value = false };
};

/**
 * Template to determine if A is of the type in T.
 * @tparam A Type to test for.
 * @tparam T List of types to check against.
 * @note T must not contain void.
 */
template<typename A, typename... T>
struct is_oneof {
	enum {
		/**
		 * true if A is in T, false otherwise.
		 */
		value = _is_oneof<A, T..., void>::value
	};
};

/**
 * Tagged union type that contains one of the given types, or nothing.
 * @tparam T List of possible types.
 * @note T must not contain void.
 */
template<typename... T>
class oneof {
	public:
		/**
		 * Constructor, initialize containing nothing.
		 */
		oneof() : index(0) {}

		/**
		 * Constructor, initialize with given value.
		 * @tparam A Type to initialize with, must be in T.
		 * @param ins Value to initialize with.
		 */
		template<typename A,
				std::enable_if_t<is_oneof<A, T...>::value, bool> = true>
		oneof(const A& ins) : index(0) {
			set(ins);
		}

		/**
		 * Destructor.
		 */
		~oneof() {
			clear();
		}
		
		

		/**
		 * Get the stored value.
		 * @tparam A Type to get the value as, must be in T.
		 * @return Pointer to the stored value, or nullptr if the stored value is not of type A.
		 */
		template<typename A,
				std::enable_if_t<is_oneof<A, T...>::value, bool> = true>
		A* as(){
			if(index == 0){
				return nullptr;
			}else{
				return store.template as<A>(index-1);
			}
		}

		/**
		 * Check the type of the stored value.
		 * @tparam A Type to check, must be in T.
		 * @return true if the store.value is of type A, false otherwise.
		 */
		template<typename A,
				std::enable_if_t<is_oneof<A, T...>::value, bool> = true>
		bool is(){
			if(index == 0){
				return false;
			}else{
				return store.template is<A>(index-1);
			}
		}

		/**
		 * Check if a value has been stored.
		 * @return true if there is a stored.value, false otherwise.
		 */
		bool is_set(){
			return (index != 0);
		}

		/**
		 * Store a value.
		 * If a value is already stored its destructor is called before being overwritten.
		 * @tparam A Type to set, must be in T.
		 * @param ins Value to store, copied using operator=.
		 */
		template<typename A,
				std::enable_if_t<is_oneof<A, T...>::value, bool> = true>
		void set(const A& ins){
			clear();
			index = store.template set<A>(ins, 0);
		}

		/**
		 * Store a value.
		 * If a value is already stored its destructor is called before being overwritten.
		 * @tparam A Type to set, must be in T.
		 * @param ins Value to store, copied using operator=.
		 * @return Reference to the stored value.
		 */
		template<typename A,
				std::enable_if_t<is_oneof<A, T...>::value, bool> = true>
		A& operator=(const A& ins){
			set(ins);
			return *as<A>();
		}

		/**
		 * Construct a value in place.
		 * If a value is already stored its destructor is called before being overwritten.
		 * @tparam A Type to construct, must be in T.
		 * @tparam ARGS Types of constructor arguments.
		 * @param args Constructor arguments.
		 */
		template<typename A, typename... ARGS,
				std::enable_if_t<is_oneof<A, T...>::value, bool> = true>
		void make(ARGS... args){
			clear();
			index = store.template make<A, ARGS...>(args..., 0);
		}

		/**
		 * Clear the stored value.
		 * If a value is stored its destructor is called first.
		 */
		void clear(){
			if(index != 0){
				store.destroy(index-1);
				index = 0;
			}
		}

	private:
		_oneof<T..., void> store;
		unsigned int index;
};

} // namespace tmp

#endif // TMP_ONEOF_H_

