#include <CalcScreen/calccontroller.h>
#include <CalcScreen/calcwindow.h>

namespace nex {
    void CalcController::PerformCompute(const QString& expression, double x) {
        model_.computeExpression(expression, x);

        if (model_.GetError().isEmpty()) {
            view_->ShowResult(model_.GetComputeResult());
        } else {
            view_->ShowError(model_.GetError());
        }
    }
}  // namespace nex
