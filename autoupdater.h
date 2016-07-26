/*
 * Copyright (C) 2008 Remko Troncon
 */

#ifndef AUTOUPDATER_H
#define AUTOUPDATER_H

#include <QObject>

class QDateTime;
class QUrl;
class QMenu;
class QMenuBar;

class AutoUpdater
{

public:

    virtual ~AutoUpdater();

    virtual bool        automaticallyChecksForUpdates() = 0;
    virtual bool        automaticallyDownloadsUpdates() = 0;
    virtual void        checkForUpdateInformation() = 0;
    virtual void        checkForUpdates() = 0;
    virtual void        checkForUpdatesInBackground() = 0;
    virtual QUrl        feedURL() = 0;
    virtual QDateTime   lastUpdateCheckDate() = 0;
    virtual void        resetUpdateCycle() = 0;
    virtual void        setAutomaticallyChecksForUpdates(bool autoChecks) = 0;
    virtual void        setAutomaticallyDownloadsUpdates(bool autoDownloads) = 0;
    virtual void        setEnableUpdateMenu(bool enable) = 0;
    virtual void        setFeedURL(QUrl& url) = 0;
    virtual void        setUpdateCheckInterval(long seconds) = 0;
    virtual long        updateCheckInterval() = 0;
    virtual bool        updateInProgress() = 0;
};

#endif
