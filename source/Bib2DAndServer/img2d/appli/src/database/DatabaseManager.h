#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlError>
#include <QFile>
#include <QDir>
#include <QtSql/QSqlQuery>
#include <Tables.h>
#include <QString>
#include <QDateTime>
#include <QVariant>
#include <vector>

class DataBaseManager
{
public:
    DataBaseManager();
    ~DataBaseManager();

    bool openDB(QString &path);
    bool deleteDB();
    bool isOpen();
    void closeDB();
    QSqlError lastError();
    bool insertDoctor(QString identifiant, QString mdp, QString nom, QString prenom, int sizeMax);
    bool deleteDoctor(QString identifiant);
    bool connectDoctor(QString identifiant, QString mdp);
    bool selectDoctor(QString identifiant, QString mdp, Doctor* doctor);
    bool insertExam(QString name, int size, QDateTime date, QString idDoctor, Patient patient);
    bool deleteExam(int id);
    bool updateExamName(int id, QString name);
    bool listExamDoctor(QString idDoctor, std::vector<ExamFile*>* lExamFile);
    int freeSpaceDoctor(QString idDoctor);

private:
    QSqlDatabase db;
    bool createDoctorTable();
    bool createExamFileTable();
    bool createPatientTable();
    int insertExamFile(QString name, int size, QDateTime date, QString idDoctor);
    bool insertPatient(QString lastname, QString firstname, int age, QChar sex, int idExamFile);
};

#endif // DATABASEMANAGER_H
