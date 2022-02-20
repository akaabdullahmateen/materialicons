#ifndef SUGGESTIONBUTTON_H
#define SUGGESTIONBUTTON_H

#include <QPushButton>

class SuggestionButton : public QPushButton
{
    Q_OBJECT

public:
    explicit SuggestionButton(QWidget *parent = nullptr);

    void setFileLocation(QString fileLocation);
    void setFileName(QString fileName);
    void setIconName(QString iconName);

    QString getFileLocation();
    QString getFileName();
    QString getIconName();

signals:
    void suggestionClicked(QString fileLocation
                           , QString fileName
                           , QString iconName
                           , bool suggestionUsed);

protected:
    void mousePressEvent(QMouseEvent *event) override;

private:
    QString fileLocation;
    QString fileName;
    QString iconName;

};

#endif // SUGGESTIONBUTTON_H
