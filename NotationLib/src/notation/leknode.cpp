#include <notation/leknode.h>

namespace nex {
    int LekOperator::GetRank() {
        int rank = 0;

        switch (opChar) {
            case PLUS:
            case MINUS:
            rank = 1;
            break;

            case MULT:
            case DIV:
            case MOD:
            rank = 2;
            break;

            case UNARY_MINUS:
            case UNARY_PLUS:
            rank = 3;
            break;

            case POW:
            rank = 4;
            break;

            case FUNC_SIN:
            case FUNC_COS:
            case FUNC_TAN:
            case FUNC_ASIN:
            case FUNC_ACOS:
            case FUNC_ATAN:
            case FUNC_LN:
            case FUNC_LOG:
            case FUNC_SQRT:
            rank = 5;
            break;
        }

        return rank;
    }

    LekOperator::Sides LekOperator::GetSide() {
        Sides side = SIDE_LEFT;

        switch (opChar) {
            case POW:
            case UNARY_PLUS:
            case UNARY_MINUS:
            side = SIDE_RIGHT;
            break;
        }

        return side;
    }

    bool LekOperator::IsFunction() {
        bool result = false;

        switch (opChar) {
            case FUNC_SIN:
            case FUNC_COS:
            case FUNC_TAN:
            case FUNC_ASIN:
            case FUNC_ACOS:
            case FUNC_ATAN:
            case FUNC_LN:
            case FUNC_LOG:
            case FUNC_SQRT:
                result = true;
                break;
        }

        return result;
    }
}  // namespace nex