//
// Created by B.User on 04/07/2022.
//
#include "models.h"
class MinistryService{

public:
    static vector<Location> returnAllLocations(){
        vector<Location> locations;
        ifstream file;
        file.open("locations.txt", ios::app);
        string line;
        string storedLine;
        while(getline(file, line)){
            stringstream ss(line);
            string token;
            Location location =  returnSingleLocation(line);
            locations.push_back(location);
        }
        file.close();
        return locations;
    }
    static vector<Disease> returnAllDiseases(){
        vector<Disease> diseases;
        ifstream file;
        file.open("diseases.txt", ios::app);
        string line;
        string storedLine;
        while(getline(file, line)){
            stringstream ss(line);
            string token;
            Disease disease =  returnSingleDisease(line);
            diseases.push_back(disease);
        }
        file.close();
        return diseases;
    }
    static int returnLastId(){
        vector<Location> all = returnAllLocations();
        int lastId = 0;
        for(auto & i : all){
            if(i.getId() > lastId){
                lastId = i.getId();
            }
        }
        return lastId;
    }
    static int returnLastIdFromDiseaseFile(){
        vector<Disease> all = returnAllDiseases();
        int lastId = 0;
        for(auto & i : all){
            if(i.getId() > lastId){
                lastId = i.getId();
            }
        }
        return lastId;
    }
    static void AddLocation(Location location) {
        ofstream file;
        file.open("locations.txt", ios::app);
        bool locationExists = locationExistsByName(location.getName());
        if (locationExists) {
            cout << "Location already exists" << endl;
            cout<<endl;
            exit(0);
        }
        int lastId = returnLastId();
        location.setId(lastId + 1);
        file << location.getId() << "  " << location.getName() << "  " << endl;
        cout << "Location "<<location.getName()<<" added successfully" << endl;
        file.close();
    }
    static bool locationExistsByName(string location){
        vector<Location> locations = returnAllLocations();
        bool exists = false;
        for(auto & i : locations){
            if(i.getName() == location){
                exists = true;
            }
            return exists;
            }
        return exists;
    }
    static Location returnSingleLocation(const string &line){
        stringstream ss(line);
        Location location;
        string item;
        int i=0;
        for(string rowElement; ss >> rowElement;) {

            if (reinterpret_cast<const char *>(rowElement[rowElement.length() - 1] ) == " ")
                rowElement.pop_back();

            if (i == 0) location.setId(stoi(rowElement));
            else if(i == 1) location.setName(rowElement);
            i++;
        }
        return location;
    }
    static Disease returnSingleDisease(const string &line){
        stringstream ss(line);
        Disease disease;
        string item;
        int i=0;
        for(string rowElement; ss >> rowElement;) {

            if (reinterpret_cast<const char *>(rowElement[rowElement.length() - 1] ) == " ")
                rowElement.pop_back();

            if (i == 0) disease.setId(stoi(rowElement));
            else if(i == 1) disease.setName(rowElement);
            else if(i == 2) disease.setLocationId(stoi(rowElement));
            else if(i == 3) disease.setNumberOfCases(stoi(rowElement));
            i++;
        }
        return disease;
    }
    static void deleteAnExistingLocation() {
        vector<Location> locations = returnAllLocations();
        cout<<endl<<endl;
        cout<<"  \t\t\t LIST OF LOCATIONS WE HAVE "<<endl;
        for(int i = 0; i < locations.size(); i++){
            cout<<" \t\t\t Location "<<i<<" "<<locations[i].getName()<<endl;
        }
        string name;
        cout << "     ENTER LOCATION NAME TO DELETE" << endl;
        cin >> name;
        for_each(name.begin(), name.end(), [](char &c){
            c = toupper(c);
        });
        bool locationExists = locationExistsByName(name);
        if(!locationExists){
            cout << "Location does not exist" << endl;
            cout<<endl;
            exit(0);
        }

        ifstream file("locations.txt");
        ofstream tempFile("temp.txt");
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            string token;
            if (line.find(name) != string::npos) {
                cout<<" You are going to delete "<<line<<endl;
            }else{
                tempFile << line << endl;
            }
        }
        file.close();
        tempFile.close();
        remove("locations.txt");
        rename("temp.txt", "locations.txt");
    }
    static bool checkIfAlocationExistsById(int id){
        bool exists = false;
        vector<Location> locations = returnAllLocations();
        for(auto & i : locations){
            if(i.getId() == id){
                exists = true;
                return exists;
            }
        }
        return exists;
    }
    static bool checkIfADiseaseExistsByName(string name){
        bool exists = false;
        vector<Disease> diseases = returnAllDiseases();
        for(auto & i : diseases){
            if(i.getName() == name){
                exists = true;
                return exists;
            }
        }
        return exists;
    }
    static Location getLocationByName(int id){
        vector<Location> locations = returnAllLocations();
        Location location;
        for(auto & i : locations){
            if(i.getId() == id){
                location = i;
                return location;
            }
        }
        return location;
    }
    static void recordAdiseaseAndItsCase(Disease disease){
        ofstream file;
        file.open("diseases.txt", ios::app);
        int lastId = returnLastIdFromDiseaseFile()+1;
        bool locationExists = checkIfAlocationExistsById(disease.getLocationId());
        if (!locationExists) {
            cout<<endl;
            cout << "\t\t Location you are trying to add does not exist" << endl;
            cout<<endl;
            exit(0);
        }
        bool diseaseExists = checkIfADiseaseExistsByName(disease.getName());
        if(diseaseExists){
            cout<<endl;
            cout << "\t Disease you are trying to add already exists" << endl;
            cout<<endl;
            exit(0);
        }
        if(disease.getNumberOfCases() <= 0){
            cout<<endl;
            cout << "\t Number of cases should be greater than 0" << endl;
            cout<<endl;
            exit(0);
        }
        Location location = getLocationByName(disease.getLocationId());
        Disease addDisease = Disease(lastId,disease.getName(), disease.getLocationId(), disease.getNumberOfCases());
       file << addDisease.getId() << "  " << addDisease.getName() << "  " << addDisease.getLocationId() << "  " << addDisease.getNumberOfCases() << endl;
        cout<<"\t\t "<<addDisease.getName()<<" has be added to "<<location.getName()<<" with "<<addDisease.getNumberOfCases()<<" cases successfully "<<endl;
        file.close();
    }

};