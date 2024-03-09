#include "DSVWriter.h"
#include "StringUtils.h"
#include <iostream>


struct CDSVWriter::SImplementation {
	
	std::shared_ptr< CDataSink > DSink;
	char DDelimiter;
	bool DQuoteAll;
	int numRows;

	SImplementation(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
		DSink = sink;
		DQuoteAll = quoteall;
		numRows = 0;

		if (DDelimiter == '\"')
			DDelimiter = ',';
		else
			DDelimiter = delimiter;
	}

	bool WriteRow(const std::vector<std::string> &row) {
		int rowSize = row.size();

		std::string currRow;
		std::string item;

 		for (int i = 0; i < rowSize; i++) {
			
			// duplicates quotes (escape)

			for (int j = 0; j < row[i].length(); j++) {
				if (row[i][j] == '\"')
					item += "\"";

				item += row[i][j];
			}
			
			// condition to quote item
			// quoteall, or contains delimiter, quote, or newline

			if (DQuoteAll || item.find(DDelimiter) != std::string::npos || item.find('\"') != std::string::npos || item.find("\n") != std::string::npos)
				item = "\"" + item + "\"";

			if (i != rowSize - 1)
				item += DDelimiter;
			
			currRow += item;
			item = "";
		}

		if (numRows != 0)
			currRow = '\n' + currRow;
		
		numRows++;

		std::vector< char > currRowVect;
		for (int i = 0; i < currRow.length(); i++) {
			currRowVect.push_back(currRow[i]);
		}

		DSink->Write(currRowVect);

		return true;
	}
};

CDSVWriter::CDSVWriter(std::shared_ptr< CDataSink > sink, char delimiter, bool quoteall) {
	DImplementation = std::make_unique<SImplementation>(sink, delimiter, quoteall);
}

CDSVWriter::~CDSVWriter() {}

bool CDSVWriter::WriteRow(const std::vector<std::string> &row) {
	return DImplementation->WriteRow(row);
}
