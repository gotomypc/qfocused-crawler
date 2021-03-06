#ifndef QCRALER_KIT_PARSER_H
#define QCRALER_KIT_PARSER_H

#include <QObject>
#include <QDebug>

#include "qcrawler_common.h"
#include "qcrawler_util.h"
#include "qcrawler_processor.h"

#include "qcrawler_webpage.h"
#include <qwebsettings.h>

class QCrawlerKitParser  : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerKitParser(QCrawlerDB *db, QCrawlerUrlQueue *queue): QCrawlerProcessor(db, queue) {
        QCrawlerConfig *config = QCrawlerConfig::getInstance();
        // TODO config
        page = new QCrawlerPage();

        // pre fetch dns entries to speed up
        QWebSettings::globalSettings()->setAttribute(QWebSettings::DnsPrefetchEnabled, true);

        page->settings()->setAttribute(QWebSettings::JavascriptEnabled, config->enable_js());
        page->settings()->setAttribute(QWebSettings::AutoLoadImages, config->auto_load_image());
        page->settings()->setAttribute(QWebSettings::JavaEnabled, false);
        //default charset
        QWebSettings::globalSettings()->setDefaultTextEncoding("GB18030-0");
        page->settings()->setDefaultTextEncoding("GB18030-0");
        page->settings()->setAttribute(QWebSettings::JavaEnabled, false);
        page->settings()->setAttribute(QWebSettings::PluginsEnabled, false);

        page->settings()->setAttribute(QWebSettings::JavascriptCanOpenWindows, false);
        page->settings()->setAttribute(QWebSettings::DeveloperExtrasEnabled, false);
        page->settings()->setAttribute(QWebSettings::PrintElementBackgrounds, false);

        page->setUserAgent(config->user_agent());
    }

    ~QCrawlerKitParser() {
        delete page;
    }

public slots:
    virtual int process(QCrawlerRecord &rec);

private:
    QCrawlerPage* page;
};

#endif
