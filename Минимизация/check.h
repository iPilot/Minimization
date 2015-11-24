#pragma once
#include <iostream>
#include <cstdio>
#include <string>
#include <algorithm>

#define sz(a) (int)a.size()

using namespace std;

pair <bool, int> check_data(string& st, int n)
{
	int k = 1;
	while (n > 0) k *= 2, n--;
	if (k != sz(st)) return make_pair(false, k);
	for(int i = 0; i < sz(st); i++) 
		if (st[i] != '1' && st[i] != '0') return make_pair(false, -i);
	return make_pair(true, k);
}

bool check(string& s, int n, int k)
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

void next(int * p, int n)
{
	n--;
	p[n]++;
	while(p[n] > 1) p[n--] %= 2, p[n]++;
}