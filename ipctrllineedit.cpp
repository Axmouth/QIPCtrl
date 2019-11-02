
#include "ipctrllineedit.h"
#include <QDebug>

IPCtrlLineEdit::IPCtrlLineEdit(const QString & contents, QWidget *parent) :
    QLineEdit(contents, parent), selectOnMouseRelease(false)
{
    QIntValidator *valid = new QIntValidator(0, 255, this);
    setValidator(valid);
    //(*linesIterator)->setInputMask("000");
    connect(this, &QLineEdit::textChanged, this, &IPCtrlLineEdit::onTextChange);
}

void IPCtrlLineEdit::jumpIn()
{
    setFocus();

    selectOnMouseRelease = false;
    selectAll();
}

void IPCtrlLineEdit::onTextChange()
{
    if(text() == "" || text() == " " || text() == "  "){
        setText("0");
    }
    if(text().toInt() > 255){
        setText("255");
    }
}

void IPCtrlLineEdit::focusInEvent(QFocusEvent *event)
{
    QLineEdit::focusInEvent(event);
    selectOnMouseRelease = true;
}


void IPCtrlLineEdit::mouseReleaseEvent(QMouseEvent *event)
{
    if(!selectOnMouseRelease)
        return;

    selectOnMouseRelease = false;
    selectAll();

    QLineEdit::mouseReleaseEvent(event);
}

void IPCtrlLineEdit::keyPressEvent(QKeyEvent * event)
{
    int key = event->key();
    int cursorPos = cursorPosition();

    // Jump forward by Space
    if (key == Qt::Key_Space) {
        emit jumpForward();
        event->accept();
        return;
    }

    // Jump Backward only from 0 cursor position
    if (cursorPos == 0) {
        if ((key == Qt::Key_Left) || (key == Qt::Key_Backspace)) {
            emit jumpBackward();
            event->accept();
            return;
        }
    }

    // Jump forward from last postion by right arrow
    if (cursorPos == text().count()) {
        if (key == Qt::Key_Right) {
            emit jumpForward();
            event->accept();
            return;
        }
    }

    // After key is placed cursor has new position
    QLineEdit::keyPressEvent(event);
    int freshCurPos = cursorPosition();

    if ((freshCurPos == 3) && (key != Qt::Key_Right))
        emit jumpForward();
}
