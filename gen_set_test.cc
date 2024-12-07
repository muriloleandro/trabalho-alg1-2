/* ./gen_set_test (n) (id) (out_dir)
 * n  - number of elements * 10^(-2);
 * id - test id
 * out_dir - test output directory
 */

#include <iostream>
#include <fstream>
#include <set>
#include <random>
#include <cstdlib>
#include <format>

int
main(int argc, char **argv)
{
	int n, m, k, id;
	std::string out_dir;
	std::set<int> s1, s2, un, is;
	std::random_device rd;
	std::mt19937 rng(rd());
	std::ofstream f, f2;
	std::vector<int> elems;

	if (argc>3) {
		n = atoi(argv[1]);
		id = atoi(argv[2]);
		out_dir = std::string(argv[3]);
	} else return EXIT_FAILURE;

	std::uniform_int_distribution<> dist (1, n*100);

	for (unsigned j=0; j<n; j++)
		s1.insert(dist(rng));

	for (unsigned j=0; j<n; j++)
		s2.insert(dist(rng));

	for (unsigned j=0; j<n/10; j++)
		elems.push_back(dist(rng));

	f.open(std::format("{}/{}.in",   out_dir, id));
	f2.open(std::format("{}/{}.out", out_dir, id));

	f << rng()%2 << std::endl;

	f << std::format("{} {}", s1.size(), s2.size()) << std::endl;

	for (auto &i : s1) f << i << " ";
	f << std::endl;

	for (auto &i : s2) f << i << " ";
	f << std::endl;

	f << n/10 << std::endl;
	for (auto &elem : elems) f << elem << std::endl;

	for (auto &elem : elems) {
		if (s1.count(elem)>0) f2 << elem << " is in" << std::endl;
		else f2 << elem << " is not in" << std::endl;
	}

	std::set_union(s1.begin(), s1.end(), s2.begin(), s2.end(),
	               std::inserter(un, un.begin()));

	for (auto &i : un) f2 << i << " ";
	if (!un.empty()) f2 << std::endl;

	std::set_intersection(s1.begin(), s1.end(), s2.begin(), s2.end(),
	                      std::inserter(is, is.begin()));

	for (auto &i : is) f2 << i << " ";
	if (!is.empty()) f2 << std::endl;

	f.close();
	f2.close();

	return 0;
}
