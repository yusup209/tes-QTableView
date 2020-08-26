#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include <QDialog>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QVariantMap>
#include <qjsontablemodel/qjsontablemodel.h>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QDateTime>
#include <QStandardItemModel>

QT_BEGIN_NAMESPACE
namespace Ui { class MainDialog; }
QT_END_NAMESPACE

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(QWidget *parent = nullptr);
    ~MainDialog();

private slots:
    void on_pushButton_clicked();
    void defineTableHeader(int rowCount);
    void LoadData();
    void LoadDataResponse(QNetworkReply*);
    void populateDataToTable();
    void refreshData();

    void on_pushButton_2_clicked();

private:
    Ui::MainDialog *ui;
    QJsonArray dataResponse;
    QStandardItemModel *model;
    QString apiUrl = "https://jsonplaceholder.typicode.com/users";
};
#endif // MAINDIALOG_H
