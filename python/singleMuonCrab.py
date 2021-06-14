# TEMPLATE used for automatic script submission of multiple datasets
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'SingleMuon'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'singleMuon2018.py'
config.JobType.maxMemoryMB = 2000
config.JobType.maxJobRuntimeMin = 400
config.section_("Data")

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/SingleMuon/Run2018D-ZMu-PromptReco-v2/RAW-RECO'
config.Data.splitting = 'FileBased'#'Automatic' #'EventBased'#'EventAwareLumiBased'
config.Data.unitsPerJob = 3
#config.Data.totalUnits = 1#number of event for testing
config.Data.outLFNDirBase = '/store/user/lwiens/Run2018D_SingleMuon_ZMu_PromptReco_v1_L1Ntuple'
#config.Data.publication = True
config.Data.publication = False
config.Data.outputDatasetTag = 'Run2018D_ZMu_PromptReco_v1_L1Ntuple_test'

config.section_("Site")

config.Site.storageSite = 'T2_DE_DESY'
