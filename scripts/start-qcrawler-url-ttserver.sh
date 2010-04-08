#!/usr/bin/env bash

export TZ=Asia/Shanghai
export LC_ALL='en_US.UTF8'

export LD_LIBRARY_PATH=/opt/qcrawler-thirdparty/lib:$LD_LIBRARY_PATH
export PATH=/opt/qcrawler-thirdparty/bin:$PATH

BIN=$(readlink -f -- $(dirname -- "$0"))
cd $BIN/..

LOGFILE=log/qcrawler-url-ttserver.log
DATAFILE=data/qcrawler-url.tch

test -d log || mkdir -p log
test -d data || mkdir -p data

#xmsiz=536870912 512M at least
exec ttserver -port 1979 -thnum 10 -log "$LOGFILE" -dmn -le "${DATAFILE}#bnum=10000000#opts=lb#rcnum=5000"
#ttserver -port 1979 -thnum 10 -le "${DATAFILE}#bnum=1000000#opts=lb#rcnum=5000"
