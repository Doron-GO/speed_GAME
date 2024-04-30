#pragma once
#include<string>

class GetAtr {
public:

	bool operator()(rapidxml::xml_node<>* node, std::string atrName, float& num)
	{
		if (node == nullptr)
		{
			return false;
		}
		auto atrstr = node->first_attribute(atrName.c_str());
		if (atrstr == nullptr)
		{
			//TRACE("�A�g���r���[�g�̎擾�G���[:%s\n", atrName.c_str());
			return false;
		}
		num = atof(atrstr->value());
		return true;

	}
	bool operator()(rapidxml::xml_node<>* node, std::string atrName, int& num)
	{
		if (node == nullptr)
		{
			return false;
		}
		auto atrstr = node->first_attribute(atrName.c_str());
		if (atrstr == nullptr)
		{
			//TRACE("�A�g���r���[�g�̎擾�G���[:%s\n",atrName.c_str());
			return false;
		}
		num = atoi(atrstr->value());
		return true;

	}

	bool operator()(rapidxml::xml_node<>* node, std::string atrStr, unsigned int& num)
	{
		if (node == nullptr) {
			return false;
		}
		auto atr = node->first_attribute(atrStr.c_str());
		if (atr == nullptr)
		{
			//TRACE("�A�g���r���[�g�̎擾�G���[");
			return false;
		}
		num = atoi(atr->value());
		return true;

	}

	bool operator()(rapidxml::xml_node<>* node, std::string atrName, std::string& str)
	{
		if (node == nullptr) {

			return false;
		}
		auto atr = node->first_attribute(atrName.c_str());
		if (atr == nullptr)
		{
			//TRACE("�A�g���r���[�g�̎擾�G���[");
			return false;
		}
		str = atr->value();
		return true;

	}

};
