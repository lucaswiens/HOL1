#pragma once

#include <TFile.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>

class DataReader {
	private:
		TFile *inputFile;
		TTree *l1HoTree, *l1MuonRecoTree, *l1BmtfInputTree;
		TBranch *l1BmtfInputBranch;
		TTreeReader *l1HoReader, *l1MuonRecoReader, *l1BmtfInputReader;
	public:
		//Upgrade BMTF Muon Inputs
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
		//BMTF Input Variables
		std::unique_ptr<TTreeReaderValue<int>> bmtfPhSize, bmtfThSize;
		std::unique_ptr<TTreeReaderArray<int>> bmtfPhBx, bmtfPhWh, bmtfPhSe, bmtfPhSt, bmtfPhCode, bmtfPhTs2Tag, bmtfThBx, bmtfThWh, bmtfThSe, bmtfThSt, bmtfThTheta, bmtfThCode;
		std::unique_ptr<TTreeReaderArray<float>> bmtfPhAng, bmtfPhBandAng;

		DataReader(std::string);
		~DataReader();
		bool Next();
		void clear();
};
