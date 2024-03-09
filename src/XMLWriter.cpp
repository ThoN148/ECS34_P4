#include "XMLWriter.h"
#include "StringUtils.h"
#include "XMLEntity.h"

struct CXMLWriter::SImplementation {

	std::shared_ptr < CDataSink > DSink;
	std::vector < SXMLEntity > EntitiesStarted;
	SXMLEntity::EType lastWritten;

	SImplementation(std::shared_ptr < CDataSink > sink) {
		DSink = sink;
	}

	bool Flush() {
		
		int i = EntitiesStarted.size() - 1;
		SXMLEntity TempEntity;
		
		while (i >= 0) {
			WriteEntity({SXMLEntity::EType::EndElement, EntitiesStarted[i].DNameData});
			i--;
		}
		return true;
	}

	bool WriteEntity(const SXMLEntity &entity) {
		std::string currEntity = Reformat(entity.DNameData);

		if (entity.DType == SXMLEntity::EType::StartElement) {
			
			if (lastWritten == SXMLEntity::EType::CharData)
				return false;

			currEntity = "<" +  currEntity;

			// Formats attributes
			std::string currAttribute, currAttributeKey, currAttributeValue;
			for (size_t i = 0; i < entity.DAttributes.size(); i++) {
				
				currAttributeKey = Reformat(entity.DAttributes[i].first);
				currAttributeValue = Reformat(entity.DAttributes[i].second);
				
				currAttribute = currAttributeKey + "=" + "\"" + currAttributeValue + "\"";
				currEntity += " " + currAttribute;
			}

			currEntity += ">";

			EntitiesStarted.push_back(entity);
			lastWritten = SXMLEntity::EType::StartElement;
		
		} else if (entity.DType == SXMLEntity::EType::EndElement) {
			
			// Ensures end entity is closing last start entity
			if (EntitiesStarted.empty())
				return false;
			else if (EntitiesStarted.back().DNameData != entity.DNameData)
				return false;
			else
				EntitiesStarted.pop_back();
			
			currEntity = "</" + currEntity + ">";

			lastWritten = SXMLEntity::EType::EndElement;

		} else if (entity.DType == SXMLEntity::EType::CompleteElement) {

			currEntity = "<" +  currEntity;

			// Formats attributes
			std::string currAttribute, currAttributeKey, currAttributeValue;
			for (size_t i = 0; i < entity.DAttributes.size(); i++) {
				
				currAttributeKey = Reformat(entity.DAttributes[i].first);
				currAttributeValue = Reformat(entity.DAttributes[i].second);
				
				currAttribute = currAttributeKey + "=" + "\"" + currAttributeValue + "\"";
				currEntity += " " + currAttribute;
			}

			currEntity += "/>";
			lastWritten = SXMLEntity::EType::CompleteElement;

		} else {
			
			if (EntitiesStarted.empty())
				return false;

			lastWritten = SXMLEntity::EType::CharData;
		}

		std::vector< char > currEntityVect;
		for (int i = 0; i < currEntity.length(); i++) {
			currEntityVect.push_back(currEntity[i]);
		}

		DSink->Write(currEntityVect);

		return true;
	}
			
	std::string Reformat(std::string old) {
		std::string retString;

		for (int i = 0; i < old.size(); i++) {
				
				if (old[i] == '&')
					retString += "&amp;";
				else if (old[i] == '\"')
					retString += "&quot;";
				else if (old[i] == '\'')
					retString += "&apos;";
				else if (old[i] == '<')
					retString += "&lt;";
				else if (old[i] == '>')
					retString += "&gt;";
				else	
					retString += old[i];
			}
		return retString;
	}

};

CXMLWriter::CXMLWriter(std::shared_ptr< CDataSink > sink) {
	DImplementation = std::make_unique < SImplementation >(sink);
}

CXMLWriter::~CXMLWriter() {}

bool CXMLWriter::Flush() {
	return DImplementation->Flush();
}

bool CXMLWriter::WriteEntity(const SXMLEntity &entity) {
	return DImplementation->WriteEntity(entity);
}
