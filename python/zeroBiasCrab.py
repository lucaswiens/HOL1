# TEMPLATE used for automatic script submission of multiple datasets
from WMCore.Configuration import Configuration
config = Configuration()

config.section_("General")
config.General.requestName = 'ZeroBias1'
config.General.workArea = 'crab_projects'

config.section_("JobType")
config.JobType.pluginName = 'Analysis'
config.JobType.psetName = 'zeroBiasCrab.py'
config.JobType.maxMemoryMB = 2000
config.JobType.maxJobRuntimeMin = 400
config.section_("Data")

config.Data.inputDBS = 'global'
config.Data.inputDataset = '/ZeroBias/Run2018C-v1/RAW'
config.Data.splitting = 'FileBased'#'Automatic' #'EventBased'#'EventAwareLumiBased'
config.Data.unitsPerJob = 3
config.Data.totalUnits = 1 #number of event for testing
config.Data.outLFNDirBase = '/store/user/lwiens/ZeroBias1_Run2018C_v1_L1Ntuple'
#config.Data.publication = True
config.Data.publication = False
config.Data.outputDatasetTag = 'Run2018C_ZeroBias_v1_L1Ntuple'

config.section_("Site")
#config.Site.whitelist = ['T2_DE_DESY']
#config.Site.whitelist = ['T1_FR_CCIN2P3_Tape']
#config.Site.whitelist = [u'T0_CH_CERN', u'T1_FR_CCIN2P3_Tape']

#[u'T3_US_UCR', u'T3_US_CMU', u'T3_US_FNALLPC', u'T3_FR_IPNL', u'T3_KR_KISTI', u'T3_US_Kansas', u'T3_RU_FIAN', u'T3_US_Brown', u'T3_US_UCD', u'T3_TW_NTU_HEP', u'T3_US_NERSC', u'T3_US_NotreDame', u'T2_RU_SINP', u'T3_US_PSC', u'T3_US_SDSC', u'T3_IN_PUHEP', u'T3_US_OSG', u'T2_GR_Ioannina', u'T3_US_MIT', u'T2_CH_CERN_HLT', u'T3_CH_CERNBOX', u'T3_US_ANL', u'T3_CH_CERN_HelixNebula', u'T3_US_Princeton_ICSE', u'T3_IN_TIFRCloud', u'T3_CH_CERN_OpenData', u'T0_CH_CERN', u'T3_GR_IASA', u'T3_CN_PKU', u'T3_US_Rutgers', u'T0_CH_CSCS_HPC', u'T3_IR_IPM', u'T2_RU_ITEP', u'T3_US_JHU', u'T3_BY_NCPHEP', u'T3_US_TACC', u'T3_KR_UOS', u'T3_CH_PSI', u'T3_US_UMiss', u'T3_IT_MIB']
#config.Site.blacklist = ['T2_DE_DESY']
config.Site.storageSite = 'T2_DE_DESY'
