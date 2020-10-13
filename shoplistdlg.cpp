#include "shoplistdlg.h"
#include "ui_shoplistdlg.h"
#include <QClipboard>
#include <QMessageBox>
#include <QStringListModel>

//---------------------------------------------------------------
ShopListDlg::ShopListDlg( QWidget *parent) : QDialog( parent), ui( new Ui::ShopListDlg)
{
    ui->setupUi( this) ;

    ui->outList->setModel( new QStringListModel( QStringList() << "es1" << "es2")) ;
    ui->inList->setModel( new QStringListModel( )) ;
}

//---------------------------------------------------------------
ShopListDlg::~ShopListDlg()
{
    delete ui ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnOk_clicked()
{
    close() ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnCancel_clicked()
{
    close() ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnAdd_clicked()
{
    moveCurr( ui->outList, ui->inList) ;
}

//---------------------------------------------------------------
void
ShopListDlg::moveCurr( QListView* pSrc, QListView* pDest)
{
    auto list = dynamic_cast<QStringListModel*>( pSrc->model())->stringList() ;
    auto nCurr = pSrc->currentIndex().row() ;
    auto szCurr = list.at( nCurr) ;
    list.removeAt( nCurr) ;

    dynamic_cast<QStringListModel*>( pSrc->model())->setStringList( list) ;
    list = dynamic_cast<QStringListModel*>( pDest->model())->stringList() ;
    list.append( szCurr) ;
    dynamic_cast<QStringListModel*>( pDest->model())->setStringList( list) ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnRemove_clicked()
{
    moveCurr( ui->inList, ui->outList) ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnAbout_clicked()
{
    QMessageBox::about( this, "About", "Made by Sdutz") ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnCopy_clicked()
{
    auto list = dynamic_cast<QStringListModel*>( ui->inList->model())->stringList() ;

    QString szRes ;
    foreach( auto curr, list) {
        szRes += curr + "\n" ;
    }

    QApplication::clipboard()->setText( szRes) ;
}
