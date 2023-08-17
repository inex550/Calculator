#include "plotwindow.h"

#include <QMessageBox>
#include <cmath>

#include "ui_plotwindow.h"

namespace nex {
    PlotWindow::PlotWindow(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::PlotWindow)
        , controller_(this)
    {
        ui->setupUi(this);

        ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

        connect(ui->redrawBtn, SIGNAL(clicked()), this, SLOT(RedrawBtnClicked()));
    }

    PlotWindow::~PlotWindow() { delete ui; }

    void PlotWindow::SetExpression(QString expression) {
        this->expression_ = expression;
        controller_.PerformCompute(expression, DEFAULT_FROM_XY, DEFAULT_TO_XY, DEFAULT_FROM_XY, DEFAULT_TO_XY);

        ui->fromXEdit->setText(QString::number(DEFAULT_FROM_XY));
        ui->toXEdit->setText(QString::number(DEFAULT_TO_XY));
        ui->fromYEdit->setText(QString::number(DEFAULT_FROM_XY));
        ui->toYEdit->setText(QString::number(DEFAULT_TO_XY));
    }

    void PlotWindow::RedrawPlot(double fromX, double toX, double fromY, double toY,
                                const QList<double>& arrX,
                                const QList<double>& arrY) {
        if (ui->plot->graphCount() == 0) {
            ui->plot->addGraph();
        }

        ui->plot->graph(0)->setData(arrX, arrY);

        ui->plot->xAxis->setLabel("X");
        ui->plot->xAxis->setRange(fromX, toX);

        ui->plot->yAxis->setLabel("Y");
        ui->plot->yAxis->setRange(fromY, toY);

        ui->plot->replot();
    }

    void PlotWindow::ShowError(const QString& error) {
        QMessageBox::critical(this, "Error", error);
        this->close();
    }

    void PlotWindow::RedrawBtnClicked() {
        bool fromXOk = false;
        bool toXOk = false;
        bool fromYOk = false;
        bool toYOk = false;

        double fromX = ui->fromXEdit->text().toDouble(&fromXOk);
        double toX = ui->toXEdit->text().toDouble(&toXOk);
        double fromY = ui->fromYEdit->text().toDouble(&fromYOk);
        double toY = ui->toYEdit->text().toDouble(&toYOk);

        if (!fromXOk || !toXOk || !fromYOk || !toYOk) {
            QMessageBox::critical(this, "Error", "Поля заполнены некорректно");
        } else if ((fromX < -MAX_GRAPHIC_VALUE || fromX > MAX_GRAPHIC_VALUE) || (toX < -MAX_GRAPHIC_VALUE || toX > MAX_GRAPHIC_VALUE)) {
            QMessageBox::critical(this, "Error", QString("Значение поля не может быть больше/меньше ") + QString::number(MAX_GRAPHIC_VALUE));
        } else {
            controller_.PerformCompute(expression_, fromX, toX, fromY, toY);
        }
    }
}  // namespace nex
