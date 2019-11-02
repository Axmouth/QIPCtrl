#include "ipctrl.h"
#include <QDebug>
#include <QErrorMessage>

void makeCommonStyle(QLineEdit* line) {
    line->setContentsMargins(0, 0, 0, 0);
    line->setAlignment(Qt::AlignCenter);
    line->setStyleSheet("QLineEdit { border: 0px none; }");
    line->setFrame(false);
    //line->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
}

QLineEdit* makeIpSpliter() {
    QLineEdit *spliter = new QLineEdit(".");
    makeCommonStyle(spliter);

    spliter->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
    spliter->setMaximumWidth(10);
    spliter->setReadOnly(true);
    spliter->setFocusPolicy(Qt::NoFocus);
    return spliter;
}

IPCtrl::IPCtrl(QWidget *parent) :
    QFrame(parent)
{
    setContentsMargins(0, 0, 0, 0);
    setStyleSheet("QFrame { background-color: white;  border: 1px solid white; border-radius: 15px; }\n IPCtrl {border: 1px solid gray;}");
    //setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    QList <IPCtrlLineEdit *>::iterator linesIterator;

    lines.append(new IPCtrlLineEdit("0", this));
    lines.append(new IPCtrlLineEdit("0", this));
    lines.append(new IPCtrlLineEdit("0", this));
    lines.append(new IPCtrlLineEdit("0", this));

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->setSpacing(0);
    setLayout(mainLayout);

    for (linesIterator = lines.begin(); linesIterator != lines.end(); ++linesIterator) {
        makeCommonStyle(*linesIterator);
        mainLayout->addWidget(*linesIterator);

        if (*linesIterator != lines.last()) {
            connect(*linesIterator, &IPCtrlLineEdit::jumpForward,
                *(linesIterator+1), &IPCtrlLineEdit::jumpIn);
            mainLayout->addWidget(makeIpSpliter());
        }
        if (*linesIterator != lines.first()) {
            connect(*linesIterator, &IPCtrlLineEdit::jumpBackward,
                *(linesIterator-1), &IPCtrlLineEdit::jumpIn);
        }
    }

}

QString IPCtrl::getIPText()
{
    QString address = "";
    for (IPCtrlLineEdit *lineEdit: lines) {
        QString temp = "";
        if (address != "") {
            temp = ".";
        }
        address += temp + lineEdit->text();
    }

    return address;
}

void IPCtrl::setIPText(QString IPText)
{
    //QRegularExpression reIP("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$"); // Okay, passes padding zeroes
    //QRegularExpression reIP("^((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)(\\.)){3}+((25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?))$"); // Okay, passes padding zeroes
    //QRegularExpression reIP("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$"); // Looks Perfect
    QRegularExpression reIP("^((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])$"); //
    if (reIP.match(IPText).hasMatch()) {
        QStringList IPNumList = IPText.split(".");
        int i = 0;
        //while (IPNumList.count() < 4) {
        //    IPNumList.insert(IPNumList.count()-1, "0");
        //}
        for (IPCtrlLineEdit *lineEdit : lines) {
            lineEdit->setText(IPNumList.at(i));
            i++;
        }
    } else {
        qCritical() << "IPCtrl::setIPText(QString IPText) : Input could not be recognized as an IP Address.";
    }
}
