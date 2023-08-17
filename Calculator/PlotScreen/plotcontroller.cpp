#include <PlotScreen/plotcontroller.h>
#include <PlotScreen/plotwindow.h>

namespace nex {
    void PlotController::PerformCompute(const QString& expression, double fromX, double toX, double fromY, double toY) {
        model_.computeGraphic(expression, fromX, toX);

        if (model_.GetError().isEmpty()) {
            view_->RedrawPlot(fromX, toX, fromY, toY, model_.GetArrX(),
                            model_.GetArrY());
        } else {
            view_->ShowError(model_.GetError());
        }
    }
}  // namespace nex
