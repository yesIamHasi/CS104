#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
/*
* QUIZ.cpp
* Author/s: NAME
* Usage:
*	This program presents a quiz to a registered user. For each correct answer +4 is awarded and for incorrect answer -1/4
* is deducted. After the quiz user data is stored in the file students.txt in the format <Name,Reg. No.,Score> 
* Requirements:
*	This program requires Students.txt and Quiz.txt in the current working directory.
*/
int STUDENTS = 6;
int L_STUDENTS = STUDENTS*3; // length of students array
int QUIZ = 6;
int L_QUIZ = QUIZ*6; // length of quiz array

using namespace std;

// CSV == Comma Separated Values
vector<string> readCSV(char filename[], int SIZE){
    /*
	* Reads a CSV file and returns an array of Comma Separated Values
	*/
	ifstream File (filename); // Initialize File stream: 
	int counter = 0;
	vector<string> DATA_ARRAY(SIZE);
	string line;
	
	while ( File.good() ) 
	{
     	getline ( File, line, '\n' ); // Split the file into lines
     	//cout << line << endl; 
     	istringstream templine(line); // Convert the lines to a line strean
	  	string data;
	  	while (getline( templine, data,',')){ // Split the lines in commas
	  		//cout << data << endl;
	  		DATA_ARRAY[counter] = data;
    		//cout << student[counter] << endl; //For debugging
    	counter += 1;
		}
	}
	File.close();
	//cout << student[0];
	return DATA_ARRAY;	
}

void writeCSV(string *names, string *registration, string *score){
 	/*
	 * Writes arrray input in CSV format to Students.txt
	 */
	ofstream file;
	file.open("Students.txt");
	for (int i=0; i<STUDENTS; i++){
		file << names[i] << "," << registration[i] << "," << score[i] << endl;
	}
	file.close();
}
bool inList(string &name, string *list, int SIZE){
	/*
	* Retun true if name is in the array list.
	*/
	for (int i=0; i<SIZE; i++){
		if ( name == list[i]){
			return true;
		}
	}
	return false;
}

int indexOf(string &name, string *list, int SIZE){
	/*
	* Returns the index of name in the array list.
	*/
	for (int i=0; i<SIZE; i++){
		if ( name == list[i]){
			return i;
		}
	}
	return -1;
}

void display(string *QUESTION, string *As, string *Bs, string *Cs, string *Ds, string *correct, string *names, string *registration, string *score){
	/*
	* Handle UI I/O s
	* Also it should be used in the default function display of a class.
	*/
	float STUDENT_SCORE = 0;
	cout << "Welcome to Quiz" << endl;
	cout << "Enter your Name: ";
	string name;
	cin >> name;
	//cout << name;
	cout << "Enter your Registration No: ";
	string reg;
	cin >> reg;
	//cout << reg;
	
	// Check if the person is registered in database
	bool reg_exist = inList(reg, registration, STUDENTS); 
	bool name_exist = inList(name, names, STUDENTS); 
	if (reg_exist && name_exist){
		cout << "User Found!"<<endl;
		
		// For question in questions ask question one by one.
		for (int i=0; i<QUIZ; i++){
			cout << QUESTION[i] << "." << endl;
			cout << "0) " << As[i] << " 1) " << Bs[i] << " 2) " << Cs[i] << " 3) " << Ds[i] <<endl;
			cout << "\n";
			int choice;
			cout << "(0, 1, 2, 3) << ";
			cin >> choice;
			switch (choice){
				case 0:
					if (As[i] == correct[i]){
						STUDENT_SCORE += 4;
						break;
					}
				case 1:
					if (Bs[i] == correct[i]){
						STUDENT_SCORE += 4;
						break;
					}
				case 2:
					if (Cs[i] == correct[i]){
						STUDENT_SCORE += 4;
						break;
					}
				case 3:
					if (Ds[i] == correct[i]){
						STUDENT_SCORE += 4;
						break;
					}
				default:
					STUDENT_SCORE -= 0.25;
					break;
			}
			
		}
		int STUDENT_INDEX = indexOf(name, names, STUDENTS);
		//cout << STUDENT_INDEX;
		string tempSCORE = to_string(STUDENT_SCORE);
		score[STUDENT_INDEX] = tempSCORE;
		//cout << STUDENT_SCORE;
		writeCSV(names, registration, score);
	}
}

