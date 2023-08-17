#ifndef __CREDITSCREEN_CREDITMODEL_H__
#define __CREDITSCREEN_CREDITMODEL_H__

namespace nex {
    class CreditModel {
    public:
        void CalcAnnuite(double creditSum, double creditTerm, double percent);

        void CalcDifferentiated(double creditSum, double creditTerm, double percent);

        double GetMonthPayment() { return monthPayment_; }

        double GetStartMonthPayment() { return startMonthPayment_; }

        double GetEndMonthPayement() { return endMonthPayment_; }

        double GetOverpayment() { return overpayment_; }

        double GetTotalPayement() { return totalPayment_; }

    private:
        double monthPayment_ = 0.0;
        double startMonthPayment_ = 0.0;
        double endMonthPayment_ = 0.0;

        double overpayment_ = 0.0;

        double totalPayment_ = 0.0;
    };
}  // namespace nex

#endif  // __CREDITSCREEN_CREDITMODEL_H__
