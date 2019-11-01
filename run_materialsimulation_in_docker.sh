#!/bin/bash

CONTAINER=materialsim
RESULT_IMAGE=materialsim_result

docker run \
  --name $CONTAINER \
  pklaus/cbmroot_materialsim:DEC17 \
  "source ~/.bashrc; cd /cbmroot/macro/mvd; root -b ./materialsimulation.C"

docker commit $CONTAINER $RESULT_IMAGE

docker run \
  --name $CONTAINER \
  $RESULT_IMAGE \
  "source ~/.bashrc; cd /cbmroot/macro/mvd; root -b ./materialanalysis.C"

docker commit $CONTAINER $RESULT_IMAGE

for FILE in Sim_Box_1MEvents_mvd_15a_360phi.{params,mc,radlen}.root
do
  docker cp $CONTAINER:/cbmroot/macro/mvd/$FILE ./output/
done

docker rm $CONTAINER

echo "you can run    docker run --rm -it $RESULT_IMAGE /bin/bash    to analyse the result inside of a container"
