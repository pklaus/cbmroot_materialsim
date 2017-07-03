#!/bin/bash

CBMSRCDIR=/local/cbmroot_JUN17_trunk/cbmroot_svn

cp $CBMSRCDIR/mvd/CbmMvdRadLength.{cxx,h} ./
cp $CBMSRCDIR/macro/mvd/material{analysis.C,simulation.c} ./
cp $CBMSRCDIR/macro/run/modules/registerSetup.C ./
cp $CBMSRCDIR/geometry/mvd/mvd_v17y.geo.root ./
cp $CBMSRCDIR/geometry/mvd/mvd_v17y.geo.root ./
cp $CBMSRCDIR/geometry/setup/setup_mvd_only.C ./
