#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog( QWidget *parent = nullptr
            , QString iconLocation = ""
            , QString fileName = ""
            , QString iconName = ""
            , QString baseColor = ""
            , QString projectFolder = "");

    ~Dialog();

public slots:
    void onCloseButtonClicked();
    void onSaveButtonClicked();
    void onCopyLinkButtonClicked();
    void resetCopyLinkButtonText();
    void resetSaveButtonText();
    void onColorPreviewClicked();
    void onColorEditTextChanged();

private:
    Ui::Dialog  *ui;
    QString     iconLocation;
    QString     fileName;
    QString     iconName;
    QString     baseColor;
    QString     projectFolder;

    void defineConnections();

};

#endif // DIALOG_H
