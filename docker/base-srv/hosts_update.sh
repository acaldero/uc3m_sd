#!/bin/bash
#set -x


if [ ! -f /etc/hosts.base ]; then
     cp /etc/hosts /etc/hosts.base
fi

cat /etc/hosts.base /shared/etc_hosts > /etc/hosts

