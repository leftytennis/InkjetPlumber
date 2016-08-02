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

#include <QDateTime>
#include <QDebug>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"

PreferencesDialog::PreferencesDialog(QWidget* parent)
    : QDialog(parent)
    , current_job_(nullptr)
    , ui(new Ui::PreferencesDialog)
{
    ui->setupUi(this);

    connect(ui->listWidget_Settings, &QListWidget::currentRowChanged, this, &PreferencesDialog::setup_printer_settings);
    connect(ui->checkBox_run_maintenance, &QCheckBox::stateChanged, this, &PreferencesDialog::printer_state_changed);
    connect(ui->buttonBox, &QDialogButtonBox::clicked, this, &PreferencesDialog::dialog_button_clicked);
    connect(ui->checkBox_run_maintenance, &QCheckBox::toggled, this, &PreferencesDialog::maint_job_toggled);
    connect(ui->radiobutton_use_cups_output, &QRadioButton::clicked, this, &PreferencesDialog::output_type_clicked);
    connect(ui->radiobutton_use_ijp_output, &QRadioButton::clicked, this, &PreferencesDialog::output_type_clicked);

    QSettings s;
    s.beginGroup("general");
    bool auto_launch = s.value("autolaunch", true).toBool();
    bool auto_update = s.value("autoupdate", true).toBool();
    bool development_updates = s.value("development", false).toBool();
    bool page_paper_info = s.value("pagepaperinfo", true).toBool();
    bool printer_info = s.value("printerinfo", true).toBool();
    s.endGroup();

    ui->checkbox_auto_launch->setChecked(auto_launch);
    ui->checkbox_auto_update->setChecked(auto_update);
    ui->checkbox_development->setChecked(development_updates);
    ui->checkbox_page_paper_info->setChecked(page_paper_info);
    ui->checkbox_printer_info->setChecked(printer_info);

    ui->listWidget_Colors->setViewMode(QListView::IconMode);
    ui->listWidget_Colors->setIconSize(QSize(32, 32));

    ui->listWidget_Colors->setFont(QFont("Courier New", 10));

    // add colors to the color listWidget
    ui->listWidget_Colors->addItem(create_color_item(Qt::cyan));
    ui->listWidget_Colors->addItem(create_color_item(Qt::yellow));
    ui->listWidget_Colors->addItem(create_color_item(Qt::magenta));
    ui->listWidget_Colors->addItem(create_color_item(Qt::black));
    ui->listWidget_Colors->addItem(create_color_item(Qt::gray));
    ui->listWidget_Colors->addItem(create_color_item(Qt::lightGray));
    ui->listWidget_Colors->addItem(create_color_item(Qt::red));
    ui->listWidget_Colors->addItem(create_color_item(Qt::green));
    ui->listWidget_Colors->addItem(create_color_item(Qt::blue));

    ui->tabWidget->setCurrentIndex(0);

    // select first printer in list
    ui->listWidget_Settings->setCurrentRow(0);

    return;
}

PreferencesDialog::~PreferencesDialog()
{
    if (ui)
    {
        delete ui;
        ui = nullptr;
    }

    return;
}

QListWidgetItem* PreferencesDialog::create_color_item(const QColor color) const
{
    QString color_name = color.name();
    QPixmap pixmap(150, 150);
    pixmap.fill(color);
    QIcon icon(pixmap);

    QListWidgetItem* item = new QListWidgetItem(icon, color_name);
    item->setFlags(item->flags() | Qt::ItemIsUserCheckable);

    return item;
}

void PreferencesDialog::dialog_button_clicked(QAbstractButton* button)
{
    if (button)
    {
        QDialogButtonBox::StandardButton standard_button = ui->buttonBox->standardButton(button);
        switch (standard_button)
        {
            case QDialogButtonBox::Ok:
                // update preferences and write settings
                accept();
                break;
            case QDialogButtonBox::Cancel:
                reject();
                break;
            case QDialogButtonBox::Apply:
                // update preferences only
                break;
            case QDialogButtonBox::RestoreDefaults:
                // restore defaults (from job or settings?)
                break;
            default:
                qDebug("Unknown standard button type: %d", standard_button);
                break;
        }
    }

    return;
}

