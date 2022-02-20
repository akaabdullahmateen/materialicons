#include "iconbutton.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QIcon>

IconButton::IconButton(QWidget *parent
                       , QString fileLocation
                       , QString fileName
                       , QString iconName)
    : QWidget{parent}
{
    this->fileLocation  = fileLocation;
    this->fileName      = fileName;
    this->iconName      = iconName;

    frame               = new QFrame();
    iconFrame           = new QFrame();
    icon                = new QLabel();
    text                = new QLabel();
    frameLayout         = new QVBoxLayout();
    layout              = new QVBoxLayout();
    iconFrameLayout     = new QHBoxLayout();

    icon->setFixedSize(40,40);

    text->setWordWrap(true);
    text->setAlignment(Qt::AlignCenter);
    text->setStyleSheet(textStyleSheet);

    iconFrame->setLayout(iconFrameLayout);
    iconFrameLayout->addWidget(icon);

    frameLayout->addWidget(iconFrame);
    frameLayout->addWidget(text);
    frameLayout->setContentsMargins(0,0,0,0);
    frameLayout->setSpacing(0);
    frame->setLayout(frameLayout);

    this->setLayout(layout);
    layout->addWidget(frame);

    wasPressed = false;
}

void IconButton::setIcon(QString icon){
    QPixmap original = QPixmap(icon);
    QPixmap temp(original.size());

    temp.fill(QColor(95, 99, 104));
    temp.setMask(original.createMaskFromColor(Qt::transparent));

    this->icon->setPixmap(temp);
    this->icon->setScaledContents(true);
}

void IconButton::setText(QString text){
    this->text->setText(text);
}

QString IconButton::getFileLocation(){
    return fileLocation;
}

QString IconButton::getFileName(){
    return fileName;
}

void IconButton::mousePressEvent(QMouseEvent *){
    frame->setStyleSheet(pressStyleSheet);
    wasPressed = true;
}

void IconButton::mouseReleaseEvent(QMouseEvent *){
    frame->setStyleSheet(releaseStyleSheet);

    if(wasPressed){
        onIconClicked();
        wasPressed = false;
    }
}

void IconButton::enterEvent(QEnterEvent *){
    frame->setStyleSheet(enterStyleSheet);
}

void IconButton::leaveEvent(QEvent *){
    frame->setStyleSheet(leaveStyleSheet);
}

void IconButton::onIconClicked(){
    emit iconClicked(fileLocation
                     , fileName
                     , iconName
                     , false);
}

IconButton::~IconButton(){
}
