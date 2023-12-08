#include "SceneWriter.h"
#include "GameObjectManager.h"




SceneWriter::SceneWriter()
{
}

SceneWriter::~SceneWriter()
{
}

void SceneWriter::WriteToFile(std::string inputFilePath)
{
	std::string filePath = "";
	if (inputFilePath.find(".iet") != std::string::npos)
	{
		filePath = inputFilePath;
	}
	else
	{
		filePath = inputFilePath + ".iet";
	}

	std::ofstream sceneFile;
	sceneFile.open(filePath, std::ios::out);

	std::cout << "FilePath: " << filePath << "\n";

	std::vector<AGameObject*> allObjects = GameObjectManager::getInstance()->getAllGameObjects();

	AGameObject* currentObject;
	AComponent* objectComponent;
	PhysicsComponent* physicsComponent;

	for (int i = 0; i < allObjects.size(); i++)
	{
		currentObject = allObjects[i];

		sceneFile << currentObject->getObjectName() << std::endl;
		Vector3D pos = currentObject->getLocalPosition();
		Vector3D rot = currentObject->getLocalRotation();
		Vector3D scale = currentObject->getLocalScale();

		sceneFile << "Type: " << currentObject->getObjectType() << std::endl;
		sceneFile << "Position: " << pos.x << " " << pos.y << " " << pos.z << std::endl;
		sceneFile << "Rotation: " << rot.x << " " << rot.y << " " << rot.z << std::endl;
		sceneFile << "Scale: " << scale.x << " " << scale.y << " " << scale.z << std::endl;

		if (currentObject->isActive())
		{
			sceneFile << "Active: 1" << std::endl;
		}
		else
		{
			sceneFile << "Active: 0" << std::endl;
		}

		objectComponent = currentObject->findComponentOfType(AComponent::PHYSICS);

		if (objectComponent)
		{
			physicsComponent = (PhysicsComponent*)objectComponent;

			sceneFile << "PhysicsComponent: 1" << std::endl;
			sceneFile << "Active: " << physicsComponent->isActive() << std::endl;
			sceneFile << "Static: " << physicsComponent->isStatic() << std::endl;
			sceneFile << "Gravity: " << physicsComponent->isGravityEnabled() << std::endl;
			sceneFile << "Mass: " << physicsComponent->getMass() << std::endl;
		}
		else
		{
			sceneFile << "PhysicsComponent: 0" << std::endl;
			sceneFile << "Active: 0" << std::endl;
			sceneFile << "Static: 0" << std::endl;
			sceneFile << "Gravity: 0" << std::endl;
			sceneFile << "Mass: 0" << std::endl;
		}

		objectComponent = nullptr;
		physicsComponent = nullptr;
	}

	sceneFile.close();
}

