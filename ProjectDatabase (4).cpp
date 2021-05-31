#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>
#include <sstream>
using namespace std;

bool checkInputSizeIsOne(vector<char> cstr);
bool StringCheck(string requiredInput);
bool DateSyntaxCheck(string str, int amount, char DMY);
bool checkVarChar(string str);
bool isInputANumber(string str);
bool isIDValid(string str);

class VarChar {        // The class
public:          // Access specifier
    short int size;
    string payload; // Attribute
    VarChar(string y) { // Constructor with parameters
        payload = y;
        transform(payload.begin(), payload.end(), payload.begin(), ::tolower);
        size = payload.size();

        vector<char> cstr(payload.c_str(), payload.c_str() + size + 1);
    }
};

class user {
public:
    int ID;
    string name; //varchar
    string dOB;
    string address; //varchar
    string symptomLevel; //varchar
    string visitedLocation = "No"; //varchar
    string overSeas;
    int locationAmnt;
    string covidTestResult = "Negative";
    string Status = "Alive";
    bool recommendedTest = 0;
};

void Menu(bool returningUser);
void option1(bool updateData, int patientIDbefore);
void option2();
bool option3();
bool option4();
bool option5();

//Returns bool (0 = file failed to open, 1 = location successfully added to database)
bool enterHighRisk(string Location); //Function that when called enters the high risk locations into database.

// Output: 1 = true / 0 = false, 2 = file failed to open
int IsLocationHighRisk(string Location); //Detects if location is high risk from database should be lower case.

bool writeNewEntry(user currentUser); //Creates a new patient entry in database.
bool ReadSymptoms(); //Reads symptoms from symptoms database required for option 1.
bool readPatientEntry(int ID); //Reads a patient entry depending on the integer argument.
void patientInfoCopy(); //Creates backup of patientinfo required when updating entry.
bool updatePatientEntry(user currentUserWrite); //Updates entry depending on the ID.
bool IDexists(int ID); //checks id in database output: 0 = doesn't find, 1 = exists

//Updates the 3 entries
bool updatePatientStatus(int ID, string covidTestResult, string Status, string Locations);

int main()
{
    patientInfoCopy();
    //readPatientEntry(3);
    bool returningUser = 0;
	char entryOption;
	int e = 0;
	while (e < 1)
	{
		cout << "|||  COVID TEST RECOMMENDATION  |||" << endl << endl;
		cout << "Are you a returning user? y/n:\t";
		cin >> entryOption;
		switch (entryOption)
		{
		case 'n':
		case 'N':
			cout << "Welcome new user!" << endl << endl;
            returningUser = 1;
			Menu(returningUser);
			e++;
			break;
		case 'y':
		case 'Y':
			cout << "Please enter your COVID RESULTS by pressing 2 on the menu list.";
            returningUser = 0;
			Menu(returningUser);
			e++;
			break;
		default:
			cout << "Invalid Entry! please enter the character 'y' or 'n'!\n" << endl;
		}

	}

	return 0;
}

void Menu(bool returningUser)
{
	char menuEnt;
	cout << "|COVID RECOMMENDATION PROGRAM|" << endl << endl;
	cout << "1- Enter your detail for COVID-Test Recommendation" << endl;
	cout << "2- Submit Your Covid test status & Update the Location database" << endl;
	cout << "3- Display the Updated Location (High Risk for COVID)" << endl;
	cout << "4- Update COVID Patient Details" << endl;
	cout << "5- Display the COVID Positive Patient Detail" << endl;
	cout << "6- Quit" << endl;
	cout << endl;
	int ex = 0;
	while (ex < 1)
	{
		cout << "Enter your choice:\t" << endl;
		cin >> menuEnt;
		switch (menuEnt)
		{
		case '1':
			//statements to display for 1st menu option
			option1(0, 0);

			break;

		case '2':
			//statements to display for 2nd menu option
            option2();

			break;

		case '3':
			//statements to display for 3rd menu option
			option3();

			break;

		case '4':
			//statements to display for 4th menu option
            option4();

			break;

		case '5':
			//statements to display for 5th menu option
            option5();

			break;

		case '6':
			//statements to display for 6th menu option
            cout << "Goodbye" << endl;
            exit(0);

			break;

		default:
			cout << "Invalid Entry... please choose from the menu options above!" << endl;
		}
	}
}

