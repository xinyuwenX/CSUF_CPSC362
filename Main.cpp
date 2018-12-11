/*
 project_362_02.cpp
 ============================= CPSC 362 Project info ===============================
 Project #2 (Check-Out & Check-In & Labeling)
 Due date: 11/17/2018
 Group members:Xinyu Wen, Xianghui Huang, Yintao Wang
 Email: xinyuwen@csu.fullerton.edu, jerryhuang6666@gmail.com, wyt@csu.fullerton.edu
 Class meeting time: Monday & Wednesday 15:00-16:50
 ===================================================================================
 */
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_SECURE_NO_WARNINGS


#include <iostream>
#include <io.h>
#include <cstdio>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <direct.h>
#include <cstring>
#include <fstream>
#include <iostream>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <ctime>
#include <map>
#include <vector>

using namespace std;

void copyFile(char * src, char * dest, char * manifest, int cut, int flag);
int copyDir(const char * p_src, const char * p_dest, char * manifest, int cut);
string getArtIDFileName(char fileName[]);
void writeFile(char file_name[], const char *message);
void getManifestName(const string cmd, char manifest_name[]);
bool mapToFile(char filename[], map<string, string> &fileMap);
bool fileToMap(char filename[], map<string, string> &fileMap);
void splitString(vector<string> &v_str, string str, char ch);
void addLabel(char filename[], char destination[]);
vector<string> find_addresses(string file_name);
vector<string> find_addresses_fileName(vector<string> v_addresses);
void check_out(char* src, char * dest, char* r_manifest, char * w_manifest, int cut);
char* string_to_char(string s);
char* label_to_manifest(char *label);
int num_of_manifest;

int main(int argc, char *argv[]) {

	int status = 0;
	char manifest[260], message[260], manifest_path[260], manifest_name[260];
	//status = copyDir(src, dest);
	//status = copyDir("C:\\Users\\yintaowang\\test\\src", "C:\\Users\\yintaowang\\test\\repo");

	//command_line
	//const char *command_line = "CREATE";
	//const char *command_line = "CHECKIN";
	const char *command_line = "CHECKOUT";
	//const char *command_line = "LABEL";

	//get arg
	if ((command_line == "CREATE") || (command_line == "CHECKIN")) {
		//const char *src = argv[2];
		//const char *dest = argv[3];
	}
	else if (command_line == "CHECKOUT") {
		//const char *src = argv[2];
		//const char *dest = argv[3];
		//const char *r_manifest = argv[4];
	}
	else if (command_line == "LABEL") {
		//const char *label = argv[2];
		//const char *target = argv[3];
	}
	//get arg end

	//TEST
	/*char src[260] = "C:\\Users\\yintaowang\\test\\src";
	char dest[260] = "C:\\Users\\yintaowang\\test\\repo";
	char r_manifest[260] = "C:\\Users\\yintaowang\\test\\repo\\manifest_17.txt";*/

	//CREATE & CHECKIN & LABEL
	//const char *src = "C:\\Users\\Xinyu\\Downloads\\362_test\\src";
	//const char *dest = "C:\\Users\\Xinyu\\Downloads\\362_test\\repo";
	//CHECKOUT
	const char *src = "C:\\Users\\Xinyu\\Downloads\\362_test\\repo";
	const char *dest = "C:\\Users\\Xinyu\\Downloads\\362_test\\checkout";
	//const char *r_manifest = "manifest_1.txt";
	const char *r_manifest = "label_test";




	if ((command_line == "CREATE") || (command_line == "CHECKIN") || (command_line == "CHECKOUT")) {
		//get manifest path
		if (command_line == "CHECKOUT") {
			strcpy(manifest_path, src);
		}
		else {
			strcpy(manifest_path, dest);
		}

		//manifest file name
		string manifest_p = "dir ";
		manifest_p.append(manifest_path);
		manifest_p.append("\\manifest*.txt /b /a-d | find /v /c \"&#@\"");

		getManifestName(manifest_p, manifest_name);
		strcpy(manifest, manifest_path);
		strcat(manifest, "\\");
		strcat(manifest, manifest_name);
		strcpy(message, command_line);
		strcat(message, " ");
		strcat(message, src);
		strcat(message, " ");
		strcat(message, dest);

		if (command_line == "CHECKOUT") {
			strcat(message, " ");
			strcat(message, r_manifest);
		}
	}

	//get current time
	time_t now = time(0);

	//label file name
	//TODO where is label.txt???
	char label_file[260];
	strcpy(label_file, dest);
	strcat(label_file, "\\label.txt");
	string label_default = "";

	if (command_line == "CREATE") {
		//create manifest file
		writeFile(manifest, message);
		writeFile(manifest, ctime(&now));
		//create label.txt
		writeFile(label_file, label_default.c_str());
		//create repository
		status = copyDir(src, dest, manifest, strlen(dest));
	}
	else if (command_line == "CHECKIN") {
		//create manifest file
		writeFile(manifest, message);
		writeFile(manifest, ctime(&now));
		//check in
		status = copyDir(src, dest, manifest, strlen(dest));
	}
	else if (command_line == "CHECKOUT") {
		//create manifest file
		writeFile(manifest, message);
		writeFile(manifest, ctime(&now));
		//check out
		check_out(_strdup(src), _strdup(dest), _strdup(r_manifest), manifest, strlen(src));
	}
	else if (command_line == "LABEL") {
		//labeling
		char destination[260];
		strcpy(destination, dest);
		addLabel(label_file, destination);
	}
	else {
		cout << "input command is invalid!!!" << endl;
		system("pause");
		return 0;
	}

	//display execution result
	if (status == 0) {
		cout << command_line << " successfully." << endl << endl;
	}
	else {
		cout << command_line << " Failed." << endl << endl;
	}
	system("pause");
	return 0;
}

