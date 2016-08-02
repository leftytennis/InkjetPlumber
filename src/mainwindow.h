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

#include <QAbstractTextDocumentLayout>
#include <QAction>
#include <QMainWindow>
#include <QDateTime>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QKeySequence>
#include <QMap>
#include <QMapIterator>
#include <QMenu>
#include <QMessageBox>
#include <QPageLayout>
#include <QPageSetupDialog>
#include <QPainter>
#include <QPrintDialog>
#include <QPrintEngine>
#include <QPrintPreviewDialog>
#include <QPrinter>
#include <QPrinterInfo>
#include <QPrintPreviewDialog>
#include <QPrintPreviewWidget>
#include <QProcess>
#include <QProcessEnvironment>
#include <QSet>
#include <QSetIterator>
#include <QSettings>
#include <QStringList>
#include <QStringListModel>
#include <QSystemTrayIcon>
#include <QTemporaryFile>
#include <QTextDocument>
#include <QTimer>

#include "aboutdialog.h"
#include "preferencesdialog.h"
#include "version.h"

#if defined(Q_OS_OSX)
#include "sparkleautoupdater.h"
#endif

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
#if defined(Q_OS_OSX)
    explicit MainWindow(SparkleAutoUpdater* updater = 0, QWidget* parent = 0);
#else
    explicit MainWindow(QWidget* parent = 0);
#endif
    ~MainWindow();

    virtual void closeEvent(QCloseEvent* event);

signals:

    void update_maint_job(MaintenanceJob* job, bool save = true);

private slots:

    void about_to_show_tray_menu();
#if defined(Q_OS_OSX)
    void check_for_update();
#endif
    void maint_job_updated(MaintenanceJob* job, bool save = true);
    void show_about_dialog();
    void show_main_window();
    void show_preferences_dialog();
    void timer_expired();

private:

    MaintenanceJob* find_maint_job(const QString& printer_name) const;
    QString get_color_mode_string(QPrinter::ColorMode color_mode) const;
    QString get_duplex_string(QPrinter::DuplexMode mode) const;
    QString get_pagesize_string(const QPageSize& page_size) const;
    QString get_state_string(QPrinter::PrinterState state) const;
    QString get_unit_string(QPageSize::Unit unit) const;
    void log_message(const QString& msg) const;
    void generate_custom_page(MaintenanceJob* job, QPrinter* printer);
    void paint_swatch(QPrinter* printer, QPainter& painter, int* x, int y, QColor color) const;
    void print_generated_test_page(MaintenanceJob* job);
    void print_self_test_page(MaintenanceJob* job);
    void read_settings();
    void read_printer_settings(const QString& printer_name);
    void run_maint_job(MaintenanceJob* job);
#if defined(Q_OS_OSX)
    void setup_sparkle();
#endif
    void show_printer_info(const QString& printer_name) const;
    void write_printer_settings(const QString& printer_name);
    void write_printer_settings(MaintenanceJob* job);

    AboutDialog* about_dlg_;
    QMenu* app_menu_;
    bool auto_launch_;
    bool auto_update_;
    bool development_updates_;
    MaintenanceJobMap maint_job_map_;
    QStringList messages_;
    bool page_paper_info_;
    PreferencesDialog* preferences_dlg_;
    bool printer_info_;
    QTimer* timer_;
    QSystemTrayIcon tray_;
    QMenu* tray_menu_;
    bool tray_warning_;
    Ui::MainWindow* ui;
#if defined(Q_OS_OSX)
    SparkleAutoUpdater* updater_;
#endif
};

#endif // MAINWINDOW_H
