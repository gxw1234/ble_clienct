#ifndef DISPOSITION_H
#define DISPOSITION_H
#include <QWidget>
#include "tcpserver/tcpapp.h"
#include <QTextEdit>
#include <QLineEdit>
#include <QLabel>
#include <QPushButton>
#include <QGridLayout>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSpinBox>
#include "common/cmdanalyze.h"

struct SingleKeyPress {
    QString feature_name;
    QString key_cmd;
    QString key_ir;
    QString key_ble;
    QString handler;
    SingleKeyPress(const QString& feature, const QString& cmd, const QString& ir, const QString& ble, const QString& handle)
        : feature_name(feature), key_cmd(cmd), key_ir(ir), key_ble(ble), handler(handle) {}
};

struct SingleKeyUp {
    QString feature_name;
    QString key_cmd;

    SingleKeyUp(const QString& feature, const QString& cmd)
        : feature_name(feature), key_cmd(cmd) {}
};


struct TriggerKey {
    QString feature_name;
    QString first_key_cmd;
    int delay;
    QString after_key_cmd;

    TriggerKey(const QString& feature, const QString& firstCmd, int d, const QString& afterCmd)
        : feature_name(feature), first_key_cmd(firstCmd), delay(d), after_key_cmd(afterCmd) {}
};



struct Combinationsname {
    QString keycmd;
    int delay;

};

struct CombinationKey {
    QString feature_name;
    QList<Combinationsname> first_key_cmd;
    int delay;
    QList<Combinationsname> after_key_cmd;
};





struct FunctionModule {
    QString feature_name;
    QString description;
    QString _assert;

    FunctionModule(const QString& feature, const QString& desc, const QString& _assert)
        : feature_name(feature), description(desc), _assert(_assert) {}
};

struct ReadVersion {
    QString feature_name;
    QString description;
    QString _assert;

    ReadVersion(const QString& feature, const QString& desc, const QString& _assert)
        : feature_name(feature), description(desc), _assert(_assert) {}
};










class Disposition : public QWidget
{
         Q_OBJECT
public:
    explicit Disposition(QWidget *parent = nullptr);
    void initView();
    void setnetworkserviceOBJECT(Tcpapp *tcpaap ,bool status);
    bool connection_state;

private:

    QLabel *burn_qlabel=nullptr;
    QLineEdit *burn_lindit=nullptr;
    QPushButton *start_study_button=nullptr;
    QPushButton *generate_json_button=nullptr;


    QSpinBox *QSpinBox_cdm =nullptr;
    QPushButton *Generate_cmd=nullptr;

    Tcpapp *tcpaap = nullptr;
    QTextEdit *showlog=nullptr;

    QList<SingleKeyPress> singleKeyPressList;
    QList<SingleKeyUp> singleKeyUpList;
    QList<TriggerKey> TriggerKeyList;
    QList<FunctionModule> FunctionModuleList;
    QList<ReadVersion> ReadVersionList;
    Cmdanalyze  get_cmd;





    QJsonArray  createSingleKeyPressJson(const QList<SingleKeyPress>& keyPressList);
    QJsonArray  createSingleKeyUpJson(const QList<SingleKeyUp>& keyUpList);
    QJsonArray  createSingleKeyUpJson(const QList<TriggerKey>& TriggerKeyList);
    QJsonArray  createSingleFunctionModuleJson(const QList<FunctionModule>& FunctionModuleList);
    QJsonArray  createSingleReadVersionJson(const QList<ReadVersion>& ReadVersionList);

private slots:
    void onstart_burn();
    void handleDataReceived(quint8 dataType, const QByteArray& buffer,bool islen_, bool ismd5_);
    void handleConnected_state(bool connected_state);
    void onstart_savejson();

    void Generate_cmd_start();

};

#endif // DISPOSITION_H
