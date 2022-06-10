#pragma once

#include <iostream>

#include <boost/property_tree/ptree.hpp>
using boost::property_tree::ptree;
#include <boost/property_tree/xml_parser.hpp>
#include <boost/typeof/typeof.hpp>
#include <string.h>


using namespace std;

namespace pp
{	
	class CXmlAnalisys
	{
	public:
		CXmlAnalisys(string& xmlName)
		{
			try
			{
				read_xml(xmlName, m_tree, boost::property_tree::xml_parser::trim_whitespace);	
			}
			catch(...)
			{}
		}

		~CXmlAnalisys()
		{}

		void mobToChildNodeByName(const string& nodeName)
		{
			if(m_rootNode.empty())
			{
				m_nowNode = m_rootNode = m_tree.get_child(nodeName);
				return;
			}

			m_nowNode = m_nowNode.get_child(nodeName);
		}

		string getValueByName(const string& nodeName, const string& paramName)
		{
			BOOST_AUTO(child, m_nowNode.begin());
			for (; child != m_nowNode.end(); ++child) 
			{ 
				if( nodeName == child->first)
				{
					return child->second.get<string>("<xmlattr>." + paramName);				
				}
			}

			return string();
		}

	private:
		ptree m_tree;
		ptree m_rootNode;// 根节点
		ptree m_nowNode;// 当前节点

	};
}