void PreferencesDialog::done(int result)
{
    bool is_error = false;
    QRegularExpression numeric("^[1-9](?:[0-9]{0,1})$");

    if (result == QDialog::Accepted)
    {
        QString hours = ui->lineEdit_hours->text();
        QRegularExpressionMatch m = numeric.match(hours);
        if (m.hasMatch())
        {
            ui->lineEdit_hours->setStyleSheet("");
        }
        else
        {
            ui->lineEdit_hours->setStyleSheet("background-color: #ffcccc");
            ui->lineEdit_hours->setFocus();
            is_error = true;
        }
        if (!is_error && current_job_)
        {
            current_job_->enabled = ui->checkBox_run_maintenance->isChecked();
            current_job_->hours = ui->lineEdit_hours->text().toInt();
            current_job_->cyan = ui->listWidget_Colors->item(0)->checkState() == Qt::Checked ? true : false;
            current_job_->yellow = ui->listWidget_Colors->item(1)->checkState() == Qt::Checked ? true : false;
            current_job_->magenta = ui->listWidget_Colors->item(2)->checkState() == Qt::Checked ? true : false;
            current_job_->black = ui->listWidget_Colors->item(3)->checkState() == Qt::Checked ? true : false;
            current_job_->gray = ui->listWidget_Colors->item(4)->checkState() == Qt::Checked ? true : false;
            current_job_->light_gray = ui->listWidget_Colors->item(5)->checkState() == Qt::Checked ? true : false;
            current_job_->red = ui->listWidget_Colors->item(6)->checkState() == Qt::Checked ? true : false;
            current_job_->green = ui->listWidget_Colors->item(7)->checkState() == Qt::Checked ? true : false;
            current_job_->blue = ui->listWidget_Colors->item(8)->checkState() == Qt::Checked ? true : false;
            IJPOutputType output_type = IJPOutputType::OutputTypeCUPS;
            if (ui->radiobutton_use_cups_output->isChecked())
                output_type = IJPOutputType::OutputTypeCUPS;
            else if (ui->radiobutton_use_ijp_output->isChecked())
                output_type = IJPOutputType::OutputTypeGenerated;
            current_job_->output_type = output_type;
            emit update_maint_job(current_job_, true);
        }
    }

    if (is_error) return;

    // all field validation passed, save settings

    QSettings s;
    s.beginGroup("general");
    s.setValue("autolaunch", ui->checkbox_auto_launch->isChecked());
    s.setValue("autoupdate", ui->checkbox_auto_update->isChecked());
    s.setValue("development", ui->checkbox_development->isChecked());
    s.setValue("pagepaperinfo", ui->checkbox_page_paper_info->isChecked());
    s.setValue("printerinfo", ui->checkbox_printer_info->isChecked());
    s.endGroup();
    s.sync();

    // let everyone know the settings have been updated
    emit settings_updated();

    QDialog::done(result);

    return;
}

void PreferencesDialog::maint_job_toggled(bool checked)
{
    ui->groupbox_output->setEnabled(checked);

    if (checked && ui->radiobutton_use_ijp_output->isChecked())
        ui->groupbox_custom_output_options->setEnabled(true);
    else
        ui->groupbox_custom_output_options->setEnabled(false);

    return;
}

void PreferencesDialog::output_type_clicked(bool checked)
{
    Q_UNUSED(checked);

    if (ui->radiobutton_use_cups_output->isChecked())
        ui->groupbox_custom_output_options->setEnabled(false);
    else if (ui->radiobutton_use_ijp_output->isChecked())
        ui->groupbox_custom_output_options->setEnabled(true);

    return;
}

MaintenanceJob* PreferencesDialog::find_maint_job(const QString& printer_name) const
{
    MaintenanceJob* job = nullptr;

    if (maint_job_map_.contains(printer_name))
        job = maint_job_map_.value(printer_name);

    return job;
}

void PreferencesDialog::printer_state_changed(int state)
{
    Q_UNUSED(state);
    bool checked = ui->checkBox_run_maintenance->isChecked();
    ui->lineEdit_hours->setEnabled(checked);
    return;
}

void PreferencesDialog::set_maintenance_map(MaintenanceJobMap& map)
{
    maint_job_map_ = map;

    ui->listWidget_Settings->clear();

    MaintenanceJobMapIterator it(maint_job_map_);

    while (it.hasNext())
    {
        it.next();
        MaintenanceJob* job = it.value();
        ui->listWidget_Settings->addItem(job->printer_name);
    }

    // select first printer in list
    ui->listWidget_Settings->setCurrentRow(0);

    return;
}

void PreferencesDialog::setup_printer_settings(int current_row)
{
    Q_UNUSED(current_row);

    QListWidgetItem* item = ui->listWidget_Settings->currentItem();

    if (item)
    {
        QString printer_name = item->text();
        MaintenanceJob* job = find_maint_job(printer_name);
        // save current job being shown in the dialog
        current_job_ = job;
        if (current_job_)
        {
            ui->checkBox_run_maintenance->setChecked(job->enabled);
            ui->lineEdit_hours->setEnabled(job->enabled);
            ui->lineEdit_hours->setText(QString::number(job->hours));
            QDateTime epoch(QDate(2016,7,1));
            if (current_job_->last_maint.isValid() && current_job_->last_maint > epoch)
                ui->label_last_maint->setText(current_job_->last_maint.toString("yyyy-MM-dd hh:mm:ss"));
            else
                ui->label_last_maint->setText("never");
            switch (current_job_->output_type)
            {
                case IJPOutputType::OutputTypeCUPS:
                    ui->radiobutton_use_cups_output->setChecked(true);
                    break;
                case IJPOutputType::OutputTypeGenerated:
                    ui->radiobutton_use_ijp_output->setChecked(true);
            }
            if (ui->listWidget_Colors->count() == 9)
            {
                ui->listWidget_Colors->item(0)->setCheckState(job->cyan ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(1)->setCheckState(job->yellow ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(2)->setCheckState(job->magenta ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(3)->setCheckState(job->black ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(4)->setCheckState(job->gray ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(5)->setCheckState(job->light_gray ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(6)->setCheckState(job->red ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(7)->setCheckState(job->green ? Qt::Checked : Qt::Unchecked);
                ui->listWidget_Colors->item(8)->setCheckState(job->blue ? Qt::Checked : Qt::Unchecked);
            }
            // enable group boxes according to whether or not maint job is enabled
            ui->groupbox_custom_output_options->setEnabled(current_job_->enabled);
            ui->groupbox_output->setEnabled(current_job_->enabled);
        }
        else
        {
            qDebug("No maintenance job found for printer %s", qUtf8Printable(printer_name));
        }
    }
    else
    {
        current_job_ = nullptr;
    }

    return;
}
