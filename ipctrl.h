#ifndef IPCTRL_H
#define IPCTRL_H

#include <QWidget>
#include <QLineEdit>
#include <QFrame>
#include <QHBoxLayout>
#include "ipctrllineedit.h"

class IPCtrl :  public QFrame
{
    Q_OBJECT

public:
    IPCtrl(QWidget *parent = nullptr);
};

#endif // IPCTRL_H
