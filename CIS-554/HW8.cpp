//HW8 by Bo Li
//SU Net ID: bli158  SUID: 218717316

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <algorithm>    // random_shuffle
#include <random>
#include <fstream>

using namespace std;

vector<pair<string, int>> deck;
vector<pair<string, int>> collection;
ofstream file;
bool win = false;
bool firstTieRound = true;

void initDeck();
void shuffleCards(vector<pair<string, int>>& vec);

class Player {
public:
	vector<pair<string, int>> hand;
	vector<pair<string, int>> table;
	vector<string> popFromHand;

	int id;
	int cardsInHand;
	bool dealer;
	bool lost;
	bool tie;
	Player* next;

	Player() {
		id = 0;
		cardsInHand = 0;
		dealer = false;
		lost = false;
		next = nullptr;
		tie = false;
	}

	Player(int i) {
		id = i;
		cardsInHand = 0;
		dealer = false;
		lost = false;
		next = nullptr;
		tie = false;
	}

};


class Game {
public:
	Player* start;  // start to assign card
	Player* first;  // player 1
	int number_players;
	int dealer_pos;
	int cur_players;

	Game() {
		start = nullptr;
		first = nullptr;
		number_players = 0;
		dealer_pos = 0;
		cur_players = 0;
	}
	Game(int n, int d) {
		start = nullptr;
		first = nullptr;
		number_players = n;
		dealer_pos = d;
		cur_players = n;
	}

	~Game();
	void makePlayers();
	void assignCardsToPlayers();
	void battle();
	int findMin();
	int numWinners(int min);
	void endRoundForOneWinner(int min);
	void endRoundForMoreWinners(int min);
	bool outOFGame(Player* p);
	void gameOver(Player* theWinner, Player* theLoser);
	void printCardsForPlayers();
	void printWinner(Player* win);
};


void Game::makePlayers() {  // number of players n & position of dealer d
	Player* p;
	for (int i = number_players; i > 0; i--) {
		p = new Player(i);
		p->next = start;
		start = p;
	}

	p = start;
	while (p) {  // // player 1
		if (p->id == 1) {
			first = p;
			break;
		}

		p = p->next;
	}

	p = start;
	while (p) {  // make circular
		if (p->next == nullptr) {
			p->next = start;
			break;
		}
		p = p->next;
	}

	for (int i = 0; i < dealer_pos - 1; i++) {   // position of start to assign card
		start = start->next;
	}
	start->dealer = true;
	start = start->next;
}


void Game::assignCardsToPlayers() {
	initDeck();
	file << "************** initial deck of cards before shuffle ****\n\n";
	for (int i = 0; i < deck.size(); i++)
		file << deck[i].first << "  ";

	shuffleCards(deck);      // shuffle deck
	file << "\n\n****************** after shuffle **************\n\n";
	for (int i = 0; i < deck.size(); i++)
		file << deck[i].first << "  ";

	makePlayers();  // create players and dealer

	auto p = start;
	for (int i = 0; i < deck.size(); i++) { // assign 52 cards to player sequentially
		p->hand.insert(p->hand.begin(), deck[i]);
		p->cardsInHand++;
		p = p->next;
	}
}


void Game::printCardsForPlayers() {
	auto p = first;
	for (int i = 0; i < number_players; i++) {
		file << "cards for player " << p->id << "\n";

		for (int j = 0; j < p->hand.size(); j++) {
			file << p->hand[j].first << " ";
		}
		file << "\n";
		p = p->next;
	}
}


