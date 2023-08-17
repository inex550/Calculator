#ifndef __CALCSCREEN_CALCCONTROLLER_H__
#define __CALCSCREEN_CALCCONTROLLER_H__

#include <notationmodel.h>

#include <QString>

namespace nex {
    class CalcWindow;

    class CalcController {
    public:
        CalcController(CalcWindow* view) : view_(view) {}

        void PerformCompute(const QString& expression, double x);

    private:
        CalcWindow* view_;

        NotationModel model_;
    };
}  // namespace nex

#endif  // __CALCSCREEN_CALCCONTROLLER_H__
