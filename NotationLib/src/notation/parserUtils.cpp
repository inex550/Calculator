#include "parserUtils.h"

#include <cstdio>
#include <cstring>

namespace nex {
    bool IsOperator(char sim) {
        switch (sim) {
            case LekOperator::PLUS:
            case LekOperator::MINUS:
            case LekOperator::MULT:
            case LekOperator::DIV:
            case LekOperator::POW:
            case LekOperator::MOD:
            case LekOperator::UNARY_PLUS:
            case LekOperator::UNARY_MINUS:
                return true;
                break;
        }

        return false;
    }

    const char* AddNumber(const char* str, LekList& outList) {
        double number = 0.0;
        int numberLength = 0;
        std::sscanf(str, "%lf%n", &number, &numberLength);

        outList.PushBack(Leksem(number));

        // Указатель на последний символ
        return str + numberLength - 1;
    }

    const char* AddFunctionOrThrow(const char* str, LekList& tmpList) {
        int funcCharLength = 0;

        if (strncmp(str, "sin", 3) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_SIN));
            funcCharLength = 3;
        } else if (strncmp(str, "cos", 3) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_COS));
            funcCharLength = 3;
        } else if (strncmp(str, "tan", 3) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_TAN));
            funcCharLength = 3;
        } else if (strncmp(str, "asin", 4) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_ASIN));
            funcCharLength = 4;
        } else if (strncmp(str, "acos", 4) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_ACOS));
            funcCharLength = 4;
        } else if (strncmp(str, "atan", 4) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_ATAN));
            funcCharLength = 4;
        } else if (strncmp(str, "ln", 2) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_LN));
            funcCharLength = 2;
        } else if (strncmp(str, "log", 3) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_LOG));
            funcCharLength = 3;
        } else if (strncmp(str, "sqrt", 4) == 0) {
            tmpList.PushBack(LekOperator(LekOperator::FUNC_SQRT));
            funcCharLength = 4;
        } else {
            throw notation_error("Can't recognize function in expression");
        }

        // Указатель на последний символ
        return str + funcCharLength - 1;
    }

    void AddOperatorOrThrow(LekOperator op, LekList& outList, LekList& tmpList, bool shouldBeUnary) {
        if (shouldBeUnary) {
            if (op == LekOperator::PLUS) {
                op = LekOperator::UNARY_PLUS;
            } else if (op == LekOperator::MINUS) {
                op = LekOperator::UNARY_MINUS;
            } else {
                throw notation_error("Operator is in wrong place");
            }
        }

        while (!tmpList.IsEmpty()) {
            Leksem& lek = tmpList.LastLek();
            if (lek.op.GetRank() > op.GetRank() || (lek.op.GetSide() == LekOperator::SIDE_LEFT && lek.op.GetRank() == op.GetRank())) {
                outList.PushBack(lek);
                tmpList.PopBack();
            } else {
                // Выход из цикла если лексема не удовлетворяет условиям
                break;
            }
        }

        tmpList.PushBack(op);
    }

    void AddBracketOperatorsOrThrow(LekList& outList, LekList& tmpList) {
        while (!tmpList.IsEmpty()) {
            Leksem& lek = tmpList.LastLek();

            if (lek.op == LekOperator::BKT_OPEN) {
            // Выход из цикла если лексема это открывающая скобка
            break;
            }

            outList.PushBack(lek);
            tmpList.PopBack();
        }

        if (tmpList.IsEmpty()) {
            // Ошибка, если весь tmpList стёрся, но открывающая скобка так и не нашлась
            throw notation_error("Can't find opening bracket");
        }

        // Ошибки не произошло, значит последняя лексема в списке это открывающая
        // скобка Её нужно удалить
        tmpList.PopBack();
    }
}  // namespace nex