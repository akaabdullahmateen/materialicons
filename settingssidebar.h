#ifndef SETTINGSSIDEBAR_H
#define SETTINGSSIDEBAR_H

#include <QWidget>

class SettingsSideBar : public QWidget
{
    Q_OBJECT

public:
    explicit SettingsSideBar(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;

signals:
    void mousePressed();

};

#endif // SETTINGSSIDEBAR_H
