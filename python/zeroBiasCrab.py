# TEMPLATE used for automatic script submission of multiple datasets
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZeroBias1'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'zeroBiasConfig.py'
config.JobType.maxMemoryMB = 3000
#config.JobType.maxJobRuntimeMin = 400
config.section_("Data")

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/ZeroBias/Run2018D-v1/RAW'
config.Data.splitting = 'FileBased'#'Automatic' #'EventBased'#'EventAwareLumiBased'
config.Data.unitsPerJob = 1
#config.Data.totalUnits = 1000 #number of event for testing
config.Data.outLFNDirBase = '/store/user/lwiens/Run2018D_ZeroBias_v1_RAW_ReprocessAfterDcacheIncident'
#config.Data.publication = True
config.Data.publication = False
config.Data.outputDatasetTag = 'Run2018D_ZeroBias'

config.section_("Site")

config.Site.storageSite = 'T2_DE_DESY'
