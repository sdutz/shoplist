#pragma once

//---------------------------------------------------------------
#include <QDialog>
#include <QListView>
#include <QSettings>

QT_BEGIN_NAMESPACE
namespace Ui { class ShopListDlg ; }
QT_END_NAMESPACE

//---------------------------------------------------------------
class ShopListDlg : public QDialog
{
    Q_OBJECT

    public:
        ShopListDlg( QWidget *parent = nullptr) ;
        ~ShopListDlg() ;

    private slots:
            void on_btnOk_clicked() ;
            void on_btnCancel_clicked() ;
            void on_btnAdd_clicked() ;
            void on_btnRemove_clicked() ;
            void on_btnAbout_clicked() ;
            void on_btnCopy_clicked() ;
            void on_btnInsert_clicked() ;
            void closeEvent( QCloseEvent* pEvent) ;
            void on_btnDelete_clicked() ;

    private:
            QString removeCurr( QListView* pSrc) ;
            void addToList( QListView* pDst, const QString& szToAdd) ;
            void moveCurr( QListView* pSrc, QListView* pDst) ;
            void save() ;
    private:
            bool            m_bMod = false ;
            QSettings       m_set ;
            Ui::ShopListDlg *ui = nullptr ;
} ;

