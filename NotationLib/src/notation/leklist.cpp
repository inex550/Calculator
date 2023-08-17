#include <notation/except.h>
#include <notation/leklist.h>

#include <cmath>
#include <cstddef>

namespace nex {
    double LekList::CalcX(double x) {
        numbers_.clear();

        for (const Leksem& lek : nodes_) {
            if (lek.IsNumber()) {
                numbers_.push_back(lek.num);
            } else if (lek.IsX()) {
                numbers_.push_back(x);
            } else {
                if (lek.op == LekOperator::PLUS && numbers_.size() >= 2) {
                    numbers_[numbers_.size() - 2] = numbers_[numbers_.size() - 2] + numbers_[numbers_.size() - 1];
                    numbers_.pop_back();
                } else if (lek.op == LekOperator::MINUS && numbers_.size() >= 2) {
                    numbers_[numbers_.size() - 2] = numbers_[numbers_.size() - 2] - numbers_[numbers_.size() - 1];
                    numbers_.pop_back();
                } else if (lek.op == LekOperator::MULT && numbers_.size() >= 2) {
                    numbers_[numbers_.size() - 2] = numbers_[numbers_.size() - 2] * numbers_[numbers_.size() - 1];
                    numbers_.pop_back();
                } else if (lek.op == LekOperator::DIV && numbers_.size() >= 2) {
                    numbers_[numbers_.size() - 2] = numbers_[numbers_.size() - 2] / numbers_[numbers_.size() - 1];
                    numbers_.pop_back();
                } else if (lek.op == LekOperator::POW && numbers_.size() >= 2) {
                    numbers_[numbers_.size() - 2] = std::pow(numbers_[numbers_.size() - 2], numbers_[numbers_.size() - 1]);
                    numbers_.pop_back();
                } else if (lek.op == LekOperator::MOD && numbers_.size() >= 2) {
                    numbers_[numbers_.size() - 2] = std::fmod(numbers_[numbers_.size() - 2], numbers_[numbers_.size() - 1]);
                    numbers_.pop_back();
                } else if (lek.op == LekOperator::FUNC_SIN && numbers_.size() >= 1) {
                    numbers_.back() = std::sin(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_COS && numbers_.size() >= 1) {
                    numbers_.back() = std::cos(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_TAN && numbers_.size() >= 1) {
                    numbers_.back() = std::tan(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_ASIN && numbers_.size() >= 1) {
                    numbers_.back() = std::asin(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_ACOS && numbers_.size() >= 1) {
                    numbers_.back() = std::acos(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_ATAN && numbers_.size() >= 1) {
                    numbers_.back() = std::atan(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_LN && numbers_.size() >= 1) {
                    numbers_.back() = std::log(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_LOG && numbers_.size() >= 1) {
                    numbers_.back() = std::log10(numbers_.back());
                } else if (lek.op == LekOperator::FUNC_SQRT && numbers_.size() >= 1) {
                    numbers_.back() = std::sqrt(numbers_.back());
                } else if (lek.op == LekOperator::UNARY_MINUS && numbers_.size() >= 1) {
                    numbers_.back() = -numbers_.back();
                } else if (lek.op != LekOperator::UNARY_PLUS || numbers_.size() < 1) {
                    throw notation_error("Illegal arguments count in one of operators");
                }
            }
        }

        if (numbers_.size() < 1) {
            throw notation_error("No one number");
        }
        if (numbers_.size() > 1) {
            throw notation_error("Too many numbers");
        }

        return numbers_[0];
    }
}  // namespace nex