#include <CreditScreen/creditcontroller.h>
#include <CreditScreen/creditwindow.h>

namespace nex {
    void CreditController::PerformAnnuiteCalc(double creditSum, double creditTerm, double percent) {
        model_.CalcAnnuite(creditSum, creditTerm, percent);

        view_->ShowMonthPayment(QString::number(model_.GetMonthPayment()) + " ₽");
        view_->ShowOverpayment(QString::number(model_.GetOverpayment()) + " ₽");
        view_->ShowTotalPayment(QString::number(model_.GetTotalPayement()) + " ₽");
    }

    void CreditController::PerformDifferentiatedCalc(double creditSum, double creditTerm, double percent) {
        model_.CalcDifferentiated(creditSum, creditTerm, percent);

        view_->ShowMonthPayment(
            QString::number(model_.GetStartMonthPayment()) + " ₽ ... " +
            QString::number(model_.GetEndMonthPayement()) + " ₽"
        );
        view_->ShowOverpayment(QString::number(model_.GetOverpayment()) + " ₽");
        view_->ShowTotalPayment(QString::number(model_.GetTotalPayement()) + " ₽");
    }
}  // namespace nex
