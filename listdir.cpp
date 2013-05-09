//#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <cerrno>
#include <fstream>

//Define the directory path from the executable to the folder that contains the .html template files
// DO NOT end this string with a '/' character
#define PATH './lokeus_mobile/templates'

//What is the target html file
#define TARGET 'index.html'

using namespace std;

/*
 * Tool to take template files, and append them into an index.html file into type template sections
*/

//Function compliments of http://stackoverflow.com/questions/2602013/read-whole-ascii-file-into-c-stdstring
string get_file_contents(const char *filename)
{
  ifstream in(filename, ios::in | ios::binary);
  if (in)
  {
    string contents;
    in.seekg(0, ios::end);
    contents.resize(in.tellg());
    in.seekg(0, ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}

int main (void)
{
	DIR *dp;
	struct dirent *ep;
	string contents;
	string targetInsert = TARGET;
	vector<string> filenames;	
	
	dp = opendir ( PATH );
	if (dp != NULL)
	{
		while (ep = readdir(dp))
			filenames.push_back(ep->d_name);
			(void)closedir(dp);
	}
	else
		perror ("Couldn't open the directory");
		
	while(filenames.size() > 0)
	{	
		string filename = filenames.back();

		int htmlPos = filename.find(".html");
		if (filename == ".." || filename == "." || htmlPos <= 0 || filename == targetInsert) {
			filenames.pop_back();
			continue;
		}
		
		//Remove the .html from the filename
		string idName = filenames.back().replace(htmlPos,5,"");
		
		filename = PATH + "/" + filename;

		//This is the beginning of text wrapper (opening tag)
		contents += "<script type=\"text/template\" id=\"" + idName + "\" >";
		
		contents += get_file_contents((char*)filename.c_str());
		
		//This is the end of the text wrapper (closing tag)
		contents += "</script>";
		
		filenames.pop_back();
	}
	targetInsert = PATH + "/" + targetInsert;
	string targetContents = get_file_contents( targetInsert.c_str());
	
	//Insert this whole string after the targetString, in this case after the <body> tag
	string targetString = "<body>";

	int targetPosition = targetContents.find(targetString);
	targetContents.insert(targetPosition + targetString.length() ,contents);
	cout<<targetContents<<endl;

	return 0;
}
