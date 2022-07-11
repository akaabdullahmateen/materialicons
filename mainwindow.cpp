#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dialog.h"
#include "suggestionbutton.h"
#include "iconbutton.h"
#include "settingssidebar.h"

#include <QDir>
#include <QToolButton>
#include <QScrollArea>
#include <QScrollBar>
#include <QVBoxLayout>
#include <QFileInfo>
#include <QTimer>
#include <QFileDialog>
#include <QStandardPaths>
#include <QRegularExpression>
#include <QScreen>
#include <QGraphicsEffect>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    initializeSettings();
    initializeVariables();
    initializeContentLayout();
    initializeSuggestions();
    defineConnections();
    customizeScrollArea();
    populateContent();
    prepareUi();
}

void MainWindow::initializeSettings(){
    QCoreApplication::setOrganizationName("lambrella");
    QCoreApplication::setOrganizationDomain("lambrella.materialicons.com");
    QCoreApplication::setApplicationName("Material Icons");
    QCoreApplication::setApplicationVersion("1.0");
}

void MainWindow::initializeVariables(){
    suggestionBoxHeight = 0;
    currentSuggestion   = -1;
    baseColor           = settings.value("baseColor", "#000000").toString();
    projectFolder       = settings.value("projectFolder", QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation)).toString();
    resourceFolder      = settings.value("resourceFolder", QStandardPaths::writableLocation(QStandardPaths::DownloadLocation)).toString();
    resourcesDirPath    = "/home/yahya/Documents/projects/materialicons/resources";
}

void MainWindow::initializeContentLayout(){
    contentLayout = new FlowLayout();
    ui->content->setLayout(contentLayout);
}

void MainWindow::initializeSuggestions(){
    suggestionBoxLayout = new QVBoxLayout();
    suggestionBoxLayout->setContentsMargins(2,2,2,2);
    suggestionBoxLayout->setSpacing(0);

    suggestionBox = new QWidget(ui->centerBody);
    suggestionBox->setFixedWidth(ui->searchEdit->width() - 15);
    suggestionBox->setFixedHeight(suggestionBoxHeight);
    suggestionBox->setStyleSheet(suggestionBoxStyleSheet);
    suggestionBox->setLayout(suggestionBoxLayout);
    suggestionBox->hide();

    QGraphicsDropShadowEffect *dropShadowEffect = new QGraphicsDropShadowEffect();
    dropShadowEffect->setColor(QColor(217, 218, 218));
    dropShadowEffect->setBlurRadius(8);
    dropShadowEffect->setOffset(1, 1);
    suggestionBox->setGraphicsEffect(dropShadowEffect);
}

void MainWindow::defineConnections(){
    connect(ui->sourceButton,           SIGNAL(clicked()),              this, SLOT(onSourceButtonClicked()));
    connect(ui->searchEdit,             SIGNAL(textEdited(QString)),    this, SLOT(onSearchEditTextEditted()));
    connect(ui->searchEdit,             SIGNAL(returnPressed()),        this, SLOT(onReturnPressed()));
    connect(ui->settingsButton,         SIGNAL(clicked()),              this, SLOT(onSettingsButtonClicked()));
    connect(ui->settingsCloseButton,    SIGNAL(clicked()),              this, SLOT(onSettingsCloseButtonClicked()));
    connect(ui->colorEdit,              SIGNAL(returnPressed()),        this, SLOT(onColorEditReturnPressed()));
    connect(ui->projectFolderButton,    SIGNAL(clicked()),              this, SLOT(onProjectFolderButtonClicked()));
    connect(ui->resourceFolderButton,   SIGNAL(clicked()),              this, SLOT(onResourceFolderButtonClicked()));
    connect(ui->searchEdit,             &SearchLineEdit::downPressed,   this, &MainWindow::onDownPressed);
    connect(ui->searchEdit,             &SearchLineEdit::upPressed,     this, &MainWindow::onUpPressed);
    connect(ui->searchEdit,             &SearchLineEdit::mousePressed,  this, &MainWindow::onMousePressedInSearchEdit);
    connect(ui->settingsSideBar,        &SettingsSideBar::mousePressed, this, &MainWindow::onMousePressedInSettingsSideBar);
}

void MainWindow::customizeScrollArea(){
    ui->scrollArea->verticalScrollBar()->setStyleSheet(verticalScrollBarStyleSheet);
}

void MainWindow::populateContent(){
    qDebug() << resourcesDirPath;
    QDir resourcesDir(resourcesDirPath);
    QStringList fileNameList = resourcesDir.entryList(QDir::Files, QDir::Name);

    foreach(QString fileName, fileNameList){
        QFileInfo fileInfo(fileName);
        QString fileBaseName = fileInfo.baseName();

        QStringList fileNameParts = fileBaseName.split(QRegularExpression("[-_\\s+]"));

        for(int i = 0; i < fileNameParts.size(); i++){
            fileNameParts[i].replace(0, 1, fileNameParts[i].at(0).toUpper());
        }

        QString iconName        = fileNameParts.join(" ");
        QString fileLocation    = resourcesDirPath + QDir::separator() + fileName;
        IconButton *iconButton  = new IconButton(nullptr, fileLocation, fileName, iconName);

        iconButton->setText(iconName);
        iconButton->setIcon(fileLocation);
        iconButton->setFixedSize(115,130);

        connect(iconButton, &IconButton::iconClicked, this, &MainWindow::handler);

        contentLayout->addWidget(iconButton);
    }
}

