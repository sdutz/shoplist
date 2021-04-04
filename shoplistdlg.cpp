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
#define LIST_MODEL dynamic_cast<QStringListModel*>

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
ShopListDlg::save()
{
    auto list = LIST_MODEL( ui->inList->model())->stringList() ;
    m_set.setValue( SL_IN, list.join( ",")) ;
    list = LIST_MODEL( ui->outList->model())->stringList() ;
    m_set.setValue( SL_OUT, list.join( ",")) ;
    m_set.setValue( SL_W, width()) ;
    m_set.setValue( SL_H, height()) ;

    m_bMod = false ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnOk_clicked()
{
    if ( m_bMod) {
        save() ;
    }

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
    moveCurr( *ui->outList, *ui->inList) ;
}

//---------------------------------------------------------------
void
ShopListDlg::moveCurr( QListView& lSrc, QListView& lDst)
{
    addToList( lDst, removeCurr( lSrc)) ;
}

//---------------------------------------------------------------
void
ShopListDlg::closeEvent( QCloseEvent* pEvent)
{
    if ( m_bMod  &&  QMessageBox::question( this, "ShopList", "Do you want to save?") == QMessageBox::Yes) {
        save() ;
    }
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnRemove_clicked()
{
    moveCurr( *ui->inList, *ui->outList) ;
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
    auto list = LIST_MODEL( ui->inList->model())->stringList() ;
    QApplication::clipboard()->setText( list.join( "\n")) ;
}

//---------------------------------------------------------------
void
ShopListDlg::on_btnInsert_clicked()
{
    addToList( *ui->outList, QInputDialog::getText( this, windowTitle(), "Add item")) ;
}

//---------------------------------------------------------------
QString
ShopListDlg::removeCurr( QListView& lSrc)
{
    auto list = LIST_MODEL( lSrc.model())->stringList() ;
    auto nCurr = lSrc.currentIndex().row() ;
    if ( nCurr < 0) {
        return "" ;
    }

    auto szRet = list.at( nCurr) ;
    list.removeAt( nCurr) ;
    LIST_MODEL( lSrc.model())->setStringList( list) ;
    m_bMod = true ;
    return szRet ;
}

//---------------------------------------------------------------
void
ShopListDlg::addToList( QListView& lDst, const QString& szToAdd)
{
    if ( szToAdd.isEmpty()) {
        return ;
    }

    auto list = LIST_MODEL( lDst.model())->stringList() ;
    if ( list.contains( szToAdd)) {
        return ;
    }
    list.append( szToAdd) ;
    list.sort() ;
    LIST_MODEL( lDst.model())->setStringList( list) ;
    m_bMod = true ;
}

//---------------------------------------------------------------
void
ShopListDlg::ShopListDlg::on_btnDelete_clicked()
{
    removeCurr( *ui->outList) ;
}
