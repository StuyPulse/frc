#include <sstream>
#include <fstream>
#include <cstdarg>
#include <vector>
#include "Record.h"

Record::Record(void)
{
	this->areWePlaying = false;
	this->areWeSaving = false;
	this->saveFile = new ofstream();
	this->playFile = new ifstream();
	
}
Record::~Record(void)
{
	delete this->saveFile;
	delete this->playFile;
}
	
Record::OpenForSaving(int recordNumber)
{
	stringstream filename;
	filename << recordNumber << ".txt";
	this->saveFile->close();
	this->playFile->close();
	this->saveFile->open(filename.str());
	this->areWePlaying = false;
	this->areWeSaving = true;
}

Record::OpenForPlaying(int recordNumber)
{
	stringstream filename;
	filename << recordNumber << ".txt";
	this->saveFile->close();
	this->playFile->close();
	this->playFile->open(filename.str());
	this->areWePlaying = true;
	this->areWeSaving = false;
}

Record::Close(void)
{
	this->saveFile->close();
	this->playFile->close();
	this->areWePlaying = false;
	this->areWeSaving = false;
}

Record::Save(int count, ...)
{
	if(this->areWeSaving){
		va_list output_record;		//sets the correct type for our var arg array
		va_start(output_record, count);	//inits the var arg array
		for(int i=1; i<=count; i++){
			if(i < count){
				(*(this->saveFile)) << va_arg(output_record, double) << "\t";
			}
			else{
				(*(this->saveFile)) << va_arg(output_record, double) << "\n";
			}
		}
		va_end(output_record);
	}
}

vector<double> *Record::Play(void)
{
	vector<double> *returnRecord;
	double field;
	if(this->areWePlaying){
		returnRecord = new vector<double>();
		while(this->playFile->peek() != '\n' && this->playFile->good()){
			(*(this->playFile)) >> field;
			returnRecord->push_back(field);
		}
	}
	return returnRecord;
}

bool Record::CanIContinuePlaying(void)
{
	if(this->areWePlaying){
		return this->playFile->good();
	}
	else{
		return false;
	}
}