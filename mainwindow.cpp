#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <ctime>
#include <stdlib.h>
#include <QMessageBox>
#include <QTimer>


void MainWindow::funcionActivacionTimer(){
    QPixmap pix(":/ticket.png");
    if(ui->n_ticket_s->text()!=" "){           
           ui->n_ticket_s_2->setScaledContents(1);
           ui->n_ticket_s_2->setPixmap(pix);
        contador++;
        if(contador>3){
            contador=0;
            ui->n_ticket_s->setText(" ");
            ui->n_ticket_s_2->setText(" ");
        }
    }
    QPixmap pix2(":/moneda_10.png");
    QPixmap pix3(":/moneda_5.png");
    QPixmap pix4(":/moneda_2.png");
    QPixmap pix5(":/moneda_1.png");
    QIcon Icono10(pix2);
    QIcon Icono5(pix3);
    QIcon Icono2(pix4);
    QIcon Icono1(pix5);
    ui->moneda_10->setIcon(Icono10);
    ui->moneda_5->setIcon(Icono5);
    ui->moneda_2->setIcon(Icono2);
    ui->moneda_1->setIcon(Icono1);
    //ui->moneda_10->setIconSize(pix2.rect().size());
    //ui->lcdNumber->display(contador);

}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    QTimer *cronometro=new QTimer(this);
    connect(cronometro, SIGNAL(timeout()), this, SLOT(funcionActivacionTimer()));
    cronometro->start(500);
}




MainWindow::~MainWindow()
{
    delete ui;
}
/*
int acc_ticket=0;
QString tabla;
int acc_tickets=0;
int credito=0;
*/
struct ticket{
    int no_ticket;
    QString h_salida;
    QString h_entrada;
    int s_entrada;
    int pago;
    bool registrado=false;
    bool pagado=false;
}myTicket[50];

