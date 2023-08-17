#ifndef __CREDITSCREEN_CREDITWINDOW_H__
#define __CREDITSCREEN_CREDITWINDOW_H__

#include <CreditScreen/creditcontroller.h>

#include <QMainWindow>

namespace Ui {
    class CreditWindow;
}

namespace nex {
    class CreditWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit CreditWindow(QWidget *parent = nullptr);
        ~CreditWindow();

        void ShowMonthPayment(QString monthPaymentStr);
        void ShowOverpayment(QString overpaymentStr);
        void ShowTotalPayment(QString totalPaymentStr);

    private slots:
        void CalcBtnClicked();

    private:
        Ui::CreditWindow *ui;
        CreditController controller_;
    };
}  // namespace nex

#endif  // __CREDITSCREEN_CREDITWINDOW_H__
