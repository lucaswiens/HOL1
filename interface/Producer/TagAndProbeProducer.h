#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

//#include <Math/GenVector/LorentzVector.h>
//#include <Vector4D.h>
//#include <TMath.h>
//#include <Math/GenVector/PtEtaPhiM4D.h>

#include <Math/Vector4Dfwd.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>


class TagAndProbeProducer : public BaseProducer {
	private:
		double ptCut, etaCut;
		char workingPointCut;
	public:
		TagAndProbeProducer(const double &ptCut, const double &etaCut, const char &workingPointCut);
		~TagAndProbeProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};
