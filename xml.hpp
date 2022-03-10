#pragma once

#include <iostream>

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <string.h>

#include "libbase.hpp"

using namespace std;

namespace pp
{	
	class CXmlAnalisys
	{
	public:
		CXmlAnalisys(string& xmlName);
		~CXmlAnalisys();
	
	public:
		void mobToChildNodeByName(const string& nodeName);
		// 根据字段名称获取值
		string getValueByName(const string& nodeName, const string& paramName);
		string getNodeName();

	private:
		ptree m_tree;
		ptree m_rootNode;// 根节点
		ptree m_nowNode;// 当前节点

	};
}
