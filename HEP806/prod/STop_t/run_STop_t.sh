#!/bin/bash
if [ $# != 1 ]; then
    echo "JOB SECTION NUMBER IS MISSING!!!"
    exit 1
fi
SECTION=`printf %03d $1`

if [ _$CMS_PATH == _ ]; then
  export CMS_PATH=/cvmfs/cms.cern.ch
  source $CMS_PATH/cmsset_default.sh
fi

hostname
tar xzf job.tar.gz
cd CMSSW_8_0_26_patch1/src/CATTools/CatAnalyzer/prod/STop_t

scram build ProjectRename
eval `scram runtime -sh`
if [ -f $CMSSW_BASE/proxy.x509 ]; then
    export X509_USER_PROXY=$CMSSW_BASE/proxy.x509
fi
echo BEGIN `date` cmsRun job_${SECTION}_cfg.py #>> /cms/scratch/dygyun/80X/CMSSW_8_0_26_patch1/src/CATTools/CatAnalyzer/prod/STop_t/submit.log
ls -al
time cmsRun job_${SECTION}_cfg.py 
EXITCODE=$?
ls -al
if [ $EXITCODE == 0 ]; then
    echo ENDED `date` cmsRun job_${SECTION}_cfg.py #>> /cms/scratch/dygyun/80X/CMSSW_8_0_26_patch1/src/CATTools/CatAnalyzer/prod/STop_t/submit.log
else
    rm -f core.*
    echo TERMINATED_$EXITCODE `date` cmsRun job_${SECTION}_cfg.py #>> /cms/scratch/dygyun/80X/CMSSW_8_0_26_patch1/src/CATTools/CatAnalyzer/prod/STop_t/submit.log
    exit 1
fi

for FILE in vallot.root; do
    EXT=${FILE##*.}
    PREFIX=${FILE%.${EXT}}
    TRANSFERCMD=xrdcp 
    DESTDIR=root://cms-xrdr.sdfarm.kr:1094///xrd//store/user/dygyun/Cattools/Catv806_Medium_Id_CSVT/SingleTop_t
    ${TRANSFERCMD} ${FILE} ${DESTDIR}/${PREFIX}_${SECTION}.${EXT}
    if [ $? -ne 0 ]; then
        echo "Failed to copy file.. retry in 5 seconds"
        sleep 5
        ${TRANSFERCMD} ${FILE} ${DESTDIR}/${PREFIX}_${SECTION}.${EXT}
    fi
    if [ $? -ne 0 ]; then
        echo "Failed to copy file.. (trial2) retry in 30 seconds"
        sleep 30
        ${TRANSFERCMD} ${FILE} ${DESTDIR}/${PREFIX}_${SECTION}.${EXT}
    fi
done
echo FINISHED `date` # >> /cms/scratch/dygyun/80X/CMSSW_8_0_26_patch1/src/CATTools/CatAnalyzer/prod/STop_t/submit.log
