//
//    Copyright (c) 2019 Jeff Thompson <jefft@threeputt.org>
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

#include <QDateTime>

#include "maintenancejob.h"

MaintenanceJob::MaintenanceJob(QObject *parent)
    : QObject(parent)
    , enabled(false)
    , hours(55)
    , cyan(true)
    , yellow(true)
    , magenta(true)
    , black(true)
    , gray(true)
    , light_gray(true)
    , red(true)
    , green(true)
    , blue(true)
    , last_maint(QDateTime())
    , output_type(IJPOutputType::OutputTypeCUPS)
{
    return;
}

MaintenanceJob::MaintenanceJob(const QString &name, QObject *parent)
    : QObject(parent)
    , printer_name(name)
    , enabled(false)
    , hours(55)
    , cyan(true)
    , yellow(true)
    , magenta(true)
    , black(true)
    , gray(true)
    , light_gray(true)
    , red(true)
    , green(true)
    , blue(true)
    , last_maint(QDateTime())
    , output_type(IJPOutputType::OutputTypeCUPS)
{
    return;
}

MaintenanceJob::MaintenanceJob(const MaintenanceJob &rhs)
    : QObject(rhs.parent())
    , printer_name(rhs.printer_name)
    , enabled(rhs.enabled)
    , hours(rhs.hours)
    , cyan(rhs.cyan)
    , yellow(rhs.yellow)
    , magenta(rhs.magenta)
    , black(rhs.black)
    , gray(rhs.gray)
    , light_gray(rhs.light_gray)
    , red(rhs.red)
    , green(rhs.green)
    , blue(rhs.blue)
    , last_maint(rhs.last_maint)
    , output_type(rhs.output_type)
{
    return;
}

MaintenanceJob::~MaintenanceJob()
{
    return;
}

MaintenanceJob &MaintenanceJob::operator=(const MaintenanceJob &rhs)
{
    printer_name = rhs.printer_name;
    enabled = rhs.enabled;
    hours = rhs.hours;
    cyan = rhs.cyan;
    yellow = rhs.yellow;
    magenta = rhs.magenta;
    black = rhs.black;
    gray = rhs.gray;
    light_gray = rhs.gray;
    red = rhs.red;
    green = rhs.green;
    blue = rhs.blue;
    last_maint = rhs.last_maint;
    output_type = rhs.output_type;
    return *this;
}
