/*
 * Copyright (C) 2008 Remko Troncon
 */

#ifndef SPARKLEAUTOUPDATER_H
#define SPARKLEAUTOUPDATER_H

#include <QString>
#include <QUrl>
#include <QMenu>
#include <QMenuBar>

#include "autoupdater.h"

class QDateTime;

class SparkleAutoUpdater : public AutoUpdater
{

public:

        SparkleAutoUpdater();
        ~SparkleAutoUpdater();

        bool        automaticallyChecksForUpdates();
        bool        automaticallyDownloadsUpdates();
        void        checkForUpdateInformation();
        void        checkForUpdates();
        void        checkForUpdatesInBackground();
        QUrl        feedURL();
        QDateTime   lastUpdateCheckDate();
        void        resetUpdateCycle();
        void        setAutomaticallyChecksForUpdates(bool autoChecks);
        void        setAutomaticallyDownloadsUpdates(bool autoDownloads);
        void        setEnableUpdateMenu(bool enable);
        void        setFeedURL(QUrl& url);
        void        setUpdateCheckInterval(long seconds);
        long        updateCheckInterval();
        bool        updateInProgress();
        bool        validateMenuItem(QMenuBar* item);

private:

        class Private;
        Private* d;
};

#endif
