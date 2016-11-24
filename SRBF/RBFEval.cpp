#include "RBFEval.h"

void RBF::RBFEval(double x, double y, double z, double *val)
{
	for (int i = 0; i < N; ++i)
	{
		val[i] = 0.0f;
		float cosine = glm::dot(centers[i], glm::normalize(glm::vec3(x, y, z)));
		
		val[i] = exp(-bandWidths[i]) * exp(bandWidths[i] * glm::dot(centers[i], glm::normalize(glm::vec3(x, y, z))));
	}
}