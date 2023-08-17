#include <DepositScreen/depositmodel.h>

namespace nex {
    void DepositModel::ComputeDeposit(
        double sum, int placement, double percent,
        bool capitalizePercent,
        const QList<AddRemItem>& adds,
        const QList<AddRemItem>& rems
    ) {
        percent /= 100;

        totalPercent_ = 0.0;
        totalTax_ = 0.0;

        double monthTaxLim = (1000000 * 0.45) / 12;

        for (int month = 1; month <= placement; ++month) {
            double monthPercent = sum * percent;
            double monthTax = (monthPercent - monthTaxLim) * 0.13;
            if (monthTax < 0) monthTax = 0;

            monthPercent -= monthTax;
            totalTax_ += monthTax;

            totalPercent_ += monthPercent;

            double addsSum = GetAddsByMonth(month, adds, rems);
            sum += addsSum;

            if (capitalizePercent) {
            sum += monthPercent;
            }
        }

        totalSum_ = sum;
    }

    double DepositModel::GetAddsByMonth(int month, const QList<AddRemItem>& adds, const QList<AddRemItem>& rems) {
        double addsSum = 0.0;
        double remsSum = 0.0;

        for (const AddRemItem& addItem : adds) {
            if (addItem.month == month) addsSum += addItem.sum;
        }

        for (const AddRemItem& remItem : rems) {
            if (remItem.month == month) remsSum += remItem.sum;
        }

        return addsSum + remsSum;
    }
}  // namespace nex
