#include <iostream>

#include "Sampler.h"
#include "Scene.h"
#include "SRBFRenderer.h"

using namespace std;

const int sqrtNumSamples = 50;
const int nBands = BAND;

const int sqrtN = 6;//sqrtN * sqrtN srbfs


const int NMESH = 4;


int main()
{

	////PRTRenderer prtRender(600, 600);

	Sampler sampler;
	sampler.generateSamples(sqrtNumSamples, sqrtN);

	/*for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < sqrtN * sqrtN; ++j)
		{
			cout << sampler.samples[i].rbfValues[j] << "\t";
		}
		cout << endl;
	}
	cout << endl;*/

	Light light(sqrtN);

	light.directLight(sampler);
	//light.rotateLightCoeffs(43.3, 225.0);
	////light.lightFromImage("./Environments/uffizi_probe.pfm", sampler, nBands);
	
	const char *names[6] = { "sphere.obj", "walla.obj", "wallb.obj", "wallc.obj" };
	
	Scene scene;
	
	//this part: load scene and generate coefficients.  Now we store this information into a file
	/*char path[128];
	for (int i = 0; i < NMESH; ++i)
	{
		sprintf(path, "./%s/%s", "models", names[i]);
		scene.addModelFromFile(path);
	}

	bool ret = scene.generateCoeffs(sampler, sqrtN);

	if (!ret)
	{
		exit(-2);
	}*/

	//scene.saveAllData(sqrtN);
	scene.loadAllData(sqrtN);

	PRTRenderer prtRender(600, 600);
	prtRender.compileShaderFromFile("./shaders/verShader.glsl", "./shaders/fragShader.glsl");
	prtRender.setUniform();
	prtRender.renderSceneWithLight(scene, light);

	return 0;
}

