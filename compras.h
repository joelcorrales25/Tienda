#ifndef COMPRAS_H
#define COMPRAS_H

#include <QDialog>

namespace Ui {
class Compras;
}

class Compras : public QDialog
{
    Q_OBJECT

public:
    explicit Compras(QWidget *parent = nullptr);
    ~Compras();

    void registro (QString val);
    void mercaderia (QString productos);

    void setSubtotal(QString subtotal);
    void setIva(QString iva);
    void setTotal(QString total);

public slots:
    void LimpiarPantalla();

private:
    Ui::Compras *ui;
};

#endif // COMPRAS_H
