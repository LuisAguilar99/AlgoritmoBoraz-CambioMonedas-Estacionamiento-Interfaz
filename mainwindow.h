#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int total_dinero;
    int ticket_f=0;
    char timeString[9];
    int acc_ticket=0;
    QString tabla;
    int acc_tickets=0;
    int credito=0;
    int contador=0;


private slots:

    void on_tomar_ticket_clicked();

    void on_boton_pagar_clicked();

    void on_moneda_10_clicked();

    void on_moneda_5_clicked();

    void on_moneda_2_clicked();

    void on_moneda_1_clicked();

    void funcionActivacionTimer();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
