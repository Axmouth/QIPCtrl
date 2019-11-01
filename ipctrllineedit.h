#ifndef IPCTRLLINEEDIT_H
#define IPCTRLLINEEDIT_H

#include <QKeyEvent>
#include <QMouseEvent>
#include <QLineEdit>
#include <QIntValidator>

class IPCtrlLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit IPCtrlLineEdit(const QString & contents = "", QWidget *parent = 0);
    virtual ~IPCtrlLineEdit() {}

signals:
    void jumpForward();
    void jumpBackward();

public slots:
    void jumpIn();

protected:
    virtual void focusInEvent(QFocusEvent *event);
    virtual void keyPressEvent(QKeyEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent *event);

private:
    bool selectOnMouseRelease;
};

#endif // IPCTRLLINEEDIT_H
