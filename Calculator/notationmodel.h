#ifndef __NOTATIONMODEL_H__
#define __NOTATIONMODEL_H__

#include <notation/except.h>
#include <notation/parser.h>

#include <QList>
#include <QString>
#include <vector>

namespace nex {
    class NotationModel {
    public:
        void computeExpression(const QString& expression, double x);

        void computeGraphic(const QString& expression, double fromX, double toX);

        const QList<double>& GetArrX() { return arrX_; }
        const QList<double>& GetArrY() { return arrY_; }

        double GetComputeResult() { return computeResult_; }

        const QString& GetError() { return error_; }

    private:
        QList<double> arrX_;
        QList<double> arrY_;

        double computeResult_;

        QString error_;

        nex::NotationParser parser;
    };
}  // namespace nex

#endif  // __NOTATIONMODEL_H__
