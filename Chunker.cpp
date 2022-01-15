#include "Chunker.h"

Chunker::Chunker(string mainDatasetPath):list{3,4,5,6,7,8,9,11,12,13,14,16,18,21}
{
	
	idcount = new int[30];
	this->MakeDirectories();
	int counter = 0;
	// this is the get videos part it will read videos up to a limit write them down in their proper paths and then erase them from vector
	for (auto& p : fs::recursive_directory_iterator(mainDatasetPath)) {
		videos.push_back(Video(p.path()));
		counter++;
		if (counter == VideoBufferSize) {
			totalVideoCount += VideoBufferSize;
			this->FillDirectories();
			counter = 0;
			videos.clear();
			cout << totalVideoCount << " videos have been chunked!\n";
		}
	}
	//flush
	if (videos.size() != 0) {
		this->FillDirectories();
		videos.clear();
	}
	this->DeleteDirectories();
}

void Chunker::MakeDirectories()
{
	fs::create_directory("Datasets");
	for (int i = 0; i < 30; i++) {
		if (fs::create_directory("Datasets/"+to_string(i)))
		{
			cout << "Created Directory!\n";
		}

	}
}

void Chunker::FillDirectories()
{
	for (int i = 0; i < videos.size(); i++) {
		if (videos[i].invalid) {
			cout << "Invalid File Found!\n";
			continue;
		}
		string path = to_string(videos[i].categoryId);
		ofstream tempfile("Datasets/" + path +'/' +videos[i].id+".txt");
		tempfile << videos[i].id <<'\n';
		tempfile << videos[i].title<< '\n';
		idcount[videos[i].categoryId]++;
		for (size_t j = 0; j < videos[i].NumberOfComments(); j++) {
			tempfile << videos[i].comments[j] << '\n';
		}
		tempfile.close();
	}
}

void Chunker::DeleteDirectories()
{
	for (int i = 0; i < 14; i++) {
		fs::remove("Datasets/"+to_string(list[i]));
	}




}