void Game::battle() {
	assignCardsToPlayers();

	file << "\n\n****************** after cards are dealt **************\n\n\n";
	printCardsForPlayers();
	file << "\n";

	while (true) {
		// Case 1: First Round
		// Case 2: Every player shows the first card in the hand on the table, 
		// 1 player wins with lowest card, and get all
		// Case 3: more than 1 players win, losts do nothing, winners shows two more cards on the table,
		// compare latest card. 

		if (cur_players == 2) {	// one player has 5 cards, will lose
			vector<Player*> lastTwo;
			auto p1 = first;

			while (p1) {
				if (!p1->lost)
					lastTwo.push_back(p1);

				p1 = p1->next;
				if (p1 == first)
					break;
			}

			if (lastTwo[0]->cardsInHand == 4) {		// lastTwo[1] WINS
				gameOver(lastTwo[1], lastTwo[0]);
				printWinner(lastTwo[1]);
				break;
			}
			else if (lastTwo[1]->cardsInHand == 4) {	// lastTwo[0] WINS
				gameOver(lastTwo[0], lastTwo[1]);
				printWinner(lastTwo[0]);
				break;
			}
		}

		auto p = first;
		while (p) {
			if (outOFGame(p)) 		// cur player lost the game
				p->lost = true;

			file << "Hand " << p->id << "\n";
			for (auto i : p->hand)
				file << i.first << " ";

			file << "\n\n";

			if (!p->lost) {
				p->table.insert(p->table.begin(), p->hand[0]);
				p->hand.erase(p->hand.begin());    // remove first card from vector
				p->cardsInHand--;	// each player reduce one card in his/her hand
			}

			p = p->next;
			if (p == first) {
				break;
			}
		}

		int minimum = findMin();

		if (numWinners(minimum) == 1) 			// only 1 winner
			endRoundForOneWinner(minimum);
		else if (numWinners(minimum) > 1) {		// tie winners
			endRoundForMoreWinners(minimum);
		}
	}
}


int Game::findMin() {		// find min card as winner
	vector<int> minCard;
	int min = 0;
	auto p = first;
	while (p) {
		if (!p->lost)
			minCard.push_back(p->table[0].second);

		p = p->next;
		if (p == first)
			break;
	}
	min = *min_element(minCard.begin(), minCard.end());
	return min;
}


int Game::numWinners(int min) {
	int winners = 0;
	auto p = first;
	while (p) {
		if (!p->lost) {
			if (min == p->table[0].second)
				winners++;
		}

		p = p->next;
		if (p == first)
			break;
	}

	return winners;
}


void Game::endRoundForOneWinner(int min) {		// End round for 1 winner
	auto winner = first;
	while (winner) {				// select winner
		if (!winner->lost) {
			if (winner->table[0].second == min)
				break;
		}
		winner = winner->next;
	}

	auto p = first;
	while (p) {
		file << "table " << p->id << "\n";
		if (!p->table.empty())
			file << p->table[0].first << "\n\n";
		else
			file << " " << "\n\n";

		while (!p->table.empty()) {	// pop table from each player, and push them into one collection
			collection.push_back(p->table[0]);
			p->table.erase(p->table.begin());
		}

		p = p->next;
		if (p == first)
			break;
	}

	for (auto i : collection) {	// winner wins all cards
		winner->hand.push_back(i);
		winner->cardsInHand++;	// winners cards increasing in hand
	}
	collection.clear();	// clear buffer on vector
	shuffleCards(winner->hand);	// winner shuffle cards
}


void Game::endRoundForMoreWinners(int min) {
	if (min == 0) return;
	if (cur_players == 1) return;

	vector<Player*> all_winners;
	vector<int> minCard;
	int winners = 0;

	auto winner = first;
	while (winner) {	// find all tie winners
		if (!winner->lost) {
			if (winner->table[0].second == min) {
				all_winners.push_back(winner);
				winners++;
				winner->tie = true;
			}
		}

		winner = winner->next;
		if (winner == first)
			break;
	}

	auto p = first;
	if (firstTieRound) {	// push first card from table to collection for all players
		while (p) {
			if (!p->table.empty())
				collection.push_back(p->table[0]);

			p = p->next;
			if (p == first)
				break;
		}
	}

	/* Print Out Battle for Tie Start */
	p = first;
	while (p) {
		if (!firstTieRound) {	// not first tie round
			file << "Hand " << p->id << "\n";

			if (!p->popFromHand.empty()) {
				for (auto i : p->popFromHand)
					file << i << " ";
				p->popFromHand.clear();
			}

			for (auto i : p->hand) {
				file << i.first << " ";
			}
			file << "\n\n";
		}

		p = p->next;
		if (p == first)
			break;
	}


	p = first;
	while (p) {
		if (firstTieRound) {	// first tie round
			file << "table " << p->id << "\n";
			if (!p->table.empty())
				file << p->table[0].first << "\n\n";
			else
				file << " " << "\n\n";
		}
		else {
			file << "table " << p->id << "\n";
			if (!p->table.empty()) {
				for (auto i : p->table) {
					file << i.first << " ";
				}
				file << "\n";
			}
			else
				file << " " << "\n";

			file << "\n";
		}

		p = p->next;
		if (p == first)
			break;
	}
	/* Print Out Battle for Tie End */


	if (winners > 1) {
		for (auto i : all_winners) {	// Tie winners Face up & Face down
			for (int j = 0; j < 2; j++) {
				i->table.insert(i->table.begin(), i->hand[0]);
				collection.push_back(i->hand[0]);	// collect winnners card into collection		
				i->popFromHand.push_back(i->hand[0].first);
				i->hand.erase(i->hand.begin());
				i->cardsInHand--;
			}
		}
	}

	for (auto i : all_winners) 	// comparing new round only for tie winners
		if (!i->lost)
			minCard.push_back(i->table[0].second);

	int newMin = 0;
	if (winners > 1)
		newMin = *min_element(minCard.begin(), minCard.end());	// find new min card among tie winners

	for (auto i : all_winners)	// Last winner duing tie battle
		winner = i;

	if (first)	// no more first tie round
		firstTieRound = false;

	// ----------------temporary put here !!------------------
	if (outOFGame(p))
		p->lost = true;

	if (winners > 1)	// recursive if the new round of tie winners is still tie
		endRoundForMoreWinners(newMin);
	else if (winners == 1) {
		firstTieRound = true;

		p = first;
		while (p) {		// clear tables & popFromHand for all players 
			if (!p->table.empty()) {
				p->table.clear();
				p->popFromHand.clear();
			}

			p = p->next;
			if (p == first)
				break;
		}

		for (auto i : collection) {	// winner wins all cards
			winner->hand.push_back(i);
			winner->cardsInHand++;	// winners cards increasing in hand
		}

		collection.clear();	// clear buffer on vector
		shuffleCards(winner->hand);	// winner shuffle cards
	}
}


