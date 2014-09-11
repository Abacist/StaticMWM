#include"auxiliary.h"

int verifyBegin(CBG& g)
{
	int minYValue = g._allY[0]._value;
	for (int i = 0; i < g._allY.size(); i++)
	{
		if (minYValue > g._allY[i]._value)
		{
			minYValue = g._allY[i]._value;
		}
	}

	for (int i = 0; i < g._allX.size(); i++)
	{
		if (g._allX[i]._begin != minYValue)
		{
			return i;
		}
	}
	return -1;
}


void splitCBG(CBG& g, X midX, CBG& gl, CBG& gr)
{
	for (int i = 0; i < g._allX.size(); i++)
	{
		if (g._allX[i]._begin < midX._begin)
		{
			gl._allX.push_back(g._allX[i]);
		}
		else
		{
			gr._allX.push_back(g._allX[i]);
		}
	}
	for (int i = 0; i < g._allY.size(); i++)
	{
		if (g._allY[i]._value < midX._begin)
		{
			gl._allY.push_back(g._allY[i]);
		}
		else
		{
			gr._allY.push_back(g._allY[i]);
		}
	}
}

bool cmpX(X x1, X x2)
{
	if (x1._end < x2._end)
	{
		return true;
	}
	else if (x1._end == x2._end && x1._begin < x2._begin)
	{
		return true;
	}
	else if (x1._end == x2._end && x1._begin == x2._begin && x1._id < x2._id)
	{
		return true;
	}
	else
	{
		return false;
	}
}
