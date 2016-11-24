#include "Sampler.h"
#include "SHEval.h"
#include "RBFEval.h"

void Sampler::generateSamples(const int sqrtNumSamples, const int sqrtN)
{
	int numSamples = sqrtNumSamples * sqrtNumSamples;
	int numFunctions =  sqrtN * sqrtN;

	
	samples.resize(numSamples); 

	//sqrtN * sqrtN is the number of srbfs, the second parameter is the default bandwidth
	RBF rbf(sqrtN, 16.0);
	//srand(unsigned(time(NULL)));

	unsigned index = 0;
	for (int i = 0; i < sqrtNumSamples; ++i)
	{
		
		for (int j = 0; j < sqrtNumSamples; ++j)
		{
			double a = (i + ((double)rand() / RAND_MAX)) / (double)sqrtNumSamples;
			double b = (j + ((double)rand() / RAND_MAX)) / (double)sqrtNumSamples;

			double theta = 2.0 * acos(sqrt(1.0 - a));
			double phi = 2.0 * M_PI * b;
			double x = sin(theta) * cos(phi);
			double y = sin(theta) * sin(phi);
			double z = cos(theta);
			samples[index].xyz = glm::vec3(x, y, z);
			samples[index].phi = phi;
			samples[index].theta = theta;

			samples[index].rbfValues = new double[numFunctions];
			if (!samples[index].rbfValues)
			{
				cerr << "Unable to allocate space for SH values in samples" << endl;
				exit(-1);
			}
			
			rbf.RBFEval(x, y, z, samples[index].rbfValues);
			++index;
		}
	}

	/*for (int i = 200; i < 205; ++i)
	{
		printf("%0.5f-%0.5f-%0.5f ** %0.5f-%0.5f-%0.5f\n", samples[i].xyz.x, samples[i].xyz.y, samples[i].xyz.z, samples[i].shValues[0], samples[i].shValues[1], samples[i].shValues[2]);
	}*/
}

unsigned Sampler::size()
{
	return this->samples.size();
}

SAMPLE &Sampler::operator[](unsigned int index)
{
	assert(index >= 0 && index < samples.size());
	return samples[index];
}