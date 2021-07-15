#ifndef PRINCIPAL_H
#define PRINCIPAL_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QMainWindow>
#include <QMessageBox>

#include "producto.h"
#include "compras.h"
#define IVA 12

QT_BEGIN_NAMESPACE
namespace Ui { class Principal; }
QT_END_NAMESPACE

class Principal : public QMainWindow
{
    Q_OBJECT

public:
    Principal(QWidget *parent = nullptr);
    ~Principal();
    void limpiar();
    QString getDatos();
    void producto();
    bool buscarRepetidos(Producto *producto, int cantidad);

private slots:
    void on_cmdAgregar_released();
    void on_inProducto_currentIndexChanged(int index);
    void on_inNombre_editingFinished();
    void on_inCedula_editingFinished();
    void finalizarCompra();

private:
    Ui::Principal *ui;
    QList<Producto*> m_productos;
    float m_subtotal;
    void calcular(float subtotalProducto);
    void valID();
    bool escedulaEcuatoriana(QString cedula);
    void valCliente();
};
#endif // PRINCIPAL_H
