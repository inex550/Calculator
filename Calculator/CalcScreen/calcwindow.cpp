#include "calcwindow.h"

#include <QApplication>
#include <QFile>
#include <QMessageBox>

#include "CreditScreen/creditwindow.h"
#include "DepositScreen/depositwindow.h"
#include "PlotScreen/plotwindow.h"
#include "ui_calcwindow.h"

namespace nex {
    CalcWindow::CalcWindow(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::CalcWindow)
        , controller(this)
    {
        ui->setupUi(this);

        ui->editCalc->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
        ui->editOut->setAlignment(Qt::AlignRight | Qt::AlignVCenter);

        connect(ui->actionCredit, SIGNAL(triggered()), this, SLOT(OpenCreditCalc()));
        connect(ui->actionDeposit, SIGNAL(triggered()), this,
                SLOT(OpenDepositCalc()));

        ConnectButtons();

        this->setMinimumSize(this->width(), this->height());
    }

    CalcWindow::~CalcWindow() { delete ui; }

    void CalcWindow::ConnectButtons() {
        connect(ui->n1_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n2_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n3_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n4_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n5_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n6_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n7_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n8_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n9_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->n0_btn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));

        connect(ui->plusBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->minusBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->mulBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->divBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));

        connect(ui->sinBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->cosBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->tanBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->asinBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->acosBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->atanBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));

        connect(ui->lnBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->logBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->powBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->modBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->sqrtBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));

        connect(ui->openBktBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->closeBktBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->dotBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));
        connect(ui->xBtn, SIGNAL(clicked()), this, SLOT(AddBtnClicked()));

        connect(ui->acBtn, SIGNAL(clicked()), this, SLOT(RmBtnClicked()));
        connect(ui->rmBtn, SIGNAL(clicked()), this, SLOT(RmBtnClicked()));

        connect(ui->computeBtn, SIGNAL(clicked()), this, SLOT(ComputeBtnClicked()));
        connect(ui->drawBtn, SIGNAL(clicked()), this, SLOT(DrawBtnClicked()));
    }

    void CalcWindow::keyPressEvent(QKeyEvent* event) {
        if (event->key() == Qt::Key_Backspace) {
            ui->rmBtn->click();
        }

        switch (event->key()) {
        case Qt::Key_1:
            ui->n1_btn->click();
            break;
        case Qt::Key_2:
            ui->n2_btn->click();
            break;
        case Qt::Key_3:
            ui->n3_btn->click();
            break;
        case Qt::Key_4:
            ui->n4_btn->click();
            break;
        case Qt::Key_5:
            ui->n5_btn->click();
            break;
        case Qt::Key_6:
            ui->n6_btn->click();
            break;
        case Qt::Key_7:
            ui->n7_btn->click();
            break;
        case Qt::Key_8:
            ui->n8_btn->click();
            break;
        case Qt::Key_9:
            ui->n9_btn->click();
            break;
        case Qt::Key_0:
            ui->n0_btn->click();
            break;

        case Qt::Key_Plus:
            ui->plusBtn->click();
            break;
        case Qt::Key_Minus:
            ui->minusBtn->click();
            break;
        case Qt::Key_Asterisk:
            ui->mulBtn->click();
            break;
        case Qt::Key_Slash:
            ui->divBtn->click();
            break;
        case Qt::Key_AsciiCircum:
            ui->powBtn->click();
            break;
        case Qt::Key_Percent:
            ui->modBtn->click();
            break;

        case Qt::Key_X:
            ui->xBtn->click();
            break;
        case Qt::Key_Period:
            ui->dotBtn->click();
            break;
        case Qt::Key_ParenLeft:
            ui->openBktBtn->click();
            break;
        case Qt::Key_ParenRight:
            ui->closeBktBtn->click();
            break;

        case Qt::Key_Equal:
            ui->computeBtn->click();
            break;
        case Qt::Key_Enter:
            ui->computeBtn->click();
            break;

        default:
            QString key_text = event->text();
            QChar keyc = '\0';
            if (key_text.length() > 0) keyc = key_text[0];
            AddChar(keyc);
            break;
        }
    }

    void CalcWindow::AddBtnClicked() {
        QPushButton* btn = (QPushButton*)sender();
        QString lek = btn->text();

        if (btn == ui->powBtn)
            lek = "^";
        else if (btn == ui->modBtn)
            lek = "%";

        AddLek(lek);
    }

    void CalcWindow::RmBtnClicked() {
        QPushButton* btn = (QPushButton*)sender();

        if (btn == ui->acBtn)
            ClearAll();
        else if (btn == ui->rmBtn)
            ClearLast();
    }

    void CalcWindow::ComputeBtnClicked() {
        bool convertXOk = false;

        double x = ui->xEdit->text().toDouble(&convertXOk);

        if (!convertXOk) {
            QMessageBox::warning(this, "Внимание", "Поле 'X' заполнено неверно. Значение 'X' будет 0.0");
        }

        controller.PerformCompute(ui->editCalc->text(), x);
    }

    void CalcWindow::DrawBtnClicked() {
        QString line = ui->editCalc->text();

        PlotWindow* window = new PlotWindow(this);
        window->show();
        window->SetExpression(line);
    }

    void CalcWindow::OpenCreditCalc() {
        CreditWindow* window = new CreditWindow(this);
        window->show();
    }

    void CalcWindow::OpenDepositCalc() {
        DepositWindow* window = new DepositWindow(this);
        window->show();
    }

    void CalcWindow::AddLek(QString lek) {
        QString res = ui->editCalc->text();
        QChar lekc = lek[0];

        if (clearAfterType_) res.clear();

        if (IsOperation(lekc))
            res += " " + lek + " ";
        else if (lekc.isLetter() && lekc != 'x')
            res += lek + "(";
        else
            res += lek;

        if (res.length() > MAX_CALC_LINE_LEN) {
            this->ShowError("Слишком длинное выражение!");
        } else {
            ui->editCalc->setText(res);
        }

        clearAfterType_ = false;
    }

    void CalcWindow::AddChar(QChar lekc) {
        QString res = ui->editCalc->text();

        if (lekc.isLetter()) {
            lekc = lekc.toLower();

            if (clearAfterType_) {
                res = "";
                clearAfterType_ = false;
            }

            res += lekc;
        }

        ui->editCalc->setText(res);
    }

    bool CalcWindow::IsOperation(QChar lekc) {
        return lekc == '+' || lekc == '-' || lekc == '*' || lekc == '/' || lekc == '%' || lekc == '^';
    }

    void CalcWindow::ClearAll() {
        ui->editCalc->setText("0");
        ui->editOut->clear();

        clearAfterType_ = true;
    }

    void CalcWindow::ClearLast() {
        QString text = ui->editCalc->text();

        if (text.length() > 0) {
            text = text.first(text.length() - 1);
        }

        if (text.length() == 0) {
            text = "0";
            clearAfterType_ = true;
        }

        ui->editCalc->setText(text);
    }

    void CalcWindow::ShowResult(double result) {
        ui->editOut->setStyleSheet("color: white; font-weight: bold");
        ui->editOut->setText(QString::number(result));
    }

    void CalcWindow::ShowError(QString error) {
        ui->editOut->setStyleSheet("color: red; font-weight: normal");
        ui->editOut->setText(error);
    }
}  // namespace nex
