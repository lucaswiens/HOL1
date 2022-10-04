#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

//#include <Math/GenVector/LorentzVector.h>
//#include <Vector4D.h>
//#include <TMath.h>
//#include <Math/GenVector/PtEtaPhiM4D.h>

#include <Math/Vector4Dfwd.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>


class MuonProducer : public BaseProducer {
	private:
	public:
		MuonProducer();
		~MuonProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

