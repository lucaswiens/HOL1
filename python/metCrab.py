# TEMPLATE used for automatic script submission of multiple datasets
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'MET'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'met2018.py'
config.JobType.maxMemoryMB = 3000
config.JobType.maxJobRuntimeMin = 145
config.section_("Data")

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/MET/Run2018D-HighMET-PromptReco-v2/RAW-RECO'
config.Data.splitting = 'FileBased'#'Automatic' #'EventBased'#'EventAwareLumiBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 1#number of event for testing
config.Data.outLFNDirBase = '/store/user/lwiens/Run2018D_MET_HighMET_PromptReco_v2_L1Ntuple'
#config.Data.publication = True
config.Data.publication = False
config.Data.outputDatasetTag = 'Run2018D_MET_HighMET_PromptReco_v2_L1Ntuple'

config.section_("Site")

config.Site.storageSite = 'T2_DE_DESY'
