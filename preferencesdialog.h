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

#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QAbstractButton>
#include <QButtonGroup>
#include <QDialog>
#include <QList>
#include <QListWidgetItem>
#include <QPrinterInfo>
#include <QSettings>
#include <QStackedWidget>
#include <QStringList>

#include "maintenancejob.h"

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PreferencesDialog(QWidget* parent = 0);
    ~PreferencesDialog();

    void set_maintenance_map(MaintenanceJobMap& map);

signals:

    void settings_updated();
    void update_maint_job(MaintenanceJob* job);

private slots:

    void dialog_button_clicked(QAbstractButton* button);
    void done(int result);
    void printer_state_changed(int state);
    void setup_printer_settings(int current_row);

private:

    QListWidgetItem* create_color_item(const QColor color) const;
    MaintenanceJob* find_maint_job(const QString& printer_name) const;

    MaintenanceJob* current_job_;
    MaintenanceJobMap maint_job_map_;
    Ui::PreferencesDialog* ui;
};

#endif // PREFERENCESDIALOG_H