void addLabel(char filename[], char destination[]) {

	char trash[260];
	string manifest_p = "dir ";
	manifest_p.append(destination);
	manifest_p.append("\\manifest*.txt /b /a-d | find /v /c \"&#@\"");
	getManifestName(manifest_p, trash);


	string label, manifest_file;
	string actual_filename;
	map <string, string> manifest_label_map;  //<label, manifest filename>
	bool isValid = false;
	fileToMap(filename, manifest_label_map);

	cout << "which manifest file you want to label?" << endl;
	cin >> manifest_file;

	cout << "What label you want to add to file" << manifest_file << endl;
	cin >> label;


	//check if input is label
	map <string, string> ::iterator itr;
	itr = manifest_label_map.find(manifest_file);
	if (itr == manifest_label_map.end())
		actual_filename = manifest_file;
	else
		actual_filename = itr->second;

	for (int i = 1; i < num_of_manifest; i++) {
		string temp = "manifest_" + to_string(i) + ".txt";
		if (!actual_filename.compare(temp)) {
			isValid = true;
		}
	}
	if (isValid) {
		manifest_label_map.insert(pair <string, string>(label, actual_filename));
		mapToFile(filename, manifest_label_map);
	}
	else {
		cout << "invalid filename" << endl;
	}
}

void writeFile(char file_name[], const char *message) {
	ofstream OutFile;
	OutFile.open(file_name, ios::app);
	OutFile << message << endl;
	OutFile.close();
}

void getManifestName(const string cmd, char manifest_name[]) {

	FILE *crs = _popen(cmd.c_str(), "r");
	char result[1024] = "0";
	fread(result, sizeof(char), sizeof(result), crs);
	if (NULL != crs) {
		fclose(crs);
		crs == NULL;
	}
	int res = stoi(result, nullptr, 10);
	res += 1;
	num_of_manifest = res;
	string temp = "manifest_";
	temp.append(to_string(res));
	temp.append(".txt");
	strcpy(manifest_name, temp.c_str());
}

//copy source file contents to artifact
void copyFile(char * src_file, char * dest_file, char * manifest, int cut, int flag) {

	const int buff_size = 16384;
	char buffer[buff_size];
	size_t in_bytes, out_bytes;

	FILE * in_file = fopen(src_file, "rb");
	FILE * out_file = fopen(dest_file, "wb");

	//read source file contents then write into the artifact
	while (!feof(in_file)) {
		in_bytes = fread(buffer, 1, buff_size, in_file);
		out_bytes = fwrite(buffer, 1, in_bytes, out_file);
	}

	fclose(in_file);
	fclose(out_file);
	if (flag == 1) {
		//write manifest file CHECKOUT
		writeFile(manifest, src_file + cut);
	}
	else {
		//write manifest file
		writeFile(manifest, dest_file + cut);
	}
}

