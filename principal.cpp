#include "principal.h"
#include "ui_principal.h"
#include <QDebug>

Principal::Principal(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Principal)
{
    ui->setupUi(this);
    // Lista de productos
    m_productos.append(new Producto(1,"Leche",0.85));
    m_productos.append(new Producto(2,"Pan",0.15));
    m_productos.append(new Producto(3,"Queso",2.00));
    m_productos.append(new Producto(4,"Papas Fritas",0.60));
    m_productos.append(new Producto(5,"Yogurt",0.80));
    m_productos.append(new Producto(6,"Paquete Salchichas",1.00));
    // Mostrar la lista en la ventana
    for (int i = 0; i < m_productos.size(); ++i) {
        ui->inProducto->addItem(m_productos.at(i)->nombre());
    }
    // Colocar cabecera de la tabla
    QStringList cabecera = {"Cantidad", "Producto", "Subtotal"};
    ui->outDetalle->setColumnCount(3);
    ui->outDetalle->setHorizontalHeaderLabels(cabecera);
    // Inicializar subtotal global
    m_subtotal = 0;
    connect(ui->cmdFinalizar, SIGNAL(clicked(bool)),
            this, SLOT(finalizarCompra()));
}

Principal::~Principal()
{
    delete ui;
}

QString Principal::getDatos()
{
    return  "Cédula: " + ui->inCedula->displayText() + "\n" +
            "\nNombre: " + ui->inNombre->displayText() + "\n" +
            "\nTeléfono: " + ui->inTelefono->displayText() + "\n" +
            "\nE-mail: " + ui->inEmail->displayText() + "\n" +
            "\nDirección: " + ui->inDireccion->toPlainText()+ "\n"+
            "\nCantidad      \t                 Producto     \t           Subtotal";
}

void Principal::limpiar()
{
    ui->inNombre->setText("");
    ui->inCedula->setText("");
    ui->inEmail->setText("");
    ui->inCantidad->setValue(0);
    ui->inTelefono->setText("");
    ui->inDireccion->setPlainText("");
    ui->outDetalle->setRowCount(0);
}

void Principal::valID()
{
    QString cedula = ui->inCedula->text();
    if (cedula.length() != 10){
        ui->inCedula->setStyleSheet("background-color: rgb(255, 105, 180)");

    }else if(cedula == "9999999999" && cedula.length() == 10){
        ui->inCedula->setStyleSheet("background-color:  rgb(255, 255, 0)");

    }else{
        ui->inCedula->setStyleSheet("background-color:  rgb(255, 255, 0)");        

    }
}

bool Principal::escedulaEcuatoriana(QString cedula)
{
    QString vec[10];
    int auxiliar;
    int par = 0;
    int impar = 0;

    for(int i = 0; i < 9; i++)
    {
        vec[i] = cedula[i];
        auxiliar = vec[i].toInt();
        if((i+1)%2==0){
            par += auxiliar;
        }else{
            if(auxiliar * 2 > 9){
                impar = impar + ((auxiliar * 2) - 9);
            }else{
                impar += auxiliar * 2;
            }
        }
    }
    int UltimoNum = cedula.toInt()%10;
    int verificador = (par + impar)%10;
    if(verificador !=0){
        verificador = 10 - verificador;
    }
    return UltimoNum == verificador? true : false;
}

void Principal::valCliente()
{
    QString nombre = ui->inNombre->text();
    QString cedula = ui->inCedula->text();

    if (nombre.isEmpty()){
        ui->inNombre->setStyleSheet("background-color: rgb(255, 105, 180)");
    }else{
        ui->inNombre->setStyleSheet("background-color: rgb(255, 255, 0)");
    }

}