void SceneWriter::LoadFromIETFile(std::string inputFilePath)
{
	std::string filePath = "";
	
	if (inputFilePath.find(".iet") != std::string::npos)
	{
		filePath = inputFilePath;
	}
	else
	{
		filePath = inputFilePath + ".iet";
	}

	std::ifstream sceneFile;
	sceneFile.open(filePath, std::ios::out);
	if (sceneFile.fail())
	{
		std::cout << "ERROR: Failed to open file at path " << filePath << std::endl;
		return;
	}
	
	//delete all object in scene to prepare for loading
	std::vector<AGameObject*> allObjects = GameObjectManager::getInstance()->getAllGameObjects();
	for (int i = 0; i < allObjects.size(); i++)
	{
		std::cout << "Deleting: " << allObjects[i]->getObjectName();
		GameObjectManager::getInstance()->deleteObject(allObjects[i]);
	}

	std::string currentLine;
	int index = 0;

	std::string objectName = "";
	AGameObject::ObjectType objectType;
	Vector3D pos;
	Vector3D rot;
	Vector3D scale;

	bool isActive;
	bool hasPhysics;
	bool isPhysicsActive;
	bool isStatic;
	bool isGravityActive;
	float mass;

	while (std::getline(sceneFile, currentLine))
	{
		switch (index) {
		case 0:
		{
			objectName = currentLine;
			std::cout << objectName << std::endl;
			index++;

			break;
		}

		case 1:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			objectType = (AGameObject::ObjectType)std::stoi(split[1]);
			std::cout << objectType << std::endl;
			index++;

			break;
		}

		case 2:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			pos = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			index++;

			break;
		}

		case 3:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			rot = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			std::cout << rot.x << " " << rot.y << " " << rot.z << std::endl;
			index++;

			break;
		}

		case 4:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			scale = Vector3D(std::stof(split[1]), std::stof(split[2]), std::stof(split[3]));
			std::cout << scale.x << " " << scale.y << " " << scale.z << std::endl;
			index++;

			break;
		}

		case 5:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isActive = std::stoi(split[1]);
			std::cout << isActive << std::endl;
			index++;

			break;
		}

		case 6:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			hasPhysics = std::stoi(split[1]);
			std::cout << hasPhysics << std::endl;
			index++;

			break;
		}

		case 7:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isPhysicsActive = std::stoi(split[1]);
			std::cout << isPhysicsActive << std::endl;
			index++;

			break;
		}

		case 8:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isStatic = std::stoi(split[1]);
			std::cout << isStatic << std::endl;
			index++;

			break;
		}

		case 9:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			isGravityActive = std::stoi(split[1]);
			std::cout << isGravityActive << std::endl;
			index++;

			break;
		}

		case 10:
		{
			std::vector<std::string> split = StringUtilities::split(currentLine, ' ');
			mass = std::stof(split[1]);
			std::cout << mass << std::endl;
			index = 0;

			GameObjectManager::getInstance()->recreateObject(
				objectName,
				objectType,
				pos,
				rot,
				scale,
				hasPhysics,
				isPhysicsActive,
				isStatic,
				isGravityActive,
				mass
			);

			break;
		}

		}
	}
}

class GameObjectState
{
public:
	Vector3D position;
	Vector3D rotation;
	Vector3D scale;
};

class PhysicsState
{
public:
	float mass;
	bool useGravity;
	bool isStatic;
};