void MainWindow::on_tomar_ticket_clicked()
{

    QString temp;
    ///sacar hora
    time_t current_time;
    struct tm * time_info;
    char timeString[9];
    time(&current_time);
    time_info = localtime(&current_time);
    strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
    ///sacar hora
    acc_ticket++;
    ///Empieza conversion a segundos
    int h_s=0;
    int m_s=0;
    int s_s=0;
    int s_total=0;
    QString temp2;
    int temp_num=0;
    for(int i=0;i<2;i++){
        temp2+=timeString[i];
    }
        temp_num = temp2.split(" ")[0].toInt();
        h_s=temp_num*3600;
            temp2="";
     for(int i=3;i<5;i++){
        temp2+=timeString[i];
    }
    temp_num = temp2.split(" ")[0].toInt();
        m_s=temp_num*60;
            temp2="";
             for(int i=6;i<8;i++){
        temp2+=timeString[i];
    }
    temp_num = temp2.split(" ")[0].toInt();
    s_s=temp_num;
    s_total=h_s+m_s+s_s;
    myTicket[acc_ticket].s_entrada=s_total;
    ///Termian conversion a segundos
    myTicket[acc_ticket].registrado=true;
    //QMessageBox msg2;
      //     msg2.setText("Tu numero de ticket \nes:       "+QString::number(acc_ticket));
           //prueba timer
           ui->n_ticket_s->setText("   No Ticket\n           "+QString::number(acc_ticket));
        //     msg2.exec();
             myTicket[acc_ticket].no_ticket=acc_ticket;
             myTicket[acc_ticket].h_entrada=timeString;
    acc_tickets++;
    ///aqui rellenar tabla
    tabla="";
    for(int x=1;x<acc_tickets+1;x++){
        if(myTicket[x].registrado==true){
            tabla+="   "+QString::number(myTicket[x].no_ticket)+"        "+myTicket[x].h_entrada+"          "+myTicket[x].h_salida+"        "+QString::number(myTicket[x].pago)+"\n";
            ui->tabla_tickets->setText(tabla);
        }
    }

    /// aca terminar de rellenar
}
//int total_dinero;
//int ticket_f=0;
//char timeString[9];
void MainWindow::on_boton_pagar_clicked()
{

QString n_ticket;
n_ticket = ui->obtener_ticket->text();
ticket_f = n_ticket.split(" ")[0].toInt();
if(myTicket[ticket_f].registrado==false||myTicket[ticket_f].pagado==true){
    QMessageBox msg2;
           msg2.setText("Este ticket no fue asignado\nO ya fue pagado");
             msg2.exec();
}else {
    //aqui empieza determinar total
    int total_segundos;
        ///sacar hora
        time_t current_time;
        struct tm * time_info;
        time(&current_time);
        time_info = localtime(&current_time);
        strftime(timeString, sizeof(timeString), "%H:%M:%S", time_info);
        ///sacar hora
        ///Empieza conversion a segundos
        int h_s=0;
        int m_s=0;
        int s_s=0;
        int s_total=0;
        QString temp2;
        int temp_num=0;
        for(int i=0;i<2;i++){
            temp2+=timeString[i];
        }
            temp_num = temp2.split(" ")[0].toInt();
            h_s=temp_num*3600;
                temp2="";
         for(int i=3;i<5;i++){
            temp2+=timeString[i];
        }
        temp_num = temp2.split(" ")[0].toInt();
            m_s=temp_num*60;
                temp2="";
                 for(int i=6;i<8;i++){
            temp2+=timeString[i];
        }
        temp_num = temp2.split(" ")[0].toInt();
        s_s=temp_num;
        s_total=h_s+m_s+s_s;
       total_segundos=s_total-myTicket[ticket_f].s_entrada;
        ///Termian conversion a segundos
       if(total_segundos>0&&total_segundos<16){
       ui->mostrar_total->setText("20");
       total_dinero=20;
       }
       if(total_segundos>15&&total_segundos<31){
       ui->mostrar_total->setText("30");
       total_dinero=30;
       }
       if(total_segundos>30){
       ui->mostrar_total->setText("50");
       total_dinero=50;
       }
    /// aqui acaba determinar total
}
}
void MainWindow::on_moneda_10_clicked()
{
    credito+=10;
    ui->mostrar_saldo->setText(QString::number(credito));
    //aqui empieza calcular cantidad
    if(credito>=total_dinero){
        #define MONEDAS 5
       int monedas[]={20,10,5,2,1};
        QString g_cambio;
        QString temp;
   QMessageBox mbox;

   if(ui->dar_de_20->isChecked()){
   //nada
   }else {
       if(ui->dar_de_10->isChecked()){
       monedas[0] = monedas[1];
       }else {
           if(ui->dar_de_5->isChecked()){
       monedas[0] = monedas[2];
           }else {
               if(ui->dar_de_2->isChecked()){
                   monedas[0] = monedas[3];
               }else{
                   monedas[0] = monedas[4];
               }
   }
   }
   }
   if(ui->dar_de_10->isChecked()){
   //nada
   }else {
       if(ui->dar_de_5->isChecked()){
           monedas[1]=monedas[2];
       }else{
               if(ui->dar_de_2->isChecked()){
                   monedas[1]=monedas[3];
               }else {
           monedas[1]=monedas[4];
   }

       }
   }
   if(ui->dar_de_5->isChecked()){
   //nada
   }else {
       if(ui->dar_de_2->isChecked()){
           monedas[2]=monedas[3];
       }else {
   monedas[2] = monedas[4];
   }
   }
   if(ui->dar_de_2->isChecked()){
   //nada
   }else {
      monedas[3]=monedas[4];
   }

   int solucion[MONEDAS];

      int i, devolucion;
      devolucion=credito-total_dinero;

      for (i = 0; i < MONEDAS; i++){
         solucion[i] =0;
      }
   //borra datos basura
      //incia buble voraz
      for (i = 0; i < MONEDAS; i++){
         while (devolucion >= monedas[i])
         {
            solucion[i]++;
            devolucion -= monedas[i];
         }
      }
      //fin
      if (devolucion){
      }else{
         for (i = 0; i < MONEDAS; i++){
            //if (solucion[i]&&solucion[i]!=solucion[i+1]){
             if(solucion[i]!=0){
                temp = "Recibes "+QString::number(solucion[i])+" de "+QString::number(monedas[i])+"  "+"\n";
                g_cambio+=temp;
             }
             if(credito==total_dinero){
                 g_cambio="GRACIAS POR VISITARNOS";
             }
            //}
         }
   mbox.setText(g_cambio);
   mbox.exec();
   credito=0;
   ui->mostrar_saldo->setText(QString::number(credito));
   myTicket[ticket_f].pago=total_dinero;
   myTicket[ticket_f].pagado=true;
   myTicket[ticket_f].h_salida=timeString;
   ///aqui rellenar tabla
   tabla="";
   for(int x=1;x<acc_tickets+1;x++){
       if(myTicket[x].registrado==true){
           tabla+="   "+QString::number(myTicket[x].no_ticket)+"        "+myTicket[x].h_entrada+"          "+myTicket[x].h_salida+"        "+QString::number(myTicket[x].pago)+"\n";
           ui->tabla_tickets->setText(tabla);
       }
   }

   /// aca terminar de rellenar
   ui->mostrar_total->setText("0");
   ui->obtener_ticket->setText("");
   }
}
    //aqui termina calcular cantidad

}

