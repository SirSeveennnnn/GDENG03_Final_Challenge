#pragma once

#include "AGameObject.h"
#include "Vector3D.h"
#include "GameObjectManager.h"
#include "PhysicsComponent.h"
#include "StringUtilities.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Vector3D.h"

using namespace std;

class SceneWriter
{
public:
	static void WriteToFile(std::string inputFilePath);
	static void LoadFromIETFile(std::string inputFilePath);
	static void LoadFromUnityFile(std::string inputFilePath);

	

	//std::string directory = ""; idk what sir was cooking with this so I'm cooking my own

private:

	

	SceneWriter();
	~SceneWriter();
};