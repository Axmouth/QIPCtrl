#ifndef IPCTRL_H
#define IPCTRL_H

#include <QWidget>
#include <QLineEdit>
#include <QFrame>
#include <QHBoxLayout>
#include <QRegularExpression>
#include "ipctrllineedit.h"

class IPCtrl :  public QFrame
{
    Q_OBJECT

public:
    IPCtrl(QWidget *parent = nullptr);
    QString getIPText();
    void setIPText(QString IPText);
private:
    QList<IPCtrlLineEdit *> lines;
};

#endif // IPCTRL_H
