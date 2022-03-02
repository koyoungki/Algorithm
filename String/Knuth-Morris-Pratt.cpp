#include <iostream>
#include <string>
#include <vector>

void kmp_table(
	const	std::string&		pattern,
			std::vector<int>&	table)
{
	table.resize(pattern.size() + 1);
	table[0] = -1;
	int position = 1, match = 0;
	while (position < pattern.size())
	{
		if (pattern[position] == pattern[match])
			table[position] = table[match];
		else
		{
			table[position] = match;
			do
				match = table[match];
			while (match >= 0 && pattern[position] != pattern[match]);
		}
		++position, ++match;
	}
	table[position] = match;
}

bool kmp_include(
	const	std::string&		string,
	const	std::string&		pattern,
	const	std::vector<int>&	table)
{
	int position = 0, match = 0;
	while (position < string.size())
	{
		while (match >= 0 && string[position] != pattern[match])
			match = table[match];
		++position, ++match;
		if (match == pattern.size())
			return true;
	}
	return false;
}

void kmp_search(
	const	std::string&		string,
	const	std::string&		pattern,
	const	std::vector<int>&	table,
			std::vector<int>&	found)
{
	int position = 0, match = 0;
	while (position < string.size())
	{
		while (match >= 0 && string[position] != pattern[match])
			match = table[match];
		++position, ++match;
		if (match == pattern.size())
		{
			found.push_back(position - match);
			match = table[match];
		}
	}
}

int main()
{
	std::string string = "Peter Piper picked a peck of pickled peppers.";
	std::string pattern = "pick";
	std::vector<int> table, found;
	kmp_table(pattern, table);
	kmp_search(string, pattern, table, found);
	for (int index : found)
		std::cout << index << std::endl;
	return 0;
}