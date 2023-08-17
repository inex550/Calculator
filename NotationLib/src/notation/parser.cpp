#include <notation/parser.h>

#include "parserUtils.h"

namespace nex {
    LekList NotationParser::parseRawString(const char* str) {
        LekList outList;
        LekList tmpList;

        // Означает что в текущей итерации текущий символ
        // должен пренадлежать оператору (НЕ унарному)
        bool isOperatorPart = false;
        bool nextOnlyBkt = false;

        for (const char* strPtr = str; *strPtr != '\0'; ++strPtr) {
            char strCh = tolower(*strPtr);

            // Если последняя лексема в списке это функция
            // То текущая лексема должна быть открывающей скобкой
            if (nextOnlyBkt && !isspace(static_cast<int>(strCh)) && strCh != LekOperator::BKT_OPEN) {
                throw notation_error("Function has no brackets");
            }

            if (isdigit(static_cast<int>(strCh)) || strCh == 'x') {
                if (isOperatorPart) {
                    throw notation_error("Multiple numbers in a row");
                }

                if (strCh == 'x') {
                    outList.PushBack(Leksem::LekX());
                } else {
                    strPtr = AddNumber(strPtr, outList);
                }
                isOperatorPart = true;
                nextOnlyBkt = false;
            } else if (isalpha(static_cast<int>(strCh))) {
                strPtr = AddFunctionOrThrow(strPtr, tmpList);
                isOperatorPart = false;
                nextOnlyBkt = true;
            } else if (IsOperator(strCh)) {
                AddOperatorOrThrow(strCh, outList, tmpList, !isOperatorPart);
                isOperatorPart = false;
                nextOnlyBkt = false;
            }

            else if (strCh == LekOperator::BKT_OPEN) {
                tmpList.PushBack(LekOperator(LekOperator::BKT_OPEN));
                isOperatorPart = false;
                nextOnlyBkt = false;
            } else if (strCh == LekOperator::BKT_CLOSE) {
                AddBracketOperatorsOrThrow(outList, tmpList);
                isOperatorPart = true;
                nextOnlyBkt = false;
            }

            else if (!isspace(static_cast<int>(strCh))) {
                throw notation_error("Unknown symbol");
            }
        }

        while (!tmpList.IsEmpty()) {
            Leksem& lek = tmpList.LastLek();
            if (lek.op == LekOperator::BKT_OPEN) {
            throw notation_error("Open bracket is not closed");
            }

            outList.PushBack(lek);
            tmpList.PopBack();
        }

        return outList;
    }
}  // namespace nex