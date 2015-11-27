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

int **table, min_op = (int)1e9;
vector<string> ans;

class __term
{
	public: 
		int num, operations, length, group;
		string term, result;

		bool operator==(const __term &right) const
		{
			for (int i = 0; i < sz(term); i++)
				if (term[i] != right.term[i] && term[i] != '*' && right.term[i] != '*') return false;
			return true;
		}

		bool cmp_delta(const __term &right) const
		{
			int delta = 0;
			if (length != right.length) return false;
			for (int i = 0; i < length; i++)
			{
				if ((term[i] == '*') ^ (right.term[i] == '*')) return false;
				if (term[i] != right.term[i]) delta++;
			}
			return (delta == 1 && !((group > right.group) ^ (num > right.num)));
		}

		bool operator=(const __term &right)
		{
			length = right.length;
			group = right.group;
			num = right.num;
			operations = right.operations;
			term = right.term;
			result = right.result;
			return true;
		}

		bool operator<(const __term &right) const
		{
			return (result < right.result);
		}

		__term()
		{
			length = 0;
			group = 0;
			term = "";
			result = "";
			operations = 0;
			num = 0;
		}

		__term(int _num, int _size)
		{
			num = _num;
			length = _size; 
			term.resize(_size);
			operations = 0;
			group = 0;
			result = "";
			for (int i = length - 1; i >= 0; i--, _num /= 2)
			{
				term[i] = _num % 2 + 48;
				operations += (int)(term[i] == '0') + (int)(i > 0);
				if (term[i] == '1') group++;
			}
			set_result();
		}

		__term(const __term &a, const __term &b)
		{
			length = a.length;
			term.resize(length);
			result = "";
			operations = 0;
			num = 0;
			group = 0;
			int k = 1;
			for (int i = a.length - 1; i >= 0; i--)
			{
				if (a.term[i] == b.term[i]) term[i] = a.term[i];
				else term[i] = '*';
				if (term[i] == '1') group++, num += k;
				operations += (int)(term[i] == '0') + (int)(i > 0) - (int)(term[i] == '*');
				if (term[i] != '*') k *= 2;
			}
			set_result();
		}

		__term(const __term &a)
		{
			length = a.length;
			term = a.term;
			result = a.result;
			num = a.num;
			operations = a.operations;
			group = a.group;
		}

	private:
		void set_result()
		{
			result.clear();
			for (int i = 0, j = 0; i < length; i++)
			{
				if (term[i] == '1') result += i + 65;
				if (term[i] == '0') result += i + 97;
			}
		}
};

void printresult(const vector<__term> &h, const vector<__term> &w, string &r, int step, int r_op)
{
	int x = 0;
	step--;
	while (table[sz(h) + 1][x] != 0) x++;
	if (x < sz(w))
	{
		int y = 0;
		while (table[y][x] == 0) y++;
		for (; y < sz(h); y++)
		{
			if (table[y][x] == 1 && table[y][sz(w)] == 0)
			{
				for (int j = 0; j < sz(w); j++)
					if (table[y][j] == 1 && table[sz(h) + 1][j] == 0) table[sz(h) + 1][j] = step;
				table[y][sz(w)] = step;
				string tmp;
				if (r == "") tmp = h[y].result;
				else tmp = r + " v " + h[y].result;
				printresult(h, w, tmp, step, r_op + h[y].operations + 1);
				for (int j = 0; j < sz(w); j++)
					if (table[y][j] == 1 && table[sz(h) + 1][j] == step) table[sz(h) + 1][j] = 0;
			}
		}
		for (y = 0; y < sz(h); y++)
			if (table[y][sz(w)] == step) table[y][sz(w)] = 0;
	}
	else
	{
		if (min_op > r_op)
		{
			ans.clear();
			min_op = r_op;
			ans.push_back(r);
		}
		else
			if (min_op == r_op)	ans.push_back(r);
	}
}

pair <bool, int> check_data(string& st, int n)
{
	int k = 1;
	while (n > 0) k *= 2, n--;
	if (k != sz(st)) return mp(false, k);
	for (int i = 0; i < sz(st); i++)
		if (st[i] != '1' && st[i] != '0') return mp(false, -i);
	return mp(true, k);
}

bool check(string& s, int n, int k = 6)
{
	if (n < 1 || n > k)
	{
		printf("Wrong number of variables: expected in [1; %d], found %d\n", k, n);
		return false;
	}
	else
	{
		pair <bool, int> result = check_data(s, n);
		if (!result.first)
		{
			if (result.second > 0) printf("Wrong lenght of vector: expected = %d, found = %d\n", result.second, sz(s));
			else printf("Wrong character at position %d: expected {0, 1}, found = \'%c\'\n", -result.second, s[-result.second]);
			return false;
		}
	}
	return true;
}

bool term_cmp(const __term &a, const __term &b)
{
	return (a.operations < b.operations || a.operations == b.operations && a.result < b.result);
}

