#include <DepositScreen/depositcontroller.h>
#include <DepositScreen/depositwindow.h>

namespace nex {
    void DepositController::PerformDepositCalc(
        double sum, int placement,
        double percent,
        bool capitalizePercent,
        const QList<AddRemItem>& adds,
        const QList<AddRemItem>& rems
    ) {
        model_.ComputeDeposit(sum, placement, percent, capitalizePercent, adds, rems);

        view_->ShowTotalPercent(QString::number(model_.GetTotalPercent()) + " ₽");
        view_->ShowTotalTax(QString::number(model_.GetTotalTax()) + " ₽");
        view_->ShowTotalSum(QString::number(model_.GetTotalSum()) + " ₽");
    }
}  // namespace nex
