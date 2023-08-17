#include "addremitemwidget.h"

#include "ui_addremitemwidget.h"

namespace nex {
    AddRemItemWidget::AddRemItemWidget(QWidget* parent)
        : QDialog(parent)
        , ui(new Ui::AddRemItemWidget)
    {
        ui->setupUi(this);

        addClicked_ = false;

        connect(ui->addBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
    }

    AddRemItemWidget::~AddRemItemWidget() { delete ui; }

    AddRemItem AddRemItemWidget::ShowItem(bool& ok) {
        this->exec();

        bool isMonthOk = false;
        bool isSumOk = false;

        int month = ui->monthEdit->text().toInt(&isMonthOk);
        double sum = ui->sumEdit->text().toDouble(&isSumOk);

        ok = addClicked_ && isMonthOk && isSumOk;

        AddRemItem res;
        res.month = month;
        res.sum = sum;
        return res;
    }

    void AddRemItemWidget::AddBtnClicked() {
        addClicked_ = true;
        close();
    }
}  // namespace nex
