//
//    Copyright (c) 2022 Jeff Thompson <jefft@threeputt.org>
//
//    This file is part of Inkjet Plumber.
//
//    Inkjet Plumber is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    Inkjet Plumber is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with Inkjet Plumber.  If not, see <http://www.gnu.org/licenses/>.
//

#ifndef MAINTENANCEJOB_H
#define MAINTENANCEJOB_H

#include <QObject>
#include <QDateTime>
#include <QList>
#include <QListIterator>
#include <QMap>
#include <QMapIterator>

typedef enum IJPOutputType
{
    OutputTypeCUPS = 0,
    OutputTypeGenerated = 1
} IJPOutputType;

class MaintenanceJob : public QObject
{
    Q_OBJECT

public:

    explicit MaintenanceJob(QObject *parent = 0);
    MaintenanceJob(const QString &name, QObject *parent = 0);
    MaintenanceJob(const MaintenanceJob &rhs);
    ~MaintenanceJob();
    MaintenanceJob &operator=(const MaintenanceJob &rhs);

signals:

public slots:

public:

    QString         printer_name;
    bool            enabled;
    int             hours;
    bool            cyan;
    bool            yellow;
    bool            magenta;
    bool            black;
    bool            gray;
    bool            light_gray;
    bool            red;
    bool            green;
    bool            blue;
    QDateTime       last_maint;
    IJPOutputType   output_type;
};

Q_DECLARE_METATYPE(MaintenanceJob);
Q_DECLARE_METATYPE(MaintenanceJob *);

typedef QList<MaintenanceJob *> MaintenanceJobList;
typedef QMap<QString, MaintenanceJob *> MaintenanceJobMap;
typedef QMapIterator<QString, MaintenanceJob *> MaintenanceJobMapIterator;

#endif // MAINTENANCEJOB_H
