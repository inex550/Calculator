#ifndef __PLOTSCREEN_PLOTCONTROLLER_H__
#define __PLOTSCREEN_PLOTCONTROLLER_H__

#include <notationmodel.h>

#include <QString>

namespace nex {
    class PlotWindow;

    class PlotController {
    public:
        PlotController(PlotWindow* view) : view_(view) {}

        void PerformCompute(const QString& expression, double fromX, double toX, double fromY, double toY);

    private:
        PlotWindow* view_;
        NotationModel model_;
    };
}  // namespace nex

#endif  // __PLOTSCREEN_PLOTCONTROLLER_H__
