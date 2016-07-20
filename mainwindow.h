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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QDateTime>
#include <QMap>
#include <QMapIterator>
#include <QMenu>
#include <QPageLayout>
#include <QPainter>
#include <QPrintDialog>
#include <QPrintEngine>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintPreviewDialog>
#include <QPrintPreviewWidget>
#include <QSet>
#include <QSetIterator>
#include <QSettings>
#include <QStringList>
#include <QStringListModel>
#include <QSystemTrayIcon>
#include <QTimer>

#include "aboutdialog.h"
#include "preferencesdialog.h"
#include "sparkleautoupdater.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(SparkleAutoUpdater* updater = 0, QWidget* parent = 0);
    ~MainWindow();

    void closeEvent(QCloseEvent* event);

signals:

    void update_maint_job(MaintenanceJob* job);

private slots:

    void check_for_update();
    void paint_page(MaintenanceJob* job, QPrinter* printer);
    void maint_job_updated(MaintenanceJob* job);
    void show_about_dialog();
    void show_preferences_dialog();
    void timer_expired();

private:

    MaintenanceJob* find_maint_job(const QString& printer_name) const;
    QString get_duplex_string(QPrinter::DuplexMode mode) const;
    QString get_pagesize_string(const QPageSize& page_size) const;
    QString get_state_string(QPrinter::PrinterState state) const;
    QString get_unit_string(QPageSize::Unit unit) const;
    void log_message(const QString& msg) const;
    void print_swatch(QPainter& painter, int* x, int y, QColor color) const;
    void read_printer_settings(const QString& printer_name);
    void run_maint_job(MaintenanceJob* job);
    void setup_sparkle();
    void show_printer_info(const QString& printer_name) const;
    void write_printer_settings(const QString& printer_name);
    void write_printer_settings(MaintenanceJob* job);

    AboutDialog* about_dlg_;
    QMenu* app_menu_;
    MaintenanceJobMap maint_job_map_;
    QStringList messages_;
    QStringListModel* model_;
    PreferencesDialog* preferences_dlg_;
    QPrinter printer_;
    QSystemTrayIcon tray_;
    QTimer* timer_;
    Ui::MainWindow* ui;
    SparkleAutoUpdater* updater_;
};

#endif // MAINWINDOW_H
