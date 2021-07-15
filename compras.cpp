#include "compras.h"
#include "ui_compras.h"
#include "principal.h"
Compras::Compras(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Compras)
{
    ui->setupUi(this);
    close();
    connect(ui->cmdOk, SIGNAL(accepted()),
            this, SLOT(LimpiarPantalla()));
}

Compras::~Compras()
{
    delete ui;
}

void Compras::registro(QString val)
{
    ui->outCompra->setPlainText(val);
}

void Compras::mercaderia(QString mecaderia)
{
    ui->outProductos->setPlainText(mecaderia);
}

void Compras::setSubtotal(QString subtotal)
{
    ui->outSubtotal->setText(subtotal);
}

void Compras::setIva(QString iva)
{
    ui->outIva->setText(iva);
}

void Compras::setTotal(QString total)
{
    ui->outTotal->setText(total);
}

void Compras::LimpiarPantalla()
{
    Principal *principal = new Principal(this);
        principal->limpiar();
        principal->show();
}
