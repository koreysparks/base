#include "xml.hpp"
#include <stdio.h>

namespace pp
{
	CXmlAnalisys::CXmlAnalisys(string& xmlName)
	{
		try
		{
			read_xml(xmlName, m_tree, boost::property_tree::xml_parser::trim_whitespace);	
		}
		catch(...)
		{}
	}

	CXmlAnalisys::~CXmlAnalisys()
	{}

	void CXmlAnalisys::mobToChildNodeByName(const string& nodeName)
	{
		if(m_rootNode.empty())
		{
			m_nowNode = m_rootNode = m_tree.get_child(nodeName);
			return;
		}

		m_nowNode = m_nowNode.get_child(nodeName);
	}

	string CXmlAnalisys::getValueByName(const string& nodeName, const string& paramName)
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


}

