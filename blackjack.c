//Antonino Febbraro
//Project 1 Part 1 --- BlackJack Game 
//Due Date:October 2nd, 2016

#include <stdio.h>


int main() {

	//Display the opening title
	printf("Welcome, it is time to play some blackjack!\n");

	//assigning player two random cards to start

    //Instanciating the starting cards here
    int card1 = 0;
    int card2 = 0;
    int dealer = 0;
    int dealer2 = 0;
    int cardType = 0;

    static int aceDealt = 0; //Boolean to see if an ace has been dealt to determine if ace should be 1 or 11
    static int dealerAceDealt = 0; // same function as above variable, checking if ace was dealt for dealer

    //Setting up the random number generator
    srand(time(NULL));

    //To pick a random card, not just a random value
		//Making face cards (value of 10) more common by assinging them more keys
    cardType = rand() % (6-1+1)+1; //card type face (#3-5), ace (#6) or regular card number (#1-2).


    //for card 1
    if(cardType == 1 || cardType == 2){ //Reg card type
        card1 = rand() % (9-2+1)+1;
    }
    else if(cardType == 3 || cardType == 4 || cardType == 5){ //face card -- two options so that it is more common than other cards
        card1 = 10;
    }
    else{
        card1 = 11; //If ace is dealt, make it an 11 to start
        aceDealt = 1;
    }

    //for card 2
    cardType = rand() % (6-1+1)+1;
    if(cardType == 1 || cardType == 2){
        card2 = rand() % (9-2+1)+1;
    }
    else if(cardType == 3 || cardType == 4 || cardType == 5){
        card2 = 10;
    }
    else {
        if(aceDealt == 1){  //checking if ace was dealt
            card2 = 1;
        }
        else{  // So that you dont bust right off the bat with two aces worth 11 points
            card2 = 11; //if ace is dealt make it an 11 to start
        }
    }

    //dealer set up here

    //To pick a random card, not just a radnom value
    cardType = rand() % (6-1+1)+1; //card type face (#2), ace (#3) or regular card number (#1).

    //for card 1 -- dealer
    if(cardType == 1 || cardType == 2){ //Reg card type
        dealer = rand() % (9-2+1)+1;
    }
    else if(cardType == 3 || cardType == 4 || cardType == 5){ //face card
        dealer = 10;
    }
    else{ //Ace
        dealer = 11;
        dealerAceDealt = 1;
    }

    //for card 2 -- dealer
    cardType = rand() % (6-1+1)+1;
    if(cardType == 1 || cardType == 2){
        dealer2 = rand() % (9-2+1)+1;
    }
    else if(cardType == 3 || cardType == 4 || cardType == 5){
        dealer2 = 10;
    }
    else {

        if(dealerAceDealt == 1){ //checking if ace was dealt
            dealer2 = 1;
        }
        else{  // So that you dont bust right off the bat with two aces worth 11 points
            dealer2 = 11;
        }
    }


    //Initial sums to start the game
	int sum = card1 + card2;
        int dealerSum = dealer + dealer2;

    //The dealer --- to start off
    printf("The dealer: \n");
    printf("? + %d\n\n",dealer);

    //The Player --- Displaying their starting hand here
    printf("You:\n%d + %d = %d ",card1,card2,sum);

	//asking player for input and generating output
	char *hit[6];
	int contPlaying = 1;

	while(contPlaying == 1){ //keep playing up busted or player stands


		printf("Would you like to hit or stand? ");
		scanf("%s",&hit);
	        printf("\n");

		//checking for if player hit or stood
        if(strcmp(hit,"stand") == 0) {

            while(dealerSum < 17 && sum<=21){ //to meet project requirement of cpu after user stands dealer could still continue to hit

                int dealerNewCard = 0;

                cardType = rand() % (6-1+1)+1;
                if(cardType == 1 || cardType == 2){
                    dealerNewCard = rand() % (9-2+1)+1;
                }
                else if(cardType == 3 || cardType == 4 || cardType == 5){
                    dealerNewCard = 10;
                }
                else { //for Ace
                    if((dealerSum + 11) > 21)dealerNewCard = 1;
                    else{
                        dealerNewCard = 11;
                    }
                }
                dealerSum = dealerSum + dealerNewCard;
            }

            //Display who won here!!! -- check scores
            printf("Your hand: %d\nDealer hand: %d",sum,dealerSum); //printing scores
            if((sum > dealerSum || dealerSum > 21)&& sum <= 21){
                printf("\nYou Win!\n");

		if(dealerSum > 21 && sum <= 21) printf("\nDealer Busted! You Win!\n");
            }
            else {
                printf("\nDealer wins!");
            }

            contPlaying = 0;
        }
		else {

            //The dealer's hand displayed
            printf("The dealer: \n");
            printf("? + %d\n\n",dealer);

            //display player's new hand here --- also set up here
            int newCard = 0;

            cardType = rand() % (6-1+1)+1;
            if(cardType == 1 || cardType == 2){
                newCard = rand() % (9-2+1)+1;
            }
            else if(cardType == 3 || cardType == 4 || cardType == 5){
                newCard = 10;
            }
            else { //for Ace
               if((sum + 11)>21) newCard = 1; //if sum exceeds 21 when ace is dealt with value of 11, make value 1
               else {
                   newCard = 11; //if not exceed 21, make ace value 11
               }
            }
            printf("You:\n%d + %d = %d ",sum,newCard,sum + newCard);
            sum = sum + newCard;

            //Dealer sum
            if(dealerSum < 17){
                int dealerNewCard = 0;

                cardType = rand() % (6-1+1)+1;
                if(cardType == 1 || cardType == 2){
                    dealerNewCard = rand() % (9-2+1)+1;
                }
                else if(cardType == 3 || cardType == 4 || cardType == 5){
                    dealerNewCard = 10;
                }
                else { //for Ace
                    if((dealerSum + 11) > 21)dealerNewCard = 1;
                    else{
                        dealerNewCard = 11;
                    }
                }
                dealerSum = dealerSum + dealerNewCard;

            }

            if(dealerSum > 21){
                printf("\nDEALER BUSTED! You Win!\n");
                contPlaying = 0; //ends the game
            }

            if(sum > 21){

                printf("\nBUSTED! Dealer Wins!\n");
                contPlaying = 0; //ends the game

            }

        }

    }

	return 0; //to terminate the program

}
