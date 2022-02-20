#include "settingssidebar.h"


SettingsSideBar::SettingsSideBar(QWidget *parent)
    : QWidget{parent}
{
}

void SettingsSideBar::mousePressEvent(QMouseEvent *event){
    emit mousePressed();
    QWidget::mousePressEvent(event);
}
