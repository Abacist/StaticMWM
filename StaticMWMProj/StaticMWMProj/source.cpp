#include<iostream>
#include<algorithm>
#include"CBG.h"
#include"auxiliary.h"

using namespace std;

void staticMWM(CBG g, vector<X> & z, vector<X> & t);
vector<MatchingEdge> ESMCM(CBG g);
vector<X> EEReplaceableSet(CBG g, vector<X> z, X x);
vector<X> ESReplaceableSet(CBG g, vector<X> z, X x);
vector<X> ReplaceXinEE(CBG g, X x, vector<X> z, vector<X> x1);
void ESMWM(CBG g, vector<X>& z, vector<X>& t);

int main()
{
	cout << "hello" << endl;
	return 0;
}


void staticMWM(CBG g, vector<X> & z, vector<X> & t)
{
	int flag = verifyBegin(g);
	if (flag == -1)
	{
		ESMWM(g, z, t);
	}
	else
	{
		X selectedX = g._allX[flag];
		CBG gl, gr;
		splitCBG(g, selectedX, gl, gr);
		vector<X> zl, zr, tl, tr;
		staticMWM(gl, zl, tl);
		staticMWM(gr, zr, tr);
		for (int i = 0; i < tl.size(); i++)
		{
			CBG gr1;
			gr1._allX = zr;
			gr1._allX.push_back(tl[i]);
			gr1._allY = gr._allY;
			vector<MatchingEdge> tempM = ESMCM(gr1);
			if (tempM.size() > zr.size())
			{
				zr.push_back(tl[i]);
			}
			else
			{
				vector<X> rr = ESReplaceableSet(gr, zr, tl[i]);
				rr.push_back(tl[i]);
				sort(rr.begin(), rr.end(), cmpXinESwithEnd);
				X maxX = rr[rr.size() - 1];
				Y maxY = g._allY[0];
				for (int k = 0; k < g._allY.size(); k++)
				{
					if (maxY._value < g._allY[k]._value)
					{
						maxY = g._allY[k];
					}
				}
				if (maxX._end > maxY._value)
				{
					vector<X>::iterator it = find(zr.begin(), zr.end(), maxX);
					zr.erase(it);
					zr.push_back(tl[i]);
					t.push_back(maxX);
				}
				else
				{
					vector<X> tml;
					for (int k = 0; k < rr.size(); k++)
					{
						if (rr[k]._begin < selectedX._begin)
						{
							tml.push_back(rr[k]);
						}
					}
					sort(tml.begin(), tml.end(), cmpXinEEwithBegin);
					X x1 = tml[tml.size() - 1];
					vector<X> rl = EEReplaceableSet(gl, zl, x1);
					X x2;
					sort(rl.begin(), rl.end(), cmpXByWeight);
					x2 = rl[rl.size() - 1];
					sort(rr.begin(), rr.end(), cmpXByWeight);
					if (cmpXByWeight(x2, rr[rr.size() - 1]))
					{
						x2 = rr[rr.size() - 1];
					}
					if (x2 == selectedX)
					{
						continue;
					}
					else
					{
						vector<X>::iterator it = find(rr.begin(), rr.end(), x2);
						if (it != rr.end())
						{
							it = find(zr.begin(), zr.end(), x2);
							zr.erase(it);
							zr.push_back(selectedX);
						}
						else
						{
							vector<X> bx = ReplaceXinEE(gl, x2, zl, tml);
							sort(bx.begin(), bx.end(), cmpXinESwithEnd);
							X x3 = bx[0];
							it = find(zl.begin(), zl.end(), x2);
							zl.erase(it);
							zl.push_back(x3);
							it = find(zr.begin(), zr.end(), x3);
							zr.erase(it);
							zr.push_back(selectedX);
						}
					}
				}
			}
		}
		z = zl;
		for (int i = 0; i < zr.size(); i++)
		{
			z.push_back(zr[i]);
		}
		for (int i = 0; i < tr.size(); i++)
		{
			t.push_back(tr[i]);
		}
	}
}

