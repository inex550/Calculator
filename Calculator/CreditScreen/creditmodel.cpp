#include <CreditScreen/creditmodel.h>

#include <cmath>

namespace nex {
    void CreditModel::CalcAnnuite(double creditSum, double creditTerm, double percent) {
        percent /= 100.0;
        double monthPerPay = std::pow(1 + percent, creditTerm);

        monthPayment_ = creditSum * ((percent * monthPerPay) / (monthPerPay - 1));
        totalPayment_ = monthPayment_ * creditTerm;
        overpayment_ = totalPayment_ - creditSum;
    }

    void CreditModel::CalcDifferentiated(double creditSum, double creditTerm, double percent) {
        percent /= 100;

        double monthSumPayment = creditSum / creditTerm;

        overpayment_ = 0.0;
        totalPayment_ = 0.0;

        for (int i = 1; i <= creditTerm; ++i) {
            monthPayment_ = creditSum * (percent * ((double)i / (double)creditTerm));
            monthPayment_ += monthSumPayment;

            if (i == creditTerm) {
                startMonthPayment_ = monthPayment_;
            }

            if (i == 1) {
                endMonthPayment_ = monthPayment_;
            }

            totalPayment_ += monthPayment_;
        }

        overpayment_ = totalPayment_ - creditSum;
    }
}  // namespace nex
