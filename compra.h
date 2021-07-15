#ifndef COMPRA_H
#define COMPRA_H

#include <QDialog>

namespace Ui {
class Compra;
}

class Compra : public QDialog
{
    Q_OBJECT

public:
    explicit Compra(QWidget *parent = nullptr);
    ~Compra();

    void datos (QString datos);
    void productos (QString productos);
    void setIva(QString iva);
    void setSubtotal(QString subtotal);
    void setTotal(QString total);

public slots:
    void limpiarOk();

private:
    Ui::Compra *ui;
};

#endif // COMPRA_H



