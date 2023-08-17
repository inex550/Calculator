#ifndef __NOTATION_LEKNODE_H__
#define __NOTATION_LEKNODE_H__

namespace nex {
    struct LekOperator {
        using operator_type = char;

        enum Operators {
            NONE = '\0',

            PLUS = '+',
            MINUS = '-',
            MULT = '*',
            DIV = '/',
            POW = '^',
            MOD = '%',
            BKT_OPEN = '(',
            BKT_CLOSE = ')',
            UNARY_PLUS = '#',
            UNARY_MINUS = '~',

            FUNC_SIN = 's',
            FUNC_COS = 'c',
            FUNC_TAN = 't',
            FUNC_ASIN = '1',
            FUNC_ACOS = '2',
            FUNC_ATAN = '3',
            FUNC_LN = 'l',
            FUNC_LOG = 'L',
            FUNC_SQRT = 'q',
        };

        enum Sides {
            SIDE_LEFT,
            SIDE_RIGHT,
        };

        LekOperator() {}

        LekOperator(operator_type opChar) : opChar(opChar) {}

        bool operator==(operator_type opChar) const { return this->opChar == opChar; }

        bool operator!=(operator_type opChar) const { return this->opChar != opChar; }

        int GetRank();

        Sides GetSide();

        bool IsFunction();

        operator_type opChar = Operators::NONE;
    };

    struct Leksem {
        Leksem() {}

        Leksem(double num) : num(num) {}

        Leksem(LekOperator op) : op(op) {}

        bool IsNumber() const { return !IsOperator() && !IsX(); }

        bool IsOperator() const { return op != LekOperator::NONE; }

        bool IsX() const { return isX; }

        static Leksem LekX() {
            Leksem lek;
            lek.isX = true;
            return lek;
        }

        double num = 0.0;
        LekOperator op = LekOperator::NONE;
        bool isX = false;
    };
}  // namespace nex

#endif  // __NOTATION_LEKNODE_H__