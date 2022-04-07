#include <HOAnalysis/HOL1/interface/DataReader.h>


DataReader::DataReader(const char* inputFileName, const bool *useEmulated) {
	//inputFile = TFile::Open(inputFileName.c_str(), "READ");
	inputFile = TFile::Open(TString(inputFileName), "READ");

	// Get the runNumber:
	l1EventTree   = (TTree*)inputFile->Get("l1EventTree/L1EventTree");
	l1EventReader = new TTreeReader(l1EventTree);
	runNumber     = std::make_unique<TTreeReaderValue<unsigned int>>(*l1EventReader, "run");

	l1HoTree        = (TTree*)inputFile->Get("l1HOTree/L1HOTree");
	l1HoReader        = new TTreeReader(l1HoTree);
	nEvents = l1HoTree->GetEntries();

	//Set Reader for HO Variables
	nHcalDetIds            = std::make_unique<TTreeReaderValue<unsigned int>>(*l1HoReader, "nHcalDetIds");
	nHcalQIESamples        = std::make_unique<TTreeReaderValue<unsigned int>>(*l1HoReader, "nHcalQIESamples");
	sumQ                   = std::make_unique<TTreeReaderValue<double>>(*l1HoReader, "sumQ");
	hcalDetIdIEta          = std::make_unique<TTreeReaderArray<int>>(*l1HoReader, "hcalDetIdIEta");
	hcalDetIdIPhi          = std::make_unique<TTreeReaderArray<int>>(*l1HoReader, "hcalDetIdIPhi");
	hcalQIESample          = std::make_unique<TTreeReaderArray<int>>(*l1HoReader, "hcalQIESample");
	hcalQIESampleAdc       = std::make_unique<TTreeReaderArray<int>>(*l1HoReader, "hcalQIESampleAdc");
	hcalQIESampleDv        = std::make_unique<TTreeReaderArray<int>>(*l1HoReader, "hcalQIESampleDv");
	hcalQIESampleEr        = std::make_unique<TTreeReaderArray<int>>(*l1HoReader, "hcalQIESampleEr");
	QIESampleFc            = std::make_unique<TTreeReaderArray<float>>(*l1HoReader, "QIESampleFc");
	SampleEnergy           = std::make_unique<TTreeReaderArray<float>>(*l1HoReader, "SampleEnergy");
	QIESamplePedestal      = std::make_unique<TTreeReaderArray<float>>(*l1HoReader, "QIESamplePedestal");
	QIESampleFc_MPedestals = std::make_unique<TTreeReaderArray<float>>(*l1HoReader, "QIESampleFc_MPedestals");

	hasRecoMuon = false;
	if (strstr((char*)inputFileName, "SingleMuon") != NULL || strstr((char*)inputFileName, "MET") != NULL) {
		//std::cout << "Dataset has reco muons!" << std::endl;
		hasRecoMuon = true;
		l1MuonRecoTree  = (TTree*)inputFile->Get("l1MuonRecoTree/Muon2RecoTree");
		l1MuonRecoReader  = new TTreeReader(l1MuonRecoTree);
		//Set Reader for MuonReco Variables
		nMuon                = std::make_unique<TTreeReaderValue<unsigned short>>(*l1MuonRecoReader, "nMuons");
		muonIsLooseMuon      = std::make_unique<TTreeReaderArray<bool>>(*l1MuonRecoReader, "isLooseMuon");
		muonIsMediumMuon     = std::make_unique<TTreeReaderArray<bool>>(*l1MuonRecoReader, "isMediumMuon");
		muonIsTightMuon      = std::make_unique<TTreeReaderArray<bool>>(*l1MuonRecoReader, "isTightMuon");
		muonHlt_isomu        = std::make_unique<TTreeReaderArray<short>>(*l1MuonRecoReader, "hlt_isomu");
		muonHlt_mu           = std::make_unique<TTreeReaderArray<short>>(*l1MuonRecoReader, "hlt_mu");
		muonPassesSingleMuon = std::make_unique<TTreeReaderArray<int>>(*l1MuonRecoReader, "passesSingleMuon");
		muonCharge           = std::make_unique<TTreeReaderArray<int>>(*l1MuonRecoReader, "charge");
		muonE                = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "e");
		muonEt               = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "et");
		muonPt               = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "pt");
		muonEta              = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "eta");
		muonPhi              = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "phi");
		muonIso              = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "iso");
		muonHlt_isoDeltaR    = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "hlt_isoDeltaR");
		muonHlt_deltaR       = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "hlt_deltaR");
		muonEtaSt1           = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "etaSt1");
		muonPhiSt1           = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "phiSt1");
		muonEtaSt2           = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "etaSt2");
		muonPhiSt2           = std::make_unique<TTreeReaderArray<float>>(*l1MuonRecoReader, "phiSt2");
		muonMet              = std::make_unique<TTreeReaderArray<double>>(*l1MuonRecoReader, "met");
		muonMt               = std::make_unique<TTreeReaderArray<double>>(*l1MuonRecoReader, "mt");
	} else {
		std::cout << "Dataset does not reco muons!" << std::endl;
	}

	//l1BmtfInputTree = (TTree*)inputFile->Get("l1UpgradeTfMuonTree/L1UpgradeTfMuonTree");
	std::string emulatedString = *useEmulated ? "Emu" : "";
	std::string tfMuonName = "l1UpgradeTfMuon" + emulatedString + "Tree/L1UpgradeTfMuonTree";
	l1BmtfInputTree = (TTree*)inputFile->Get(tfMuonName.c_str());
	l1BmtfInputReader = new TTreeReader(l1BmtfInputTree);
	//Set Reader for BMTF Input Variables (DTTP)
	bmtfPhSize    = std::make_unique<TTreeReaderValue<int>>(*l1BmtfInputReader, "phSize");
	bmtfPhBx      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phBx");
	bmtfPhWh      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phWh");
	bmtfPhSe      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phSe");
	bmtfPhSt      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phSt");
	bmtfPhCode    = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phCode");
	bmtfPhTs2Tag  = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phTs2Tag");
	bmtfPhAng     = std::make_unique<TTreeReaderArray<float>>(*l1BmtfInputReader, "phAng");
	bmtfPhBandAng = std::make_unique<TTreeReaderArray<float>>(*l1BmtfInputReader, "phBandAng");
	//Set Reader for BMTF Muon Variables
	std::map<int, std::string> tfPrefix = {{Utility::Bmtf, "Bmtf"}, {Utility::Omtf, "Omtf"}, {Utility::Emtf, "Emtf"}};
	for (int tfType : {Utility::Bmtf, Utility::Omtf, Utility::Emtf}) {
		nTfMuons.insert({tfType,     std::make_unique<TTreeReaderValue<unsigned short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.nTfMuons").c_str())});
		tfMuonHwPt.insert({tfType,            std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwPt").c_str())});
		tfMuonHwEta.insert({tfType,           std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwEta").c_str())});
		tfMuonHwPhi.insert({tfType,           std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwPhi").c_str())});
		tfMuonGlobalPhi.insert({tfType,       std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonGlobalPhi").c_str())});
		tfMuonHwSign.insert({tfType,          std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwSign").c_str())});
		tfMuonHwSignValid.insert({tfType,     std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwSignValid").c_str())});
		tfMuonHwQual.insert({tfType,          std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwQual").c_str())});
		tfMuonLink.insert({tfType,            std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonLink").c_str())});
		tfMuonProcessor.insert({tfType,       std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonProcessor").c_str())});
		tfMuonTrackFinderType.insert({tfType, std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonTrackFinderType").c_str())});
		tfMuonHwHF.insert({tfType,            std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonHwHF").c_str())});
		tfMuonBx.insert({tfType,              std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonBx").c_str())});
		tfMuonWh.insert({tfType,              std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonWh").c_str())});
		tfMuonTrAdd.insert({tfType,           std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, ("L1Upgrade" + tfPrefix.at(tfType) + "Muon.tfMuonTrAdd").c_str())});
	}

	//Make just new stuff while keeping old tfMuon info.. Just outcomment the actual reading in bmtfinpuitproducer
	std::string upgradeMuonName = "l1Upgrade" + emulatedString + "Tree/L1UpgradeTree";
	l1UpgradeTree            = (TTree*)inputFile->Get(upgradeMuonName.c_str());
	l1UpgradeReader          = new TTreeReader(l1UpgradeTree);
	nUGMTMuons             = std::make_unique<TTreeReaderValue<unsigned short>>(*l1UpgradeReader, "nMuons");
	uGMTEt               = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEt");
	uGMTEtUnconstrained  = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEtUnconstrained");
	uGMTEta              = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEta");
	uGMTPhi              = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonPhi");
	uGMTEtaAtVtx         = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEtaAtVtx");
	uGMTPhiAtVtx         = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonPhiAtVtx");
	uGMTIEt              = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEt");
	uGMTIEtUnconstrained = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEtUnconstrained");
	uGMTIEta             = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEta");
	uGMTIPhi             = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIPhi");
	uGMTIEtaAtVtx        = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEtaAtVtx");
	uGMTIPhiAtVtx        = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIPhiAtVtx");
	uGMTIDEta            = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIDEta");
	uGMTIDPhi            = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIDPhi");
	uGMTChg              = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonChg");
	uGMTIso              = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonIso");
	uGMTQual             = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonQual");
	uGMTDxy              = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonDxy");
	uGMTTfMuonIdx        = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonTfMuonIdx");
	uGMTBx               = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonBx");
}

DataReader::~DataReader(){
	delete l1HoReader;
	delete l1BmtfInputReader;
	delete l1EventReader;

	if (hasRecoMuon) {
		delete l1MuonRecoReader;
	}

	inputFile->Close();
	delete inputFile;
}

int DataReader::GetEntries() {
	return nEvents;
}

bool DataReader::GetHasRecoMuon() {
	return hasRecoMuon;
}

bool DataReader::Next() {
	if (hasRecoMuon) {
		return l1HoReader->Next() && l1MuonRecoReader->Next() && l1UpgradeReader->Next() && l1BmtfInputReader->Next() && l1EventReader->Next();
	} else {
		return l1HoReader->Next() && l1UpgradeReader->Next() && l1BmtfInputReader->Next() && l1EventReader->Next();
	}
}

void DataReader::clear() {}