void option1(bool updateData, int patientIDbefore)
{
    user currentUser;
    string state, suburb, street;
    // list of all integer variables used
    int symptomLevelCode = 1, locationAmnt;
    // variable purely for exit of the while loops used in conjunction with the case statements
    int ex1 = 0;

    string firstName = " "; //first name variable
    bool passedFirstName = false;
    string lastName; //last name variable
    bool passedLastName = false;
    string patientID = " "; //patientID variable
    bool passedPatientID = false;
    string dateOfBirth; //Date of Birth variable
    bool passeddateOfBirth = false;
    string addressS; //Address variable
    bool passedAddress = false;
    string symptomLevel; //symptom level variable
    string overSeas; // overseas variable
    bool recommendTest = false;

    string low = "low";
    string medium = "medium";
    string high = "high";
    VarChar lowRisk(low);
    VarChar mediumRisk(medium);
    VarChar highRisk(high);

    //First name input
    while (!passedFirstName) {
        cout << "Please enter your first name:\t " << endl;
        cin.ignore();
        getline(cin, firstName);

        if (checkVarChar(firstName)) {
            //assign varchar value
            passedFirstName = true;
        }
    }
    //Last name input
    while (!passedLastName) {
        cout << "Please enter your last name:\t " << endl;
        getline(cin, lastName);

        if (checkVarChar(lastName)) {
            //assign varchar value
            passedLastName = true;
        }
    }
    //assigning first name and last name to a VARCHAR
    string stringName = firstName + " " + lastName;
    VarChar name(stringName);
    currentUser.name = stringName;

    //ID input
    if (!updateData) {
        while (!passedPatientID) {
            cout << "Please create a unique 6 number ID:\t";
            cin >> patientID;

            if (isIDValid(patientID)) {
                passedPatientID = true;
            }
        }
        currentUser.ID = stoi(patientID);
    }
    else 
    {
        currentUser.ID = patientIDbefore;
    }

    bool passeddateOfBirthDay = 0;
    bool passeddateOfBirthMonth = 0;
    string checkUserDateIntYear = " ";
    bool passeddateOfBirthYear = 0;
    string checkUserDateIntDay = " ";
    string checkUserDateIntMonth = " ";

    cin.ignore();
    while (!passeddateOfBirthDay) {
        cout << "enter date of birth day (DD): " << endl;
        getline(cin, checkUserDateIntDay);
        if (DateSyntaxCheck(checkUserDateIntDay, 2, 'D')) {
            passeddateOfBirthDay = true;
        }
    }

    
    while (!passeddateOfBirthMonth) {
        cout << "enter date of birth month (MM): " << endl;
        getline(cin, checkUserDateIntMonth);
        if (DateSyntaxCheck(checkUserDateIntMonth, 2, 'M')) {
            passeddateOfBirthMonth = true;
        }
    }

    cout << "enter date of birth day (YYYY): " << endl;
    getline(cin, checkUserDateIntYear);
    do {
        if (DateSyntaxCheck(checkUserDateIntYear, 4, 'Y')) {
            cout << "input was accepted" << endl;
            passeddateOfBirthYear = true;
        }
        else {
            cout << "enter date of birth year (YYYY): " << endl;
            getline(cin, checkUserDateIntYear);
        }
    } while (!passeddateOfBirthYear);
    

    dateOfBirth = checkUserDateIntDay + "/" + checkUserDateIntMonth + "/" + checkUserDateIntYear;
    currentUser.dOB = dateOfBirth;
    //converting the string DOB to a integer as required for storage in the database
    

    //living address input
    while (!passedAddress) {
        cout << "Please enter your living address in format of (streetnumber streetname suburb state)" << endl;
        cout << "Address:\t";
        getline(cin, addressS);

        if (checkVarChar(addressS)) {
            //assign varchar value
            VarChar address(addressS);
            passedAddress = true;
        }
    }
    currentUser.address = addressS;

    while (ex1 < 1)
    {
        cout << "Have you travelled overseas recently? (yes/no):\t"; // input for if user did overseas travel
        cin >> overSeas;
        if ((overSeas == "yes") || (overSeas == "Yes") || (overSeas == "YES")) {
            transform(overSeas.begin(), overSeas.end(), overSeas.begin(), ::tolower);
            ex1++;
        }
        else if ((overSeas == "no") || (overSeas == "No") || (overSeas == "NO")) {
            transform(overSeas.begin(), overSeas.end(), overSeas.begin(), ::tolower);
            ex1++;
        }
        else {
            cout << "Invalid entry... Please enter 'yes' or 'no'!" << endl;
        }

    }
    currentUser.overSeas = overSeas;
    ex1--;
    // input for the level of symptoms the user is feeling
    cout << "What level of symptoms are you currently feeling?" << endl;
    ReadSymptoms();
    while (ex1 < 1)
    {
        /* while and case block like the previous blocks to make sure user only inputs integer 1, 2 or 3.
         Handles situation if input is invalid.
         */
        cout << "1 (low), 2 (medium) or 3 (high)?:\t";
        cin >> symptomLevelCode;
        switch (symptomLevelCode)
        {
        case 1:
            symptomLevel = low;
            ex1++;
            break;
        case 2:
            symptomLevel = medium;
            ex1++;
            break;
        case 3:
            symptomLevel = high;
            ex1++;
            break;
        default:
            cout << "Invalid entry... Please enter '1', '2', or '3'!" << endl;
        }
    }
    ex1--;
    currentUser.symptomLevel = symptomLevel;

    cout << "If applicable, how many of these high risk Covid locations have you visted recently?" << endl;
    cout << "input 0 if you have visted none." << endl;
    option3();
    cout << "Amount of locations:\t";
    cin >> locationAmnt;
    currentUser.locationAmnt = locationAmnt;

    cout << endl;

    /*
     Algorithim of if the user needs a covid test or not
     */
    cout << "Based on your results," << endl;
    cout << "You are suffering " << symptomLevel << " level symptoms, and have visted " << locationAmnt << " high-risk Covid location sites." << endl << endl;
    if (symptomLevelCode == 3)
    {
        cout << "You require an URGENT Covid test! IMMEDIATELY LOCATE TO YOUR NEAREST TESTING SITE!" << endl;
        cout << endl;
        recommendTest = true;
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();
        cout << endl;
        cout << "Precautions to take:" << endl;
        cout << "- Isolate yourself at home until you recover!" << endl;
        cout << "- Avoid contact with other individuals!" << endl;
        cout << "- Wear a surgical or resuable mask when around other individuals keeping a safe distance." << endl;
        cout << "- Seek medical attention if the symptoms persist and start to impact your overall health." << endl;
        cout << endl;
        cout << "Come back to the program after your results are recieved to enter your results into menu option 2." << endl;
        currentUser.recommendedTest = recommendTest;

    }
    else if (locationAmnt >= 1)
    {
        cout << "You require a COVID test! on the basis of having been to high risk covid locations and experiencing your level of symptoms." << endl;
        cout << endl;
        recommendTest = true;
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();
        cout << endl;
        cout << "Precautions to take:" << endl;
        cout << "- Isolate yourself at home until you recover" << endl;
        cout << "- Avoid contact with other individuals" << endl;
        cout << "- Seek medical attention if the symptoms are alarmingly impacting your health!" << endl;
        cout << endl;
        cout << "Come back to the program after your results are recieved to enter your results into menu option 2." << endl;
        currentUser.recommendedTest = recommendTest;
    }
    else if ((symptomLevelCode < 3) && (locationAmnt == 0))
    {
        cout << "You DON'T need to acquire a COVID test but urgently need to follow the following precautions" << endl;
        cout << endl;
        recommendTest = false;
        cout << "Press Enter to continue..." << endl;
        cin.ignore();
        cin.get();
        cout << endl;
        cout << "Precautions to take:" << endl;
        cout << "- Isolate yourself at home until symptoms are cleared" << endl;
        cout << "- Avoid contact with other individuals" << endl;
        cout << "- Return to program if symptoms have increased!" << endl;
        cout << "- Seek medical attention if the symptoms are alarmingly impacting your health!" << endl;
        currentUser.recommendedTest = recommendTest;
    }
    if (updateData == 1) {
        updatePatientEntry(currentUser);
    }
    else {
        writeNewEntry(currentUser);
    }
    cout << endl;
    cout << "Press Enter to continue back to the main menu..." << endl;
    cin.get();
    cout << endl;
    Menu(0);
}

