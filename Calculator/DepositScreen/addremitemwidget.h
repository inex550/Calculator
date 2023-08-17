#ifndef __DEPOSITSCREEN_ADDREMITEMWIDGET_H__
#define __DEPOSITSCREEN_ADDREMITEMWIDGET_H__

#include <DepositScreen/addremitem.h>

#include <QDialog>
#include <QListWidget>

namespace Ui {
    class AddRemItemWidget;
}

namespace nex {
    class AddRemItemWidget : public QDialog {
    Q_OBJECT

    public:
        explicit AddRemItemWidget(QWidget *parent = nullptr);
        ~AddRemItemWidget();

        AddRemItem ShowItem(bool &ok);

    private:
        Ui::AddRemItemWidget *ui;

        bool addClicked_;

        private slots:
        void AddBtnClicked();
    };
}  // namespace nex

#endif  // __DEPOSITSCREEN_ADDREMITEMWIDGET_H__
