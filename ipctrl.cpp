#include "ipctrl.h"

void makeCommonStyle(QLineEdit* line) {
    line->setContentsMargins(0, 0, 0, 0);
    line->setAlignment(Qt::AlignCenter);
    line->setStyleSheet("QLineEdit { border: 0px none; }");
    line->setFrame(false);
    line->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}

QLineEdit* makeIpSpliter() {
    QLineEdit *spliter = new QLineEdit(".");
    makeCommonStyle(spliter);

    spliter->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    spliter->setMaximumWidth(10);
    spliter->setReadOnly(true);
    spliter->setFocusPolicy(Qt::NoFocus);
    return spliter;
}

IPCtrl::IPCtrl(QWidget *parent) :
    QFrame(parent)
{
    //setContentsMargins(0, 0, 0, 0);
    //setStyleSheet("QFrame { background-color: white;  border: 1px solid white; border-radius: 15px; }");

    QList <IPCtrlLineEdit *>  lines;
    QList <IPCtrlLineEdit *>::iterator linesIterator;

    lines.append(new IPCtrlLineEdit);
    lines.append(new IPCtrlLineEdit);
    lines.append(new IPCtrlLineEdit);
    lines.append(new IPCtrlLineEdit);

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
