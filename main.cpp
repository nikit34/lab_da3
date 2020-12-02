#include <iostream>
#include <fstream>
#include <cstring>
#include "TVector.h"
#include "TAvl.h"
#include "ActionTAvl.h"

#ifdef DMALLOC
#include "dmalloc.h"
#endif

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(nullptr);
	TVector cmd;
	TDetailAvl tree;

	while (std::cin >> cmd) {
		if (cmd[0] == '+')
			tree.DetailInsert();
		else if (cmd[0] == '-')
			tree.DetailRemove();
		else if (cmd[0] == '?')
			return 0;
		else if (cmd[0] == '!' && cmd.Size() == 1)
			tree.SaveLoad();
		else if (cmd[0] == '=')
			tree.Print();
		else
			tree.DetailFind(std::move(cmd));
	}

	return 0;
}