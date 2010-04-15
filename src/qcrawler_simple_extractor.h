#ifndef QCRAWLER_SIMPLE_EXTRACTOR_H
#define QCRAWLER_SIMPLE_EXTRACTOR_H

#include "qcrawler_common.h"
#include "qcrawler_util.h"

#include "qcrawler_processor.h"


class QCrawlerSimpleExtractor  : public QCrawlerProcessor
{
    Q_OBJECT

public:
    QCrawlerSimpleExtractor(QCrawlerDB * db, QCrawlerUrlQueue *queue) :QCrawlerProcessor(db, queue) {
        logger = get_qcrawler_logger("simple_extractor");

    }

    virtual ~QCrawlerSimpleExtractor() {
    }


    public std::string extractMainContent(const std::string& raw_content);

public slots:
    virtual void process(bool r, QCrawlerRecord &rec);

private:
    QCrawlerLogger logger;
};
