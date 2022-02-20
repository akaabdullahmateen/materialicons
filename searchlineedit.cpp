#include "searchlineedit.h"
#include <QKeyEvent>
#include <QMouseEvent>

SearchLineEdit::SearchLineEdit(QWidget *parent)
    : QLineEdit{parent}
{
}

void SearchLineEdit::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Down){
        emit downPressed();
    }

    else if(event->key() == Qt::Key_Up){
        emit upPressed();
    }

    QLineEdit::keyPressEvent(event);
}

void SearchLineEdit::mousePressEvent(QMouseEvent *event){
    emit mousePressed();
    QLineEdit::mousePressEvent(event);
}
