#include "DatabaseManager.h"
#include <iostream>
#include <vector>

using namespace std;

DataBaseManager::DataBaseManager()
{
}

DataBaseManager::~DataBaseManager()
{
}

bool DataBaseManager::isOpen()
{
    return db.isOpen();
}

void DataBaseManager::closeDB()
{
    db.close();
}

bool DataBaseManager::openDB(QString &path)
{
    bool ret;
    // Find QSLite driver
    db = QSqlDatabase::addDatabase("QSQLITE");
    if (QFile::exists(path))
    {
        db.setDatabaseName(path);
        ret = db.open();
    }
    else
    {    
        db.setDatabaseName(path);
        ret = db.open();
        ret = createDoctorTable();
        ret = createExamFileTable();
        ret = createPatientTable();
    }
    return ret;
}

bool DataBaseManager::createDoctorTable()
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("Create Table Doctor("
                         "id varchar(30) primary key,"
                         "password varchar(30),"
                         "lastname varchar(30),"
                         "firtsname varchar(30),"
                         "sizeMax integer)");
    }
    return ret;
}

bool DataBaseManager::createExamFileTable()
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("Create Table ExamFile("
                         "id integer primary key,"
                         "name varchar(30),"
                         "size integer,"
                         "date smalldatetime,"
                         "idDoctor varchar(30),"
                         "foreign key (idDoctor) references Doctor(id))");
    }
    return ret;
}

bool DataBaseManager::createPatientTable()
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec("Create Table Patient("
                         "id integer primary key,"
                         "lastname varchar(30),"
                         "firstname varchar(30),"
                         "age integer,"
                         "sex char,"
                         "idExamFile integer,"
                         "foreign key (idExamFile) references ExamFile(id))");
    }
    return ret;
}



QSqlError DataBaseManager::lastError()
{
    return db.lastError();
}

bool DataBaseManager::insertDoctor(QString id, QString password, QString lastname, QString firstname, int sizeMax)
{
    bool ret = false;

    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("insert into Doctor values('%1','%2','%3','%4','%5')")
                         .arg(id).arg(password).arg(lastname).arg(firstname).arg(sizeMax));
        std::cout << query.lastQuery().toStdString() <<std::endl;
    }
    return ret;
}

bool DataBaseManager::deleteDoctor(QString identifiant)
{
    bool ret = false;

    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("delete from Doctor where id='%1'").arg(identifiant));
    }
    return ret;
}

int DataBaseManager::insertExamFile(QString name, int size, QDateTime date, QString idDoctor)
{
    bool ret = false;
    int id = 0;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("insert into ExamFile values(NULL,'%1','%2','%3','%4')")
                         .arg(name).arg(size).arg(date.toString()).arg(idDoctor));
        if (ret)
        {
            id = query.lastInsertId().toInt();
        }
    }
    return id;
}

bool DataBaseManager::insertPatient(QString lastname, QString firstname, int age, QChar sex, int idExamFile)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("insert into Patient values(NULL,'%1','%2','%3','%4','%5')")
                         .arg(lastname).arg(firstname).arg(age).arg(sex).arg(idExamFile));
    }
    return ret;
}

bool DataBaseManager::insertExam(QString name, int size, QDateTime date, QString idDoctor, Patient patient)
{
    bool ret = false;
    if(size <= freeSpaceDoctor(idDoctor))
    {
        int id = insertExamFile(name, size, date, idDoctor);
        ret = insertPatient(patient.lastname, patient.firstname, patient.age, patient.sex, id);
    }
    return ret;
}

bool DataBaseManager::deleteExam(int id)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("delete from ExamFile where id='%1'").arg(id));
        if (ret)
        {
            ret = query.exec(QString("delete from Patient where idExamFile='%1'").arg(id));
        }
    }
    return ret;
}

bool DataBaseManager::updateExamName(int id, QString name)
{
    bool ret = false;
    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("update ExamFile set name='%1' where id='%2'").arg(name).arg(id));
    }
    return ret;
}

bool DataBaseManager::connectDoctor(QString id, QString password)
{
    bool ret = false;

    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("select id from Doctor where id = '%1' and password = '%2'")
                         .arg(id).arg(password));
    }
    return ret;
}

bool DataBaseManager::selectDoctor(QString id, QString password, Doctor* doctor)
{
    bool ret = false;

    if(db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("select id, lastname, firstname, sizeMax "
                                 "from Doctor where id = '%1' and password = '%2'")
                         .arg(id).arg(password));
        if (query.next())
        {
            doctor->id=query.value(0).toString();
            doctor->lastname=query.value(2).toString();
            doctor->firstname=query.value(3).toString();
            doctor->sizeMax=query.value(4).toInt();
        }
    }
    return ret;
}

bool DataBaseManager::listExamDoctor(QString idDoctor, std::vector<ExamFile*>* lExamFile)
{
    bool ret = false;

    if (db.isOpen())
    {
        QSqlQuery query;
        ret = query.exec(QString("select e.name, e.size, e.date, p.lastname, p.firstname, p.age,"
                                 "p.sex from ExamFile e, Patient p where e.idDoctor = '%1' and e.id=p.idExamFile")
                         .arg(idDoctor));      
        while (query.next())
        {
            ExamFile *examFile = new ExamFile();
            examFile->name = query.value(0).toString();
            examFile->size = query.value(1).toInt();
            examFile->date = query.value(2).toDateTime();
            examFile->patient.lastname = query.value(3).toString();
            examFile->patient.firstname = query.value(4).toString();
            examFile->patient.age = query.value(5).toInt();
            examFile->patient.sex = query.value(6).toChar();
            lExamFile->push_back(examFile);
        }
    }
    return ret;
}

int DataBaseManager::freeSpaceDoctor(QString idDoctor)
{
    int totalSpace = 0;
    int usedSpace = 0;
    if (db.isOpen())
    {
        QSqlQuery query;
        query.exec(QString("select sizeMax from Doctor d where id='%1'").arg(idDoctor));
        if (query.next()) {
            totalSpace = query.value(0).toInt();
        } else {
            cerr << "Problem wit the database" << endl;
            return 0;
        }
        query.exec(QString("select sum(size) from ExamFile where idDoctor='%1'").arg(idDoctor));
        if(query.next()) {
            usedSpace = query.value(0).toInt();
        } else {
            cerr << "Problem wit the database" << endl;
            return 0;
        }
    }
    return totalSpace - usedSpace;
}
