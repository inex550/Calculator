#ifndef __DEPOSITSCREEN_DEPOSITWINDOW_H__
#define __DEPOSITSCREEN_DEPOSITWINDOW_H__

#include <DepositScreen/depositcontroller.h>

#include <QMainWindow>

#include "addremitemwidget.h"

namespace Ui {
    class DepositWindow;
}

namespace nex {
    class DepositWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit DepositWindow(QWidget *parent = nullptr);
        ~DepositWindow();

        void ShowTotalPercent(QString totalPercentStr);
        void ShowTotalTax(QString totalTaxStr);
        void ShowTotalSum(QString totalSum);

        private slots:
        void AddAddsBtnClicked();
        void AddRemsBtnClicked();
        void RemoveSelectedBtnClicked();
        void CalcDepositClicked();

    private:
        Ui::DepositWindow *ui;
        DepositController controller_;

        QList<AddRemItem> addsItems_;
        QList<AddRemItem> remsItems_;
    };
}  // namespace nex

#endif  // __DEPOSITSCREEN_DEPOSITWINDOW_H__
