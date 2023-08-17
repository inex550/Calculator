#ifndef __NOTATION_PARSER_UTILS_H__
#define __NOTATION_PARSER_UTILS_H__

#include <notation/except.h>
#include <notation/leklist.h>

namespace nex {
    #define OP_SIDE_LEFT 1
    #define OP_SIDE_RIGHT 2

    bool IsOperator(char sim);

    int OperatorRank(LekOperator op);

    int OperatorSide(LekOperator op);

    const char* AddNumber(const char* str, LekList& outList);

    const char* AddFunctionOrThrow(const char* str, LekList& tmpList);

    void AddOperatorOrThrow(LekOperator op, LekList& outList, LekList& tmpList, bool shouldBeUnary);

    void AddBracketOperatorsOrThrow(LekList& outList, LekList& tmpList);
}  // namespace nex

#endif  // __NOTATION_PARSER_UTILS_H__