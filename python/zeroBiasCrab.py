# TEMPLATE used for automatic script submission of multiple datasets
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZeroBias1'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'zeroBias2018.py'
config.JobType.maxMemoryMB = 2000
config.JobType.maxJobRuntimeMin = 400
config.section_("Data")

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/ZeroBias/Run2018C-v1/RAW'
config.Data.splitting = 'FileBased'#'Automatic' #'EventBased'#'EventAwareLumiBased'
config.Data.unitsPerJob = 5
#config.Data.totalUnits = 1 #number of event for testing
config.Data.outLFNDirBase = '/store/user/lwiens/ZeroBias1_Run2018C_v1_L1Ntuple'
#config.Data.publication = True
config.Data.publication = False
config.Data.outputDatasetTag = 'Run2018C_ZeroBias_v1_L1Ntuple'

config.section_("Site")

config.Site.storageSite = 'T2_DE_DESY'