void option2()
{
    char reset = 0, ret, result, status;
    bool IDexistTest = 0;
    bool passedPatientID = 0;
    string patientID = " ";
    int ID;
    string locations = "No"; 

    while (reset < 1)
    {
        
        while (!passedPatientID) {
            cout << "Please enter your 6 number ID:\t";
            cin >> patientID;

            if (isIDValid(patientID)) {
                passedPatientID = true;
            }
        }

        ID = stoi(patientID);

        IDexistTest = IDexists(ID);
        if (IDexistTest)
        {
            cout << "Do you have the test results? (y/n):\t";
            cin >> ret;
            switch (ret)
            {
            case 'y':
                cout << "Were the results Positive(p) or Negative(n)?\t";
                cin >> result;
                cout << "Is the patient alive? (y/n)\t";
                cin >> status;
                if (result == 'p' and status == 'y')
                {
                    cout << "Please Isolate ASAP!\nYou must now wait 14 days and wait for symptoms to clear before returning outside.\n\nWe will need some more information from you\nPlaces that you have travelled to in the last 2 weeks are now potentially infectious.\n\nPlease provide the names of all places that you spent at least 15 minutes occupying:\n(seperate each entry with a comma, press enter when complete)\n";
                    cin.ignore();
                    getline(cin, locations);
                    string str = locations;
                    vector<string> v;
                    stringstream ss(str);
                    while (ss.good())
                    {
                        string substr;
                        getline(ss, substr, ',');
                        enterHighRisk(substr);
                    }
                    reset++;
                    break;
                }
                else if (result == 'n' and status == 'y')
                {
                    cout << "Perfect! Thanks for your assistance! Hope you feel better soon!";
                    reset++;
                    cout << "Press Enter to continue back to the main menu..." << endl;
                    cin.get();
                    Menu(0);
                }
                else if (status == 'n')
                {
                    cout << "Thats unfortunate to hear, please input the locations that the patient visited in the last 2 weeks:\n\nPlease provide the names of all places that they spent at least 15 minutes occupying:\n(seperate each entry with a comma, press enter when complete)\n";
                    cin.ignore();
                    getline(cin, locations);
                    string str = locations;
                    vector<string> v;

                    stringstream ss(str);

                    while (ss.good()) {
                        string substr;
                        getline(ss, substr, ',');
                        v.push_back(substr);
                    }

                    for (size_t i = 0; i < v.size(); i++)
                    {
                        //enterHighRisk(str);
                        //enterHighRisk(str);
                        //cout << str;
                    }
                    enterHighRisk(locations);
                }
                else
                {
                    cout << "Invalid entry... Please retry!" << endl;
                }
                reset++;
                break;
            case 'n':
                cout << "Please wait for your test results to arrive then return.\n";
                reset++;
                break;
            default:
                cout << "Invalid entry... Please enter 'y' (yes) or 'n' (no)!" << endl;
            }
            if (IDexistTest && (ret == 'y')) {
                updatePatientStatus(ID, ((result == 'p') ? "Positive" : "Negative"), ((status == 'y') ? "Alive" : "Dead"), locations);
            }
            
        }
        else
        {
            cout << "ID is not found please retry!\n";
            reset++;
        }

    }

    

}

