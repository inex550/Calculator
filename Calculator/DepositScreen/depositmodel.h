#ifndef __DEPOSITSCREEN_DEPOSITMODEL_H__
#define __DEPOSITSCREEN_DEPOSITMODEL_H__

#include <DepositScreen/addremitem.h>

#include <QList>

namespace nex {
    class DepositModel {
    public:
        void ComputeDeposit(
            double sum, int placement, double percent, bool capitalizePercent,
            const QList<AddRemItem>& adds, const QList<AddRemItem>& rems
        );

        double GetTotalPercent() { return totalPercent_; }
        double GetTotalTax() { return totalTax_; }
        double GetTotalSum() { return totalSum_; }

    private:
        double GetAddsByMonth(int month, const QList<AddRemItem>& adds, const QList<AddRemItem>& rems);

    private:
        double totalPercent_ = 0.0;
        double totalTax_ = 0.0;
        double totalSum_ = 0.0;
    };
}  // namespace nex

#endif  //  __DEPOSITSCREEN_DEPOSITMODEL_H__
