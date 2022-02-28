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
	//Set Reader for BMTF Input Variables
	bmtfPhSize    = std::make_unique<TTreeReaderValue<int>>(*l1BmtfInputReader, "phSize");
	bmtfThSize    = std::make_unique<TTreeReaderValue<int>>(*l1BmtfInputReader, "thSize");
	bmtfPhBx      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phBx");
	bmtfPhWh      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phWh");
	bmtfPhSe      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phSe");
	bmtfPhSt      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phSt");
	bmtfPhCode    = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phCode");
	bmtfPhTs2Tag  = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "phTs2Tag");
	bmtfThBx      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "thBx");
	bmtfThWh      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "thWh");
	bmtfThSe      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "thSe");
	bmtfThSt      = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "thSt");
	bmtfThTheta   = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "thTheta");
	bmtfThCode    = std::make_unique<TTreeReaderArray<int>>(*l1BmtfInputReader, "thCode");
	bmtfPhAng     = std::make_unique<TTreeReaderArray<float>>(*l1BmtfInputReader, "phAng");
	bmtfPhBandAng = std::make_unique<TTreeReaderArray<float>>(*l1BmtfInputReader, "phBandAng");
	//Set Reader for BMTF Muon Variables
	nTfMuon               = std::make_unique<TTreeReaderValue<unsigned short>>(*l1BmtfInputReader, "nTfMuons");
	tfMuonHwPt            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwPt");
	//tfMuonHwPt            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwPtUnconstrained");
	tfMuonHwEta           = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwEta");
	tfMuonHwPhi           = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwPhi");
	tfMuonGlobalPhi       = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonGlobalPhi");
	tfMuonHwSign          = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwSign");
	tfMuonHwSignValid     = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwSignValid");
	tfMuonHwQual          = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwQual");
	tfMuonLink            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonLink");
	tfMuonProcessor       = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonProcessor");
	tfMuonTrackFinderType = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonTrackFinderType");
	tfMuonHwHF            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonHwHF");
	tfMuonBx              = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonBx");
	tfMuonWh              = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonWh");
	tfMuonTrAdd           = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "tfMuonTrAdd");

	//Make just new stuff while keeping old tfMuon info.. Just outcomment the actual reading in bmtfinpuitproducer
	std::string upgradeMuonName = "l1Upgrade" + emulatedString + "Tree/L1UpgradeTree";
	l1UpgradeTree            = (TTree*)inputFile->Get(upgradeMuonName.c_str());
	l1UpgradeReader          = new TTreeReader(l1UpgradeTree);
	nBmtfMuons               = std::make_unique<TTreeReaderValue<unsigned short>>(*l1UpgradeReader, "nMuons");
	bmtfMuonEt               = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEt");
	bmtfMuonEtUnconstrained  = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEtUnconstrained");
	bmtfMuonEta              = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEta");
	bmtfMuonPhi              = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonPhi");
	bmtfMuonEtaAtVtx         = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonEtaAtVtx");
	bmtfMuonPhiAtVtx         = std::make_unique<TTreeReaderArray<float>>(*l1UpgradeReader, "muonPhiAtVtx");
	bmtfMuonIEt              = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEt");
	bmtfMuonIEtUnconstrained = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEtUnconstrained");
	bmtfMuonIEta             = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEta");
	bmtfMuonIPhi             = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIPhi");
	bmtfMuonIEtaAtVtx        = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIEtaAtVtx");
	bmtfMuonIPhiAtVtx        = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIPhiAtVtx");
	bmtfMuonIDEta            = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIDEta");
	bmtfMuonIDPhi            = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonIDPhi");
	bmtfMuonChg              = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonChg");
	bmtfMuonIso              = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonIso");
	bmtfMuonQual             = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonQual");
	bmtfMuonDxy              = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonDxy");
	bmtfMuonTfMuonIdx        = std::make_unique<TTreeReaderArray<unsigned short>>(*l1UpgradeReader, "muonTfMuonIdx");
	bmtfMuonBx               = std::make_unique<TTreeReaderArray<short>>(*l1UpgradeReader, "muonBx");
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
