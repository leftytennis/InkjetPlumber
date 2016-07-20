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

    ui->listWidget_Colors->setViewMode(QListView::IconMode);
    ui->listWidget_Colors->setIconSize(QSize(32, 32));

//    QStringList printer_names = QPrinterInfo::availablePrinterNames();
//
//    for (int i = 0; i < printer_names.count(); i++)
//    {
//        QString printer_name = printer_names[i];
//        ui->listWidget_Settings->addItem(printer_name);
//        read_printer_settings(printer_name);
//    }

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
    QString button_text;

    if (button)
    {
        QDialogButtonBox::StandardButton standard_button = ui->buttonBox->standardButton(button);
        switch (standard_button)
        {
        case QDialogButtonBox::Ok:
            // update preferences and write settings
            accept();
            //hide();
            break;
        case QDialogButtonBox::Cancel:
            reject();
            //hide();
            break;
        case QDialogButtonBox::Apply:
            // update preferences only
            break;
        case QDialogButtonBox::RestoreDefaults:
            // restore defaults (from job or settings?)
            break;
        default:
            qDebug("Unknown standard button type: %d", standard_button);
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
            emit update_maint_job(current_job_);
        }
    }

    if (!is_error) QDialog::done(result);

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
        if (job)
        {
            ui->checkBox_run_maintenance->setChecked(job->enabled);
            ui->lineEdit_hours->setEnabled(job->enabled);
            ui->lineEdit_hours->setText(QString::number(job->hours));
            if (job->last_maint.isValid())
                ui->label_last_maint->setText(job->last_maint.toString("yyyy-MM-dd hh:mm:ss"));
            else
                ui->label_last_maint->setText("never");
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
