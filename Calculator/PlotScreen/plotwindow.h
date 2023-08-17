#ifndef __PLOTSCREEN_PLOTWINDOW_H__
#define __PLOTSCREEN_PLOTWINDOW_H__

#include <PlotScreen/plotcontroller.h>

#include <QMainWindow>

#define DEFAULT_FROM_XY -10.0
#define DEFAULT_TO_XY 10.0

#define MAX_GRAPHIC_VALUE 1000000.0

#include <notation/parser.h>

namespace Ui {
class PlotWindow;
}

namespace nex {
    class PlotWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit PlotWindow(QWidget* parent = nullptr);
        ~PlotWindow();

        void SetExpression(QString expression);

        void RedrawPlot(double fromX, double toX, double fromY, double toY,
                        const QList<double>& arrX, const QList<double>& arrY);
        void ShowError(const QString& error = "Unknown Error");

        private slots:
        void RedrawBtnClicked();

    private:
        Ui::PlotWindow* ui;
        PlotController controller_;

        QString expression_;
    };
}  // namespace nex

#endif  // __PLOTSCREEN_PLOTWINDOW_H__
