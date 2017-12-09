#!/bin/sh

PONG_ID=$(curl http://127.0.0.1:7898/)

while (ps -ef | grep ${PONG_ID}  | grep circpong); do
    # I am good
    sleep 1
done

echo "Gone"
