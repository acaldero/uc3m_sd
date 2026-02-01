#!/bin/bash
set -x

# 1) Check arguments
if [ $# -lt 1 ]; then
	echo "Usage: $0 <full path where software will be downloaded>"
	exit
fi

# 2) Clean-up
DESTINATION_PATH=$1

# 3) Download MPICH
mkdir -p ${DESTINATION_PATH}
cd       ${DESTINATION_PATH}
if [ ! -f zxf mpich-4.3.1.tar.gz ]; then
    wget https://www.mpich.org/static/downloads/4.3.1/mpich-4.3.1.tar.gz
fi

tar zxf mpich-4.3.1.tar.gz
rm -fr  mpich
mv      mpich-4.3.1  mpich

# 4) Install MPICH (from source code)
mkdir -p /home/lab/bin

cd ${DESTINATION_PATH}/mpich
./configure --prefix=/home/lab/bin/mpich \
            --with-device=ch3:sock \
            --enable-threads=multiple \
            --enable-romio \
            --disable-fortran

make -j $(nproc) all
make install
sudo ldconfig

cd ${DESTINATION_PATH}/mpich/examples
make -j $(nproc) all

# 5) PATH
echo "# MPICH"                                                          >> /home/lab/.profile
echo "export PATH=/home/lab/bin/mpich/bin:\$PATH"                       >> /home/lab/.profile
echo "export LD_LIBRARY_PATH=/home/lab/bin/mpich/lib:\$LD_LIBRARY_PATH" >> /home/lab/.profile

