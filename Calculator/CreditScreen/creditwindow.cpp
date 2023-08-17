#include "creditwindow.h"

#include <QMessageBox>

#include "ui_creditwindow.h"

namespace nex {
    CreditWindow::CreditWindow(QWidget *parent)
        : QMainWindow(parent)
        , ui(new Ui::CreditWindow)
        , controller_(this)
    {
        ui->setupUi(this);

        ui->calcTypeCB->addItem("Аннуитетный");
        ui->calcTypeCB->addItem("Дифференцированный");

        connect(ui->calcBtn, SIGNAL(clicked()), this, SLOT(CalcBtnClicked()));
    }

    CreditWindow::~CreditWindow() { delete ui; }

    void CreditWindow::CalcBtnClicked() {
        bool creditSumOk = false;
        bool creditTermOk = false;
        bool interestRateOk = false;

        double creditSum = ui->creditSumEdit->text().toDouble(&creditSumOk);
        int creditTerm = ui->creditTermEdit->text().toInt(&creditTermOk);
        double interestRate = ui->interestRateEdit->text().toDouble(&interestRateOk);

        if (creditSumOk && creditTermOk && interestRateOk) {
            if (ui->calcTypeCB->currentIndex() == 0) {
                controller_.PerformAnnuiteCalc(creditSum, creditTerm, interestRate);
            } else if (ui->calcTypeCB->currentIndex() == 1) {
                controller_.PerformDifferentiatedCalc(creditSum, creditTerm, interestRate);
            } else {
                QMessageBox::critical(this, "Error", "Необходимо выбрать тип кредита");
            }
        } else {
            QMessageBox::critical(this, "Error", "Поля заполнены некорректно");
        }
    }

    void CreditWindow::ShowMonthPayment(QString monthPaymentStr) {
        ui->monthPayLabel->setText(monthPaymentStr);
    }

    void CreditWindow::ShowOverpayment(QString overpaymentStr) {
        ui->overpaymentLabel->setText(overpaymentStr);
    }

    void CreditWindow::ShowTotalPayment(QString totalPaymentStr) {
        ui->totalPayLabel->setText(totalPaymentStr);
    }
}  // namespace nex
