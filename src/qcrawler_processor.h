#include <QObject>
#include <QDebug>

class QCrawlerProcessor : public QObject
{
    Q_OBJECT

public:
    QCrawlerProcessor() {
        // TODO config
    }

public slots:
    void process(bool r);

signals:
    void processFinished(bool);
};
