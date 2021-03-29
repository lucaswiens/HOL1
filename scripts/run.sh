#!/bin/sh
cmsDriver.py l1Ntuple -s RAW2DIGI --python_filename=data.py -n 10 --no_output --era=Run2_2017 --data --conditions=110X_dataRun2_v12 --customise=L1Trigger/Configuration/customiseReEmul.L1TReEmulFromRAW --customise=L1Trigger/L1TNtuples/customiseL1Ntuple.L1NtupleAODRAWEMU --customise=L1Trigger/Configuration/customiseSettings.L1TSettingsToCaloParams_2018_v1_4_1 --no_exec

