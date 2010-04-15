#include "qcrawler_util.h"

#include <sys/time.h>

void debug_record(const QCrawlerRecord &rec)
{
    std::string str;

    google::protobuf::TextFormat::Printer printer;
    printer.SetUseUtf8StringEscaping(true);
    printer.PrintToString(rec, &str);
    fprintf(stderr, "%s", str.c_str());
}

int get_current_time()
{
    struct timeval timer;
    gettimeofday(&timer, NULL);
    return timer.tv_sec;
}



