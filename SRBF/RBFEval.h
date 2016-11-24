#ifndef _RBFEVAL_H_
#define _RBFEVAL_H_

#include <glm/glm.hpp>

#include "Global.h"

class RBF
{
public:
	RBF(int sqrtN, double _bandWidth) : N(sqrtN * sqrtN)
	{

		centers = new glm::vec3[N];
		bandWidths = new double[N];

		//generate N centers
		int index = 0;
		for (int i = 0; i < sqrtN; ++i)
		{
			for (int j = 0; j < sqrtN; ++j)
			{
				double a = (i + ((double)rand() / RAND_MAX)) / (double)sqrtN;
				double b = (j + ((double)rand() / RAND_MAX)) / (double)sqrtN;

				double theta = 2.0 * acos(sqrt(1.0 - a));
				double phi = 2.0 * M_PI * b;
				double x = sin(theta) * cos(phi);
				double y = sin(theta) * sin(phi);
				double z = cos(theta);

				centers[index++] = glm::vec3(x, y, z);
			}
		}

		//暂时设为统一值
		for (int i = 0; i < N; ++i)
		{
			bandWidths[i] = _bandWidth;
		}
	}

	//direction, 
	void RBFEval(double x, double y, double z, double *val);

private:
	const int N;//number of srbfs
	glm::vec3 *centers;
	double *bandWidths;
};


#endif