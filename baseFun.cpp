#include "baseFun.hpp"

void splitStr(vector<string>& children, const string& str, char splitchar)
{
	children.clear();
	string::size_type preplace = 0, curplace = 0;
	string substr;
	while(1)
	{
		curplace = str.find(splitchar, preplace);
		if(string::npos == curplace)
		{
			substr = str.substr(preplace, str.size() - preplace);
			children.push_back(substr);
			break;
		}
		else
		{
			substr = str.substr(preplace, curplace - preplace);
			children.push_back(substr);
			preplace = curplace + 1;
		}
	}
}

