#include "TypeChecker.h"

#include"Logger.h"

#include<algorithm>
 
TypeChecker::TypeChecker():
	m_invalidType(_T("INVALID_TYPE"))
{
} 
TypeChecker::~TypeChecker()
{
}

void TypeChecker::AddType(int objectID, const std::tstring& type) {
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end())
		m_mapTypes.insert(std::pair<int,std::vector<std::tstring>>(objectID,std::vector<std::tstring>()));

	m_mapTypes[objectID].push_back(type);
}
const std::tstring& TypeChecker::GetType(int objectID) {
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end())
	{
		Logger::log(_T("No object has been found !"),LOGTYPE_WARNING,false);
		return m_invalidType;
	}

	int index = m_mapTypes[objectID].size() - 1;
	return m_mapTypes[objectID][index];
}
bool TypeChecker::IsType(int objectID, const std::tstring& type) {
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end())
	{
		Logger::log(_T("No object has been found with type: " + type), LOGTYPE_WARNING, false);
		return false;
	}

	if (!TypeExists(type, false)) {
		Logger::log(_T("No object has been found with type: " + type), LOGTYPE_WARNING, false);
		return false; 
	}
	int index = m_mapTypes[objectID].size() - 1;
	return m_mapTypes[objectID][index]==type;
}
bool TypeChecker::IsType(const std::tstring& type, const std::tstring& isType) {
	std::map<int, std::vector<std::tstring>>::iterator itmap_from = m_mapTypes.end();
	std::map<int, std::vector<std::tstring>>::iterator itmap_to = m_mapTypes.end();

	if (!TypeExists(type,itmap_from))
	{
		Logger::log(_T("No object has been found with type: " + type + _T("and type: ") + isType), LOGTYPE_WARNING, false);
		return false;
	}
	if (!TypeExists(type, itmap_from, false)) {
		Logger::log(_T("No object has been found with type: " + type +_T("and type: ")+isType), LOGTYPE_WARNING, false);
		return false;
	}

	int index = m_mapTypes[(*itmap_from).first].size() - 1;
	return m_mapTypes[(*itmap_from).first][index] == isType;

}
bool TypeChecker::IsA(int objectID, const std::tstring& type) 
{
	std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.find(objectID);
	if (it == m_mapTypes.end())
	{
		Logger::log(_T("No object has been found with type: " + type), LOGTYPE_WARNING, false);
		return false;
	}
	if (!TypeExists(type)) {
		Logger::log(_T("No object has been found with type: " + type), LOGTYPE_WARNING, false);
		return false;
	}
	std::vector<std::tstring>::iterator it_type = std::find(m_mapTypes[objectID].begin(), m_mapTypes[objectID].end(), type);
	return it_type != m_mapTypes[objectID].end();
}
bool TypeChecker::IsA(const std::tstring& type, const std::tstring& isType)
{
	std::map<int, std::vector<std::tstring>>::iterator itmap_from = m_mapTypes.end();
	std::map<int, std::vector<std::tstring>>::iterator itmap_to = m_mapTypes.end();

	if (!TypeExists(type, itmap_from))
	{
		Logger::log(_T("No object has been found with type: " + type + _T("and type: ") + isType), LOGTYPE_WARNING, false);
		return false;
	}
	if (!TypeExists(type, itmap_from, false)) {
		Logger::log(_T("No object has been found with type: " + type + _T("and type: ") + isType), LOGTYPE_WARNING, false);
		return false;
	}
	std::vector<std::tstring>::iterator it_type = std::find(m_mapTypes[(*itmap_from).first].begin(), m_mapTypes[(*itmap_from).first].end(), type);
	return it_type != m_mapTypes[(*itmap_from).first].end();

}
bool TypeChecker::TypeExists(const std::tstring& type, bool last ) {
	for (std::map<int,std::vector<std::tstring>>::iterator it=m_mapTypes.begin(); it !=m_mapTypes.end(); ++it)
	{
		std::vector<std::tstring>::iterator it_from = std::find((*it).second.begin(), (*it).second.end(), type);
		if (it_from != (*it).second.end()) 
		{
			if ((*it).second[(*it).second.size() - 1] == type || !last)
				return true;
		}
	}
	return false;
}
bool TypeChecker::TypeExists(const std::tstring& type, std::map<int, std::vector<std::tstring>>::iterator ref_it, bool last ) {
	for (std::map<int, std::vector<std::tstring>>::iterator it = m_mapTypes.begin(); it != m_mapTypes.end(); ++it)
	{
		std::vector<std::tstring>::iterator it_from = std::find((*it).second.begin(), (*it).second.end(), type);
		if (it_from != (*it).second.end()) 
		{
			if ((*it).second[(*it).second.size() - 1] == type || !last)
			{
				ref_it = it;
				return true;
			}
		}
	}
	return false;
}