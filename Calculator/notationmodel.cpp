#include <notationmodel.h>

namespace nex {
    #define DEFAULT_GRAPHIC_ITEMS_LEN 100

    #define EXPAND_X_TIMES 5

    #define MAX_GRAPHIC_ITEMS 20000

    void NotationModel::computeExpression(const QString& expression, double x) {
        error_.clear();

        try {
            computeResult_ = parser.paraseString(expression.toStdString()).CalcX(x);
        } catch (notation_error e) {
            error_ = e.what();
        }
    }

    void NotationModel::computeGraphic(const QString& expression, double fromX, double toX) {
        error_.clear();

        fromX *= EXPAND_X_TIMES;
        toX *= EXPAND_X_TIMES;

        try {
            LekList lekList = parser.paraseString(expression.toStdString());

            double delta = toX - fromX;

            // size_t len = std::max(static_cast<size_t>(delta * 10.0),
            // static_cast<size_t>(DEFAULT_GRAPHIC_ITEMS_LEN)); len = std::min(len,
            // static_cast<size_t>(MAX_GRAPHIC_ITEMS));

            size_t len = MAX_GRAPHIC_ITEMS;

            double step = delta / len;

            arrX_.clear();
            arrY_.clear();
            arrX_.reserve(len);
            arrY_.reserve(len);

            for (size_t i = 0; i < len; ++i) {
                arrX_.push_back(fromX + step * i);
                arrY_.push_back(lekList.CalcX(arrX_[i]));
            }
        } catch (notation_error e) {
            error_ = e.what();
        }
    }
}  // namespace nex
