#include <DepositScreen/depositwindow.h>

#include <QMessageBox>

#include "ui_depositwindow.h"

namespace nex {
    DepositWindow::DepositWindow(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::DepositWindow)
        , controller_(this)
    {
        ui->setupUi(this);

        addsItems_ = QList<AddRemItem>();
        remsItems_ = QList<AddRemItem>();

        ui->periodCB->addItem("Раз в месяц");
        ui->periodCB->addItem("Раз в год");

        connect(ui->addAddsBtn, SIGNAL(clicked()), this, SLOT(AddAddsBtnClicked()));
        connect(ui->addRemsBtn, SIGNAL(clicked()), this, SLOT(AddRemsBtnClicked()));
        connect(ui->removeSelectedBtn, SIGNAL(clicked()), this,
                SLOT(RemoveSelectedBtnClicked()));
        connect(ui->calcBtn, SIGNAL(clicked()), this, SLOT(CalcDepositClicked()));
    }

    DepositWindow::~DepositWindow() { delete ui; }

    void DepositWindow::AddAddsBtnClicked() {
        bool isOk = false;

        AddRemItemWidget* newItem = new AddRemItemWidget(this);
        auto item = newItem->ShowItem(isOk);

        if (isOk) {
            addsItems_.push_back(item);
            ui->addsList->addItem("Через " + QString::number(item.month) +
                                " месяцев. Сумма: " + QString::number(item.sum));
        }
    }

    void DepositWindow::AddRemsBtnClicked() {
        bool isOk = false;

        AddRemItemWidget* newItem = new AddRemItemWidget(this);
        auto item = newItem->ShowItem(isOk);
        item.sum *= -1;

        if (isOk) {
            remsItems_.push_back(item);
            ui->remsList->addItem("Через " + QString::number(item.month) + " месяцев. Сумма: " + QString::number(item.sum));
        }
    }

    void DepositWindow::RemoveSelectedBtnClicked() {
        auto adds = ui->addsList->selectedItems();
        auto rems = ui->remsList->selectedItems();

        for (auto addItem : adds) {
            addsItems_.removeAt(ui->addsList->row(addItem));
            delete addItem;
        }
        for (auto remItem : rems) {
            remsItems_.removeAt(ui->remsList->row(remItem));
            delete remItem;
        }
    }

    void DepositWindow::CalcDepositClicked() {
        bool isOkSum = false;
        bool isOkPlacement = false;
        bool isOkPercent = false;

        double sum = ui->sumEdit->text().toDouble(&isOkSum);
        int placement = ui->placementEdit->text().toInt(&isOkPlacement);
        double percent = ui->percentEdit->text().toDouble(&isOkPercent);
        bool capitalizePercent = ui->capitalPercentCB->isChecked();

        if (isOkSum && isOkPlacement && isOkPercent) {
            controller_.PerformDepositCalc(sum, placement, percent, capitalizePercent, addsItems_, remsItems_);
        } else {
            QMessageBox::critical(this, "Error", "Поля заполнены некорректно");
        }
    }

    void DepositWindow::ShowTotalPercent(QString totalPercentStr) {
        ui->percentsLabel->setText(totalPercentStr);
    }

    void DepositWindow::ShowTotalTax(QString totalTaxStr) {
        ui->taxLabel->setText(totalTaxStr);
    }

    void DepositWindow::ShowTotalSum(QString totalSum) {
        ui->totalSumLabel->setText(totalSum);
    }
}  // namespace nex
