#!/bin/bash

#TAG=DEC17
#TAG=OCT18
TAG=OCT19

docker build -t pklaus/cbmroot_materialsim:latest src
docker tag pklaus/cbmroot_materialsim:{latest,$TAG}
