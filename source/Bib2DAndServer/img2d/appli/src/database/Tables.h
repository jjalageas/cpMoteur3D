#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <QDateTime>

class Doctor
{
public:
    QString id;
    QString lastname;
    QString firstname;
    int sizeMax;
};

class Patient
{
public:
    QString lastname;
    QString firstname;
    int age;
    QChar sex;
};

class ExamFile
{
public:
    QString name;
    int size;
    QDateTime date;
    Patient patient;
};

#endif // CLIENT_H
