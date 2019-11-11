#FROM pklaus/cbmroot:opensuse-42.3_DEC17
#FROM pklaus/cbmroot:opensuse-15.0_OCT18
FROM pklaus/cbmroot:opensuse-15.1_OCT19


#COPY CbmMvdRadLength.cxx CbmMvdRadLength.h /cbmroot/mvd/
COPY materialsimulation.C /cbmroot/macro/mvd/
#COPY materialanalysis.C /cbmroot/macro/mvd/
#COPY setup_mvd_only.C /cbmroot/geometry/setup/
COPY registerSetup.C /cbmroot/macro/run/modules/

#RUN cd /cbmroot/mvd/ \
# && sed -i 's|#endif|#pragma link C++ class CbmMvdRadLength+;\n\n#endif|' CbmMvdLinkDef.h \
# && sed -i 's|CbmMvd.cxx|CbmMvd.cxx\nCbmMvdRadLength.cxx|' CMakeLists.txt

#RUN cmake \
#    -DCMAKE_CXX_COMPILER=$($SIMPATH/bin/fairsoft-config --cxx) \
#    -DCMAKE_C_COMPILER=$($SIMPATH/bin/fairsoft-config --cc) \
#    ..

#RUN nice make -j4
