/*
 * Copyright (C) 2008 Remko Troncon
 */

#include <QApplication>
#include <QDateTime>

#include <AppKit/AppKit.h>
#include <Cocoa/Cocoa.h>

#include "sparkleautoUpdater.h"
#include <Sparkle/Sparkle.h>

@class NSMenuItem;

class SparkleAutoUpdater::Private
{
    public:
        SUUpdater* updater;
};

SparkleAutoUpdater::SparkleAutoUpdater()
{
    d = new Private;

    d->updater = [SUUpdater sharedUpdater];
    [d->updater retain];

    return;
}

SparkleAutoUpdater::~SparkleAutoUpdater()
{
    [d->updater release];
    delete d;
    return;
}

bool SparkleAutoUpdater::automaticallyChecksForUpdates()
{
    BOOL b = NO;

    if (d->updater)
        b = [d->updater automaticallyChecksForUpdates];

    return b;
}

bool SparkleAutoUpdater::automaticallyDownloadsUpdates()
{
    BOOL b = NO;

    if (d->updater)
        b = [d->updater automaticallyDownloadsUpdates];

    return b;
}

void SparkleAutoUpdater::checkForUpdateInformation()
{
    if (d->updater)
        [d->updater checkForUpdateInformation];

    return;
}

void SparkleAutoUpdater::checkForUpdates()
{
    if (d->updater)
        [d->updater checkForUpdates:nullptr];

    return;
}

void SparkleAutoUpdater::checkForUpdatesInBackground()
{
    if (d->updater)
        [d->updater checkForUpdatesInBackground];

    return;
}

QUrl SparkleAutoUpdater::feedURL()
{
    QUrl url;
    NSURL* feedURL = nullptr;
    NSString* string = nullptr;

    if (d->updater)
    {
        feedURL = [d->updater feedURL];
        string = [feedURL absoluteString];
        QString urlstr = QString::fromUtf8([string cStringUsingEncoding: NSUTF8StringEncoding]);
        url = urlstr;
    }

    return url;
}

QDateTime SparkleAutoUpdater::lastUpdateCheckDate()
{
    NSTimeInterval ti = 0;

    NSDate* aNSDate;

    aNSDate = [d->updater lastUpdateCheckDate];

    if (aNSDate)
    {
        ti = [aNSDate timeIntervalSince1970];
    }

    return QDateTime::fromTime_t(ti);
}

void SparkleAutoUpdater::resetUpdateCycle()
{
    if (d->updater)
    {
        [d->updater resetUpdateCycle];
    }

    return;
}

void SparkleAutoUpdater::setAutomaticallyChecksForUpdates(bool autoChecks)
{
    if (d->updater)
    {
        d->updater.automaticallyChecksForUpdates = autoChecks;
    }

    return;
}

void SparkleAutoUpdater::setAutomaticallyDownloadsUpdates(bool autoDownloads)
{
    if (d->updater)
    {
        d->updater.automaticallyDownloadsUpdates = autoDownloads;
    }

    return;
}

void SparkleAutoUpdater::setEnableUpdateMenu(bool enable)
{
    Q_UNUSED(enable);
    NSMenu* menu = nullptr;
    menu = [NSApp mainMenu];
    return;
}

void SparkleAutoUpdater::setFeedURL(QUrl &url)
{
    QString urlstr = url.toString();
    NSURL* feedURL = nullptr;
    NSString* string = nullptr;

    if (d->updater)
    {
        string = [[NSString alloc] initWithBytes:urlstr.toUtf8().constData() length: urlstr.length() encoding: NSUTF8StringEncoding];
        feedURL = [[NSURL alloc] initWithString: string];
        [d->updater setFeedURL: feedURL];
        [feedURL release];
        [string release];
    }

    return;
}

void SparkleAutoUpdater::setUpdateCheckInterval(long seconds)
{
    if (d->updater)
    {
        NSTimeInterval ti = seconds;
        [d->updater setUpdateCheckInterval:ti];
    }

    return;
}

long SparkleAutoUpdater::updateCheckInterval()
{
    NSTimeInterval ti = 0;

    if (d->updater)
    {
        ti = [d->updater updateCheckInterval];
    }

    return (long)ti;
}

bool SparkleAutoUpdater::updateInProgress()
{
    BOOL b = NO;

    if (d->updater)
    {
        b = [d->updater updateInProgress];
    }

    return b;
}