//create repository
int copyDir(const char * p_src, const char * p_dest, char * manifest, int cut) {

	if (p_src == NULL || p_dest == NULL) {
		return -1;
	}
	//create a folder
	_mkdir(p_dest);
	char dir[260] = { 0 };
	char src_file_name[260] = { 0 };
	char dest_file_name[260] = { 0 };

	const char * str = "\\*.*";
	strcpy_s(dir, p_src);
	strcat_s(dir, str);

	long hFile;
	_finddata_t fileInfo;

	if ((hFile = _findfirst(dir, &fileInfo)) != -1) {

		do {

			strcpy_s(src_file_name, p_src);
			strcat_s(src_file_name, "\\");
			strcat_s(src_file_name, fileInfo.name);
			strcpy_s(dest_file_name, p_dest);
			strcat_s(dest_file_name, "\\");
			strcat_s(dest_file_name, fileInfo.name);

			//if find a file
			if (!(fileInfo.attrib & _A_SUBDIR)) {

				//create a leaf folder which is named the same as the file name
				_mkdir(dest_file_name);
				//call function to get ArtID file name for the artifact.
				string artId_str = getArtIDFileName(src_file_name);
				string dest_file_name_str = dest_file_name;
				dest_file_name_str = dest_file_name_str + "\\" + artId_str;
				char *dest_file_name_char = const_cast<char *>(dest_file_name_str.c_str());
				//create the artifact of the source file
				copyFile(src_file_name, dest_file_name_char, manifest, cut, 0);

			}
			else if (strcmp(fileInfo.name, ".") != 0 && strcmp(fileInfo.name, "..") != 0) {
				//if find a directory, using the recursion
				copyDir(src_file_name, dest_file_name, manifest, cut);
			}
		} while (_findnext(hFile, &fileInfo) == 0);
		_findclose(hFile);
		return 0;
	}
	return -2;
}

// get ArtID file name
string getArtIDFileName(char fileName[])
{
	string fileNameStr = fileName;
	fstream file;
	string fileContent;
	string artIDFileName;
	string::iterator it;
	string fileTypeName;
	int const FIVEWEIGHTS[] = { 1,3,7,11,17 };
	unsigned long checksum = 0;
	int weightNum;
	int const M = pow(2, 31) - 1;

	//store all chars from a file into a string(including ' ' and '\n')
	file.open(fileNameStr);
	while (file.peek() != EOF) {
		fileContent += file.get();
	}

	//delete all '\n' from the string
	fileContent.erase(std::remove(fileContent.begin(), fileContent.end(), '\n'), fileContent.end());

	//calculate checksum of the string
	for (int i = 0; i < fileContent.length(); i++) {
		weightNum = i % 5;
		checksum += FIVEWEIGHTS[weightNum] * fileContent[i];
	}

	if (checksum < M)
		artIDFileName += std::to_string(checksum);
	else {
		double modulus = (double)checksum / M;
		artIDFileName += std::to_string(modulus);
		artIDFileName += "m";
	}

	//store type name of the file into a string
	for (int i = fileNameStr.length() - 1; i >= 0; i--) {
		fileTypeName = fileTypeName.insert(0, 1, fileNameStr[i]);
		if (fileNameStr[i] == '.')
			break;
	}

	//make a new file name(artid + "-L" + filesize)
	artIDFileName += "-L";
	artIDFileName += std::to_string(fileContent.length());
	artIDFileName += fileTypeName;

	return artIDFileName;
}

bool mapToFile(char filename[], map<string, string> &fileMap)     //Write Map
{
	ofstream ofile;
	ofile.open(filename);
	if (!ofile)
	{
		return false;           //file does not exist and cannot be created.
	}
	map <string, string> ::iterator iter;
	for (iter = fileMap.begin(); iter != fileMap.end(); ++iter)
	{
		ofile << iter->first << "|" << iter->second;
		ofile << "\n";
	}
	return true;
}

bool fileToMap(char filename[], map<string, string> &fileMap)  //Read Map
{
	ifstream ifile;
	ifile.open(filename);
	if (!ifile)
		return false;   //could not read the file.
	string line;
	string key;
	vector<string> v_str;
	while (ifile >> line)
	{
		splitString(v_str, line, '|');

		for (vector<string>::iterator iter = v_str.begin();; ++iter)        //First vector element is the key.
		{
			if (iter == v_str.begin())
			{
				fileMap[*iter] = "Unavailable";
				key = *iter;
				continue;
			}
			fileMap[key] = *iter;
			break;
		}
		v_str.clear();
	}
	return true;
}
void splitString(vector<string> &v_str, string str, char ch)
{
	string sub;
	string::size_type pos = 0;
	string::size_type old_pos = 0;
	bool flag = true;

	while (flag)
	{
		pos = str.find_first_of(ch, pos);
		if (pos == string::npos)
		{
			flag = false;
			pos = str.size();
		}
		sub = str.substr(old_pos, pos - old_pos);  // Disregard the '.'
		v_str.push_back(sub);
		old_pos = ++pos;
	}
}