bool option3() 
{
	ifstream HighRiskLocationsFileRead;

	HighRiskLocationsFileRead.open("HighRiskLocations.txt");

	if (HighRiskLocationsFileRead.fail())
	{
		cout << "\nFile failed to open successfully" << endl;
		return 0; //0 = failed to open error code.
	}

	string Location; //temporary location

	cout << "\nHigh risk locations for COVID:" << endl;

    //displays all the high risk locations to the user
	while (HighRiskLocationsFileRead.peek() != EOF)
	{
		getline(HighRiskLocationsFileRead, Location);

		cout << Location << endl;
	}

	cout << endl;

	HighRiskLocationsFileRead.close();
	return 1; //1 = code successfuly executed.
}

bool option4()
{
    string patientID = " ";
    string tempString = "1";
    bool passedPatientID = 0;

    while (!passedPatientID) {
        cout << "Please enter an ID:\t";
        cin >> patientID;

        if (isIDValid(patientID)) {
            passedPatientID = true;
        }
    }

    if (IDexists(stoi(patientID))) {
        option1(1, stoi(patientID));
        return 1;
    }

    cout << "Invalid ID" << endl;

}

bool option5() 
{
    string patientID = " ";
    string tempString = "1";
    bool passedPatientID = 0;

        while (!passedPatientID) //while ID is not of correct length/value
        {
            cout << "Please enter your 6 number ID:\t";
            cin >> patientID;

            if (isIDValid(patientID)) {
                passedPatientID = true;
            }
        }

        if (IDexists(stoi(patientID))) //if id exists in database
        {
            readPatientEntry(stoi(patientID)); //read patient entry
            return 1;
        }

        cout << "ID does not exist in the database" << endl;
}

