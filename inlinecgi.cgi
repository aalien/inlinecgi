#!/bin/sh

echo "Content-type: text/html\n"

./inlinecgi $QUERY_STRING