void Principal::finalizarCompra()
{
    Compras *consumo = new Compras();
    QString nombre = ui->inNombre->text();
    QString cedula = ui->inCedula->text();

    QStringList lista;
    QString productos;
    if(nombre.isEmpty() || cedula.length() != 10){
        QMessageBox::warning(this, "ADVERTENCIA", "Datos Necesarios Incompletos");
                return;
    }
    for( int fila = 0; fila < ui->outDetalle->rowCount(); ++fila)    {
        for( int columna = 0; columna < ui->outDetalle->columnCount(); ++columna){
            lista << ui->outDetalle->item(fila, columna)->text();
            QTableWidgetItem* item = ui->outDetalle->item(fila,columna);
            if (!item || item->text().isEmpty()){
                ui->outDetalle->setItem(fila,columna,new QTableWidgetItem("0"));
            }
            productos = lista.join( " " );
            lista<<"                                         ";
        }
        lista << "   ";
        consumo->mercaderia(productos);
    }

    consumo->registro(getDatos());
    consumo->setSubtotal(ui->outSubtotal->text());
    consumo->setIva(ui->outIva->text());
    consumo->setTotal(ui->outTotal->text());
    consumo->show();
    this->hide();
}


void Principal::on_cmdAgregar_released()
{
    // Validar que no se agregen productos con 0 cantidad
    int cantidad = ui->inCantidad->value();
    if (cantidad == 0){
        return;
    }

    // Obtener datos de la GUI
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);

    // Calcular el subtotal del producto
    float subtotal = cantidad * p->precio();

    //Buscar productos repetidos
    if(!buscarRepetidos(p,cantidad)){

        // Agregar datos a la tabla
        int fila = ui->outDetalle->rowCount();
        ui->outDetalle->insertRow(fila);
        ui->outDetalle->setItem(fila,0,new QTableWidgetItem(QString::number(cantidad)));
        ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
        ui->outDetalle->setItem(fila,2,new QTableWidgetItem(QString::number(subtotal,'f',2)));
    }
    // Limpiar datos
    ui->inCantidad->setValue(0);
    ui->inProducto->setFocus();

    // Invocar a calcular
    calcular(subtotal);
}

void Principal::on_inProducto_currentIndexChanged(int index)
{
    // Obtener el precio del producto
    float precio = m_productos.at(index)->precio();
    // Mostrar el precio
    ui->outPrecio->setText("$ " + QString::number(precio,'f',2));
}


void Principal::producto()
{
    int index = ui->inProducto->currentIndex();
    Producto *p = m_productos.at(index);
    int fila = ui->outDetalle->rowCount();
    ui->outDetalle->setItem(fila,1,new QTableWidgetItem(p->nombre()));
}

bool Principal::buscarRepetidos(Producto *producto, int cantidad)
{
    //Obtener NumFilas
    int numFilas = ui->outDetalle->rowCount();
    //Recorrer la tabla de productos
    for(int i=0;i<numFilas;i++){

        //Obtener el item en la fila y columna posicion 1
        QTableWidgetItem *item = ui->outDetalle->item(i,1);

        //Obtener el nombre del producto
        QString dato = item->data(Qt::DisplayRole).toString();

        //Comparar el producto
        if(dato==producto->nombre()){
            QTableWidgetItem *item = ui->outDetalle->item(i,0);
            int actualCantidad = item->data(Qt::DisplayRole).toInt();

            //Sumar las cantidades de un mismo producto
            int nuevaCantidad = actualCantidad + cantidad;

            //Calcular el nuevo subtotal generado
            float subtotal = nuevaCantidad*producto->precio();

            //Actualizar en la tabla
            ui->outDetalle->setItem(i,0,new QTableWidgetItem(QString::number(nuevaCantidad)));
            ui->outDetalle->setItem(i,2,new QTableWidgetItem(QString::number(subtotal)));
            return true;
        }
    }
    return false;
}

void Principal::calcular(float stProducto)
{
    m_subtotal += stProducto;
    float iva = m_subtotal * IVA / 100;
    float total = m_subtotal + iva;

    ui->outSubtotal->setText(QString::number(m_subtotal,'f',2));
    ui->outIva->setText(QString::number(iva,'f',2));
    ui->outTotal->setText(QString::number(total,'f',2));
}

void Principal::on_inCedula_editingFinished()
{
    valID();
}

void Principal::on_inNombre_editingFinished()
{
    valCliente();
}