void SceneWriter::LoadFromUnityFile(std::string inputFilePath)
{
	std::cout << "Unity File" << std::endl;

	std::ifstream file;
	std::string line;

	std::vector<std::string> wordList;

	file.open(inputFilePath, std::ios::out);


	if (file.is_open()) {
		while (std::getline(file, line)) {
			std::istringstream iss(line);
			std::string word;
			while (iss >> word) {
				std::string cleanedWord;
				for (char c : word) {
					if (std::isalnum(c) || c == '.' || c == '-') {
						cleanedWord += c;
					}
				}
				// Process each cleaned word
				//std::cout << cleanedWord << std::endl;
				wordList.push_back(cleanedWord);
			}
		}
		file.close();
	}
	else {
		std::cerr << "Unable to open file" << std::endl;
	}


	AGameObject* createdGameObject = nullptr;
	GameObjectState* gameObjectState = nullptr;
	PhysicsState* physicsState = nullptr;

	int index = 0;

	int rotationXIndex = 19;
	int rotationYIndex = 21;
	int rotationZIndex = 23;
	int rotationWIndex = 25;

	int positionXIndex = 28;
	int positionYIndex = 30;
	int positionZIndex = 32;

	int scaleXIndex = 35;
	int scaleYIndex = 37;
	int scaleZIndex = 39;

	int massIndex = 18;
	int gravityIndex = 61;
	int kinematicIndex = 63;

	for (int i = 0; i < wordList.size(); i++)
	{
		//cout << wordList[i] << endl
		if (wordList[i] == "GameObject")
		{
			createdGameObject = nullptr;
			gameObjectState = nullptr;
			physicsState = nullptr;

			cout << "GameObject Detected" << endl;
		}

		if (wordList[i] == "BoxCollider")
		{
		
			GameObjectManager::getInstance()->createObject(GameObjectManager::CUBE);
			createdGameObject = GameObjectManager::getInstance()->getAllGameObjects().back();

			if (gameObjectState != nullptr)
			{
				createdGameObject->setPosition(gameObjectState->position.x, gameObjectState->position.y, gameObjectState->position.z);
				createdGameObject->setRotation(gameObjectState->rotation.x, gameObjectState->rotation.y, gameObjectState->rotation.z);
				createdGameObject->setScale(gameObjectState->scale.x, gameObjectState->scale.y, gameObjectState->scale.z);
			}

			if (physicsState != nullptr)
			{
				PhysicsComponent* component = new PhysicsComponent(createdGameObject->getObjectName() + " Physics");
				createdGameObject->attachComponent(component);

				component->setMass(physicsState->mass);
				component->enableGravity(physicsState->useGravity);
				component->setStatic(physicsState->isStatic);
			}

			cout << "BoxCollider Detected" << " " << createdGameObject->getObjectName() << endl;
			
		}
		else if (wordList[i] == "MeshCollider")
		{
		
			GameObjectManager::getInstance()->createObject(GameObjectManager::PLANE);
			createdGameObject = GameObjectManager::getInstance()->getAllGameObjects().back();

			if (gameObjectState != nullptr)
			{
				createdGameObject->setPosition(gameObjectState->position.x, gameObjectState->position.y, gameObjectState->position.z);
				createdGameObject->setRotation(gameObjectState->rotation.x, gameObjectState->rotation.y, gameObjectState->rotation.z);
				createdGameObject->setScale(gameObjectState->scale.x * 10, 1, gameObjectState->scale.z * 10);

			}

			if (physicsState != nullptr)
			{
				PhysicsComponent* component = new PhysicsComponent(createdGameObject->getObjectName() + " Physics");
				createdGameObject->attachComponent(component);

				component->setMass(physicsState->mass);
				component->enableGravity(physicsState->useGravity);
				component->setStatic(physicsState->isStatic);
			}

			cout << "MeshCollider Detected" << " " << createdGameObject->getObjectName() << endl;
		}

		if (wordList[i] == "Transform")
		{
			cout << "Transform Detected" << endl;

			Vector3D position;
			Vector3D rotation;
			Vector3D scale;

			position.x = std::stof(wordList[i + positionXIndex]);
			position.y = std::stof(wordList[i + positionYIndex]);
			position.z = std::stof(wordList[i + positionZIndex]);

			cout << "Position x: " << position.x << " y: " << position.y << " z: " << position.z << endl << endl;

			cout << "Old Rotation x: " << std::stof(wordList[i + rotationXIndex]) << " y: " << std::stof(wordList[i + rotationYIndex]) << " z: " << std::stof(wordList[i + rotationZIndex]) << " w: " << std::stof(wordList[i + rotationWIndex]) << endl;
			rotation = Vector3D::QuaterionToEuler(std::stof(wordList[i + rotationXIndex]), std::stof(wordList[i + rotationYIndex]), std::stof(wordList[i + rotationZIndex]), std::stof(wordList[i + rotationWIndex]));

			scale.x = std::stof(wordList[i + scaleXIndex]);
			scale.y = std::stof(wordList[i + scaleYIndex]);
			scale.z = std::stof(wordList[i + scaleZIndex]);

			cout << "New Rotation x: " << rotation.x << " y: " << rotation.y << " z: " << rotation.z << endl << endl;

			if (createdGameObject != nullptr)
			{

				
				createdGameObject->setPosition(position.x, position.y, position.z);
				createdGameObject->setRotation(rotation.x, rotation.y, rotation.z);

				if (createdGameObject->getObjectType() == 1)
				{
					createdGameObject->setScale(scale.x, scale.y, scale.z);
				}
				else if (createdGameObject->getObjectType() == 2)
				{
					createdGameObject->setScale(scale.x * 10, 1, scale.z * 10);
				}

			}
			else
			{
				gameObjectState = new GameObjectState();
				gameObjectState->position = position;
				gameObjectState->rotation = rotation;
				gameObjectState->scale = scale;
			}

			
			
			
		}

		if (wordList[i] == "Rigidbody")
		{
			if (createdGameObject != nullptr)
			{
				PhysicsComponent* component = new PhysicsComponent(createdGameObject->getObjectName() + " Physics");
				createdGameObject->attachComponent(component);

				component->setMass(std::stof(wordList[i + massIndex]));
				component->enableGravity(std::stoi(wordList[i + gravityIndex]));
				component->setStatic(std::stoi(wordList[i + kinematicIndex]));
			}
			else
			{
				physicsState = new PhysicsState();
				physicsState->mass = std::stof(wordList[i + massIndex]);
				physicsState->useGravity = std::stoi(wordList[i + gravityIndex]);
				physicsState->isStatic = std::stoi(wordList[i + kinematicIndex]);
			}
		
			cout << "RigidBody Detected" << endl;
		}

		
	}
}
