#include "cancel.h"
#include "ui_cancel.h"

Cancel::Cancel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Cancel)
{
    ui->setupUi(this);
}

Cancel::~Cancel()
{
    delete ui;
}

void Cancel::Show()
{
    updateUI();
    show();
}

void Cancel::updateUI()
{
    ui->comboBox->clear();

    QSqlQuery query(DB::getInstance()->getDBInstance());
    query.prepare("select Slot from cppbuzz_bikeparking where Available='N'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->labelinfo->setText(query.lastError().text());
    }
    else
    {
        qDebug() << "read was successful "<< query.lastQuery();
    }

    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }

    if(ui->comboBox->count()<=0)
    {
        ui->btnUpdate->setEnabled(false);
    }
}

void Cancel::on_btnUpdate_clicked()
{
    qDebug() << " in Cancel::update()";
    QString sSlot = ui->comboBox->currentText();

    QSqlQuery query(DB::getInstance()->getDBInstance());
    query.prepare("update cppbuzz_bikeparking set Available='Y' where Slot='" + sSlot + "' ");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->labelinfo->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            ui->labelinfo->setText("Slot is Available now");
            qDebug() << "last query was : "<< query.lastQuery();
            updateUI();
        }
        else
        {
            ui->labelinfo->setText("Unable to update");
            qDebug() << "unable to update : " << query.lastQuery();
        }
    }

     emit mysignalc();
}
