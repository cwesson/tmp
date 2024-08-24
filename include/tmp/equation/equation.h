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
#include <cmath>

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
class operation_neg;

template<typename T>
class operation_sub;

template<typename T>
class operation_mult;

template<typename T>
class operation_div;

template<typename T>
class operation_log;

template<typename T>
class operation_pow;

enum precedence {
    PRECEDENCE_PARENTHESIS,
    PRECEDENCE_EXPONENT,
    PRECEDENCE_MULTIPLICATION,
    PRECEDENCE_ADDITION,
};

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

        equation<T> operator+(const base_equation<T>& rhs) const {
            return *eq + rhs;
        }

        equation<T> operator-(const base_equation<T>& rhs) const {
            return *eq - rhs;
        }

        equation<T> operator+(const equation<T>& rhs) const {
            return *eq + *rhs.eq;
        }

        equation<T> operator-(const equation<T>& rhs) const {
            return *eq - *rhs.eq;
        }

        equation<T> operator-() const {
            return -(*eq);
        }

        equation<T> operator*(const base_equation<T>& rhs) const {
            return *eq * rhs;
        }

        equation<T> operator/(const base_equation<T>& rhs) const {
            return *eq / rhs;
        }

        equation<T> operator*(const equation<T>& rhs) const {
            return *eq * *rhs.eq;
        }

        equation<T> operator/(const equation<T>& rhs) const {
            return *eq / *rhs.eq;
        }

        equation<T> pow(T rhs) const {
            return equation(new operation_pow(eq, new constant(rhs)));
        }

        equation<T> pow(const base_equation<T>& rhs) const {
            return equation(new operation_pow(eq, &rhs));
        }

        equation<T> pow(const equation<T>& rhs) const {
            return equation(new operation_pow(eq, rhs.eq));
        }

        bool is_constant() const {
            return eq->is_constant();
        }

        bool is_symbol() const {
            return eq->is_symbol();
        }

        int precedence() const {
            return eq->precedence();
        }

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

        friend class base_equation<T>;
        friend class operation_add<T>;
        friend class operation_neg<T>;
        friend class operation_sub<T>;
        friend class operation_mult<T>;
        friend class operation_div<T>;
        friend class operation_log<T>;
        friend class operation_pow<T>;
    
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

        equation<T> pow(T rhs) const {
            return equation(new operation_pow(this, new constant(rhs)));
        }

        equation<T> pow(const base_equation<T>& rhs) const {
            return equation(new operation_pow(this, &rhs));
        }

        equation<T> pow(const equation<T>& rhs) const {
            return equation(new operation_pow(this, rhs.eq));
        }

        template<typename U>
        friend std::ostream& operator<<(std::ostream& os, const base_equation<U>& rhs);

        virtual void print(std::ostream& os) const = 0;

        virtual int precedence() const = 0;

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
equation<T> operator+(const base_equation<T>& l, const base_equation<T>& r){
    if(l.is_constant() && r.is_constant()){
        return equation(new constant(l() + r()));
    }else{
        return equation(new operation_add(&l, &r));
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
            if(lhs.precedence() > precedence()){
                os << "(" << lhs << ")";
            }else{
                os << lhs;
            }
            os << "+";
            if(rhs.precedence() > precedence()){
                os << "(" << rhs << ")";
            }else{
                os << rhs;
            }
        }

        virtual int precedence() const override {
            return PRECEDENCE_ADDITION;
        }

        virtual equation<T> simplify() const override {
            auto l = lhs.simplify();
            auto r = rhs.simplify();
            if(l.eq->is_constant() && l() == 0){
                return r;
            }else if(r.eq->is_constant() && r() == 0){
                return l;
            }else{
                return *l.eq + *r.eq;
            }
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return (lhs.derivative(d) + rhs.derivative(d)).simplify();
        }

    protected:
        const equation<T> lhs;
        const equation<T> rhs;
};

template <typename T>
equation<T> operator-(const base_equation<T>& l, const base_equation<T>& r){
    if(l.is_constant() && r.is_constant()){
        return equation(new constant(l() - r()));
    }else{
        return equation(new operation_sub(&l, &r));
    }
}