void MainWindow::prepareUi(){
    suggestionBox->setFixedWidth(ui->searchEdit->width()-15);
    ui->searchEdit->setFocus();
    ui->colorEdit->setText(baseColor);
    move(settings.value("windowPosition", screen()->geometry().center() - frameGeometry().center()).toPoint());
    this->resize(settings.value("windowSize", QSize(1450, 800)).toSize());
    ui->settingsSideBar->setFixedWidth(0);
    QGraphicsDropShadowEffect *dropShadowEffect = new QGraphicsDropShadowEffect();
    dropShadowEffect->setColor(QColor(227, 228, 228));
    dropShadowEffect->setBlurRadius(8);
    dropShadowEffect->setOffset(-1, 0);
    ui->settingsSideBar->setGraphicsEffect(dropShadowEffect);
}

void MainWindow::handler(QString fileLocation
                         , QString fileName
                         , QString iconName
                         , bool suggestionUsed){

    suggestionBox->hide();
    ui->content->setFocus();

    Dialog *dialog = new Dialog(nullptr, fileLocation, fileName, iconName, baseColor, projectFolder);
    dialog->setWindowModality(Qt::ApplicationModal);
    dialog->show();

    if(suggestionUsed){
        if(suggestionBoxLayout->count() != 0){
            suggestionBox->show();
        }
        ui->searchEdit->setFocus();
    }

    else{
        ui->content->setFocus();
    }
}

void MainWindow::onSourceButtonClicked(){
    suggestionBox->hide();
    ui->content->setFocus();

    resourcesDirPath = QFileDialog::getExistingDirectory(nullptr
                                                         , "Select Folder"
                                                         , resourceFolder
                                                         , QFileDialog::ShowDirsOnly);

    if(resourcesDirPath != ""){
        QTimer::singleShot(2000, this, SLOT(resetSourceButtonText()));
        ui->sourceButton->setText("Sourced");
        populateContent();
    }
}

void MainWindow::resetSourceButtonText(){
    ui->sourceButton->setText("Source");
}

void MainWindow::onSearchEditTextEditted(){
    suggestionBox->setFixedWidth(ui->searchEdit->width()-15);

    if(ui->searchEdit->text().isEmpty()){
        suggestionBox->hide();
        return;
    }

    QLayoutItem *item;

    while((item = suggestionBoxLayout->takeAt(0))){
        if(QWidget *widget = item->widget()){
            widget->deleteLater();
        }

        delete item;
    }

    suggestionBoxHeight                     = 0;
    int maxWordCount                        = 5;
    int maxSuggestions                      = 8;
    bool terminate                          = false;
    QVector<QString> previousSuggestions    = {};

    for(int wordCount = 1; wordCount < maxWordCount; wordCount++){
        for(int i = 0; i < contentLayout->count(); i++){
            if(suggestionBoxLayout->count() > maxSuggestions - 1){
                terminate = true;
                break;
            }

            item                    = contentLayout->itemAt(i);
            IconButton *iconButton  = static_cast<IconButton *>(item->widget());
            QString searchText      = ui->searchEdit->text();
            QString iconName        = iconButton->text->text();
            searchText              = searchText.split(QRegularExpression("//s+")).join(" ");

            if(iconName.split(' ').count() <= wordCount and iconButton->text->text().contains(searchText, Qt::CaseInsensitive)){
                if(containString(previousSuggestions, iconButton->text->text())){
                    continue;
                }

                SuggestionButton *suggestionButton = new SuggestionButton();
                suggestionButton->setFixedHeight(35);
                suggestionButton->setText("    " + iconButton->text->text().toLower());
                QPixmap original = QPixmap(iconButton->getFileLocation());
                QPixmap temp = QPixmap(original.size());
                temp.fill(QColor(95, 99, 104));
                temp.setMask(original.createMaskFromColor(Qt::transparent));
                suggestionButton->setIcon(QIcon(temp));
                suggestionButton->setStyleSheet(suggestionButtonStyleSheet);
                suggestionButton->setFileLocation(iconButton->getFileLocation());
                suggestionButton->setFileName(iconButton->getFileName());
                suggestionButton->setIconName(iconName);
                connect(suggestionButton, &SuggestionButton::suggestionClicked, this, &MainWindow::handler);
                suggestionBoxLayout->addWidget(suggestionButton);

                previousSuggestions.append(iconName);
                suggestionBoxHeight += 40;
            }
        }

        if(terminate){
            break;
        }
    }

    suggestionBox->setFixedHeight(suggestionBoxHeight);
    suggestionBox->move(118, 120);
    suggestionBox->show();
    currentSuggestion = -1;
}

