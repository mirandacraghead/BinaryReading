#include<iostream>
#include<fstream>
#include<string>
#include<vector>
using std::cout;
using namespace std;

void menuDisplay() {
	cout << "Which file(s) to open?" << endl;
	cout << "1. fantasyheroes.dat" << endl;
	cout << "2. superheroes.dat" << endl;
	cout << "3. Both files" << endl;
}
void fileDisplay() {
	cout << "1. Print all heroes" << endl;
	cout << "2. Hero with the most items" << endl;
	cout << "3. Strongest hero" << endl;
	cout << "4. Heroes with greater than 18 intelligence" << endl;
	cout << "5. 2 clumsiest heroes" << endl;
	cout << "6. Hero with the most valuable stuff" << endl;
	cout << endl;

}
int main()
{
	int inventoryParser = 0;
	int characterCount;
	int characterNumber = 1;
	//information per character
	//variables
	int nameLength;
	short strength;
	short intelligence;
	short agility;
	int hitpoints;
	int maxHitpoints;
	float physicalArmor;
	float magicalArmor;
	//information per character's inventory 
	int inventorySize;
	int countNumber = 1;
	int inventoryNameSize;
	int itemValue;
	float itemWeight;
	int menuChoice;
	int fileChoice;
	//vectors
	vector<string> characterNames;
	vector<short> Strength;
	vector<short> Intelligence;
	vector<short> Agility;
	vector<int> Hitpoints;
	vector<int> MaxHit;
	vector<float> PhysicalArmor;
	vector<float> MagicalArmor;
	vector<int> InventorySize;
	vector<string> inventoryNames;
	vector<int> ItemValue;
	vector<float> ItemWeight;

	menuDisplay();
	cin >> menuChoice;

	if (menuChoice == 1) {
		ifstream file("fantasyheroes.dat", ios_base::binary);
		fileDisplay();
		cin >> fileChoice;
		//FIXME options 
		//1 everything DONE
		//2 heros with the most items DONE
		//3 strongest hero DONE
		//4 greater than 18 intelligence 1 DOESNT TEST IT?
		//5 2 clumsiest heroes DONE
		//6 most valuable stuff 

		//number of characters present 
		file.read((char *)&characterCount, 4);
		//keep reading the file until no characters are left 
		while (characterNumber <= characterCount) {
			file.read((char *)&nameLength, 4);
			char *name = new char[nameLength];
			//getting the name of the character
			for (int i = 0; i < nameLength; i++) {
				file.read((char *)&name[i], 1);
			}
			characterNames.push_back(name);
			//reading and storing the data 
			file.read((char*)&strength, 2);
			file.read((char *)&intelligence, 2);
			file.read((char *)&agility, 2);
			file.read((char *)&hitpoints, 4);
			file.read((char *)&maxHitpoints, 4);
			file.read((char *)&physicalArmor, 4);
			file.read((char *)&magicalArmor, 4);
			file.read((char *)&inventorySize, 4);

			//storing the information
			Strength.push_back(strength);
			Intelligence.push_back(intelligence);
			Agility.push_back(agility);
			Hitpoints.push_back(hitpoints);
			MaxHit.push_back(maxHitpoints);
			PhysicalArmor.push_back(physicalArmor);
			MagicalArmor.push_back(magicalArmor);
			InventorySize.push_back(inventorySize);

			//handling inventory 
			while (countNumber <= inventorySize) {
				file.read((char *)&inventoryNameSize, 4);
				char *itemName = new char[inventoryNameSize];
				for (int i = 0; i < inventoryNameSize; i++) {
					file.read((char *)&itemName[i], 1);
				}
				file.read((char *)&itemValue, 4);
				file.read((char *)&itemWeight, 4);
				countNumber++;

				//storing data 
				inventoryNames.push_back(itemName);
				ItemValue.push_back(itemValue);
				ItemWeight.push_back(itemWeight);
			}
			characterNumber++;
			countNumber = 1;
		}
		//print everything 
		if (fileChoice == 1) {
			for (unsigned int i = 0; i < characterNames.size(); i++) {
				cout << "Name: ";
				cout << characterNames.at(i) << endl;
				cout << "Str: " << Strength.at(i) << endl;
				cout << "Int: " << Intelligence.at(i) << endl;
				cout << "Agi: " << Agility.at(i) << endl;
				cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
				cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
				cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
				cout << "Inventory: " << endl;
				if (InventorySize.at(i) == 0) {
					cout << "   " << "Inventory empty." << endl;
				}
				else {
					int indexCount = inventoryParser + InventorySize.at(i);
					//grab the total number of items per character 
					for (int index = inventoryParser; index < indexCount; index++) {
						cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
						inventoryParser++;
					}
				}
				cout << endl;

			}
		}
		//hero with the most items 
		else if (fileChoice == 2) {
			int max = InventorySize.at(0);
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				if (max < InventorySize.at(i)) {
					max = InventorySize.at(i);
				}
			}
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				if (InventorySize.at(i) == max) {
					cout << "Name: ";
					cout << characterNames.at(i) << endl;
					cout << "Str: " << Strength.at(i) << endl;
					cout << "Int: " << Intelligence.at(i) << endl;
					cout << "Agi: " << Agility.at(i) << endl;
					cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
					cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
					cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
					cout << "Inventory: " << endl;
					if (InventorySize.at(i) == 0) {
						cout << "   " << "Inventory empty." << endl;
					}
					else {
						int indexCount = i + InventorySize.at(i);
						//grab the total number of items per character 
						for (int index = i + 1; index <= indexCount; index++) {
							cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
						}
						cout << endl;
					}
				}
			}
		}
		//strongest hero 
		else if (fileChoice == 3) {
			unsigned int index = 0;
			int max = Strength.at(0);
			for (unsigned int i = 0; i < Strength.size(); i++) {
				if (max < Strength.at(i)) {
					max = Strength.at(i);
					index = i;
				}
			}
			cout << "Name: ";
			cout << characterNames.at(index) << endl;
			cout << "Str: " << Strength.at(index) << endl;
			cout << "Int: " << Intelligence.at(index) << endl;
			cout << "Agi: " << Agility.at(index) << endl;
			cout << "HP: " << Hitpoints.at(index) << " / " << MaxHit.at(index) << endl;
			cout << "Armor: " << PhysicalArmor.at(index) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				//grab the total number of items per character 
				for (unsigned int i = index; i < index + InventorySize.at(index); i++) {
					cout << "   " << inventoryNames.at(i) << ", " << ItemValue.at(i) << ", " << ItemWeight.at(i) << endl;
				}
				cout << endl;
			}
		}
		//greater than 18 intelligence 
		else if (fileChoice == 4) {
			for (unsigned int i = 0; i < characterNames.size(); i++) {
				inventoryParser += InventorySize.at(i);
				if (Intelligence.at(i) > 18) {
					cout << "Name: ";
					cout << characterNames.at(i) << endl;
					cout << "Str: " << Strength.at(i) << endl;
					cout << "Int: " << Intelligence.at(i) << endl;
					cout << "Agi: " << Agility.at(i) << endl;
					cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
					cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
					cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
					cout << "Inventory: " << endl;
					if (InventorySize.at(i) == 0) {
						cout << "   " << "Inventory empty." << endl;
					}
					else {
						inventoryParser -= InventorySize.at(i);
						int indexCount = inventoryParser + InventorySize.at(i);
						//grab the total number of items per character 
						for (int index = inventoryParser; index < indexCount; index++) {
							cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;

						}
					}
					cout << endl;

				}
			}
		}
		//two clumsiest heroes lowest agility 
		else if (fileChoice == 5) {
			int min1 = Agility.at(0);
			//int min2 = 0;
			int index = 0;
			int index2 = 0;
			for (unsigned int i = 0; i < Agility.size(); i++) {
				if (min1 > Agility.at(i)) {
					//min2 = min1;
					min1 = Agility.at(i);
					index2 = index;
					index = i;
				}
			}
			for (int i = 0; i < index; i++) {
				inventoryParser += InventorySize.at(i);
			}
			cout << "Clumsiest hero:" << endl;
			cout << "Name: ";
			cout << characterNames.at(index) << endl;
			cout << "Str: " << Strength.at(index) << endl;
			cout << "Int: " << Intelligence.at(index) << endl;
			cout << "Agi: " << Agility.at(index) << endl;
			cout << "HP: " << Hitpoints.at(index) << " / " << MaxHit.at(index) << endl;
			cout << "Armor: " << PhysicalArmor.at(index) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				int indexCount = inventoryParser + InventorySize.at(index);
				//grab the total number of items per character 
				for (int index = inventoryParser; index < indexCount; index++) {
					cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
					inventoryParser++;
				}
			}
			cout << endl;
			inventoryParser = 0;
			for (int i = 0; i < index2; i++) {
				inventoryParser += InventorySize.at(i);
			}
			cout << "Second clumsiest hero: " << endl;
			cout << "Name: ";
			cout << characterNames.at(index2) << endl;
			cout << "Str: " << Strength.at(index2) << endl;
			cout << "Int: " << Intelligence.at(index2) << endl;
			cout << "Agi: " << Agility.at(index2) << endl;
			cout << "HP: " << Hitpoints.at(index2) << " / " << MaxHit.at(index2) << endl;
			cout << "Armor: " << PhysicalArmor.at(index2) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index2) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index2) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				int indexCount = inventoryParser + InventorySize.at(index2);
				//grab the total number of items per character 
				for (int index = inventoryParser; index < indexCount; index++) {
					cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
					inventoryParser++;
				}
			}
			cout << endl;


		}
		//most valuable stuff 
		else if (fileChoice == 6) {
			int max = 0;
			int val = 0;
			int locationItems = 0;
			int locationNaming = 0;
			unsigned int parsing = 0;
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				for (unsigned int index = parsing; index < parsing + InventorySize.at(i); index++) {
					val += ItemValue.at(index);
				}
				parsing += InventorySize.at(i);
				if (val > max) {
					max = val;
					locationItems = parsing - InventorySize.at(i);
					locationNaming = i;
				}
				val = 0;
			}
			cout << "Name: ";
			cout << characterNames.at(locationNaming) << endl;
			cout << "Str: " << Strength.at(locationNaming) << endl;
			cout << "Int: " << Intelligence.at(locationNaming) << endl;
			cout << "Agi: " << Agility.at(locationNaming) << endl;
			cout << "HP: " << Hitpoints.at(locationNaming) << " / " << MaxHit.at(locationNaming) << endl;
			cout << "Armor: " << PhysicalArmor.at(locationNaming) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(locationNaming) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			for (int i = locationItems; i < locationItems + InventorySize.at(locationNaming); i++) {
				cout << "   " << inventoryNames.at(i) << ", " << ItemValue.at(i) << ", " << ItemWeight.at(i) << endl;
			}
			cout << endl;


		}
	}
	if (menuChoice == 2) {
		ifstream file("superheroes.dat", ios_base::binary);
		fileDisplay();
		cin >> fileChoice;
		//FIXME options 
		//1 everything DONE
		//2 heros with the most items DONE
		//3 strongest hero DONE
		//4 greater than 18 intelligence 1 DOESNT TEST IT?
		//5 2 clumsiest heroes DONE
		//6 most valuable stuff 

		//number of characters present 
		file.read((char *)&characterCount, 4);
		//keep reading the file until no characters are left 
		while (characterNumber <= characterCount) {
			file.read((char *)&nameLength, 4);
			char *name = new char[nameLength];
			//getting the name of the character
			for (int i = 0; i < nameLength; i++) {
				file.read((char *)&name[i], 1);
			}
			characterNames.push_back(name);
			//reading and storing the data 
			file.read((char*)&strength, 2);
			file.read((char *)&intelligence, 2);
			file.read((char *)&agility, 2);
			file.read((char *)&hitpoints, 4);
			file.read((char *)&maxHitpoints, 4);
			file.read((char *)&physicalArmor, 4);
			file.read((char *)&magicalArmor, 4);
			file.read((char *)&inventorySize, 4);

			//storing the information
			Strength.push_back(strength);
			Intelligence.push_back(intelligence);
			Agility.push_back(agility);
			Hitpoints.push_back(hitpoints);
			MaxHit.push_back(maxHitpoints);
			PhysicalArmor.push_back(physicalArmor);
			MagicalArmor.push_back(magicalArmor);
			InventorySize.push_back(inventorySize);

			//handling inventory 
			while (countNumber <= inventorySize) {
				file.read((char *)&inventoryNameSize, 4);
				char *itemName = new char[inventoryNameSize];
				for (int i = 0; i < inventoryNameSize; i++) {
					file.read((char *)&itemName[i], 1);
				}
				file.read((char *)&itemValue, 4);
				file.read((char *)&itemWeight, 4);
				countNumber++;

				//storing data 
				inventoryNames.push_back(itemName);
				ItemValue.push_back(itemValue);
				ItemWeight.push_back(itemWeight);
			}
			characterNumber++;
			countNumber = 1;
		}
		//print everything 
		if (fileChoice == 1) {
			for (unsigned int i = 0; i < characterNames.size(); i++) {
				cout << "Name: ";
				cout << characterNames.at(i) << endl;
				cout << "Str: " << Strength.at(i) << endl;
				cout << "Int: " << Intelligence.at(i) << endl;
				cout << "Agi: " << Agility.at(i) << endl;
				cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
				cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
				cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
				cout << "Inventory: " << endl;
				if (InventorySize.at(i) == 0) {
					cout << "   " << "Inventory empty." << endl;
				}
				else {
					int indexCount = inventoryParser + InventorySize.at(i);
					//grab the total number of items per character 
					for (int index = inventoryParser; index < indexCount; index++) {
						cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
						inventoryParser++;
					}
				}
				cout << endl;

			}
		}
		//hero with the most items 
		else if (fileChoice == 2) {
			int max = InventorySize.at(0);
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				if (max < InventorySize.at(i)) {
					max = InventorySize.at(i);
				}
			}
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				if (InventorySize.at(i) == max) {
					cout << "Name: ";
					cout << characterNames.at(i) << endl;
					cout << "Str: " << Strength.at(i) << endl;
					cout << "Int: " << Intelligence.at(i) << endl;
					cout << "Agi: " << Agility.at(i) << endl;
					cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
					cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
					cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
					cout << "Inventory: " << endl;
					if (InventorySize.at(i) == 0) {
						cout << "   " << "Inventory empty." << endl;
					}
					else {
						int indexCount = i + InventorySize.at(i);
						//grab the total number of items per character 
						for (int index = i + 1; index <= indexCount; index++) {
							cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
						}
						cout << endl;
					}
				}
			}
		}
		//strongest hero 
		else if (fileChoice == 3) {
			unsigned int index = 0;
			int max = Strength.at(0);
			for (unsigned int i = 0; i < Strength.size(); i++) {
				if (max < Strength.at(i)) {
					max = Strength.at(i);
					index = i;
				}
			}
			cout << "Name: ";
			cout << characterNames.at(index) << endl;
			cout << "Str: " << Strength.at(index) << endl;
			cout << "Int: " << Intelligence.at(index) << endl;
			cout << "Agi: " << Agility.at(index) << endl;
			cout << "HP: " << Hitpoints.at(index) << " / " << MaxHit.at(index) << endl;
			cout << "Armor: " << PhysicalArmor.at(index) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				//grab the total number of items per character 
				for (unsigned int i = index; i < index + InventorySize.at(index); i++) {
					cout << "   " << inventoryNames.at(i) << ", " << ItemValue.at(i) << ", " << ItemWeight.at(i) << endl;
				}
				cout << endl;
			}
		}
		//greater than 18 intelligence 
		else if (fileChoice == 4) {
			for (unsigned int i = 0; i < characterNames.size(); i++) {
				inventoryParser += InventorySize.at(i);
				if (Intelligence.at(i) > 18) {
					cout << "Name: ";
					cout << characterNames.at(i) << endl;
					cout << "Str: " << Strength.at(i) << endl;
					cout << "Int: " << Intelligence.at(i) << endl;
					cout << "Agi: " << Agility.at(i) << endl;
					cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
					cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
					cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
					cout << "Inventory: " << endl;
					if (InventorySize.at(i) == 0) {
						cout << "   " << "Inventory empty." << endl;
					}
					else {
						inventoryParser -= InventorySize.at(i);
						int indexCount = inventoryParser + InventorySize.at(i);
						//grab the total number of items per character 
						for (int index = inventoryParser; index < indexCount; index++) {
							cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;

						}
					}
					cout << endl;

				}
			}
		}
		//two clumsiest heroes lowest agility 
		else if (fileChoice == 5) {
			int min1 = Agility.at(0);
			//int min2 = 0;
			int index = 0;
			int index2 = 0;
			for (unsigned int i = 0; i < Agility.size(); i++) {
				if (min1 > Agility.at(i)) {
					//min2 = min1;
					min1 = Agility.at(i);
					index2 = index;
					index = i;
				}
			}
			for (int i = 0; i < index; i++) {
				inventoryParser += InventorySize.at(i);
			}
			cout << "Clumsiest hero:" << endl;
			cout << "Name: ";
			cout << characterNames.at(index) << endl;
			cout << "Str: " << Strength.at(index) << endl;
			cout << "Int: " << Intelligence.at(index) << endl;
			cout << "Agi: " << Agility.at(index) << endl;
			cout << "HP: " << Hitpoints.at(index) << " / " << MaxHit.at(index) << endl;
			cout << "Armor: " << PhysicalArmor.at(index) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				int indexCount = inventoryParser + InventorySize.at(index);
				//grab the total number of items per character 
				for (int index = inventoryParser; index < indexCount; index++) {
					cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
					inventoryParser++;
				}
			}
			cout << endl;
			inventoryParser = 0;
			for (int i = 0; i < index2; i++) {
				inventoryParser += InventorySize.at(i);
			}
			cout << "Second clumsiest hero: " << endl;
			cout << "Name: ";
			cout << characterNames.at(index2) << endl;
			cout << "Str: " << Strength.at(index2) << endl;
			cout << "Int: " << Intelligence.at(index2) << endl;
			cout << "Agi: " << Agility.at(index2) << endl;
			cout << "HP: " << Hitpoints.at(index2) << " / " << MaxHit.at(index2) << endl;
			cout << "Armor: " << PhysicalArmor.at(index2) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index2) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index2) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				int indexCount = inventoryParser + InventorySize.at(index2);
				//grab the total number of items per character 
				for (int index = inventoryParser; index < indexCount; index++) {
					cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
					inventoryParser++;
				}
			}
			cout << endl;


		}
		//most valuable stuff 
		else if (fileChoice == 6) {
			int max = 0;
			int val = 0;
			int locationItems = 0;
			int locationNaming = 0;
			unsigned int parsing = 0;
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				for (unsigned int index = parsing; index < parsing + InventorySize.at(i); index++) {
					val += ItemValue.at(index);
				}
				parsing += InventorySize.at(i);
				if (val > max) {
					max = val;
					locationItems = parsing - InventorySize.at(i);
					locationNaming = i;
				}
				val = 0;
			}
			cout << "Name: ";
			cout << characterNames.at(locationNaming) << endl;
			cout << "Str: " << Strength.at(locationNaming) << endl;
			cout << "Int: " << Intelligence.at(locationNaming) << endl;
			cout << "Agi: " << Agility.at(locationNaming) << endl;
			cout << "HP: " << Hitpoints.at(locationNaming) << " / " << MaxHit.at(locationNaming) << endl;
			cout << "Armor: " << PhysicalArmor.at(locationNaming) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(locationNaming) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			for (int i = locationItems; i < locationItems + InventorySize.at(locationNaming); i++) {
				cout << "   " << inventoryNames.at(i) << ", " << ItemValue.at(i) << ", " << ItemWeight.at(i) << endl;
			}
			cout << endl;


		}


	}
	if (menuChoice == 3) {
		fileDisplay();
		cin >> fileChoice;
		ifstream file("fantasyheroes.dat", ios_base::binary);
		ifstream file2("superheroes.dat", ios_base::binary);
		file.read((char *)&characterCount, 4);
		//keep reading the file until no characters are left 
		while (characterNumber <= characterCount) {
			file.read((char *)&nameLength, 4);
			char *name = new char[nameLength];
			//getting the name of the character
			for (int i = 0; i < nameLength; i++) {
				file.read((char *)&name[i], 1);
			}
			characterNames.push_back(name);
			//reading and storing the data 
			file.read((char*)&strength, 2);
			file.read((char *)&intelligence, 2);
			file.read((char *)&agility, 2);
			file.read((char *)&hitpoints, 4);
			file.read((char *)&maxHitpoints, 4);
			file.read((char *)&physicalArmor, 4);
			file.read((char *)&magicalArmor, 4);
			file.read((char *)&inventorySize, 4);

			//storing the information
			Strength.push_back(strength);
			Intelligence.push_back(intelligence);
			Agility.push_back(agility);
			Hitpoints.push_back(hitpoints);
			MaxHit.push_back(maxHitpoints);
			PhysicalArmor.push_back(physicalArmor);
			MagicalArmor.push_back(magicalArmor);
			InventorySize.push_back(inventorySize);

			//handling inventory 
			while (countNumber <= inventorySize) {
				file.read((char *)&inventoryNameSize, 4);
				char *itemName = new char[inventoryNameSize];
				for (int i = 0; i < inventoryNameSize; i++) {
					file.read((char *)&itemName[i], 1);
				}
				file.read((char *)&itemValue, 4);
				file.read((char *)&itemWeight, 4);
				countNumber++;

				//storing data 
				inventoryNames.push_back(itemName);
				ItemValue.push_back(itemValue);
				ItemWeight.push_back(itemWeight);
			}
			characterNumber++;
			countNumber = 1;
		}
		file2.read((char *)&characterCount, 4);
		characterNumber = 1;
		//keep reading the file until no characters are left 
		while (characterNumber <= characterCount) {
			file2.read((char *)&nameLength, 4);
			char *name = new char[nameLength];
			//getting the name of the character
			for (int i = 0; i < nameLength; i++) {
				file2.read((char *)&name[i], 1);
			}
			characterNames.push_back(name);
			//reading and storing the data 
			file2.read((char*)&strength, 2);
			file2.read((char *)&intelligence, 2);
			file2.read((char *)&agility, 2);
			file2.read((char *)&hitpoints, 4);
			file2.read((char *)&maxHitpoints, 4);
			file2.read((char *)&physicalArmor, 4);
			file2.read((char *)&magicalArmor, 4);
			file2.read((char *)&inventorySize, 4);

			//storing the information
			Strength.push_back(strength);
			Intelligence.push_back(intelligence);
			Agility.push_back(agility);
			Hitpoints.push_back(hitpoints);
			MaxHit.push_back(maxHitpoints);
			PhysicalArmor.push_back(physicalArmor);
			MagicalArmor.push_back(magicalArmor);
			InventorySize.push_back(inventorySize);

			//handling inventory 
			while (countNumber <= inventorySize) {
				file2.read((char *)&inventoryNameSize, 4);
				char *itemName = new char[inventoryNameSize];
				for (int i = 0; i < inventoryNameSize; i++) {
					file2.read((char *)&itemName[i], 1);
				}
				file2.read((char *)&itemValue, 4);
				file2.read((char *)&itemWeight, 4);
				countNumber++;

				//storing data 
				inventoryNames.push_back(itemName);
				ItemValue.push_back(itemValue);
				ItemWeight.push_back(itemWeight);
			}
			characterNumber++;
			countNumber = 1;
		}
		if (fileChoice == 1) {
			for (unsigned int i = 0; i < characterNames.size(); i++) {
				cout << "Name: ";
				cout << characterNames.at(i) << endl;
				cout << "Str: " << Strength.at(i) << endl;
				cout << "Int: " << Intelligence.at(i) << endl;
				cout << "Agi: " << Agility.at(i) << endl;
				cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
				cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
				cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
				cout << "Inventory: " << endl;
				if (InventorySize.at(i) == 0) {
					cout << "   " << "Inventory empty." << endl;
				}
				else {
					int indexCount = inventoryParser + InventorySize.at(i);
					//grab the total number of items per character 
					for (int index = inventoryParser; index < indexCount; index++) {
						cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
						inventoryParser++;
					}
				}
				cout << endl;

			}
		}
		//hero with the most items 
		else if (fileChoice == 2) {
			int max = InventorySize.at(0);
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				if (max < InventorySize.at(i)) {
					max = InventorySize.at(i);
				}
			}
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				if (InventorySize.at(i) == max) {
					cout << "Name: ";
					cout << characterNames.at(i) << endl;
					cout << "Str: " << Strength.at(i) << endl;
					cout << "Int: " << Intelligence.at(i) << endl;
					cout << "Agi: " << Agility.at(i) << endl;
					cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
					cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
					cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
					cout << "Inventory: " << endl;
					if (InventorySize.at(i) == 0) {
						cout << "   " << "Inventory empty." << endl;
					}
					else {
						int indexCount = i + InventorySize.at(i);
						//grab the total number of items per character 
						for (int index = i + 1; index <= indexCount; index++) {
							cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
						}
						cout << endl;
					}
				}
			}
		}
		//strongest hero 
		else if (fileChoice == 3) {
			unsigned int parsing = 0;
			unsigned int index = 0;
			int max = Strength.at(0);
			for (unsigned int i = 0; i < Strength.size(); i++) {
				if (max < Strength.at(i)) {
					max = Strength.at(i);
					index = i;
				}
			}
			for (unsigned int i = 0; i < index; i++) {
				parsing += InventorySize.at(i);
			}
			cout << "Name: ";
			cout << characterNames.at(index) << endl;
			cout << "Str: " << Strength.at(index) << endl;
			cout << "Int: " << Intelligence.at(index) << endl;
			cout << "Agi: " << Agility.at(index) << endl;
			cout << "HP: " << Hitpoints.at(index) << " / " << MaxHit.at(index) << endl;
			cout << "Armor: " << PhysicalArmor.at(index) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				//grab the total number of items per character 
				for (unsigned int i = parsing; i < parsing + InventorySize.at(index); i++) {
					cout << "   " << inventoryNames.at(i) << ", " << ItemValue.at(i) << ", " << ItemWeight.at(i) << endl;
				}
				cout << endl;
			}
		}
		//greater than 18 intelligence 
		else if (fileChoice == 4) {
			for (unsigned int i = 0; i < characterNames.size(); i++) {
				inventoryParser += InventorySize.at(i);
				if (Intelligence.at(i) > 18) {
					cout << "Name: ";
					cout << characterNames.at(i) << endl;
					cout << "Str: " << Strength.at(i) << endl;
					cout << "Int: " << Intelligence.at(i) << endl;
					cout << "Agi: " << Agility.at(i) << endl;
					cout << "HP: " << Hitpoints.at(i) << " / " << MaxHit.at(i) << endl;
					cout << "Armor: " << PhysicalArmor.at(i) * 100 << "%" << endl;
					cout << "Magic armor: " << MagicalArmor.at(i) * 100 << "%" << endl;
					cout << "Inventory: " << endl;
					if (InventorySize.at(i) == 0) {
						cout << "   " << "Inventory empty." << endl;
						inventoryParser++;
					}
					else {
						//inventoryParser-=InventorySize.at(i);
						//grab the total number of items per character 
						int val = inventoryParser - InventorySize.at(i);
						for (int index = val; index < inventoryParser; index++) {
							cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;

						}
					}
					cout << endl;

				}
			}
		}
		//two clumsiest heroes lowest agility 
		else if (fileChoice == 5) {
			int min1 = Agility.at(0);
			int min2 = 0;
			int index = 0;
			int index2 = 0;
			for (unsigned int i = 0; i < Agility.size(); i++) {
				if (min1 > Agility.at(i)) {
					min2 = min1;
					min1 = Agility.at(i);
					index2 = index;
					index = i;
				}
				if (min2 > Agility.at(i) && min2 > min1) {
					index2 = i;
				}
			}
			for (int i = 0; i < index; i++) {
				inventoryParser += InventorySize.at(i);
			}
			cout << "Clumsiest hero:" << endl;
			cout << "Name: ";
			cout << characterNames.at(index) << endl;
			cout << "Str: " << Strength.at(index) << endl;
			cout << "Int: " << Intelligence.at(index) << endl;
			cout << "Agi: " << Agility.at(index) << endl;
			cout << "HP: " << Hitpoints.at(index) << " / " << MaxHit.at(index) << endl;
			cout << "Armor: " << PhysicalArmor.at(index) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				int indexCount = inventoryParser + InventorySize.at(index);
				//grab the total number of items per character 
				for (int index = inventoryParser; index < indexCount; index++) {
					cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
					inventoryParser++;
				}
			}
			cout << endl;
			inventoryParser = 0;
			for (int i = 0; i < index2; i++) {
				inventoryParser += InventorySize.at(i);
			}
			cout << "Second clumsiest hero: " << endl;
			cout << "Name: ";
			cout << characterNames.at(index2) << endl;
			cout << "Str: " << Strength.at(index2) << endl;
			cout << "Int: " << Intelligence.at(index2) << endl;
			cout << "Agi: " << Agility.at(index2) << endl;
			cout << "HP: " << Hitpoints.at(index2) << " / " << MaxHit.at(index2) << endl;
			cout << "Armor: " << PhysicalArmor.at(index2) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(index2) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			if (InventorySize.at(index2) == 0) {
				cout << "   " << "Inventory empty." << endl;
			}
			else {
				int indexCount = inventoryParser + InventorySize.at(index2);
				//grab the total number of items per character 
				for (int index = inventoryParser; index < indexCount; index++) {
					cout << "   " << inventoryNames.at(index) << ", " << ItemValue.at(index) << ", " << ItemWeight.at(index) << endl;
					inventoryParser++;
				}
			}
			cout << endl;


		}
		//most valuable stuff 
		else if (fileChoice == 6) {
			int max = 0;
			int val = 0;
			int locationItems = 0;
			int locationNaming = 0;
			unsigned int parsing = 0;
			for (unsigned int i = 0; i < InventorySize.size(); i++) {
				for (unsigned int index = parsing; index < parsing + InventorySize.at(i); index++) {
					val += ItemValue.at(index);
				}
				parsing += InventorySize.at(i);
				if (val > max) {
					max = val;
					locationItems = parsing - InventorySize.at(i);
					locationNaming = i;
				}
				val = 0;
			}
			cout << "Name: ";
			cout << characterNames.at(locationNaming) << endl;
			cout << "Str: " << Strength.at(locationNaming) << endl;
			cout << "Int: " << Intelligence.at(locationNaming) << endl;
			cout << "Agi: " << Agility.at(locationNaming) << endl;
			cout << "HP: " << Hitpoints.at(locationNaming) << " / " << MaxHit.at(locationNaming) << endl;
			cout << "Armor: " << PhysicalArmor.at(locationNaming) * 100 << "%" << endl;
			cout << "Magic armor: " << MagicalArmor.at(locationNaming) * 100 << "%" << endl;
			cout << "Inventory: " << endl;
			for (int i = locationItems; i < locationItems + InventorySize.at(locationNaming); i++) {
				cout << "   " << inventoryNames.at(i) << ", " << ItemValue.at(i) << ", " << ItemWeight.at(i) << endl;
			}
			cout << endl;


		}



	}
}