/**
 * @file include/tmp/equation/equation.h
 * @author Conlan Wesson
 * @copyright (c) 2021, Conlan Wesson
 */

#ifndef TMP_EQUATION_EQUATION_H_
#define TMP_EQUATION_EQUATION_H_

#include <functional>
#include <string>
#include <iostream>
#include <optional>

namespace tmp {
namespace equation {

template<typename T>
class base_equation;

template<typename T>
class symbol;

template<typename T>
class constant;

template<typename T>
class operation_add;

template<typename T>
class operation_mult;

/**
 * Represents a mathematical equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class equation {
    public:
        equation(const base_equation<T>* e) :
            eq(e)
        {
            ++(eq->ref);
        }

        equation(const equation<T>& e) :
            eq(e.eq)
        {
            ++(eq->ref);
        }

        ~equation() {
            if(--(eq->ref) == 0){
                delete eq;
            }
        }

        T operator()() const {
            return (*eq)();
        };

        /**
         * Simplify the equation.
         * @return Simplified equation.
         */
        equation<T> simplify() const {
            return eq->simplify();
        }

        /**
         * Calculate the derivative with respect to d.
         * @param d Symbol to calculate the partial derivative with respect to.
         * @return Partial derivative with respect to d.
         */
        equation<T> derivative(const symbol<T>& d) const {
            return eq->derivative(d);
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const equation<U>& rhs);

        friend class operation_add<T>;
        friend class operation_mult<T>;
    
    private:
        const base_equation<T>* eq;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const equation<T>& rhs) {
    rhs.eq->print(os);
    return os;
}

/**
 * Base class for mathematical equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class base_equation {
    public:
        base_equation() :
            ref(0)
        {}

        base_equation(const base_equation<T>& e) = delete;

        virtual T operator()() const = 0;

        virtual bool is_constant() const {
            return false;
        }

        virtual bool is_symbol() const {
            return false;
        }

        virtual equation<T> operator+(const base_equation<T>& rhs) const {
            return add(this, &rhs);
        }

        virtual equation<T> operator*(const base_equation<T>& rhs) const {
            return mult(this, &rhs);
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const base_equation<U>& rhs);

        virtual void print(std::ostream& os) const = 0;

        virtual equation<T> simplify() const = 0;

        virtual equation<T> derivative(const symbol<T>& d) const = 0;

        friend class equation<T>;
    
    private:
        mutable size_t ref;
};

template<typename T>
std::ostream& operator<<(std::ostream& os, const base_equation<T>& rhs) {
    rhs.print(os);
    return os;
}

template <typename T>
equation<T> add(const base_equation<T>* l, const base_equation<T>* r){
    if(l->is_constant() && r->is_constant()){
        return equation(new constant((*l)() + (*r)()));
    }else{
        return equation(new operation_add(l, r));
    }
}

/**
 * Addition equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_add : public base_equation<T> {
    public:
        operation_add(const base_equation<T>* l, const base_equation<T>* r) :
            base_equation<T>(),
            lhs(l), rhs(r) {}

        virtual T operator()() const override {
            return lhs() + rhs();
        }

        virtual void print(std::ostream& os) const override {
            os << lhs << "+" << rhs;
        }

        virtual equation<T> simplify() const override {
            auto l = lhs.simplify();
            auto r = rhs.simplify();
            if(l.eq->is_constant() && l() == 0){
                return r;
            }else if(r.eq->is_constant() && r() == 0){
                return l;
            }else{
                return add(l.eq, r.eq);
            }
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return add(lhs.derivative(d).eq, rhs.derivative(d).eq).simplify();
        }

    protected:
        const equation<T> lhs;
        const equation<T> rhs;
};

template <typename T>
equation<T> mult(const base_equation<T>* l, const base_equation<T>* r){
    if(l->is_constant() && r->is_constant()){
        return equation(new constant((*l)() * (*r)()));
    }else{
        return equation(new operation_mult(l, r));
    }
}

/**
 * Multiplication equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_mult : public base_equation<T> {
    public:
        operation_mult(const base_equation<T>* l, const base_equation<T>* r) :
            base_equation<T>(),
            lhs(l), rhs(r) {}

        virtual T operator()() const override {
            return lhs() * rhs();
        }

        virtual void print(std::ostream& os) const override {
            os << lhs << "*" << rhs;
        }

        virtual equation<T> simplify() const override {
            auto l = lhs.simplify();
            auto r = rhs.simplify();
            if(l.eq->is_constant()){
                if(l() == 0){
                    return equation(new constant<T>(0));
                }else if(l() == 1){
                    return r;
                }
            }else if(r.eq->is_constant()){
                if(r() == 0){
                    return equation(new constant<T>(0));
                }else if(r() == 1){
                    return l;
                }
            }
            return mult(l.eq, r.eq);
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return add(mult(lhs.derivative(d).eq, rhs.eq).eq, mult(rhs.derivative(d).eq, lhs.eq).eq).simplify();
        }

    protected:
        const equation<T> lhs;
        const equation<T> rhs;
};

/**
 * Mathematical symbol.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class symbol : public base_equation<T> {
    public:
        symbol(const char* name) :
            base_equation<T>(),
            name(name),
            value()
        {}

        bool operator==(const symbol<T>& rhs) const {
            return this == &rhs;
        }

        void operator=(const T& v) {
            value = v;
        }

        virtual T operator()() const override {
            return value.value();
        }

        virtual bool is_symbol() const override {
            return true;
        }

        virtual void print(std::ostream& os) const override {
            os << name;
        }

        virtual equation<T> simplify() const override {
            return equation(this);
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            if(*this == d){
                return equation(new constant<T>(1));
            }else{
                return equation(new constant<T>(0));
            }
        }
    
    protected:
        std::string name;
        std::optional<T> value;
};

/**
 * Mathematical constant.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class constant : public base_equation<T> {
    public:
        constant(const T& v) :
            base_equation<T>(),
            value(v)
        {}

        void operator=(const T& v) {
            value = v;
        }

        virtual bool is_constant() const override {
            return true;
        }

        virtual T operator()() const override {
            return value;
        }

        virtual void print(std::ostream& os) const override {
            os << value;
        }

        virtual equation<T> simplify() const override {
            return equation(this);
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            (void)d;
            return equation(new constant<T>(0));
        }
    protected:
        T value;
};

} // namespace equation
} // namespace tmp

#endif // TMP_EQUATION_EQUATION_H_
