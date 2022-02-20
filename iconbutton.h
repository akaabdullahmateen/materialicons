#ifndef ICONBUTTON_H
#define ICONBUTTON_H

#include <QWidget>
#include <QLabel>
#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>

class IconButton : public QWidget
{
    Q_OBJECT

public:
    QLabel *icon;
    QLabel *text;

    explicit IconButton(QWidget *parent = nullptr
                        , QString fileLocation = ""
                        , QString fileName = ""
                        , QString iconName = "");

    void setIcon(QString icon);
    void setText(QString text);

    QString getFileLocation();
    QString getFileName();

    ~IconButton();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    bool        wasPressed;
    QString     fileLocation;
    QString     fileName;
    QString     iconName;
    QFrame      *frame;
    QFrame      *iconFrame;
    QVBoxLayout *frameLayout;
    QVBoxLayout *layout;
    QHBoxLayout *iconFrameLayout;
    QString     textStyleSheet      = "QLabel{font-size: 9pt; color: #5f6368;}";
    QString     pressStyleSheet     = "QFrame{border: 0px; border-radius: 8px; background-color: #e7e8e8;}";
    QString     releaseStyleSheet   = "QFrame{border: 0px; border-radius: 8px; background-color: #f7f8f8;}";
    QString     enterStyleSheet     = "QFrame{border: 0px; border-radius: 8px; background-color: #f7f8f8;}";
    QString     leaveStyleSheet     = "QFrame{border: 0px; border-radius: 8px;}";

    void onIconClicked();

signals:
    void iconClicked(QString fileLocation
                     , QString fileName
                     , QString iconName
                     , bool suggestionUsed);
};

#endif // ICONBUTTON_H
