#!/bin/sh
rsync --exclude 'node_modules/*' -avz -e 'ssh -p 4123' . root@195.83.139.38:/root/iot-comm/greenfeed_rest
