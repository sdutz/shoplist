#pragma once

//---------------------------------------------------------------
#include <QDialog>
#include <QListView>

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

            void on_btnCopy_clicked();

private:
            void moveCurr( QListView* pSrc, QListView* pDest) ;
    private:
            Ui::ShopListDlg *ui ;
} ;

