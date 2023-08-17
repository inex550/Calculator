#ifndef __DEPOSITSCREEN_DEPOSITCONTROLLER_H__
#define __DEPOSITSCREEN_DEPOSITCONTROLLER_H__

#include <DepositScreen/depositmodel.h>

namespace nex {
    class DepositWindow;

    class DepositController {
    public:
        DepositController(DepositWindow* view) : view_(view) {}

        void PerformDepositCalc(
            double sum, int placement, double percent, bool capitalizePercent, 
            const QList<AddRemItem>& adds, const QList<AddRemItem>& rems
        );

    private:
        DepositWindow* view_;
        DepositModel model_;
    };
}  // namespace nex

#endif  // __DEPOSITSCREEN_DEPOSITCONTROLLER_H__
