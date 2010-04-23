#include "qcrawler_simple_extractor.h"

#include <QStringList>

QString QCrawlerSimpleExtractor::extractTitle(const QString &raw_title)
{
    QStringList tl = raw_title.split(QRegExp("[_-——|]"));
    if (tl.size() > 1) {
        int max_len = -1;
        int max_idx = -1;
        for ( int i = 0; i < tl.size(); i++) {
            if (tl.at(i).size() > max_len && !tl.at(i).endsWith("网")) {
                max_len = tl.at(i).size();
                max_idx = i;
            }
        }
        if (max_idx > -1) {
            return tl.at(max_idx);
        }
    } else if (tl.size() == 1) {
        if (tl.at(0).size() > 6) {
            return tl.at(0);
        }
    }

    return raw_title;
}

QString QCrawlerSimpleExtractor::extractMainContent(const QString &raw_content) {
    // blocks
    // best blocks
    // combine
    QString main_content;
    QRegExp reg("(?:、|，|。|？|,|。)");
    QStringList list = raw_content.split("\n");

    int bestIdx = -1;
    int best_size = 20;

    for (int i = 0; i < list.size(); i++) {
        if (QString(list.at(i).toUtf8()).contains(reg) && list.at(i).size() > best_size) {
            bestIdx = i;
            best_size = list.at(i).size();
        }
    }

    if (bestIdx == -1) {
        main_content = "";
    } else {
        int base_size = 0.33 * best_size > 15 ? 15 : 0.33 * best_size;
        int max_intervals = 6;
        int min_idx = bestIdx;
        for (int i = bestIdx - 1;  i >= 0; i--) {
            if (QString(list.at(i).toUtf8()).contains(reg) && list.at(i).size() > base_size) {
                min_idx = i;
            };
            if (i < min_idx - max_intervals) {
                break;
            }
        }

        int max_idx = bestIdx;
        for (int i = bestIdx + 1; i < list.size(); i++) {
            if (QString(list.at(i).toUtf8()).contains(reg) && list.at(i).size() > base_size) {
                max_idx = i;
            };
            if (i > max_idx + max_intervals) {
                break;
            }
        }

        max_idx = max_idx + 1;

        for (int i = min_idx; i < max_idx; i++) {
            main_content.append(list.at(i) + "\n");
        }
    }

    return main_content;
}


int QCrawlerSimpleExtractor::process(QCrawlerRecord &rec)
{
    rec.set_title(extractTitle(rec.raw_title()));
    rec.set_content(extractMainContent(rec.raw_content()));
    return 0;
}




