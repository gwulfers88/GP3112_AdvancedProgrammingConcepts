#include <iostream>
#include <cassert>
#include <string>

using namespace std;

typedef int     fsm_state;
typedef char    fsm_input;

bool is_final_state(fsm_state state) {  return (state == 3) ? true : false;  }
fsm_state get_start_state(void) {  return 0;  }
fsm_state move(fsm_state state, fsm_input input)
{

	// our alphabet includes only 'a' and 'b'
	if (input != 'a' && input != 'b')
	{
		assert(0);
	}

	switch (state)
	{
	case 0:
	{
		if (input >= 'A' && input <= 'Z')
		{
			return 1;
		}
		else if (input == 'b')
		{
			return 0;
		}
	}break;

	case 1:
	{
		if (input == 'a')
		{
			return 1;
		}
		else if (input == 'b')
		{
			return 2;
		}
	}break;

	case 2:
	{
		if (input == 'a')
		{
			return 1;
		}
		else if (input == 'b')
		{
			return 3;
		}
	}break;

	case 3:
	{
		if (input == 'a')
		{
			return 1;
		}
		else if (input == 'b')
		{
			return 0;
		}
	}break;

	default:
		assert(0);
		break;
	}

	return 0;
}

bool recognize(string str) 
{
	if (str == "")
		return false;
		
	fsm_state state = get_start_state();
	string::const_iterator i = str.begin();
	fsm_input input = *i;
	
	while (i != str.end()) 
	{
		state = move(state, *i);
		++i;
	}
	
	if (is_final_state(state))
		return true;
	else
		return false;
	
}

// simple driver for testing
int main(int argc, char** argv)
{
	(recognize("this is a test thing.") ? cout << 1 : cout << 0);
  
	getchar();

	return 0;
}