bool updatePatientEntry(user currentUserWrite) 
{
    patientInfoCopy(); //create copy file
    ifstream PatientInfoFileRead;

    PatientInfoFileRead.open("PatientInfo.txt");

    if (PatientInfoFileRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    ifstream PatientInfoCopyRead;

    PatientInfoCopyRead.open("PatientInfoCopy.txt");

    if (PatientInfoCopyRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    string idString = to_string(currentUserWrite.ID);
    string lineToRead;
    int lineCount = 0;
    bool IDfound = 0;

    while ((PatientInfoFileRead.peek() != EOF) || (IDfound == 0))
    {
        getline(PatientInfoFileRead, lineToRead);
        lineCount++;

        if (lineToRead == ("ID= " + idString))
        {
            IDfound = 1;
            break;
        }
    }

    PatientInfoFileRead.close(); 

    if (IDfound == 0) {
        cout << "Incorrect ID" << endl;
        return 0;
    }

    ofstream PatientInfoFileWrite;

    PatientInfoFileWrite.open("PatientInfo.txt");

    if (PatientInfoFileWrite.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    int currentLine = 1;
    string lineToRead2;

    if (IDfound) 
    {
        while ((PatientInfoCopyRead.peek() != EOF))
        {
            if (currentLine == lineCount) //if current line is the begining of correct entry
            {
                //rewrite entry
                PatientInfoFileWrite << "ID= " << currentUserWrite.ID << endl;
                PatientInfoFileWrite << currentUserWrite.name << endl;
                PatientInfoFileWrite << currentUserWrite.dOB << endl;
                PatientInfoFileWrite << currentUserWrite.address << endl;
                PatientInfoFileWrite << currentUserWrite.symptomLevel << endl;
                PatientInfoFileWrite << currentUserWrite.visitedLocation << endl;
                PatientInfoFileWrite << currentUserWrite.overSeas << endl;
                PatientInfoFileWrite << currentUserWrite.locationAmnt << endl;
                PatientInfoFileWrite << currentUserWrite.covidTestResult << endl;
                PatientInfoFileWrite << currentUserWrite.Status << endl;
                PatientInfoFileWrite << currentUserWrite.recommendedTest << endl;

                for (int i = 0; i < 11; i++) //skip 11 lines in copy file
                {
                    getline(PatientInfoCopyRead, lineToRead2);
                    currentLine++;
                    
                }
                continue; //return to begining of while loop
            }

            //copy from backup
            getline(PatientInfoCopyRead, lineToRead2);
            PatientInfoFileWrite << lineToRead2 << endl;
            currentLine++;
        }
    }

    PatientInfoFileRead.close();
    PatientInfoCopyRead.close();
    return 1;
}

bool updatePatientStatus(int ID, string covidTestResult, string Status, string Locations) 
{
    patientInfoCopy(); //copies PatientInfo.txt to PatientInfoCopy.txt required for replacing entries
    user currentUserWrite;
    ifstream PatientInfoFileRead;

    PatientInfoFileRead.open("PatientInfo.txt");

    if (PatientInfoFileRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    ifstream PatientInfoCopyRead;

    PatientInfoCopyRead.open("PatientInfoCopy.txt");

    if (PatientInfoCopyRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    string idString = to_string(ID);
    string lineToRead;
    int lineCount = 0;
    bool IDfound = 0;

    while ((PatientInfoFileRead.peek() != EOF) || (IDfound == 0))
    {
        getline(PatientInfoFileRead, lineToRead);
        lineCount++; //keeps track of what line the id header begins

        if (lineToRead == ("ID= " + idString)) //copy patient entry as most info will remain same.
        {
            IDfound = 1;

            currentUserWrite.ID = ID;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.name = lineToRead;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.dOB = lineToRead;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.address = lineToRead;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.symptomLevel = lineToRead;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.visitedLocation = Locations;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.overSeas = lineToRead;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.locationAmnt = stoi(lineToRead);

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.covidTestResult = covidTestResult;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.Status = Status;

            getline(PatientInfoFileRead, lineToRead);
            currentUserWrite.recommendedTest = stoi(lineToRead);

            break;
        }
    }

    PatientInfoFileRead.close(); //close so that when reopen it begins at the beginning of file

    if (IDfound == 0) //if ID not found exit program with 0
    {
        cout << "Incorrect ID" << endl;
        return 0;
    }

    ofstream PatientInfoFileWrite;

    PatientInfoFileWrite.open("PatientInfo.txt");

    if (PatientInfoFileWrite.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    int currentLine = 1;
    string lineToRead2;

    if (IDfound)
    {
        while ((PatientInfoCopyRead.peek() != EOF))
        {
            if (currentLine == lineCount) //if correct line
            {
                //rewrite entry
                PatientInfoFileWrite << "ID= " << currentUserWrite.ID << endl;
                PatientInfoFileWrite << currentUserWrite.name << endl;
                PatientInfoFileWrite << currentUserWrite.dOB << endl;
                PatientInfoFileWrite << currentUserWrite.address << endl;
                PatientInfoFileWrite << currentUserWrite.symptomLevel << endl;
                PatientInfoFileWrite << currentUserWrite.visitedLocation << endl;
                PatientInfoFileWrite << currentUserWrite.overSeas << endl;
                PatientInfoFileWrite << currentUserWrite.locationAmnt << endl;
                PatientInfoFileWrite << currentUserWrite.covidTestResult << endl;
                PatientInfoFileWrite << currentUserWrite.Status << endl;
                PatientInfoFileWrite << currentUserWrite.recommendedTest << endl;

                //getline(PatientInfoCopyRead, lineToRead2);
                for (int i = 0; i < 11; i++) {
                    getline(PatientInfoCopyRead, lineToRead2);
                    currentLine++;

                }
                continue;
            }

            getline(PatientInfoCopyRead, lineToRead2);
            PatientInfoFileWrite << lineToRead2 << endl;
            currentLine++;
        }
    }

    PatientInfoFileRead.close();
    PatientInfoCopyRead.close();
    return 1;
}

bool IDexists(int ID) {
    string lineToRead;
    string idString = to_string(ID);
    ifstream PatientInfoFileRead;

    PatientInfoFileRead.open("PatientInfo.txt");

    if (PatientInfoFileRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    while ((PatientInfoFileRead.peek() != EOF))
    {
        getline(PatientInfoFileRead, lineToRead);

        if (lineToRead == ("ID= " + idString))
        {
            PatientInfoFileRead.close();
            return 1; //return 1 indicating it was found
        }
    }
    PatientInfoFileRead.close();
    return 0; //return 0 indicating it was not found
}

void patientInfoCopy() {
    ifstream PatientInfoFileRead;

    PatientInfoFileRead.open("PatientInfo.txt");

    if (PatientInfoFileRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        //return 0; //0 = failed to open error code.
    }

    ofstream PatientInfoFileCopy;

    PatientInfoFileCopy.open("PatientInfoCopy.txt");

    if (PatientInfoFileCopy.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        //return 0; //0 = failed to open error code.
    }

    string lineToRead;

    while ((PatientInfoFileRead.peek() != EOF)) //copy entire file until the end is reached
    {
        getline(PatientInfoFileRead, lineToRead);
        
        PatientInfoFileCopy << lineToRead << endl;
    }

    PatientInfoFileRead.close();
    PatientInfoFileCopy.close();
}

bool enterHighRisk(string Location) 
{
	ofstream HighRiskLocationsFileWrite;

	HighRiskLocationsFileWrite.open("HighRiskLocations.txt", fstream::app); //open with cursor at bottom of file

	if (HighRiskLocationsFileWrite.fail()) 
	{
		cout << "\nFile failed to open successfully" << endl;
		return 0; //0 = failed to write data.
	}

	HighRiskLocationsFileWrite << Location << endl;

	HighRiskLocationsFileWrite.close();
	return 1; //1 = data successfuly written
}

//No longer used keep just in case
int IsLocationHighRisk(string Location) 
{
	ifstream HighRiskLocationsFileRead;

	HighRiskLocationsFileRead.open("HighRiskLocations.txt");

	if (HighRiskLocationsFileRead.fail()) 
	{
		cout << "\nFile failed to open successfully" << endl;
		return 2; //2 = failed to open error code.
	}

	string TestLocation; //location to test parameter with

	while (HighRiskLocationsFileRead.peek() != EOF)
	{
		getline(HighRiskLocationsFileRead, TestLocation);

		if (TestLocation == Location) 
        {
			HighRiskLocationsFileRead.close();
			return 1; //1 = high risk location code
		}
	}

	HighRiskLocationsFileRead.close();
	return 0; //0 = not high risk location code.
}

bool writeNewEntry(user currentUserWrite)
{
    ofstream PatientInfoFileWrite;

    PatientInfoFileWrite.open("PatientInfo.txt", fstream::app); //open append mode

    if (PatientInfoFileWrite.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    //write new patient
    PatientInfoFileWrite << "ID= " << currentUserWrite.ID << endl;
    PatientInfoFileWrite << currentUserWrite.name << endl;
    PatientInfoFileWrite << currentUserWrite.dOB << endl;
    PatientInfoFileWrite << currentUserWrite.address << endl;
    PatientInfoFileWrite << currentUserWrite.symptomLevel << endl;
    PatientInfoFileWrite << currentUserWrite.visitedLocation << endl;
    PatientInfoFileWrite << currentUserWrite.overSeas << endl;
    PatientInfoFileWrite << currentUserWrite.locationAmnt << endl;
    PatientInfoFileWrite << currentUserWrite.covidTestResult << endl;
    PatientInfoFileWrite << currentUserWrite.Status << endl;
    PatientInfoFileWrite << currentUserWrite.recommendedTest << endl;

    PatientInfoFileWrite.close();
    return 1; //1 = data successfuly written
}

bool ReadSymptoms()
{
    //open file as input
    ifstream SymptomRiskFileRead;

    SymptomRiskFileRead.open("SymptomRisk.txt");

    if (SymptomRiskFileRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        cout << "Unable  to  recommend  COVID  Test – required data missing" << endl;
        return 0; //0 = failed to open error code.
    }

    string lineToRead; //string to store the current line read.

    //outputs to inform the user
    cout << "What level of symptoms are you currently feeling?" << endl;

    getline(SymptomRiskFileRead, lineToRead);
    cout << "Input 1 - " << lineToRead << endl;

    getline(SymptomRiskFileRead, lineToRead);
    cout << "Input 2 - " << lineToRead << endl;

    getline(SymptomRiskFileRead, lineToRead);
    cout << "Input 3 - " << lineToRead << endl;

    SymptomRiskFileRead.close();

    return 1; //1 = function successfully executed.
}

bool readPatientEntry(int ID) 
{
    //open file as input
    ifstream PatientInfoFileRead;

    PatientInfoFileRead.open("PatientInfo.txt");

    if (PatientInfoFileRead.fail())
    {
        cout << "\nFile failed to open successfully" << endl;
        return 0; //0 = failed to open error code.
    }

    string lineToRead; //string to store the current line read.
    string idString = to_string(ID);
    bool idFound = 0;

    while (PatientInfoFileRead.peek() != EOF)
    {
        getline(PatientInfoFileRead, lineToRead);

        if (lineToRead == ("ID= " + idString))
        {
            cout << "ID found" << endl;
            cout << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Name= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "DOB= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Address= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Symptom level= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Visited Location= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Overseas= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "High risk locations visited= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "COVID test result= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Status= " << lineToRead << endl;

            getline(PatientInfoFileRead, lineToRead);
            cout << "Has been recommended COVID test= " << ((lineToRead == "1") ? "Yes" : "No") << endl;

            PatientInfoFileRead.close();
            return 1; //1 = function successfully executed.
        }
    }

    cout << "Invalid ID" << endl;

    PatientInfoFileRead.close();

    return 0; //0 = ID read failed.
}

//function used for the validation of inputs which are required to be only 1 character in size
bool checkInputSizeIsOne(vector<char> cstr) {
    //assigning a deafult result to return
    bool result = false;
    //checking if the input is to long (since vector points to 1 memory point past the actual vector)
    if (cstr.size() >= 3) {
        cout << "input is to long" << endl;
    }
    else {
        //checking if the input is to short
        if (cstr.size() <= 1) {
            cout << "input is to small" << endl;
        }
        //checking if the input is an actual character
        else {
            if ((cstr[0] >= 'A') && (cstr[0] <= 'z')) {
                cout << "character was accepted" << endl;
                result = true;
            }
            //error message used when the input is not a character   
            else {
                cout << "invalid character was used: " << cstr[0] << endl;
                result = false;
            }
        }
    }
    return result;
}

bool StringCheck(string requiredInput) {
    bool result = false;
    //checking if the input is to long
    if (requiredInput.length() >= 30) {
        cout << "input was to long" << endl;
        return result;
    }
    //checking if the input is to short
    else if (requiredInput.length() < 1) {
        cout << "input was to short" << endl;
        return result;
    }
    //checking if the input is an actual string
    else {
        for (int i = 0; i < requiredInput.length(); i++) {
            if ((requiredInput[i] >= 65 && requiredInput[i] <= 90) || (requiredInput[i] >= 97 && requiredInput[i] <= 122) || requiredInput[i] == 32) {
                result = true;
            }
            //error message used when the input is not a string
            else {
                cout << "invalid character was used" << endl;
                return false;
            }
        }
    }
    return result;

}

bool DateSyntaxCheck(string str, int amount, char DMY) {
    bool result = false;
    //checking if the input was the correct size i.e. of size 2 for the month input
    if (str.length() != amount) {
        //error message used when the input is not the correct size
        cout << "input was incorrect length" << endl;
        return result;
    }
    else {
        //checking if the input is a number
        if (isInputANumber(str)) {
            //converting the input into a integer for symplified validation functions
            int int_test = stoi(str);
            //assigning different conditional statments for their corresponding timeframes i.e. checking that a month input 
            // is between 1 and 12
            switch (DMY) {
            case 'D':
                if ((int_test > 31) || (int_test <= 0)) {
                    cout << "incorrect day input" << endl;
                    return false;
                }
                else {
                    cout << "day input accepted" << endl;
                    result = true;
                }
                break;
            case 'M':
                if ((int_test > 12) || (int_test <= 0)) {
                    cout << "incorrect month input" << endl;
                    return false;
                }
                else {
                    cout << "month input accepted" << endl;
                    result = true;
                }
                break;
            case 'Y':
                if ((int_test > 2021) || (int_test <= 0)) {
                    cout << "incorrect year input" << endl;
                    return false;
                }
                else {
                    cout << "year input accepted" << endl;
                    result = true;
                }
                break;
            default:
                cout << "please select a timeframe" << endl;
            }
        }
        //error message used when the input is not a number
        else {
            cout << "input was not a number" << endl;
            return false;
        }
    }
    return result;
}

bool isIDValid(string str) {
    bool result = false;
    // the value 4 is used as a random size
    if (str.size() == 6) {
        if (isInputANumber(str)) {
            //converting the input into a integer
            cout << "ID was accepted" << endl;
            //also need a function here to check if the ID exists in the database!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            result = true;
        }
        //error message used when the input is not a number
        else {
            cout << "input was not a number" << endl;
            return false;
        }
    }
    else {
        //error message used when the input is not the correct size
        cout << "input was incorrect length" << endl;
        return false;
    }
    return result;

}

//function used for checking if a string is completely comprised of numbers otherwise will return false
bool isInputANumber(string str) {
    bool result = false;
    //iterating through the elements within the string and checking if each is a number 
    for (int i = 0; i < str.size(); i++)
    {
        if (isdigit(str[i])) {
            result = true;
        }
        else {
            return false;
        }
    }
    return result;
}

bool checkVarChar(string str) {
    bool result = false;
    if (str.size() <= 80) {
        for (int i = 0; i < str.size(); i++)
        {
            if ((isdigit(str[i])) || (((str[i] >= 65 && str[i] <= 90) || (str[i] >= 97 && str[i] <= 122) || str[i] == 32))) {
                result = true;
            }
            else {
                cout << "input needs to contain only numbers or letters i.e. 70 redwood road" << endl;
                return false;
            }
        }
    }
    else {
        //error message used when the input is not the correct size
        cout << "input was to long" << endl;
        return false;
    }
    return result;

}