int main(){
	// Load Students
	vector<string> students = readCSV("Students.txt", L_STUDENTS);
	/*for (int iq = 0; iq < L_STUDENTS; iq++){
		//cout << iq;
		cout << students[iq] << endl;
	}*/
	// Load Quiz
	//
	// Splite the array students into three arrays NAME, REGISTRATION and SCORE
	//
	string NAMES[STUDENTS];
	for (int i=0; i<L_STUDENTS; i+=3){
		// Find the term number of AP
		int n = (i-0)/3; // For 0 index array +1 is ommited
		NAMES[n] = students[i];
		//cout << n;
	}
	string REGISTRATION[STUDENTS];
	for (int i=1; i<L_STUDENTS; i+=3){
		// Find the term number of AP
		int n = (i-1)/3; // For 0 index array +1 is ommited
		REGISTRATION[n] = students[i];
		//cout << students[i] << endl;
	}
	string SCORE[STUDENTS];
	for (int i=2; i<L_STUDENTS; i+=3){
		// Find the term number of AP
		int n = (i-2)/3; // For 0 index array +1 is ommited
		SCORE[n] = students[i];
		//cout << students[i] << endl;
	}
	//
	// Split the array quiz into QUESTION, As, Bs, Cs, Ds, CORRECT
	//
	vector<string> quiz = readCSV("Quiz.txt", L_QUIZ);
	/*for (int iq = 0; iq < L_QUIZ; iq++){
		//cout << iq;
		cout << quiz[iq] << endl;
	}*/
	string QUESTION[QUIZ];
	for (int i=0; i<L_QUIZ; i+=6){
		// Find the term number of AP
		int n = (i-0)/6; // For 0 index array +1 is ommited
		QUESTION[n] = quiz[i];
		//cout << quiz[i] << endl;
	}
	string As[QUIZ];
	for (int i=1; i<L_QUIZ; i+=6){
		// Find the term number of AP
		int n = (i-1)/6; // For 0 index array +1 is ommited
		As[n] = quiz[i];
		//cout << n << quiz[i] << endl;
	}
	string Bs[QUIZ];
	for (int i=2; i<L_QUIZ; i+=6){
		// Find the term number of AP
		int n = (i-2)/6; // For 0 index array +1 is ommited
		Bs[n] = quiz[i];
		//cout << n << quiz[i] << endl;
	}
	
	string Cs[QUIZ];
	for (int i=3; i<L_QUIZ; i+=6){
		// Find the term number of AP
		int n = (i-3)/6; // For 0 index array +1 is ommited
		Cs[n] = quiz[i];
		//cout << n << quiz[i] << endl;
	}
	
	string Ds[QUIZ];
	for (int i=4; i<L_QUIZ; i+=6){
		// Find the term number of AP
		int n = (i-4)/6; // For 0 index array +1 is ommited
		Ds[n] = quiz[i];
		//cout << n << quiz[i] << endl;
	}
	string CORRECT[QUIZ];
	for (int i=5; i<L_QUIZ; i+=6){
		// Find the term number of AP
		int n = (i-5)/6; // For 0 index array +1 is ommited
		CORRECT[n] = quiz[i];
		//cout << n << quiz[i] << endl;
	}
	// UI
	display(QUESTION, As, Bs, Cs, Ds, CORRECT, NAMES, REGISTRATION, SCORE);
	//cout << "SCORE" << STUDENT_SCORE;
	return 0;
}

