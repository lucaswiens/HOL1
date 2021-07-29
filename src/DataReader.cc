#include <HOAnalysis/HOL1/interface/DataReader.h>


DataReader::DataReader(const char* inputFileName) {
	//inputFile = TFile::Open(inputFileName.c_str(), "READ");
	inputFile = TFile::Open(TString(inputFileName), "READ");

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
	} /* else {
		std::cout << "Dataset does not reco muons!" << std::endl;
	} */

	l1BmtfInputTree = (TTree*)inputFile->Get("l1UpgradeTfMuonTree/L1UpgradeTfMuonTree");
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
	nTfMuon               = std::make_unique<TTreeReaderValue<unsigned short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.nTfMuons");
	tfMuonHwPt            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwPt");
	//tfMuonHwPt            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwPtUnconstrained");
	tfMuonHwEta           = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwEta");
	tfMuonHwPhi           = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwPhi");
	tfMuonGlobalPhi       = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonGlobalPhi");
	tfMuonHwSign          = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwSign");
	tfMuonHwSignValid     = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwSignValid");
	tfMuonHwQual          = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwQual");
	tfMuonLink            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonLink");
	tfMuonProcessor       = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonProcessor");
	tfMuonTrackFinderType = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonTrackFinderType");
	tfMuonHwHF            = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonHwHF");
	tfMuonBx              = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonBx");
	tfMuonWh              = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonWh");
	tfMuonTrAdd           = std::make_unique<TTreeReaderArray<short>>(*l1BmtfInputReader, "L1UpgradeBmtfMuon.tfMuonTrAdd");
}

DataReader::~DataReader(){
	delete l1HoReader;
	delete l1BmtfInputReader;

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
		return l1HoReader->Next() && l1MuonRecoReader->Next() && l1BmtfInputReader->Next();
	} else {
		return l1HoReader->Next() && l1BmtfInputReader->Next();
	}
}

void DataReader::clear() {}
