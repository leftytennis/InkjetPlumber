//
//    Copyright (c) 2016 Jeff Thompson <jefft@threeputt.org>
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

#include <QApplication>

#include "version.h"
#include "mainwindow.h"

#include "cocoainitializer.h"
#include "autoupdater.h"
#include "sparkleautoupdater.h"


int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("Inkjet Plumber");
    a.setApplicationVersion(INKJETPLUMBER_VERSION);
    a.setOrganizationDomain("threeputt.org");
    a.setOrganizationName("Jeff Thompson");

    SparkleAutoUpdater* updater = nullptr;

    CocoaInitializer initializer;
    updater = new SparkleAutoUpdater();

    MainWindow w(updater);
    w.show();

    return a.exec();
}
