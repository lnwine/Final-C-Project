#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <string>

class Card;
class Hand;
class Deck;
class Match;
class Game;

//struct to create a card with a value and a suit
struct Card
{
	std::string value;
	std::string suit;

public:
	Card(std::string value, std::string suit) : value(value), suit(suit) {}
	Card() : value(""), suit("") {}
	friend std::ostream &operator<<(std::ostream &os, const Card &c)
	{
		os << c.value << " of " << c.suit;
		return os;
	}
};

//a deck of cards
class Deck
{
	public:
	std::vector<Card> Cards;
	Deck createDeck();
	Hand Deal(Deck &d);
};

//a hand created from a deck
class Hand
{
public:
	std::vector<Card> HandCards;
	Card playCard();
	void collectCards(std::vector<Card> cards);
	int size();
};

//class to hold two players, each with a hand
class Match
{
public:
	Hand player1;
	Hand player2;
	int execute(Hand &player, Hand &comp);
};

//operator to sort cards by value
bool operator<(const Card &player, const Card &comp)
{
	int valP;
	int valComp;
	if(player.value != "Jack" && player.value != "Queen" && player.value != "King" && player.value != "Ace"){
		valP = atoi(player.value.c_str());}
	else if(player.value == "Jack"){
		valP = 11;}
	else if(player.value == "Queen"){
		valP = 12;}
	else if(player.value == "King"){
		valP = 13;}
	else if(player.value == "Ace"){
		valP = 14;}
	if(comp.value != "Jack" && comp.value != "Queen" && comp.value != "King" && comp.value != "Ace"){
		valComp = atoi(comp.value.c_str());}
	else if(comp.value == "Jack"){
		valComp = 11;}
	else if(comp.value == "Queen"){
		valComp = 12;}
	else if(comp.value == "King"){
		valComp = 13;}
	else if(comp.value == "Ace"){
		valComp = 14;}
	if(valP < valComp){
		return true;}
	return false;
}

//operator to tell if two cards are equal
bool operator==(const Card &player, const Card &comp)
{
	if(player.value == comp.value)
	{
		return true;
	}
	return false;
}

//create a standard 52 card deck
Deck createDeck()
{
	Deck d;
	std::vector<std::string> values = {"2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Ace"};
	std::vector<std::string> suits = {"Spades", "Hearts", "Clubs", "Diamonds"};

	for(int i = 0; i < 13; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			Card newCard;
			newCard.value = values[i];
			newCard.suit = suits[j];
			d.Cards.push_back(newCard);
		}
	}
	return d;
}

//Deal half the deck to a player
Hand Deal(Deck &d)
{
	Hand dealtHand;
	while(dealtHand.size() < 26)
	{
		int num = rand() % d.Cards.size();
		Card current = d.Cards[num];
		dealtHand.HandCards.push_back(current);
		d.Cards.erase(d.Cards.begin() + num);
	}
	return dealtHand;
}

//play a card from a hand
Card Hand::playCard()
{
	Card played = HandCards[0];
	//std::cout << HandCards[0];
	HandCards.erase(HandCards.begin());
	//std::cout << HandCards[0];
	return played;
}

//collect a vector of cards that have been played
void Hand::collectCards(std::vector<Card> cards)
{
	for(int i = 0; i < cards.size(); i++)
	{
		HandCards.push_back(cards[i]);
	}
}

int Hand::size()
{
	return HandCards.size();
}

//execute a single round of play
int Match::execute(Hand &player, Hand &comp)
{
	Card playerCard = player.playCard();
	std::cout << "You played: " << playerCard << "\n";
	//std::cout << player.playCard();
	Card compCard = comp.playCard();
	std::cout << "Computer played: " << compCard << "\n";
	std::vector<Card> allCards = {playerCard, compCard};
	if(playerCard < compCard)
	{
		std::cout << "You lose this round!" << "\n";
		comp.collectCards(allCards);
		//std::cout << comp.HandCards.size();
		std::cout << "Your current hand size is: " << player.HandCards.size() << "\n";
		std::cout << "Computer's current hand size is: " << comp.HandCards.size() << "\n";
		std::cout << "\n";
		return 1;
	}
	else if(compCard < playerCard)
	{
		std::cout << "You win this round!" << "\n";
		player.collectCards(allCards);
		std::cout << "Your current hand size is: " << player.HandCards.size() << "\n";
		std::cout << "Computer's current hand size is: " << comp.HandCards.size() << "\n";
		std::cout << "\n";
		return 2;
	}
	else if(playerCard == compCard)
	{
		std::cout << "It's a tie!" << "\n";
		std::vector<Card> playerHidden;
		std::vector<Card> compHidden;
		if(player.HandCards.size() > 4){
		playerHidden = {player.playCard(), player.playCard(), player.playCard()};}
		else{
			for(int i = 0; i < player.HandCards.size() -1; i++)
				{playerHidden.push_back(player.playCard());}
		}
		if(comp.HandCards.size() > 4){
		compHidden = {comp.playCard(), comp.playCard(), comp.playCard()};}
		else{
			for(int i = 0; i < comp.HandCards.size() -1; i++)
				{compHidden.push_back(comp.playCard());}
		}
		int result = execute(player, comp);
		if(result == 0)
		{
			result = execute(player, comp);
		}
		if(result == 1)
		{
			std::cout << "You lost the war! Cards you lost are: " << playerHidden[0] << ", " << playerHidden[1] << ", " << playerHidden[2] << "\n";
			comp.collectCards(allCards);
			comp.collectCards(playerHidden);
			comp.collectCards(compHidden);
			std::cout << "Your current hand size is: " << player.HandCards.size() << "\n";
			std::cout << "Computer's current hand size is: " << comp.HandCards.size() << "\n";
			std::cout << "\n";
		}
		else if(result == 2)
		{
			std::cout << "You won the war! Cards you win are: " << compHidden[0] << ", " << compHidden[1] << ", " << compHidden[2] << "\n";
			player.collectCards(allCards);
			player.collectCards(playerHidden);
			player.collectCards(compHidden);
			std::cout << "Your current hand size is: " << player.HandCards.size() << "\n";
			std::cout << "Computer's current hand size is: " << comp.HandCards.size() << "\n";
			std::cout << "\n";
		}
		return 0;

	}
}

int main()
{
	std::string begin;
	std::cout << "Welcome to the game of War! You have 100 rounds to try and win the game. Press any key to begin." << "\n";
	std::cin >> begin;
	Deck d = createDeck();
	Hand player;
	Hand comp;
	player = Deal(d);
	comp = Deal(d);
	Match newMatch;
	newMatch.player1 = player;
	newMatch.player2 = comp;
	int counter = 0;
	while(player.HandCards.size() != 0 && comp.HandCards.size() != 0 && counter <= 100)
	{
		std::string yes;
		newMatch.execute(player, comp);
		//std::cout << player.HandCards.size();
		std::cout << "Press any key to play another round: ";
		std::cin >> yes;
		counter++;
	}
	if(player.HandCards.size() < comp.HandCards.size())
	{
		std::cout << "Sorry, you lost the game." << std::endl;
	}
	else if (comp.HandCards.size() < player.HandCards.size())
	{
		std::cout << "Congratulations, you won the game!" << std::endl;
	}
	return 0;
}
