/*
 project_362.cpp
 ============================= CPSC 362 Project info ===============================
 Project #3 (Merged)
 Due date: 12/14/2018
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
#include <sstream>
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
string label_to_manifest(char *label, char filename[]);

vector<string> get_manifest_information(string manifest_file);
string get_src_manifest(string manifest_file);
bool compare_manifests(string manifest_1, string manifest_2);
vector<string> sort_manifests(vector<string> unsorted_manifests);
vector<string> get_manifests_within_the_same_branch(string manifest_file, vector<string> all_manifests);
bool check_CREATE(string manifest_file);
vector<string> get_all_manifests(string repo_address);
vector<string> trace(string manifest_file, string repo_address);
string find_grandma(vector<string> manifests_1, vector<string> manifests_2);
string get_grandma(string manifest_1, string manifest_2, string repo_address);

int num_of_manifest;

int main(int argc, char *argv[]) {

	int status = 0;
	char manifest[260], message[260], manifest_path[260], manifest_name[260];
	//repo path for merge
	const char *repo_path = "C:\\Users\\Xinyu\\Downloads\\362_test\\repo";
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
	else if (command_line == "MERGE") {
		//const char *repo_manifest = argv[2];
		//const char *target_path = argv[3];

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
	//merge
	const char *repo_manifest = "label_test";
	const char *target_path = "C:\\Users\\Xinyu\\Downloads\\362_test\\dory";



	if ((command_line == "CREATE") || (command_line == "CHECKIN") || (command_line == "CHECKOUT") || (command_line == "MERGE")) {
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
	else if (command_line == "MERGE") {
		//do check in ro make sure the target manifest is up-to-date
		status = copyDir(target_path, repo_path, manifest, strlen(repo_path));
		//merge
		merge(repo_manifest, manifest);


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

string label_to_manifest(char *label, char filename[]) {
	//if input is label, return manifest
	//else label is manifest
	string actual_filename = "";
	map <string, string> manifest_label_map;  //<label, manifest filename>
				//check if input is label
	fileToMap(filename, manifest_label_map);
	map <string, string> ::iterator itr;
	//string Label(1, label);
	string str(label);
	itr = manifest_label_map.find(label);
	if (itr == manifest_label_map.end())
		// if input is not label
		actual_filename = label;
	// if input is key, return value.
	else
		actual_filename = itr->second;
	return actual_filename;
}

//string to char*
char* string_to_char(string str) {
	char * writable = new char[str.size() + 1];
	copy(str.begin(), str.end(), writable);
	writable[str.size()] = '\0';
	return writable;
}

//check out
void check_out(char* src, char * dest, char* r_manifest, char * w_manifest, int cut) {
	string label_src(src);
	string label_temp = "label.txt";
	label_temp = label_src + "\\" + label_temp;

	char label[256] = "";
	for (int i = 0; i < label_temp.size(); i++)
		label[i] = label_temp[i];

	r_manifest = string_to_char(label_to_manifest(r_manifest, label));

	string src_temp(src);
	string man_temp(r_manifest);
	src_temp = src_temp + "\\" + man_temp;

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

		string src_temp(src);
		string dest_temp(dest);
		string temp_src1(temp_src);
		string temp_dest1(temp_dest);

		src_temp += temp_src1;
		dest_temp += temp_dest1;

		copyFile(string_to_char(src_temp), string_to_char(dest_temp), w_manifest, cut, 1);
	}
}

//merge start
//get 3 parts from a manifest file: operation, src_address, dest_address
vector<string> get_manifest_information(string manifest_file) {
	ifstream file;
	char c;
	string temp;
	vector<string> information;

	file.open(manifest_file);

	while (true) {
		temp = "";
		while (true) {
			c = file.get();
			if (c == ' ' || c == '\n')
				break;
			else
				temp += c;
		}
		information.push_back(temp);
		if (c == '\n')
			break;
	}

	file.close();

	return information;
}

//get the source manifest file name in the 3rd line
string get_src_manifest(string manifest_file) {
	ifstream file;
	char c;
	string temp;
	string src_manifest;
	unsigned line_counter = 0;

	file.open(manifest_file);
	while (true) {
		temp = "";
		while (true) {
			c = file.get();
			if (c == '\n' || c == EOF)
				break;
			else
				temp += c;
		}
		//skip the first 2 lines
		if (line_counter < 2) {
			line_counter++;
			continue;
		}
		else if (line_counter > 3)
			break;

		src_manifest = temp;
		if (c == EOF)
			break;
	}

	file.close();

	return src_manifest;
}

//return true if manifest_1 is older than manifest_2
bool compare_manifests(string manifest_1, string manifest_2) {
	string temp_1 = "";
	string temp_2 = "";
	int man_1;
	int man_2;
	const int POSITION_BEGIN = 9; //"manifest_"--> 9
	const int POSITION_END = 4; //".txt"--> 4

	for (int i = POSITION_BEGIN; i < manifest_1.size() - POSITION_END; i++)
		temp_1 += manifest_1[i];

	for (int i = POSITION_BEGIN; i < manifest_2.size() - POSITION_END; i++)
		temp_2 += manifest_2[i];

	istringstream(temp_1) >> man_1;
	istringstream(temp_2) >> man_2;
	if (man_1 > man_2)
		return true;
	else
		return false;
}

//sort the vector of manifests, from the oldest to the newest
vector<string> sort_manifests(vector<string> unsorted_manifests) {
	int least_index = 0;
	vector<string> sorted_manifests;

	while (unsorted_manifests.size() > 0) {
		for (int i = 1; i < unsorted_manifests.size(); i++) {
			if (compare_manifests(unsorted_manifests[least_index], unsorted_manifests[i]))
				least_index = i;
		}
		swap(unsorted_manifests[least_index], unsorted_manifests[unsorted_manifests.size() - 1]);
		sorted_manifests.push_back(unsorted_manifests[unsorted_manifests.size() - 1]);
		unsorted_manifests.pop_back;
	}

	return sorted_manifests;
}

//if the given manifest is "CHECKIN", return all manifests older than itself within the same branch
vector<string> get_manifests_within_the_same_branch(string manifest_file, vector<string> all_manifests) {

	vector<string> manifests_within_the_same_branch;

	if (get_manifest_information(manifest_file)[0] == "CHECKIN") {
		for (int i = 0; i < all_manifests.size(); i++) {
			if (get_manifest_information(all_manifests[i])[0] == "CHECKIN"
				&& (get_manifest_information(all_manifests[i])[1] == get_manifest_information(manifest_file)[1]))
				manifests_within_the_same_branch.push_back(all_manifests[i]);
			else if (get_manifest_information(all_manifests[i])[1] == "CHECKOUT"
				&& (get_manifest_information(all_manifests[i])[2] == get_manifest_information(manifest_file)[1]))
				manifests_within_the_same_branch.push_back(all_manifests[i]);
		}
	}

	manifests_within_the_same_branch = sort_manifests(manifests_within_the_same_branch);

	while (manifests_within_the_same_branch[manifests_within_the_same_branch.size() - 1] != manifest_file)
		manifests_within_the_same_branch.pop_back();

	return manifests_within_the_same_branch;
}

//return true if the given 
bool check_CREATE(string manifest_file) {
	if (get_manifest_information(manifest_file)[0] == "CREATE")
		return true;
	return false;
}

vector<string> get_all_manifests(string repo_address) {

}

//trace the given manifest to its oldest ancestor
vector<string> trace(string manifest_file, string repo_address) {
	vector<string> manifest_families;
	vector<string> temp;
	vector<string> all_manifest_files;
	string temp_str;

	all_manifest_files = get_all_manifests(repo_address);

	while (true) {
		temp = get_manifests_within_the_same_branch(manifest_file, all_manifest_files);
		for (int i = 0; i < temp.size(); i++)
			manifest_families.push_back(temp[i]);
		manifest_families = sort_manifests(manifest_families);
		temp_str = manifest_families[0];
		if (check_CREATE(temp_str))
			break;
		manifest_file = get_src_manifest(temp_str);
	}

	return manifest_families;
}

//given 2 vectors, find grandma
string find_grandma(vector<string> manifests_1, vector<string> manifests_2) {
	int position = 0;
	int len_1 = manifests_1.size();
	int len_2 = manifests_2.size();

	while (position < len_1 && position < len_2) {
		if (manifests_1[position] == manifests_2[position])
			position++;
		else {
			position--;
			break;
		}
	}

	if (position == len_1 || position == len_2)
		position--;

	return manifests_1[position];
}

//given 2 manifests addresses and repo address, get grandma
string get_grandma(string manifest_1, string manifest_2, string repo_address) {
	string temp;
	string manifest_file_1 = "";
	string manifest_file_2 = "";
	vector<string> manifests_1;
	vector<string> manifests_2;
	string grandma;

	for (int i = repo_address.size() + 1; i < manifest_1.size(); i++)
		manifest_file_1 += manifest_1[i];

	for (int i = repo_address.size() + 1; i < manifest_2.size(); i++)
		manifest_file_2 += manifest_2[i];

	manifests_1 = trace(manifest_file_1, repo_address);
	manifests_2 = trace(manifest_file_2, repo_address);

	grandma = find_grandma(manifests_1, manifests_2);
}

void merge(string repo_manifest, string target_manifest) {





}

vector<string> mergeFiles(string repo_manifest, string target_manifest) {
	vector<string> r_version_files = find_addresses_fileName(find_addresses(repo_manifest));
	vector<string> t_version_files = find_addresses_fileName(find_addresses(target_manifest));
	vector<string> r_version_artIds = find_addresses(repo_manifest);
	vector<string> t_version_artIds = find_addresses(target_manifest);
	vector<string> merge_files;

	//compare artIDs to decide merge or not
	for (int i = 0; i < r_version_files.size(); i++) {
		int t_index = find(t_version_files.begin(), t_version_files.end(), r_version_files[i]) - t_version_files.begin();
		if (t_index != t_version_files.size()) {
			//both tree has the file, compare their artIDs
			if (r_version_artIds[i] != t_version_artIds[t_index]) {
				merge_files.push_back(r_version_files[i]);
			}
		}
	}
	return merge_files;
}


vector<string> traceBranchPath(char manifest, string repo) {


}