//extract addresses from a manifest file then store them into a vector
vector<string> find_addresses(string file_name) {
	ifstream file;
	char c;
	string temp;
	vector<string> all_addresses;
	unsigned line_counter = 0;

	file.open(file_name);
	while (true) {
		temp = "";
		while (true) {
			c = file.get();
			if (c == '\n' || c == EOF)
				break;
			else
				temp += c;
		}
		//skip the first 3 lines
		if (line_counter < 3) {
			line_counter++;
			continue;
		}
		all_addresses.push_back(temp);
		if (c == EOF)
			break;
	}
	file.close();

	return all_addresses;
}

//remove the content after the last '\'
vector<string> find_addresses_fileName(vector<string> v_addresses) {
	vector<string> all_addresses = v_addresses;
	int index_last_backslash;
	string temp_string;
	for (int i = 0; i < all_addresses.size() - 1; i++) {
		for (int j = 0; j < all_addresses[i].length(); j++) {
			if (all_addresses[i][j] == '\\')
				index_last_backslash = j;
		}
		temp_string = all_addresses[i];
		all_addresses[i] = "";
		for (int j = 0; j < index_last_backslash; j++) {
			all_addresses[i] += temp_string[j];
		}
	}
	return all_addresses;
}

vector<string> eliminate_repeat(vector<string> v_addresses) {
	vector<string> addresses_no_repeat;
	bool repeat;
	for (int i = 0; i < v_addresses.size(); i++) {
		repeat = false;
		for (int j = 0; j < addresses_no_repeat.size(); j++) {
			if (v_addresses[i] == addresses_no_repeat[j]) {
				repeat = true;
				break;
			}
		}
		if (!repeat)
			addresses_no_repeat.push_back(v_addresses[i]);
	}
	return addresses_no_repeat;
}

char* label_to_manifest(char *label) {
	//if input is label, return manifest
	//else label is manifest
	string actual_filename = "";
	map <string, string> manifest_label_map;  //<label, manifest filename>
	//check if input is label
	map <string, string> ::iterator itr;
	itr = manifest_label_map.find(label);
	if (itr == manifest_label_map.end())
		// if input is not label
		return label;
	// if input is key, return value.
	actual_filename = itr->second;

	return string_to_char(actual_filename);
}

 //string to char*
char* string_to_char(string s) {
	char c[260];
	for (int i = 0; i < s.size(); i++)
		c[i] = s[i];
	return c;
}


void check_out(char* src, char * dest, char* r_manifest, char * w_manifest, int cut) {
	r_manifest = label_to_manifest(r_manifest);
	cout << "r_manifest: " << r_manifest << endl;
	char *src_temp = _strdup(src);
	char *man_temp = _strdup(r_manifest);
	strcat(src_temp, "\\");
	strcat(src_temp, man_temp);
	vector<string> v_addresses = find_addresses(src_temp);
	vector<string> v_addresses_fileName = find_addresses_fileName(v_addresses);
	vector<string> v_addresses_folder = find_addresses_fileName(v_addresses_fileName);
	vector<string> v_addresses_folder_no_repeat = eliminate_repeat(v_addresses_folder);
	char* temp_src;
	char* temp_dest;
	string cmd;

	for (int i = 0; i < v_addresses_folder_no_repeat.size(); i++) {
		cout << v_addresses_folder_no_repeat[i] << endl;
		cmd = "mkdir ";
		string temp(dest);
		cmd += temp;
		cmd += v_addresses_folder_no_repeat[i];
		system(cmd.c_str());
	}

	for (int i = 0; i < v_addresses.size() - 1; i++) {
		temp_src = &v_addresses[i][0u];
		temp_dest = &v_addresses_fileName[i][0u];
		char *src_temp = _strdup(src);
		char *dest_temp = _strdup(dest);
		strcat(src_temp, temp_src);
		strcat(dest_temp, temp_dest);
		copyFile(src_temp, dest_temp, w_manifest, cut, 1);
	}
}
