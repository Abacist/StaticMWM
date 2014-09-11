#include<iostream>
#include<algorithm>
#include"CBG.h"
#include"auxiliary.h"

using namespace std;

void staticMWM(CBG& g, vector<X> & z, vector<X> & t);
vector<MatchingEdge> ESMCM(CBG& g);

int main()
{
	cout << "hello" << endl;
	return 0;
}


void staticMWM(CBG& g, vector<X> & z, vector<X> & t)
{
	int flag = verifyBegin(g);
	if (flag == -1)
	{
		//return ESMWM
	}
	else
	{
		X seletedX = g._allX[flag];
		CBG gl, gr;
		splitCBG(g, seletedX, gl, gr);
		vector<X> zl, zr, tl, tr;
		staticMWM(gl, zl, tl);
		staticMWM(gr, zr, tr);
		for (int i = 0; i < tl.size(); i++)
		{

		}
	}
}

vector<MatchingEdge> ESMCM(CBG& g)
{
	vector<MatchingEdge> m;
	sort(g._allX.begin(), g._allX.end(), cmpX);
	int i = 0, j = 0;
	while (i != g._allX.size() && j != g._allY.size())
	{
		if (g._allX[i]._end >= g._allY[j]._value)
		{
			MatchingEdge me;
			me._x = g._allX[i];
			me._y = g._allY[j];
			m.push_back(me);
			j++;
		}
		i++;
	}
	return m;
}