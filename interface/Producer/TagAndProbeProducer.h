#pragma once

#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

#include <Math/Vector4Dfwd.h>
#include <Math/GenVector/LorentzVector.h>
#include <Math/GenVector/PtEtaPhiM4D.h>

class TagAndProbeProducer : public BaseProducer {
	private:
		double tagPtCut, probePtCut, l1PtCut, etaCut, deltaRTagAndTfCut, deltaRTagAndProbeCut;
		char tagWorkingPointCut, probeWorkingPointCut;
		const double zBosonMass = 91.1876;
		const double jPsiMass = 3.096;
		const double muonMass = 0.1056583755;
	public:
		TagAndProbeProducer(const double &tagPtCut, const double &probePtCut, const double &l1PtCut, const double &etaCut, const double &deltaRTagAndTfCut, const double &deltaRTagAndProbeCut, const char &tagWorkingPointCut, const char &probeWorkingPointCut);
		~TagAndProbeProducer();
		void Produce(DataReader* dataReader, HoProduct* product, HoHistogramCollection* histCollection);
		void EndJob(HoHistogramCollection* histCollection);
};

