#pragma once

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

class DataReader {
	private:
		TFile *inputFile;
		TTree *l1HoTree, *l1MuonRecoTree, *l1BmtfInputTree, *l1UpgradeTree, *l1EventTree;
		TBranch *l1BmtfInputBranch;
		TTreeReader *l1HoReader, *l1MuonRecoReader, *l1BmtfInputReader, *l1UpgradeReader, *l1EventReader;
		int nEvents;
		bool hasRecoMuon;
	public:
		// Event Variables
		std::unique_ptr<TTreeReaderValue<unsigned int>> runNumber;
		//HO Variables
		std::unique_ptr<TTreeReaderValue<unsigned int>> nHcalDetIds, nHcalQIESamples;
		std::unique_ptr<TTreeReaderArray<int>> hcalDetIdIEta, hcalDetIdIPhi, hcalQIESample, hcalQIESampleAdc, hcalQIESampleDv, hcalQIESampleEr;
		std::unique_ptr<TTreeReaderArray<float>> SampleEnergy, QIESampleFc,  QIESamplePedestal, QIESampleFc_MPedestals;
		std::unique_ptr<TTreeReaderValue<double>> sumQ;
		//Reco Muon Variables
		std::unique_ptr<TTreeReaderValue<unsigned short>> nMuon;
		std::unique_ptr<TTreeReaderArray<bool>> muonIsLooseMuon, muonIsMediumMuon, muonIsTightMuon;
		std::unique_ptr<TTreeReaderArray<short>> muonHlt_isomu, muonHlt_mu;
		std::unique_ptr<TTreeReaderArray<int>> muonPassesSingleMuon, muonCharge;
		std::unique_ptr<TTreeReaderArray<float>> muonE, muonEt, muonPt, muonEta, muonPhi, muonIso, muonHlt_isoDeltaR, muonHlt_deltaR, muonEtaSt1, muonPhiSt1, muonEtaSt2, muonPhiSt2;
		std::unique_ptr<TTreeReaderArray<double>> muonMet, muonMt;
		//BMTF Input Variables (Drift Tube Trigger Primitive)
		std::unique_ptr<TTreeReaderValue<int>> bmtfPhSize, bmtfThSize;
		std::unique_ptr<TTreeReaderArray<int>> bmtfPhBx, bmtfPhWh, bmtfPhSe, bmtfPhSt, bmtfPhCode, bmtfPhTs2Tag, bmtfThBx, bmtfThWh, bmtfThSe, bmtfThSt, bmtfThTheta, bmtfThCode;
		std::unique_ptr<TTreeReaderArray<float>> bmtfPhAng, bmtfPhBandAng;
		//BMTF Variables (from L1UpgradeTree)
		std::unique_ptr<TTreeReaderValue<unsigned short>> nBmtfMuons;
		std::unique_ptr<TTreeReaderArray<short>> bmtfMuonIEt, bmtfMuonIEtUnconstrained, bmtfMuonIEta, bmtfMuonIPhi, bmtfMuonIEtaAtVtx, bmtfMuonIPhiAtVtx, bmtfMuonIDEta, bmtfMuonIDPhi, bmtfMuonChg, bmtfMuonBx;
		std::unique_ptr<TTreeReaderArray<unsigned short>> bmtfMuonIso, bmtfMuonQual, bmtfMuonDxy, bmtfMuonTfMuonIdx;
		std::unique_ptr<TTreeReaderArray<float>> bmtfMuonEt, bmtfMuonEtUnconstrained, bmtfMuonEta, bmtfMuonPhi, bmtfMuonEtaAtVtx, bmtfMuonPhiAtVtx;

		//BMTF Variables
		std::unique_ptr<TTreeReaderValue<unsigned short>> nTfMuon;
		std::unique_ptr<TTreeReaderArray<short>> tfMuonHwPt, tfMuonHwEta, tfMuonHwPhi, tfMuonGlobalPhi, tfMuonHwSign, tfMuonHwSignValid, tfMuonHwQual, tfMuonLink, tfMuonProcessor, tfMuonTrackFinderType, tfMuonHwHF, tfMuonBx, tfMuonWh, tfMuonTrAdd;

		//DataReader(std::string);
		DataReader(const char*, const bool*);
		~DataReader();
		bool Next();
		void clear();
		int GetEntries();
		bool GetHasRecoMuon();
};

