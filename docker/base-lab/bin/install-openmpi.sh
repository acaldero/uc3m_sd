#!/bin/bash
set -x

sudo apt-get update
sudo apt-get install -y libopenmpi-dev openmpi-bin openmpi-common openmpi-doc
sudo apt-get clean

