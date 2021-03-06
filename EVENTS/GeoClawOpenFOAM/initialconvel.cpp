#include "initialconvel.h"
#include "ui_initialconvel.h"
#include <QDebug>

//*********************************************************************************
// Initial conditions: Velocity
//*********************************************************************************
initialconVel::initialconVel(int type, QWidget *parent) :
    QFrame(parent),
    ui(new Ui::initialconVel)
{
    ui->setupUi(this);

    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Delete initial conditions: Velocity
//*********************************************************************************
initialconVel::~initialconVel()
{
    delete ui;
}

//*********************************************************************************
// Refresh data
//*********************************************************************************
void initialconVel::refreshData(int type)
{
    // Initialize to show / hide elements
    hideshowelems(type);
}

//*********************************************************************************
// Show - hide elements
//*********************************************************************************
void initialconVel::hideshowelems(int type)
{
    if((type == 1) || (type == 2))
    {
        ui->Lbl_Notice->show();
        ui->Lbl_Vel->hide();
        ui->DSpBx_Vx->hide();
        ui->DSpBx_Vy->hide();
        ui->DSpBx_Vz->hide();
        ui->Lbl_Regions->hide();
        ui->Tbl_IniCondTable->hide();
        ui->Btn_AddRegion->hide();
        ui->Btn_RemRegion->hide();
    }
    else
    {
        ui->Lbl_Notice->hide();
        ui->Lbl_Vel->show();
        ui->DSpBx_Vx->show();
        ui->DSpBx_Vy->show();
        ui->DSpBx_Vz->show();
        ui->Lbl_Regions->show();
        ui->Tbl_IniCondTable->show();
        ui->Btn_AddRegion->show();
        ui->Btn_RemRegion->show();
    }
}

//*********************************************************************************
// Get data from initial phase
//*********************************************************************************
bool initialconVel::getData(QMap<QString, QString>& map,int type)
{
    bool hasData = false;

    // If not dealing with SW-solutions
    //if((type != 1) || (type != 2))
    if(type > 2)
    {
        // Get global initial velocity
        QString glveldata = ui->DSpBx_Vx->textFromValue(ui->DSpBx_Vx->value()) +
                "," + ui->DSpBx_Vy->textFromValue(ui->DSpBx_Vy->value()) +
                "," + ui->DSpBx_Vz->textFromValue(ui->DSpBx_Vz->value());
        map.insert("InitialVelocityGlobal",glveldata);
        map.insert("NumVelocityRegion",QString::number(ui->Tbl_IniCondTable->rowCount()));

        // Get local initial velocity
        if(ui->Tbl_IniCondTable->rowCount() > 0)
        {
            for(int ii=0;ii<ui->Tbl_IniCondTable->rowCount(); ++ii)
            {
                QString veldata = ui->Tbl_IniCondTable->item(ii,0)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,1)->text() +
                        "," + ui->Tbl_IniCondTable->item(ii,2)->text();
                map.insert("InitialVelocityRegion"+QString::number(ii),veldata);
            }
        }

    }

    // Change hasData to be true
    hasData = true;

    // Return hasdata
    return hasData;
}

//*********************************************************************************
// Add regions for pressure initial condition
//*********************************************************************************
void initialconVel::on_Btn_AddRegion_clicked()
{
    ui->Tbl_IniCondTable->insertRow(ui->Tbl_IniCondTable->rowCount());
}

//*********************************************************************************
// Remove regions for pressure initial condition
//*********************************************************************************
void initialconVel::on_Btn_RemRegion_clicked()
{
    ui->Tbl_IniCondTable->removeRow(ui->Tbl_IniCondTable->currentRow());
}