void MainWindow::on_moneda_5_clicked()
{
    credito+=5;
    ui->mostrar_saldo->setText(QString::number(credito));
    //aqui empieza calcular cantidad
    if(credito>=total_dinero){
        #define MONEDAS 5
       int monedas[]={20,10,5,2,1};
        QString g_cambio;
        QString temp;
   QMessageBox mbox;

   if(ui->dar_de_20->isChecked()){
   //nada
   }else {
       if(ui->dar_de_10->isChecked()){
       monedas[0] = monedas[1];
       }else {
           if(ui->dar_de_5->isChecked()){
       monedas[0] = monedas[2];
           }else {
               if(ui->dar_de_2->isChecked()){
                   monedas[0] = monedas[3];
               }else{
                   monedas[0] = monedas[4];
               }
   }
   }
   }
   if(ui->dar_de_10->isChecked()){
   //nada
   }else {
       if(ui->dar_de_5->isChecked()){
           monedas[1]=monedas[2];
       }else{
               if(ui->dar_de_2->isChecked()){
                   monedas[1]=monedas[3];
               }else {
           monedas[1]=monedas[4];
   }

       }
   }
   if(ui->dar_de_5->isChecked()){
   //nada
   }else {
       if(ui->dar_de_2->isChecked()){
           monedas[2]=monedas[3];
       }else {
   monedas[2] = monedas[4];
   }
   }
   if(ui->dar_de_2->isChecked()){
   //nada
   }else {
      monedas[3]=monedas[4];
   }

   int solucion[MONEDAS];

      int i, devolucion;
      devolucion=credito-total_dinero;

      for (i = 0; i < MONEDAS; i++){
         solucion[i] =0;
      }
   //borra datos basura
      //incia buble voraz
      for (i = 0; i < MONEDAS; i++){
         while (devolucion >= monedas[i])
         {
            solucion[i]++;
            devolucion -= monedas[i];
         }
      }
      //fin
      if (devolucion){
      }else{
         for (i = 0; i < MONEDAS; i++){
            //if (solucion[i]&&solucion[i]!=solucion[i+1]){
             if(solucion[i]!=0){
                temp = "Recibes "+QString::number(solucion[i])+" de "+QString::number(monedas[i])+"  "+"\n";
                g_cambio+=temp;
             }
             if(credito==total_dinero){
                 g_cambio="GRACIAS POR VISITARNOS";
             }
            //}
         }
   mbox.setText(g_cambio);
   mbox.exec();
   credito=0;
   ui->mostrar_saldo->setText(QString::number(credito));
   myTicket[ticket_f].pago=total_dinero;
   myTicket[ticket_f].pagado=true;
   myTicket[ticket_f].h_salida=timeString;
   ///aqui rellenar tabla
   tabla="";
   for(int x=1;x<acc_tickets+1;x++){
       if(myTicket[x].registrado==true){
           tabla+="   "+QString::number(myTicket[x].no_ticket)+"        "+myTicket[x].h_entrada+"          "+myTicket[x].h_salida+"        "+QString::number(myTicket[x].pago)+"\n";
           ui->tabla_tickets->setText(tabla);
       }
   }

   /// aca terminar de rellenar
   ui->mostrar_total->setText("0");
   ui->obtener_ticket->setText("");
   }
}
    //aqui termina calcular cantidad
}

void MainWindow::on_moneda_2_clicked()
{
    credito+=2;
    ui->mostrar_saldo->setText(QString::number(credito));
    //aqui empieza calcular cantidad
    if(credito>=total_dinero){
        #define MONEDAS 5
       int monedas[]={20,10,5,2,1};
        QString g_cambio;
        QString temp;
   QMessageBox mbox;

   if(ui->dar_de_20->isChecked()){
   //nada
   }else {
       if(ui->dar_de_10->isChecked()){
       monedas[0] = monedas[1];
       }else {
           if(ui->dar_de_5->isChecked()){
       monedas[0] = monedas[2];
           }else {
               if(ui->dar_de_2->isChecked()){
                   monedas[0] = monedas[3];
               }else{
                   monedas[0] = monedas[4];
               }
   }
   }
   }
   if(ui->dar_de_10->isChecked()){
   //nada
   }else {
       if(ui->dar_de_5->isChecked()){
           monedas[1]=monedas[2];
       }else{
               if(ui->dar_de_2->isChecked()){
                   monedas[1]=monedas[3];
               }else {
           monedas[1]=monedas[4];
   }

       }
   }
   if(ui->dar_de_5->isChecked()){
   //nada
   }else {
       if(ui->dar_de_2->isChecked()){
           monedas[2]=monedas[3];
       }else {
   monedas[2] = monedas[4];
   }
   }
   if(ui->dar_de_2->isChecked()){
   //nada
   }else {
      monedas[3]=monedas[4];
   }

   int solucion[MONEDAS];

      int i, devolucion;
      devolucion=credito-total_dinero;

      for (i = 0; i < MONEDAS; i++){
         solucion[i] =0;
      }
   //borra datos basura
      //incia buble voraz
      for (i = 0; i < MONEDAS; i++){
         while (devolucion >= monedas[i])
         {
            solucion[i]++;
            devolucion -= monedas[i];
         }
      }
      //fin
      if (devolucion){
      }else{
         for (i = 0; i < MONEDAS; i++){
            //if (solucion[i]&&solucion[i]!=solucion[i+1]){
             if(solucion[i]!=0){
                temp = "Recibes "+QString::number(solucion[i])+" de "+QString::number(monedas[i])+"  "+"\n";
                g_cambio+=temp;
             }
             if(credito==total_dinero){
                 g_cambio="GRACIAS POR VISITARNOS";
             }
            //}
         }
   mbox.setText(g_cambio);
   mbox.exec();
   credito=0;
   ui->mostrar_saldo->setText(QString::number(credito));
   myTicket[ticket_f].pago=total_dinero;
   myTicket[ticket_f].pagado=true;
   myTicket[ticket_f].h_salida=timeString;
   ///aqui rellenar tabla
   tabla="";
   for(int x=1;x<acc_tickets+1;x++){
       if(myTicket[x].registrado==true){
           tabla+="   "+QString::number(myTicket[x].no_ticket)+"        "+myTicket[x].h_entrada+"          "+myTicket[x].h_salida+"        "+QString::number(myTicket[x].pago)+"\n";
           ui->tabla_tickets->setText(tabla);
       }
   }

   /// aca terminar de rellenar
   ui->mostrar_total->setText("0");
   ui->obtener_ticket->setText("");
   }
}
    //aqui termina calcular cantidad
}