bool Game::outOFGame(Player* p) { // player lost game
	if (p->lost) return false; // player has been lost

	if (p->cardsInHand < 5) {	// remove all info of the lost player
		if (!p->hand.empty()) {	// collect all rest of cards into collection from the lost player
			for (auto i : p->hand)
				collection.push_back(i);
		}

		p->hand.clear();
		p->table.clear();
		p->popFromHand.clear();
		p->cardsInHand = 0;
		p->tie = false;
		cur_players--;	// decrease current players in game

		return true;
	}
	return false;
}


void Game::gameOver(Player* theWinner, Player* theLoser) {
	cur_players--;

	for (auto i : theLoser->hand)	// winner collects all 52 cards
		theWinner->hand.push_back(i);

	theLoser->hand.clear();
	shuffleCards(theWinner->hand);
}


void Game::printWinner(Player* win)
{
	file << "Game Over!!  The winner is player " << win->id << "\n\n";
	auto p = first;
	while (p) {
		file << "Final hand " << p->id << "\n";
		if (p->hand.empty())
			file << " " << "\n";
		else {
			for (auto i : p->hand)
				file << i.first << " ";
			file << "\n";
		}
		file << "\n";

		p = p->next;
		if (p == first)
			break;
	}
}


Game::~Game() {
	Player* last = first;
	auto p = first;

	while (p) {		// retrieve last player
		last = p;

		p = p->next;
		if (p == first)
			break;
	}

	p = first;
	while (p) {		// release memory
		p->hand.clear();
		p->popFromHand.clear();
		p->table.clear();

		if (p != last) {
			auto temp = p->next;
			delete p;
			p = temp;
		}
		else {
			delete p;
			break;
		}
	}

	deck.clear();
	collection.clear();
}


void initDeck() {		// initialize deck with 52 cards
	vector<string> unit = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };
	vector<string> suit = { "C", "D", "H", "S" };
	int index = 0;
	for (int i = 0; i < 4; i++) {
		for (int j = 12; j >= 0; j--) {
			pair<string, int> pir = { unit[j] + suit[i], j + 1 };
			deck.push_back(pir);

			index++;
		}
	}
}


void shuffleCards(vector<pair<string, int>>& vec) {
	random_shuffle(begin(vec), end(vec));
}


int main()
{
	int player_num;
	int dealer;

	cout << "Number of players: ";
	cin >> player_num;
	if (player_num < 2 || player_num > 7)
		return 0;

	cout << "Dealer: (1-k): ";
	cin >> dealer;

	if (dealer < 1 || dealer > player_num)
		return 0;

	file.open("data1.txt");

	Game game(player_num, dealer);
	game.battle();

	file.close();
	cout << "Done" << endl;

	getchar();
	getchar();

	return 0;
}
