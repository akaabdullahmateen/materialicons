#include "dialog.h"
#include "ui_dialog.h"

#include <QClipboard>
#include <QTimer>
#include <QColorDialog>
#include <QFileDialog>
#include <QStandardPaths>

Dialog::Dialog(QWidget *parent
               , QString iconLocation
               , QString fileName
               , QString iconName
               , QString baseColor
               , QString projectFolder)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);

    this->iconLocation  = iconLocation;
    this->fileName      = fileName;
    this->iconName      = iconName;

    if(baseColor == ""){
        this->baseColor = "#000000";
    }

    else{
        this->baseColor = baseColor;
    }

    if(projectFolder == ""){
        this->projectFolder = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    }

    else{
        this->projectFolder = projectFolder;
    }

    ui->iconName->setText(iconName);
    ui->iconLocation->setText(iconLocation);
    ui->iconPreview->setPixmap(QPixmap(ui->iconLocation->text()));
    ui->colorEdit->setText(this->baseColor);

    onColorEditTextChanged();
    defineConnections();

    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint);
}

void Dialog::defineConnections(){
    connect(ui->closeButton,    SIGNAL(clicked()),              this, SLOT(onCloseButtonClicked()));
    connect(ui->saveButton,     SIGNAL(clicked()),              this, SLOT(onSaveButtonClicked()));
    connect(ui->copyLinkButton, SIGNAL(clicked()),              this, SLOT(onCopyLinkButtonClicked()));
    connect(ui->colorPreview,   SIGNAL(clicked()),              this, SLOT(onColorPreviewClicked()));
    connect(ui->colorEdit,      SIGNAL(textChanged(QString)),   this, SLOT(onColorEditTextChanged()));
}

void Dialog::onCloseButtonClicked(){
    this->close();
}

void Dialog::onSaveButtonClicked(){
    QPixmap original    = QPixmap(iconLocation);
    QPixmap temp        = QPixmap(original.size());

    QColor color;
    color.setNamedColor(ui->colorEdit->text());

    if(color.isValid() == false){
        color = QColor(0,0,0);
    }

    temp.fill(color);
    temp.setMask(original.createMaskFromColor(Qt::transparent));

    QString rawSaveLocation = QFileDialog::getSaveFileName(nullptr
                                                          , "Save As"
                                                          , projectFolder);

    if(rawSaveLocation == ""){
        return;
    }

    QTimer::singleShot(2000, this, SLOT(resetSaveButtonText()));
    ui->saveButton->setText("Saved");

    QFileInfo fileInfo = QFileInfo(rawSaveLocation);
    QDir dir = fileInfo.dir();
    QString saveLocation = dir.absolutePath() + QDir::separator() + fileInfo.baseName() + ".png";
    temp.save(saveLocation, "PNG", -1);
}

void Dialog::onCopyLinkButtonClicked(){
    QClipboard *clipboard = QGuiApplication::clipboard();
    QTimer::singleShot(2000, this, SLOT(resetCopyLinkButtonText()));
    ui->copyLinkButton->setText("Copied");
    clipboard->setText(ui->iconLocation->text(), QClipboard::Clipboard);
}

void Dialog::resetCopyLinkButtonText(){
    ui->copyLinkButton->setText("Copy Link");
}

void Dialog::resetSaveButtonText(){
    ui->saveButton->setText("Save");
}

void Dialog::onColorPreviewClicked(){
    QColor color;
    color.setNamedColor(ui->colorEdit->text());
    color = QColorDialog::getColor(color, nullptr, "Select Color");
    ui->colorEdit->setText(color.name(QColor::HexRgb));
}

void Dialog::onColorEditTextChanged(){
    QColor color;
    color.setNamedColor(ui->colorEdit->text());

    if(color.isValid() == false){
        color = QColor(0,0,0);
    }

    QPixmap original    = QPixmap(":/icons/native/circle.png");
    QPixmap temp        = QPixmap(original.size());

    temp.fill(color);
    temp.setMask(original.createMaskFromColor(Qt::transparent));
    ui->colorPreview->setIcon(QIcon(temp));
}

Dialog::~Dialog(){
    delete ui;
}
