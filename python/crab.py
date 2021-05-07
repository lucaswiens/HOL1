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
#config.Site.whitelist = ['T2_DE_DESY']
#config.Site.whitelist = ['T1_FR_CCIN2P3_Tape']
#config.Site.whitelist = [u'T0_CH_CERN', u'T1_FR_CCIN2P3_Tape']

#[u'T3_US_UCR', u'T3_US_CMU', u'T3_US_FNALLPC', u'T3_FR_IPNL', u'T3_KR_KISTI', u'T3_US_Kansas', u'T3_RU_FIAN', u'T3_US_Brown', u'T3_US_UCD', u'T3_TW_NTU_HEP', u'T3_US_NERSC', u'T3_US_NotreDame', u'T2_RU_SINP', u'T3_US_PSC', u'T3_US_SDSC', u'T3_IN_PUHEP', u'T3_US_OSG', u'T2_GR_Ioannina', u'T3_US_MIT', u'T2_CH_CERN_HLT', u'T3_CH_CERNBOX', u'T3_US_ANL', u'T3_CH_CERN_HelixNebula', u'T3_US_Princeton_ICSE', u'T3_IN_TIFRCloud', u'T3_CH_CERN_OpenData', u'T0_CH_CERN', u'T3_GR_IASA', u'T3_CN_PKU', u'T3_US_Rutgers', u'T0_CH_CSCS_HPC', u'T3_IR_IPM', u'T2_RU_ITEP', u'T3_US_JHU', u'T3_BY_NCPHEP', u'T3_US_TACC', u'T3_KR_UOS', u'T3_CH_PSI', u'T3_US_UMiss', u'T3_IT_MIB']
config.Site.blacklist = ['T2_DE_DESY']
config.Site.storageSite = 'T2_DE_DESY'
