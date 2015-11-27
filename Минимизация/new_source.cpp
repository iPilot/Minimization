#include "functions.h"

vector<term> impl, core, ost;
vector<set<term>> terms, nterms;

int main()
{
	int n;
	string input;
	setlocale(2, "rus");
	cout << "Введите количество переменных:\n";
	cin >> n;
	cout << "\nВведите вектор значений функции:\n";
	cin >> input;
	if (check(input, n))
	{
		terms.resize(n + 1);
		nterms.resize(n + 1);
		for (int i = 0; i < sz(input); i++)
			if (input[i] == '1')
			{
				term tmp(i, n);
				terms[tmp.group].insert(tmp);
				impl.push_back(tmp);
			}
		bool f = true;
		while (f)
		{
			f = false;
			for (int i = 0; i <= n; i++)
			{
				for (auto j = terms[i].begin(); j != terms[i].end(); j++)
				{
					bool scl = false;
					if (i > 0)
						for (auto k = terms[i - 1].begin(); k != terms[i - 1].end(); k++)
							if ((*j).cmp_delta(*k))
							{
								scl = f = true;
								term tmp(*j, *k);
								nterms[tmp.group].insert(tmp);
							}
					if (i < sz(terms) - 1)
						for (auto k = terms[i + 1].begin(); k != terms[i + 1].end(); k++)
							if ((*j).cmp_delta(*k))
							{
								scl = f = true;
								term tmp(*j, *k);
								nterms[tmp.group].insert(tmp);
							}
					if (!scl) nterms[(*j).group].insert(*j);
				}
			}
			terms.clear();
			terms = nterms;
			nterms.clear();
			nterms.resize(n + 1);
		}

		for (int i = 0; i < sz(terms); i++)
			for (auto j = terms[i].begin(); j != terms[i].end(); j++) core.push_back(*j);

		sort(all(core), term_cmp);

		table = new int*[sz(core) + 2];
		for (int z = 0; z < sz(core) + 2; z++)
		{
			table[z] = new int[sz(impl) + 2];
			for (int zz = 0; zz < sz(impl) + 2; zz++) table[z][zz] = 0;
		}

		for (int i = 0; i < sz(core); i++)
			for (int j = 0; j < sz(impl); j++)
				if (core[i] == impl[j])
				{
					table[i][j] = 1;
					table[sz(core)][j]++;
				}

		for (int i = 0; i < sz(impl); i++)
		{
			if (table[sz(core)][i] == 1 && table[sz(core) + 1][i] == 0)
			{
				int k = 0;
				while (table[k][i] == 0) k++;
				table[k][sz(impl)] = -1;
				ost.push_back(core[k]);
				for (int j = 0; j < sz(impl); j++)
					if (table[k][j] == 1) table[sz(core) + 1][j] = -1;
			}
		}

		cout << "\nВозможные минимальные ДНФ:\n";

		if (sz(core) == 0 && sz(ost) == 0) cout << "0\n";
		else
			if (sz(core) == 1 && sz(ost) == 1 && ost[0].result == "") cout << "1\n";
			else
			{
				string result = "";
				int op = 0;
				for (int z = 0; z < sz(ost); z++)
				{
					result += ost[z].result;
					op += ost[z].operations;
					if (z < sz(ost) - 1) result += " v ", op++;
				}

				printresult(core, impl, result, -1, op);
				for (int z = 0; z < sz(ans); z++)
					cout << ans[z] << endl;
			}
	}
	system("pause");
	return 0;
}