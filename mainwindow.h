#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>

#include "flowlayout.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void onSourceButtonClicked();
    void onSearchEditTextEditted();
    void onReturnPressed();
    void resetSourceButtonText();
    void onSettingsButtonClicked();
    void onSettingsCloseButtonClicked();
    void resetSuggestionBoxWidth();
    void onColorEditReturnPressed();
    void onProjectFolderButtonClicked();
    void onResourceFolderButtonClicked();

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    Ui::MainWindow  *ui;
    FlowLayout      *contentLayout;
    QWidget         *suggestionBox;
    QVBoxLayout     *suggestionBoxLayout;
    QSettings       settings;
    int             suggestionBoxHeight;
    int             currentSuggestion;
    int             defaultMaxColumns;
    QString         resourcesDirPath;
    QString         baseColor;
    QString         projectFolder;
    QString         resourceFolder;
    QString         suggestionButtonStyleSheet = "QPushButton{border-radius: 0px; font-size: 10pt; font-weight: 600; color: #5f6368; padding-left: 30px; text-align: left;  border: 0px;} QPushButton:hover{background-color: #f7f8f8;} QPushButton:pressed{background-color: #e7e8e8;} QPushButton[whatsThis=\"HOVERED\"]{background-color: #e8f0fe;}";
    QString         verticalScrollBarStyleSheet = "QScrollBar:vertical {border: 0px;background:transparent;width: 17px;border-radius: 3px;margin: 7px 10px 30px 0px;}QScrollBar::handle:vertical {min-height: 100px;border: 0px solid red;border-radius: 3px;background-color: #979797;}QScrollBar::add-line:vertical {height: 0px;subcontrol-position: bottom;subcontrol-origin: margin;}QScrollBar::sub-line:vertical {height: 0 px;subcontrol-position: top;subcontrol-origin: margin;}";
    QString         suggestionBoxStyleSheet = "QWidget{border:1px solid #dadce0; border-top: 0px; border-bottom-left-radius: 8px; border-bottom-right-radius: 8px;}";

    void handler(QString fileLocation
                 , QString fileName
                 , QString iconName
                 , bool suggestionUsed);

    void onDownPressed();
    void onUpPressed();
    void onMousePressedInSearchEdit();
    void onMousePressedInSettingsSideBar();

    void initializeSettings();
    void initializeVariables();
    void initializeSuggestions();
    void initializeContentLayout();
    void initializeSettingsSideBar();
    void defineConnections();
    void populateContent();
    void customizeScrollArea();
    void prepareUi();
    bool containString(QVector<QString> list, QString string);
};
#endif // MAINWINDOW_H
