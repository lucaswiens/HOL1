#include <HOAnalysis/HOL1/interface/Producer/BaseProducer.h>

BaseProducer::BaseProducer(){}

float BaseProducer::DeltaR(const float &eta1, const float &phi1, const float &eta2, const float &phi2) {
	return std::sqrt(std::pow(phi1 - phi2, 2) + std::pow(eta1 - eta2, 2));
}
