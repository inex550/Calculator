#ifndef __NOTATION_PARSER_H__
#define __NOTATION_PARSER_H__

#include <notation/leklist.h>

#include <string>

namespace nex {
    class NotationParser {
    public:
        LekList parseRawString(const char* str);

        LekList paraseString(const std::string& str) {
            return parseRawString(str.c_str());
        }
    };
}  // namespace nex

#endif  // __NOTATION_PARSER_H__