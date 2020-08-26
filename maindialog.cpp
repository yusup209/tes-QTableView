#include "maindialog.h"
#include "ui_maindialog.h"
#include "QNetworkProxyFactory"

MainDialog::MainDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::MainDialog)
{
    ui->setupUi(this);
    defineTableHeader(0);
    LoadData();
}

MainDialog::~MainDialog()
{
    delete ui;
}

void MainDialog::defineTableHeader(int rowCount){
    model = new QStandardItemModel(this);
    model->setRowCount(rowCount);
    model->setColumnCount(4);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Username"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
}

void MainDialog::LoadData(){
    QNetworkProxyFactory::setUseSystemConfiguration(true);
    QNetworkAccessManager *man = new QNetworkAccessManager(this);
    QNetworkRequest req;

    req = QNetworkRequest(QUrl(apiUrl));
    connect(man, &QNetworkAccessManager::finished, this, &MainDialog::LoadDataResponse);
    qDebug() << "starting sending get request...";
    ui->pushButton->setEnabled(false);
    ui->pushButton_2->setEnabled(false);
    man->get(req);
}

void MainDialog::LoadDataResponse(QNetworkReply *repl){
    QString response = repl->readAll();

    if (response.trimmed() != ""){
        qDebug() << "get data users sukses";
        QJsonDocument doc = QJsonDocument::fromJson(response.toUtf8());
        dataResponse = doc.array();
        populateDataToTable();
        ui->tableView->setModel(model);

        ui->pushButton->setEnabled(true);
        ui->pushButton_2->setEnabled(true);

    } else {
        qDebug() << "get data users g a g a l, karena kosong";
    }
}

void MainDialog::populateDataToTable(){
    int dataCount = dataResponse.count();
    defineTableHeader(dataCount);
    int it = 0;
    for(auto item : dataResponse){
        QJsonObject currentObject = item.toObject();

        int id = currentObject["id"].toInt();
        QString name = currentObject["name"].toString();
        QString username = currentObject["username"].toString();
        QString email = currentObject["email"].toString();

        QStandardItem *itemId = new QStandardItem(QString::number(id));
        QStandardItem *itemName = new QStandardItem(name);
        QStandardItem *itemUsername = new QStandardItem(username);
        QStandardItem *itemEmail = new QStandardItem(email);

        model->setItem(it,0,itemId);
        model->setItem(it,1,itemName);
        model->setItem(it,2,itemUsername);
        model->setItem(it,3,itemEmail);

        it++;
    }
}

void MainDialog::refreshData(){
    model->clear();
    LoadData();
}


void MainDialog::on_pushButton_clicked()
{
    //btn refresh table
    refreshData();
}

void MainDialog::on_pushButton_2_clicked()
{
    //clear data
    ui->pushButton->setEnabled(false);
    model->clear();
    ui->pushButton->setEnabled(true);
}
