#include<iostream>
#include<vector>
#include<deque>
#include <utility>
#include<random>
using namespace std;

enum class single_hex :short{BLUE,RED,EMPTY};

class HexBoard {
public:
	HexBoard();
	HexBoard(int size);
	bool bfs(vector<pair<int, int>> search_queue);
	bool place_chess(int x,int y,char player);
	bool check_win(int x,int y);	
	string print_board();
private:
	vector<vector<char>>hex_board;
	int board_size;
	//single_hex player;
	//bool valid_flag;
};
//default board_size is 11
HexBoard::HexBoard(): board_size(11),hex_board(11,vector<char>(11,' ')) {};
HexBoard::HexBoard(int size) : board_size(size),hex_board(size, vector<char>(size, ' ')) {};
bool HexBoard::bfs(vector<pair<int, int>> search_queue ) {
	pair<bool, bool>reach_edge;
	reach_edge.first = false;
	reach_edge.second = false;
	if (search_queue.empty()) {
		return false;
	}

	//use broad first search
	int current_x = search_queue[0].first;
	int current_y= search_queue[0].second;
	char current_player = hex_board[current_x][current_y];
	vector<vector<bool>> visited(board_size, vector<bool>(board_size));
	deque<pair<int, int>> my_path;

	for (auto i = search_queue.begin(); i != search_queue.end(); ++i) {
		my_path.push_back(*i);
		visited[i->first][i->second] = true;
	}
	while (!(my_path.empty())) {
		pair<int,int> first_elem = my_path.front();
		if ((current_player == 'R' && first_elem.first == 0) || (current_player == 'B' && first_elem.second == 0)) {
			reach_edge.first = true;
		}
		if ((current_player == 'R' && first_elem.first == board_size-1) || (current_player == 'B' && first_elem.second == board_size - 1)) {
			reach_edge.second = true;
		}
		my_path.pop_front();
		//find neighbors near current node
		int x = first_elem.first-1;
		int y = first_elem.second;
		if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
			if (visited[x][y] != true && hex_board[x][y] == current_player) {
				my_path.push_back(make_pair(x, y));
				visited[x][y] = true;
			}
		}


		x = first_elem.first - 1;
		y = first_elem.second+1;
		if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
			if (visited[x][y] != true && hex_board[x][y] == current_player) {
				my_path.push_back(make_pair(x, y));
				visited[x][y] = true;
			}
		}

		x = first_elem.first ;
		y = first_elem.second - 1;
		if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
			if (visited[x][y] != true && hex_board[x][y] == current_player) {
				my_path.push_back(make_pair(x, y));
				visited[x][y] = true;
			}
		}

		x = first_elem.first;
		y = first_elem.second + 1;
		if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
			if (visited[x][y] != true && hex_board[x][y] == current_player) {
				my_path.push_back(make_pair(x, y));
				visited[x][y] = true;
			}
		}

		x = first_elem.first+1;
		y = first_elem.second - 1;
		if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
			if (visited[x][y] != true && hex_board[x][y] == current_player) {
				my_path.push_back(make_pair(x, y));
				visited[x][y] = true;
			}
		}

		x = first_elem.first + 1;
		y = first_elem.second ;
		if (x >= 0 && x < board_size && y >= 0 && y < board_size) {
			if (visited[x][y] != true && hex_board[x][y] == current_player) {
				my_path.push_back(make_pair(x, y));
				visited[x][y] = true;
			}
		}
	}
	
	return reach_edge.first && reach_edge.second;

};
bool HexBoard::place_chess(int x, int y, char player) {
	if (x >= 0 && x < board_size && y >= 0 && y < board_size && hex_board[x][y] == ' ') {
		hex_board[x][y] = player;
		return true;
	}
	else {
		return false;
	}
};
string HexBoard::print_board() {
	string output = "";
	
	output += hex_board[0][0];
	for (auto column = 1; column < board_size; column++) {
		output += " - ";
		output+= hex_board[0][column];
	}
	for (auto raw = 1; raw < board_size; raw++) {
		output += "\n";
		for (auto i = 0; i < 2*raw-1; i++) {
			output += " ";
		}
		//output += (raw," ");
		for (auto i = 0; i < board_size - 1; i++) {
			output += "\\ / ";
		}
		//output += (board_size - 1, "\\ / ");
		output+="\\";
		output += '\n';
		for (auto i = 0; i < raw * 2; i++) {
			output += " ";
		}
		//output+= (raw*2, " ");
		output+= hex_board[raw][0];
		for (auto column = 1; column < board_size; column++) {
			output += " - ";
			output += hex_board[raw][column];
		}
		output += "\n";
	}
	return output;
};

bool HexBoard::check_win(int x,int y) {
	//pair<bool, bool> reach_edge(false,false);
	if (x >= 0 && x < board_size && y >= 0 && y < board_size && hex_board[x][y] != ' ') {
		vector<pair<int, int>>search_queue(1, make_pair(x, y));
		return bfs(search_queue);
	}
	return false;
};

int main() {
	char player_human;
	char player_computer;
	bool who_goes = false;
	cout << "Welcome to the HEX game,Blue team should reach horizontally,Red team should reach vertically\n";
	cout << "First,please choose a team\n";
	cout << "Choose your color(enter B or R,Blue goes first):(B)Blue,(R)Red:";
	cin >> player_human;
	if (player_human == 'B') {
		player_computer = 'R';
	}
	else if (player_human == 'R') {
		player_computer = 'B';
	}
	while (!(player_human == 'B' || player_human == 'R')) {
		cout << "Choose your color(enter B or R,Blue goes first):(B)Blue,(R)Red:";
		cin >> player_human;
		if (player_human == 'B') {
			player_computer = 'R';
		}
		else if (player_human == 'R') {
			player_computer = 'B';
		}
	}
	HexBoard b=HexBoard(4);
	cout<<b.print_board();
	int temp_x;
	int temp_y;
	char temp_char;
	int computer_x;
	int computer_y;

	random_device seed;
	ranlux48 engine(seed());
	uniform_int_distribution<> distrib(0, 4);
	//int random = distrib(engine);
	if (player_human == 'B') {
		who_goes = false;
	}
	else if (player_human == 'R') {
		who_goes = true;
	}
	while (true) {
		
		if (who_goes) {
			cout << "computer move:\n";
			//COMPUTER MOVES RANDOMLY(DUMB)
			computer_x = distrib(engine);
			computer_y = distrib(engine);
			while (!b.place_chess(computer_x, computer_y, player_computer)) {
				//cout << "INVALID!please enter(i,j) to place a chess(0begins):";
				computer_x = distrib(engine);
				computer_y = distrib(engine);
			}
			cout << b.print_board();
			if (b.check_win(computer_x, computer_y)) {
				cout << "COMPUTER WIN";
				break;
			}
			;
		}
		else {
			cout << "please enter(i,j) to place a chess(0begins):";
			cin >> temp_x >> temp_char >> temp_y;
			while (!b.place_chess(temp_x, temp_y, player_human)) {
				cout << "INVALID!please enter(i,j) to place a chess(0begins):";
				cin >> temp_x >> temp_char >> temp_y;
			};
			cout << b.print_board();
			if (b.check_win(temp_x, temp_y)) {
				cout << "YOU WIN";
				break;
			}
		}

		who_goes = !who_goes;

	}
	
}

