#include "suggestionbutton.h"

#include <QMouseEvent>

SuggestionButton::SuggestionButton(QWidget *parent)
    : QPushButton{parent}
{

}

void SuggestionButton::setFileLocation(QString fileLocation){
    this->fileLocation = fileLocation;
}

void SuggestionButton::setFileName(QString fileName){
    this->fileName = fileName;
}

void SuggestionButton::setIconName(QString iconName){
    this->iconName = iconName;
}

QString SuggestionButton::getFileLocation(){
    return fileLocation;
}

QString SuggestionButton::getFileName(){
    return fileName;
}

QString SuggestionButton::getIconName(){
    return iconName;
}

void SuggestionButton::mousePressEvent(QMouseEvent *){
    emit suggestionClicked(fileLocation, fileName, iconName, true);
}
