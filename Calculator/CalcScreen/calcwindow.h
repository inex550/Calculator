#ifndef __CALCSCREEN_CALCWINDOW_H__
#define __CALCSCREEN_CALCWINDOW_H__

#include <CalcScreen/calccontroller.h>
#include <notation/except.h>
#include <notation/parser.h>

#include <QKeyEvent>
#include <QMainWindow>

#define MAX_CALC_LINE_LEN 255

QT_BEGIN_NAMESPACE
namespace Ui {
    class CalcWindow;
}
QT_END_NAMESPACE

namespace nex {
    class CalcWindow : public QMainWindow {
    Q_OBJECT

    public:
        CalcWindow(QWidget *parent = nullptr);
        ~CalcWindow();

        void ShowResult(double result);
        void ShowError(QString error = "Unknown Error");

    protected:
        void keyPressEvent(QKeyEvent *event);

    private slots:
        void AddBtnClicked();
        void RmBtnClicked();
        void ComputeBtnClicked();
        void DrawBtnClicked();

        void OpenCreditCalc();
        void OpenDepositCalc();

        private:
        void ConnectButtons();

        bool IsOperation(QChar lekc);

        void AddLek(QString lek);
        void AddChar(QChar lekc);
        void ClearAll();
        void ClearLast();

    private:
        Ui::CalcWindow *ui;
        CalcController controller;

        nex::NotationParser parser_;

        bool clearAfterType_ = true;
    };
}  // namespace nex

#endif  // __CALCSCREEN_CALCWINDOW_H__
