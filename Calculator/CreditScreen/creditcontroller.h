#ifndef __CREDITSCREEN_CREDITCONTROLLER_H__
#define __CREDITSCREEN_CREDITCONTROLLER_H__

#include <CreditScreen/creditmodel.h>

namespace nex {
class CreditWindow;

class CreditController {
    public:
        CreditController(CreditWindow* view) : view_(view) {}

        void PerformAnnuiteCalc(double creditSum, double creditTerm, double percent);

        void PerformDifferentiatedCalc(double creditSum, double creditTerm, double percent);

    private:
        CreditWindow* view_;
        CreditModel model_;
    };
}  // namespace nex

#endif  // __CREDITSCREEN_CREDITCONTROLLER_H__
