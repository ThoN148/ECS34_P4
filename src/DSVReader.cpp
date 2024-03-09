#include "DSVReader.h"
#include "StringUtils.h"
#include <iostream>

struct CDSVReader::SImplementation{
	
	std::shared_ptr< CDataSource > DSrc;
	char DDelimiter;
	bool emptyRow = false;
	
	SImplementation(std::shared_ptr< CDataSource> src, char delimiter) {
		DSrc = src;
		
		if (DDelimiter == '\"')
			DDelimiter = ',';
		else
			DDelimiter = delimiter;
	}

	bool End() const {
		return DSrc->End();
	}

	bool ReadRow(std::vector<std::string> &row) {
		
		// Getting one row from the source
		int numQuotes = 0;
		std::string currRow;
		char c = 'x';
		row.clear();

		if (End()) {
			if (emptyRow)
				currRow = "";
			else
				return false;
		}
		
		while (!End()) {
			if (!DSrc->Get(c)){
				return false;
			}

			if (c == '\n' && numQuotes % 2 == 0) {
				char temp;
				if (!DSrc->Peek(temp)) 
					emptyRow = true;
				
				break;
			}
			
			if (c == '\"'){
				numQuotes++;
			}

			currRow += c;
		}

		// Separating items in the row
		numQuotes = 0;
		std::string currItem = "";
		for (int i = 0; i < currRow.length(); i++) {

			if (currRow[i] == DDelimiter && numQuotes % 2 == 0) {
				row.push_back(currItem);
				currItem = "";
				continue;
			}
			
			if (currRow[i] == '\"')
				numQuotes++;
			
			currItem += currRow[i];
		}

		row.push_back(currItem);

		for (int i = 0; i < row.size(); i++) {
			
			for (int j = 0; j < row[i].length(); j++) {
				
				if (row[i][j] == '\"' && !(row[i][j - 1] == '\"' || row[i][j + 1] == '\"'))
					row[i].erase(j, 1);
				
			}

			row[i] = StringUtils::Replace(row[i], "\"\"", "\"");
		}

		/*for (int i = 0; i < row.size(); i++){
			std::cout<<i<<"'"<<row[i]<<"'";
		}*/

		return true;
	}
};

CDSVReader::CDSVReader(std::shared_ptr< CDataSource > src, char delimiter) {
	DImplementation = std::make_unique<SImplementation>(src, delimiter);
}

CDSVReader::~CDSVReader() {};

bool CDSVReader::End() const{
	return DImplementation->End();
}

bool CDSVReader::ReadRow(std::vector<std::string> &row) {
	return DImplementation->ReadRow(row);
}
