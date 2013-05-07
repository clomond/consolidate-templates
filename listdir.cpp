//#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <vector>
#include <string>
#include <vector>
#include <iostream>
#include <cerrno>
#include <fstream>

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
	string targetInsert = "index.html";
	vector<string> filenames;	
	
	dp = opendir ("./lokeus_mobile/templates");
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
		if (filename == ".." || filename == "." || htmlPos <= 0 || filename == targetInsert){
			filenames.pop_back();
			continue;
		}
		
		string idName = filenames.back().replace(htmlPos,5,"");
		filename = "./lokeus_mobile/templates/" + filename;
		contents += "<script type=\"text/template\" id=\"" + idName + "\" >";
		contents += get_file_contents((char*)filename.c_str());
		contents += "</script>";
		filenames.pop_back();
	}
	targetInsert = "./lokeus_mobile/templates/" + targetInsert;

	string targetContents = get_file_contents( targetInsert.c_str());
	int targetPosition = targetContents.find("<body>");
	targetContents.insert(targetPosition+6,contents);
	cout<<targetContents<<endl;

	return 0;
}
