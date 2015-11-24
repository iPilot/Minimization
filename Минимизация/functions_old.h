#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#define sz(a) (int)a.size()
#define mp make_pair
#define pb push_back
#define all(a) a.begin(), a.end()
#define BIG (long long)1e15

using namespace std;

typedef long long ll;

typedef pair<string, int> term;

void next(int * p, int n)
{
	n--;
	p[n]++;
	while (p[n] > 1) p[n--] %= 2, p[n]++;
}

void getterm(term &terma, int k, int size)
{
	int l, p;
	terma.second = 0;
	terma.first.clear();
	for (l = 0, p = k % 2; k > 0; k /= 2, l++, p = k % 2)
	{
		if (p == 1) terma.second++;
		terma.first += p + 48;
	}
	for (; l < size; l++) terma.first += '0';
	reverse(all(terma.first));
}

bool term_comp(term terma, term termb)
{
	int delta = 0;
	for (int i = 0; i < sz(terma.first); i++)
	{
		if ((terma.first[i] == '*') ^ (termb.first[i] == '*')) return false;
		if (terma.first[i] != termb.first[i]) delta++;
	}
	return (delta == 1 && termb.second > terma.second);
}

bool term_compa(string a, string b)
{
	for (int i = 0; i < sz(a); i++)
		if (a[i] != b[i] && b[i] != '*') return false;
	return true;
}

int new_term(term a, term b, term &c)
{
	c.first.clear();
	c.second = 0;
	int k = 1, result = 0;
	for (int i = sz(a.first) - 1; i >= 0; i--)
	{
		if (a.first[i] == b.first[i]) c.first += a.first[i];
		else c.first += '*';
		if (c.first[sz(a.first) - i - 1] == '1') c.second += k, result++;
		if (c.first[sz(a.first) - i - 1] != '*') k *= 2;
	}
	reverse(all(c.first));
	return result;
}

int calcoperations(string &input)
{
	int result = 0;
	for (int i = 0; i < sz(input); i++)
	{
		if (input[i] >= 'a' && input[i] <= 'z') result += 2;
		if (input[i] >= 'A' && input[i] <= 'Z') result++;
		if (input[i] == ' ') result--;
	}
	result--;
	return result;
}

void findminresult(string result, set<string> &terms, set<string> &next, set<string>::iterator j, int * min, string &minresult)
{
	if (j == terms.end())
	{
		int cur = calcoperations(result);
		if (cur < *min)
		{
			*min = cur;
			minresult = result;
		}
		return;
	}
	else
	{
		int cur_min = (int)1e9, count = 0, p;
		string resulta = "";
		for (auto z = next.begin(); z != next.end(); z++)
		{
			if (term_compa(*j, *z))
			{
				resulta.clear();
				for (int i = 0; i < sz((*z)); i++)
				{
					if ((*z)[i] == '0') resulta += i + 97;
					if ((*z)[i] == '1') resulta += i + 65;
				}
				p = calcoperations(resulta);
				cur_min = std::min(p, cur_min);
				if (p == cur_min) count++;
			}
		}
		cout << count << endl;
		findminresult(result + " v ", terms, next, ++j, min, minresult);
		/*for (auto z = next.begin(); z != next.end(); z++)
		{
		if (term_compa(*j, *z))
		{
		resulta.clear();
		for (int i = 0; i < sz((*z)); i++)
		{
		if ((*z)[i] == '0') resulta += i + 97;
		if ((*z)[i] == '1') resulta += i + 65;
		}
		if (calcoperations(resulta) == cur_min)
		{
		findminresult(result + " v " + resulta, terms, next, ++j, min, minresult);
		j--;
		}
		}
		}*/
	}
}