template <typename T>
equation<T> operator-(const base_equation<T>& r){
    if(r.is_constant()){
        return equation(new constant(-r()));
    }else{
        return equation(new operation_neg(&r));
    }
}

/**
 * Negative equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_neg : public base_equation<T> {
    public:
        operation_neg(const base_equation<T>* r) :
            base_equation<T>(),
            rhs(r) {}

        virtual T operator()() const override {
            return -rhs();
        }

        virtual void print(std::ostream& os) const override {
            os << "-";
            if(rhs.precedence() > precedence()){
                os << "(" << rhs << ")";
            }else{
                os << rhs;
            }
        }

        virtual int precedence() const override {
            return PRECEDENCE_ADDITION;
        }

        virtual equation<T> simplify() const override {
            auto r = rhs.simplify();
            if(r.eq->is_constant() && r() == 0){
                return equation(new constant<T>(0));
            }else{
                return equation(this);
            }
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return (-rhs.derivative(d)).simplify();
        }

    protected:
        const equation<T> rhs;
};

/**
 * Subtraction equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_sub : public base_equation<T> {
    public:
        operation_sub(const base_equation<T>* l, const base_equation<T>* r) :
            base_equation<T>(),
            lhs(l), rhs(r) {}

        virtual T operator()() const override {
            return lhs() - rhs();
        }

        virtual void print(std::ostream& os) const override {
            if(lhs.precedence() > precedence()){
                os << "(" << lhs << ")";
            }else{
                os << lhs;
            }
            os << "-";
            if(rhs.precedence() > precedence()){
                os << "(" << rhs << ")";
            }else{
                os << rhs;
            }
        }

        virtual int precedence() const override {
            return PRECEDENCE_ADDITION;
        }

        virtual equation<T> simplify() const override {
            auto l = lhs.simplify();
            auto r = rhs.simplify();
            if(l.eq->is_constant() && l() == 0){
                return -(*r.eq);
            }else if(r.eq->is_constant() && r() == 0){
                return l;
            }else{
                return *l.eq - *r.eq;
            }
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return (lhs.derivative(d) - rhs.derivative(d)).simplify();
        }

    protected:
        const equation<T> lhs;
        const equation<T> rhs;
};

template <typename T>
equation<T> operator*(const base_equation<T>& l, const base_equation<T>& r){
    if(l.is_constant() && r.is_constant()){
        return equation(new constant(l() * r()));
    }else{
        return equation(new operation_mult(&l, &r));
    }
}

template <typename T>
equation<T> operator*(T l, const base_equation<T>& r){
    if(r.is_constant()){
        return equation(new constant(l * r()));
    }else{
        return equation(new operation_mult(new constant(l), &r));
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
            if(lhs.precedence() > precedence()){
                os << "(" << lhs << ")";
            }else{
                os << lhs;
            }
            os << "*";
            if(rhs.precedence() > precedence()){
                os << "(" << rhs << ")";
            }else{
                os << rhs;
            }
        }

        virtual int precedence() const override {
            return PRECEDENCE_MULTIPLICATION;
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
            return *l.eq * *r.eq;
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return ((lhs.derivative(d) * rhs) + (rhs.derivative(d) * lhs)).simplify();
        }

    protected:
        const equation<T> lhs;
        const equation<T> rhs;
};


template <typename T>
equation<T> operator/(const base_equation<T>& l, const base_equation<T>& r){
    if(l.is_constant() && r.is_constant()){
        return equation(new constant(l() / r()));
    }else{
        return equation(new operation_div(&l, &r));
    }
}

template <typename T>
equation<T> operator/(T l, const base_equation<T>& r){
    if(r.is_constant()){
        return equation(new constant(l * r()));
    }else{
        return equation(new operation_div(new constant(l), &r));
    }
}

/**
 * Division equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_div : public base_equation<T> {
    public:
        operation_div(const base_equation<T>* l, const base_equation<T>* r) :
            base_equation<T>(),
            lhs(l), rhs(r) {}

        virtual T operator()() const override {
            return lhs() / rhs();
        }

        virtual void print(std::ostream& os) const override {
            if(lhs.precedence() > precedence()){
                os << "(" << lhs << ")";
            }else{
                os << lhs;
            }
            os << "/";
            if(rhs.precedence() > precedence()){
                os << "(" << rhs << ")";
            }else{
                os << rhs;
            }
        }

        virtual int precedence() const override {
            return PRECEDENCE_MULTIPLICATION;
        }

        virtual equation<T> simplify() const override {
            auto l = lhs.simplify();
            auto r = rhs.simplify();
            if(l.eq->is_constant()){
                if(l() == 0){
                    return equation(new constant<T>(0));
                }
            }else if(r.eq->is_constant()){
                if(r() == 1){
                    return l;
                }
            }
            return l / r;
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return (((lhs.derivative(d) * rhs) - (rhs.derivative(d) * lhs)) / rhs.pow(equation(new constant<T>(2)))).simplify();
        }

    protected:
        const equation<T> lhs;
        const equation<T> rhs;
};

/**
 * Logarithmic equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_log : public base_equation<T> {
    public:
        operation_log(const base_equation<T>* r) :
            base_equation<T>(),
            rhs(r) {}

        virtual T operator()() const override {
            return std::log(rhs());
        }

        virtual void print(std::ostream& os) const override {
            os << "ln(" << rhs << ")";
        }

        virtual int precedence() const override {
            return PRECEDENCE_PARENTHESIS;
        }

        virtual equation<T> simplify() const override {
            auto r = rhs.simplify();
            return equation<T>(new operation_log(r.eq));
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            return (rhs.derivative(d) / rhs).simplify();
        }

    protected:
        const equation<T> rhs;
};

/**
 * Exponentiation equation.
 * @tparam T Type of data used in equation.
 */