void MainWindow::onSettingsButtonClicked(){
    if(ui->settingsButton->isChecked()){
        ui->settingsSideBar->setFixedWidth(315);
    }
    else{
        ui->settingsSideBar->setFixedWidth(0);
    }
    QTimer::singleShot(1, this, SLOT(resetSuggestionBoxWidth()));
}

void MainWindow::onSettingsCloseButtonClicked(){
    ui->settingsSideBar->setFixedWidth(0);
    ui->settingsButton->setChecked(false);
    QTimer::singleShot(1, this, SLOT(resetSuggestionBoxWidth()));
}

void MainWindow::resetSuggestionBoxWidth(){
    suggestionBox->setFixedWidth(ui->searchEdit->width()-15);
}

bool MainWindow::containString(QVector<QString> list, QString string){
    foreach(QString stringFromList, list){
        if(stringFromList.size() != string.size()){
            continue;
        }

        if(stringFromList == string){
            return true;
        }
    }

    return false;
}

void MainWindow::mousePressEvent(QMouseEvent *){
    ui->content->setFocus();
    suggestionBox->hide();
}

void MainWindow::onDownPressed(){
    if(suggestionBoxLayout->count() == 0){
        return;
    }

    if(currentSuggestion < suggestionBoxLayout->count() - 1){
        currentSuggestion++;

        SuggestionButton *suggestionButton = static_cast<SuggestionButton *>(suggestionBoxLayout->itemAt(currentSuggestion)->widget());
        suggestionButton->setWhatsThis("HOVERED");
        suggestionButton->setStyleSheet(suggestionButtonStyleSheet);

        if(currentSuggestion > 0){
            SuggestionButton *previousButton = static_cast<SuggestionButton *>(suggestionBoxLayout->itemAt(currentSuggestion - 1)->widget());
            previousButton->setWhatsThis("");
            previousButton->setStyleSheet(suggestionButtonStyleSheet);
        }
    }
}

void MainWindow::onUpPressed(){
    if(suggestionBoxLayout->count() == 0){
        return;
    }

    if(currentSuggestion > 0){
        currentSuggestion--;

        SuggestionButton *suggestionButton = static_cast<SuggestionButton *>(suggestionBoxLayout->itemAt(currentSuggestion)->widget());
        suggestionButton->setWhatsThis("HOVERED");
        suggestionButton->setStyleSheet(suggestionButtonStyleSheet);

        if(currentSuggestion <  suggestionBoxLayout->count() - 1){
            SuggestionButton *previousButton = static_cast<SuggestionButton *>(suggestionBoxLayout->itemAt(currentSuggestion + 1)->widget());
            previousButton->setWhatsThis("");
            previousButton->setStyleSheet(suggestionButtonStyleSheet);
        }
    }
}

void MainWindow::onReturnPressed(){
    SuggestionButton *suggestionButton = static_cast<SuggestionButton *>(suggestionBoxLayout->itemAt(currentSuggestion)->widget());
    handler(suggestionButton->getFileLocation()
            , suggestionButton->getFileName()
            , suggestionButton->getIconName()
            , true);
}

void MainWindow::onMousePressedInSearchEdit(){
    if(suggestionBoxLayout->count() == 0){
        return;
    }
    suggestionBox->show();
}

void MainWindow::onMousePressedInSettingsSideBar(){
    ui->settingsSideBar->setFocus();
    onColorEditReturnPressed();
}

void MainWindow::onColorEditReturnPressed(){
    QColor color;
    color.setNamedColor(ui->colorEdit->text());

    if(color.isValid() == false){
        color = QColor(0,0,0);
    }

    QString colorName = color.name(QColor::HexRgb);
    ui->colorEdit->setText(colorName);
    ui->settingsSideBar->setFocus();
    this->baseColor = colorName;
    settings.setValue("baseColor", baseColor);
}

void MainWindow::onProjectFolderButtonClicked(){
    QString projectFolder = QFileDialog::getExistingDirectory(nullptr
                                                              , "Select Folder"
                                                              , this->projectFolder);
    if(projectFolder != ""){
        this->projectFolder = projectFolder;
        settings.setValue("projectFolder", projectFolder);
    }
}

void MainWindow::onResourceFolderButtonClicked(){
    QString resourceFolder = QFileDialog::getExistingDirectory(nullptr
                                                                , "Select Folder"
                                                                , this->resourceFolder);
    if(resourceFolder != ""){
        this->resourceFolder = resourceFolder;
        settings.setValue("resourceFolder", resourceFolder);
    }
}

void MainWindow::resizeEvent(QResizeEvent *event){
    suggestionBox->setFixedWidth(ui->searchEdit->width()-15);
    QMainWindow::resizeEvent(event);
}

void MainWindow::closeEvent(QCloseEvent *event){
    settings.setValue("windowPosition", this->pos());
    settings.setValue("windowSize", this->size());
    QMainWindow::closeEvent(event);
}

MainWindow::~MainWindow(){
    delete ui;
}