vector<MatchingEdge> ESMCM(CBG g)
{
	vector<MatchingEdge> m;
	sort(g._allX.begin(), g._allX.end(), cmpXinESwithEnd);
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

vector<X> ESReplaceableSet(CBG g, vector<X> z, X x)
{
	vector<X> r;
	sort(z.begin(), z.end(), cmpXinESwithEnd);
	sort(g._allY.begin(), g._allY.end(), cmpYInc);
	if (x._end < g._allY[0]._value)
	{
		return r;
	}
	int i = 0;
	while (true)
	{
		r.push_back(z[i]);
		if (z[i]._end == g._allY[i]._value && x._end <= g._allY[i]._value)
		{
			break;
		}
		i++;
		if (i == z.size() || i == g._allY.size())
		{
			break;
		}
	}
	return r;
}

vector<X> EEReplaceableSet(CBG g, vector<X> z, X x)
{
	vector<X> r;
	sort(z.begin(), z.end(), cmpXinEEwithBegin);
	sort(g._allY.begin(), g._allY.end(), cmpYDesc);
	if (x._begin > g._allY[0]._value)
	{
		return r;
	}
	int i = 0;
	while (true)
	{
		r.push_back(z[i]);
		if (z[i]._begin == g._allY[i]._value && x._begin >= g._allY[i]._value)
		{
			break;
		}
		i++;
		if (i == z.size() || i == g._allY.size())
		{
			break;
		}
	}
	return r;
}

vector<X> ReplaceXinEE(CBG g, X x, vector<X> z, vector<X> x1)
{
	sort(z.begin(), z.end(), cmpXinEEwithBegin);
	sort(g._allY.begin(), g._allY.end(), cmpYDesc);
	vector<int> tightIndex;
	for (int i = 0; i < z.size() && i < g._allY.size(); i++)
	{
		if (z[i]._begin == g._allY[i]._value)
		{
			tightIndex.push_back(i);
		}
	}
	if (tightIndex.size() == 0 || g._allY[tightIndex[0]]._value <= x._begin)
	{
		return x1;
	}
	else 
	{
		int i = 0;
		while (g._allY[tightIndex[i]]._value>x._begin)
		{
			i++;
			if (i == tightIndex.size())
			{
				break;
			}
		}
		i--;
		int yValue = g._allY[tightIndex[i]]._value;
		vector<X> selectedX;
		for (int i = 0; i < x1.size(); i++)
		{
			if (x1[i]._begin > yValue)
			{
				selectedX.push_back(x1[i]);
			}
		}
		return selectedX;
	}
}

void ESMWM(CBG g, vector<X>& z, vector<X>& t)
{
	z.clear(); t.clear();
	for (int i = 0; i < g._allX.size(); i++)
	{
		CBG tempg;
		tempg._allX = z;
		tempg._allX.push_back(g._allX[i]);
		tempg._allY = g._allY;
		vector<MatchingEdge> me = ESMCM(tempg);
		if (me.size() > z.size())
		{
			z.push_back(g._allX[i]);
		}
		else
		{
			vector<X> r = ESReplaceableSet(tempg, z, g._allX[i]);
			r.push_back(g._allX[i]);
			sort(r.begin(), r.end(), cmpXinESwithEnd);
			int maxX = r[r.size() - 1]._end;
			int maxY = g._allY[0]._value;
			for (int j = 0; j < g._allY.size(); j++)
			{
				if (g._allY[j]._value > maxY)
				{
					maxY = g._allY[j]._value;
				}
			}
			if (maxX > maxY)
			{
				vector<X>::iterator it = find(z.begin(), z.end(), r[r.size() - 1]);
				z.erase(it);
				z.push_back(g._allX[i]);
				t.push_back(r[r.size() - 1]);
			}
			else
			{
				sort(r.begin(), r.end(), cmpXByWeight);
				vector<X>::iterator it = find(z.begin(), z.end(), r[r.size() - 1]);
				z.erase(it);
				z.push_back(g._allX[i]);
			}
		}
	}
}