template<typename T>
class operation_pow : public base_equation<T> {
    public:
        operation_pow(const base_equation<T>* l, const base_equation<T>* r) :
            base_equation<T>(),
            lhs(l), rhs(r) {}

        virtual T operator()() const override {
            return std::pow(lhs(), rhs());
        }

        virtual void print(std::ostream& os) const override {
            if(lhs.precedence() > precedence()){
                os << "(" << lhs << ")";
            }else{
                os << lhs;
            }
            os << "^";
            if(rhs.precedence() > precedence()){
                os << "(" << rhs << ")";
            }else{
                os << rhs;
            }
        }

        virtual int precedence() const override {
            return PRECEDENCE_EXPONENT;
        }

        virtual equation<T> simplify() const override {
            auto l = lhs.simplify();
            auto r = rhs.simplify();
            if(l.eq->is_constant()){
                if(l() == 0){
                    return equation(new constant<T>(0));
                }else if(l() == 1){
                    return equation(new constant<T>(1));
                }else if(r.eq->is_constant()){
                    return equation(new constant(std::pow(l(), r())));
                }
            }else if(r.eq->is_constant()){
                if(r() == 0){
                    return equation(new constant<T>(1));
                }else if(r() == 1){
                    return l;
                }
            }
            return l.eq->pow(*r.eq);
        }

        virtual equation<T> derivative(const symbol<T>& d) const override {
            if(rhs.eq->is_constant() && rhs() > 0){
                return (rhs * lhs.pow(rhs - constant<T>(1))).simplify();
            }else{
                return (lhs.pow(rhs) * ((lhs.derivative(d) * (rhs / lhs)) + (rhs.derivative(d) * new operation_log<T>(lhs.eq)))).simplify();
            }
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
            return this->name == rhs.name;
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

        virtual int precedence() const override {
            return PRECEDENCE_PARENTHESIS;
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
        explicit constant(const T& v) :
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

        virtual int precedence() const override {
            return PRECEDENCE_PARENTHESIS;
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

/**
 * User-defined literal operator.
 * @param x Literal.
 * @return Symbolic constant.
 */
constant<double> operator""_sym(long double x) {
    return constant(static_cast<double>(x));
}

} // namespace equation
} // namespace tmp

#endif // TMP_EQUATION_EQUATION_H_
