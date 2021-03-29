# TEMPLATE used for automatic script submission of multiple datasets

#cmsDriver.py l1Ntuple -s RAW2DIGI --python_filename=data.py -n 10 --no_output --era=Run2_2018 --data --conditions=110X_dataRun2_v12 --customise=L1Trigger/Configuration/customiseReEmul.L1TReEmulFromRAW --customise=L1Trigger/L1TNtuples/customiseL1Ntuple.L1NtupleAODRAWEMU --customise=L1Trigger/Configuration/customiseSettings.L1TSettingsToCaloParams_2018_v1_4_1 --filein=file:/eos/cms/store/data/Run2018D/SingleMuon/RAW-RECO/ZMu-PromptReco-v2/000/321/457/00000/60D23B7B-C7A5-E811-B14B-FA163EF4F4A1.root

from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SingleMuon'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'data.py'
config.JobType.maxMemoryMB = 2500
config.section_("Data")

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/SingleMuon/Run2017C-ZMu-PromptReco-v3/RAW-RECO'
config.Data.splitting = 'FileBased'#'Automatic' #'EventBased'#'EventAwareLumiBased'
config.Data.unitsPerJob = 1
config.Data.totalUnits = 1#number of event for testing
config.Data.outLFNDirBase = '/store/user/lwiens/Run2017C_SingleMuon_ZMu_RAW_RECO'
#config.Data.publication = True
config.Data.publication = False
config.Data.outputDatasetTag = 'Run2017C_ZMu-PromptReco_L1Ntuple_test'

config.section_("Site")
config.Site.whitelist = ['T2_DE_DESY']
config.Site.storageSite = 'T2_DE_DESY'
