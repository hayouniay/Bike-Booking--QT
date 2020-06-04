#include "book.h"
#include "ui_book.h"

Book::Book(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Book)
{
    ui->setupUi(this);
    // Connect button signal to appropriate slot
    connect(this, SIGNAL(mysignal()), parent, SLOT(updateUI()));
}

Book::~Book()
{
    delete ui;
}

void Book::Show()
{
    updateUI();
    show();
}

void Book::updateUI()
{
    ui->comboBox->clear();

    QSqlQuery query(DB::getInstance()->getDBInstance());
    query.prepare("select Slot from cppbuzz_bikeparking where Available='Y'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->labelinfo->setText(query.lastError().text());
    }
    else{
        qDebug() << "read was successful "<< query.lastQuery();
       }

    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString());
    }
}

void Book::on_pushButton_clicked()
{
    QString sSlot = ui->comboBox->currentText();

    ui->comboBox->clear();
    ui->labelinfo->setText("");

    QSqlQuery query(DB::getInstance()->getDBInstance());
    query.prepare("update cppbuzz_bikeparking set Available='N' where Slot='" + sSlot + "'");

    if(!query.exec())
    {
        qDebug() << query.lastError().text() << query.lastQuery();
        ui->labelinfo->setText(query.lastError().text());
    }
    else{
        if(query.numRowsAffected() > 0)
        {
            qDebug() << "Update was successful "<< query.lastQuery();
            ui->labelinfo->setText("Update was successful!");
        }
        else {
            ui->labelinfo->setText("Update was not successful!");
        }
       }
    updateUI();
    emit mysignal();
}

