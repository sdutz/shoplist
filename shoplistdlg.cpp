#include "shoplistdlg.h"
#include "ui_shoplistdlg.h"
#include <QClipboard>
#include <QMessageBox>
#include <QInputDialog>
#include <QStringListModel>

//---------------------------------------------------------------
constexpr char SL_W   [] = "SL_W" ;
constexpr char SL_H   [] = "SL_H" ;
constexpr char SL_IN  [] = "SL_IN" ;
constexpr char SL_OUT [] = "SL_OUT" ;

//---------------------------------------------------------------
ShopListDlg::ShopListDlg( QWidget *parent) : QDialog( parent), ui( new Ui::ShopListDlg)
{
    ui->setupUi( this) ;
    resize( m_set.value( SL_W).toInt(), m_set.value( SL_H).toInt()) ;
    ui->inList->setModel( new QStringListModel( m_set.value( SL_IN).toString().split( ","))) ;
    ui->outList->setModel( new QStringListModel( m_set.value( SL_OUT).toString().split( ","))) ;
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
    auto list = dynamic_cast<QStringListModel*>(ui->inList->model())->stringList() ;
    m_set.setValue( SL_IN, list.join( ",")) ;
    list = dynamic_cast<QStringListModel*>(ui->outList->model())->stringList() ;
    m_set.setValue( SL_OUT, list.join( ",")) ;

    m_set.setValue( SL_W, width()) ;
    m_set.setValue( SL_H, height()) ;

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
    QApplication::clipboard()->setText( list.join( "\n")) ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnInsert_clicked()
{
    auto szNew = QInputDialog::getText( this, windowTitle(), "Add item") ;
    if ( szNew.isEmpty()) {
        return ;
    }
    auto list = dynamic_cast<QStringListModel*>( ui->outList->model())->stringList() ;
    if ( list.indexOf( szNew) == -1) {
        list.append( szNew) ;
        dynamic_cast<QStringListModel*>( ui->outList->model())->setStringList( list) ;
    }
}
