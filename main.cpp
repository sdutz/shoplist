#include "shoplistdlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a( argc, argv) ;
    a.setApplicationDisplayName( "ShopLost") ;
    a.setApplicationVersion( "1.0") ;
    a.setOrganizationName( "sdutz") ;
    a.setApplicationName( "ShopList") ;

    ShopListDlg w ;
    w.show() ;
    return a.exec() ;
}
