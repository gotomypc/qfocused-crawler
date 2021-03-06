#include "qcrawler.h"

#include <QDateTime>

void QCrawler::start() {
    int proc_size = processors.size();
    while (true) {
        QCrawlerRecord rec;

        for (int i = 0; i < proc_size; i++) {
            int ret = processors[i]->process(rec);

            fprintf(stdout, "%s %10s %2d %s\n", QDateTime::currentDateTime().toString("yyyy-dd-mm hh:mm:ss").toUtf8().constData(), processors[i]->objectName().toUtf8().constData(), ret, rec.crawl_url().url().toUtf8().constData());
            if (ret > 0) {
            // log
                break;
            } else if (ret < 0) {
                // log
                exit(1);
            }
        }
    }
}

QCrawler::QCrawler(QCrawlerUrlQueue *uq) {
    db = new QCrawlerDB();
    url_queue = uq;

    freq_control = new QCrawlerFreqControl();

    get_task = new QCrawlerGetTask(db, url_queue, freq_control);
    get_task->setObjectName("task");
    processors.append(get_task);

    parser = new QCrawlerKitParser(db, url_queue);
    parser->setObjectName("parser");
    processors.append(parser);


    focus_filter = new QCrawlerFocusFilter(db, url_queue);
    focus_filter->setObjectName("filter");
    processors.append(focus_filter);

    simple_extractor = new QCrawlerSimpleExtractor(db, url_queue);
    simple_extractor->setObjectName("extractor");
    processors.append(simple_extractor);

    storage_record = new QCrawlerStorageRecord(db, url_queue);
    storage_record->setObjectName("storage");
    processors.append(storage_record);
}

QCrawler::~QCrawler()
{
    int proc_size = processors.size();
    for (int i = 0; i < proc_size; i++) {
        delete processors[i];
    }
}