void MainWindow::on_moneda_1_clicked()
{
    credito+=1;
    ui->mostrar_saldo->setText(QString::number(credito));
    //aqui empieza calcular cantidad
    if(credito>=total_dinero){
        #define MONEDAS 5
       int monedas[]={20,10,5,2,1};
        QString g_cambio;
        QString temp;
   QMessageBox mbox;

   if(ui->dar_de_20->isChecked()){
   //nada
   }else {
       if(ui->dar_de_10->isChecked()){
       monedas[0] = monedas[1];
       }else {
           if(ui->dar_de_5->isChecked()){
       monedas[0] = monedas[2];
           }else {
               if(ui->dar_de_2->isChecked()){
                   monedas[0] = monedas[3];
               }else{
                   monedas[0] = monedas[4];
               }
   }
   }
   }
   if(ui->dar_de_10->isChecked()){
   //nada
   }else {
       if(ui->dar_de_5->isChecked()){
           monedas[1]=monedas[2];
       }else{
               if(ui->dar_de_2->isChecked()){
                   monedas[1]=monedas[3];
               }else {
           monedas[1]=monedas[4];
   }

       }
   }
   if(ui->dar_de_5->isChecked()){
   //nada
   }else {
       if(ui->dar_de_2->isChecked()){
           monedas[2]=monedas[3];
       }else {
   monedas[2] = monedas[4];
   }
   }
   if(ui->dar_de_2->isChecked()){
   //nada
   }else {
      monedas[3]=monedas[4];
   }

   int solucion[MONEDAS];

      int i, devolucion;
      devolucion=credito-total_dinero;

      for (i = 0; i < MONEDAS; i++){
         solucion[i] =0;
      }
   //borra datos basura
      //incia buble voraz
      for (i = 0; i < MONEDAS; i++){
         while (devolucion >= monedas[i])
         {
            solucion[i]++;
            devolucion -= monedas[i];
         }
      }
      //fin
      if (devolucion){
      }else{
         for (i = 0; i < MONEDAS; i++){
            //if (solucion[i]&&solucion[i]!=solucion[i+1]){
             if(solucion[i]!=0){
                temp = "Recibes "+QString::number(solucion[i])+" de "+QString::number(monedas[i])+"  "+"\n";
                g_cambio+=temp;
             }
             if(credito==total_dinero){
                 g_cambio="GRACIAS POR VISITARNOS";
             }
            //}
         }
   mbox.setText(g_cambio);
   mbox.exec();
   credito=0;
   ui->mostrar_saldo->setText(QString::number(credito));
   myTicket[ticket_f].pago=total_dinero;
   myTicket[ticket_f].pagado=true;
   myTicket[ticket_f].h_salida=timeString;
   ///aqui rellenar tabla
   tabla="";
   for(int x=1;x<acc_tickets+1;x++){
       if(myTicket[x].registrado==true){
           tabla+="   "+QString::number(myTicket[x].no_ticket)+"        "+myTicket[x].h_entrada+"          "+myTicket[x].h_salida+"        "+QString::number(myTicket[x].pago)+"\n";
           ui->tabla_tickets->setText(tabla);
       }
   }

   /// aca terminar de rellenar
   ui->mostrar_total->setText("0");
   ui->obtener_ticket->setText("");
   }
}
    //aqui termina calcular cantidad
}


