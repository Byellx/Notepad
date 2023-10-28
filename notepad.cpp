#include "notepad.h"
#include "ui_notepad.h"
#include <QMessageBox>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QFontDialog>
#include <QFont>
#include <QColorDialog>
#include <QColor>
/*#include <QtPrintSupport/QPrintDialog>
#include <QtPrintSupport/qprinter.h>*/


Notepad::Notepad(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Notepad)
{
    ui->setupUi(this);
    this->setCentralWidget(ui->textEdit);
}

Notepad::~Notepad()
{
    delete ui;
}

void Notepad::on_actionNovo_triggered()
{
    local_archive = "";
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

void Notepad::on_actionAbrir_triggered()
{
    QString filter = "Todos Arquivos (*.*) ;; Arquivos de texto (*.txt)";
    QString archive_name = QFileDialog::getOpenFileName(this, "Abrir", QDir::homePath(), filter);
    QFile archive(archive_name);
    local_archive = archive_name;

    if(!archive.open(QFile::ReadOnly | QFile::Text)){
        QMessageBox::warning(this, "Erro", "Não foi possível abrir o arquivo.");
        return;
    }

    QTextStream input(&archive);
    QString text1 = input.readAll();
    ui->textEdit->setText(text1);
    archive.close();

}

void Notepad::on_actionSalvar_como_triggered()
{
    QString filter = "Arquivos de texto (*.txt)";
    QString archive_name = QFileDialog::getSaveFileName(this, "Salvar como", QDir::homePath(), filter);

    QFile archive(archive_name);

    local_archive = archive_name;
    if(!archive.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Erro", "Não foi possível salvar o arquivo.");
        return;
    }

    QTextStream output(&archive);
    QString text = ui->textEdit->toPlainText();
    output << text;
    archive.flush();
    archive.close();
}

void Notepad::on_actionSalvar_triggered()
{
    QFile archive(local_archive);

    if(!archive.open(QFile::WriteOnly | QFile::Text)){
        QMessageBox::warning(this, "Erro", "Não foi possível salvar o arquivo.");
        return;
    }

    QTextStream output(&archive);
    QString text = ui->textEdit->toPlainText();
    output << text;
    archive.flush();
    archive.close();
}

void Notepad::on_actionFechar_triggered()
{
    close();
}

void Notepad::on_actionCopiar_triggered()
{
    ui->textEdit->copy();
}

void Notepad::on_actionRecortar_triggered()
{
    ui->textEdit->cut();
}

void Notepad::on_actionColar_triggered()
{
    ui->textEdit->paste();
}

void Notepad::on_actionDesfazer_triggered()
{
    ui->textEdit->undo();
}

void Notepad::on_actionRefazer_triggered()
{
    ui->textEdit->redo();
}

void Notepad::on_actionFonte_triggered()
{
    bool fonte_ok;
    QFont fonte = QFontDialog::getFont(&fonte_ok, this);
    if(fonte_ok){
        ui->textEdit->setFont(fonte);
    }else{
        return;
    }
}


void Notepad::on_actionCor_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::black, this, "Escolha uma cor");
    if(cor.isValid()){
        ui->textEdit->setTextColor(cor);
    }
}


void Notepad::on_actionCor_de_Fundo_triggered()
{
    QColor cor = QColorDialog::getColor(Qt::white, this, "Escolha uma cor");
    if(cor.isValid()){
        ui->textEdit->setTextBackgroundColor(cor);
    }
}


/*void Notepad::on_actionImprimir_triggered()
{
    QPrinter impressora;
    impressora.setPrinterName("Minha Impressora");
    QPrintDialog caixa_de_impressao(&impressora, this);

    if(caixa_de_impressao.exec() == QDialog::Rejected){
        return;
    }

    ui->textEdit->print(&impressora);
}
*/
