#!/bin/sh
rm *.htm
url=$(awk -F = '{print $2}' url.txt)
for i in $(cat file.txt);
do
  wget ${url}${i}
  iconv -sc -f big5 -t utf-8 ${i} -o ./utf8/${i}
done
