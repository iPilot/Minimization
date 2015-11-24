#include "functions.h"

vector<set<term>> terms, terms_next;

bool pows[1024];

int smain()
{
	int n;
	string input;
	cin >> n >> input;
	if (check(input, n))
	{
		term termb, nterm;
		terms.resize(n+1);
		terms_next.resize(sz(terms));
		for (int l = 1; l <= sz(input); pows[l] = true, l *= 2);
		for (int i = 0; i < sz(input); i++)
		{
			if (input[i] == '1')
			{
				getterm(termb, i, n);
				terms[termb.second].insert(mp(termb.first, i));
			}
		}
		bool f = true;
		while (f)
		{
			f = false;
			for (int i = 0; i < sz(terms); i++)
			{
				for (auto j = terms[i].begin(); j != terms[i].end(); j++)	
				{
					bool prev = true, next = true;
					if (i < sz(terms)-1)
					{
						for (auto k = terms[i + 1].begin(); k != terms[i + 1].end(); k++)
							if (term_comp(*j, *k))
							{
								f = true;
								next = false;
								int q = new_term(*j, *k, nterm);
								terms_next[q].insert(nterm);
							}
					}
					if (i > 0)
					{
						for (auto k = terms[i - 1].begin(); k != terms[i - 1].end(); k++)
							if (term_comp(*k, *j))
							{
								f = true;
								prev = false;
								int q = new_term(*k, *j, nterm);
								terms_next[q].insert(nterm);
							}
					}
					if (prev && next) terms_next[i].insert(*j);
				}
			}
			terms.clear();
			terms = terms_next;
			terms_next.clear();
			terms_next.resize(sz(terms));
		}
		set<string> _terms, _next, _nexta;
		for (int i = 0; i < sz(input); i++)
		{
			if (input[i] == '1')
			{
				getterm(termb, i, n);
				_terms.insert(termb.first);
			}
		}
		for (int i = 0; i < sz(terms); i++)
			for (auto j = terms[i].begin(); j != terms[i].end(); j++) _next.insert(j->first);
		_nexta = _next;
		string minterm, result;
		for (auto j = _terms.begin(); j != _terms.end();)
		{
			int count = 0;
			minterm.clear();
			for (auto i = _next.begin(); i != _next.end(); i++)
				if (term_compa(*j, *i))
				{
					count++;
					if (count == 1) minterm = *i;
				}
			if (count == 1)
			{
				_nexta.erase(minterm);
				for (auto z = _terms.begin(); z != _terms.end();)
					if (term_compa(*z, minterm))
					{
						_terms.erase(z);
						z = _terms.begin();
					}
					else z++;
				j = _terms.begin();
			}
			else j++;
		}
		for (auto j = _nexta.begin(); j != _nexta.end(); j++) _next.erase(*j);
		for (auto j = _next.begin(); j != _next.end(); j++)
		{
			if (j != _next.begin()) result += " v ";
			for (int i = 0; i < sz((*j)); i++)
			{
				if ((*j)[i] == '0') result += i + 97;
				if ((*j)[i] == '1') result += i + 65;
			}
		}
		int min = (int)1e9;
		string minresult;
		if (!_terms.empty())
		{
			findminresult(result, _terms, _nexta, _terms.begin(), &min, minresult);
			cout << minresult << endl;
		}
		else cout << result << endl;
		system("pause");
	}
	else
	{
		system("pause");
	}
	return 0;
}