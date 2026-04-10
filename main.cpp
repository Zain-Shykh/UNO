#include<iostream>
#include<ctime>
#include <windows.h>
#include<cstdlib>
#include<fstream>
using namespace std;

//constant colors
const int BLACK = 0;
const int BLUE = 1;
const int GREEN = 2;
const int CYAN = 3;
const int RED = 4;
const int MAGENTA = 5;
const int YELLOW = 6;
const int WHITE = 7;


int main() ;
void startGame();
void shuffling(int deck[][15]);
//Function for console color
void setColor(int textColor, int bgColor) 
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}

int deck[8][15] = {0};
int discardpile[108]={0};
int TURN=0;
int wc;

    bool checkdeck(int deck[8][15]){
        bool flag;
    for(int i=0;i<8;i++){
        for(int j=0;j<15;j++){
            if(deck[i][j]!=0)
                return false;
            }

        }
        return true;
    }
    void repopulate(int deck[8][15],int discardpile[108]){
            int x=0;
        for(int i=0;i<8;i++){
        for(int j=0;j<15;j++){
            deck[i][j]=discardpile[x];
            discardpile[x]=0;
            x++;
            if(x==107)
            break;
        }
        }
        shuffling(deck);
    }
    void updatediscardpile(int topcard, int discardpile[]) 
    {
    	bool flag=checkdeck(deck);
    if(flag==true){
        repopulate(deck,discardpile);
    }
    for(int i=107;i>=0;i--)
    {
        discardpile[i]=discardpile[i-1];
    }
    discardpile[0] = topcard;
}

//Function for calling uno
bool calluno(int hand[],int count)
{
    int cardcount=0;
    char call;
    for(int i=0;i<count;i++)
    {
        if(hand[i]!=0){
            cardcount++;
        }
    }
    if(cardcount==2)
    {
        cin>>call;
        if(call=='U')
        return true;
        else
        return false;
    }
    
    return true;
	}
	
//Update hands function
void updatehand(int hand[], int &count) 
{
    int i = 0;
    while (i < count)
    {
        if (hand[i] == 0) 
        { 
            for (int j = i; j < count - 1; j++) 
            {
                hand[j] = hand[j + 1];
            }
            hand[count - 1] = 0;  
            count--;  
        }
       else
        {
            i++;  
        }
    }
}

//Save load game function
void saveLoadGameResult() 
{
    int a=0,b=0;
    ifstream inputFile("scores.txt");

    if (!inputFile)
    {
        cout << "Error" << endl;
        return;
    }
    inputFile >> a >> b;
    inputFile.close();

    if(TURN==0)
    {
        a++;
    } 
    else
    b++;
    ofstream outputFile("scores.txt");
    if (!outputFile) 
    {
        cout << "Error." << endl;
        return;
    }
    outputFile << a << " " << b << endl;
    outputFile.close();
}

//Function for draw card in
void drawcardin(int deck[8][15], int hand[], int &count)
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 15; j++)
         {
            if (deck[i][j] != 0)
           {  
                hand[count] = deck[i][j];  
                deck[i][j] = 0;  
                count++;  
                return;
            }
        }
    }
}

//function for handeling special cards 
void handleSpecialCard(int card, int &topCard, int hand1[], int &count1, int hand2[], int &count2)
{
    // int color;
    if(card/100!=0){
        int num=card%100;
    switch (num)
    {
        case 10: 
            cout << "You played a Skip card. Skipping the opponent's turn." << endl;
            if(TURN==0)
                TURN--;
            else if(TURN==1)
                TURN++;     
            break;

        case 11:  
            cout << "You played a Reverse card. Reversing the turn." << endl;
             if(TURN==0)
                TURN--;
            else if(TURN==1)
                TURN++;   
            break;

        case 12:  
            cout << "You played a Draw Two card. Opponent draws two cards." << endl;
            if (TURN == 0) 
            {
                drawcardin(deck, hand2, count2);
                drawcardin(deck, hand2, count2);
                TURN--;
            }
            else if(TURN==1)  
            {
                drawcardin(deck, hand1, count1);
                drawcardin(deck, hand1, count1);
                TURN++; 
            }
              
            break;
    }
}
    else if(card==1){
            cout << "You played a Wild card.\n Please Choose a color (5 = Red, 6 = Green, 7 = Blue, 8 = Yellow): ";
            cin >>wc;
            if(wc==5)
            cout<<"New Color is Red\n";
            else if(wc==6)
            cout<<"New Color is Green\n";
            else if(wc==7)
            cout<<"New Color is Blue\n";
            else if(wc==8)
            cout<<"New Color is Yellow\n";
    }
    	
    
       else if(card==2){
            cout << "You played a Wild Draw Four card. Opponent draws four cards." << endl;
            if (TURN == 0) 
            {
                drawcardin(deck, hand2, count2);
                drawcardin(deck, hand2, count2);
                drawcardin(deck, hand2, count2);
                drawcardin(deck, hand2, count2);
                drawcardin(deck, hand2, count2);
            }
            else if(TURN==1)
            {
                drawcardin(deck, hand1, count1);
                drawcardin(deck, hand1, count1);
                drawcardin(deck, hand1, count1);
                drawcardin(deck, hand1, count1);
                drawcardin(deck, hand1, count1);
            }
            
            cout << "Choose a color (5 = Red, 6 = Green, 7 = Blue, 8 = Yellow): ";
            cin >> wc;
            
              if(wc==5)
            cout<<"New Color is Red\n";
            else if(wc==6)
            cout<<"New Color is Green\n";
            else if(wc==7)
            cout<<"New Color is Blue\n";
            else if(wc==8)
            cout<<"New Color is Yellow\n";
            

            if(TURN==0)
                TURN--;
            else if(TURN==1)
                TURN++;
			}
						        
}

//card printing function
void printcard(int card)
 {
    int color, cardNumber;
    if(card==1){
    	cout << "-------------------" << endl;
    	cout << "|                 |" << endl;
    	cout << "|    Wild Card    |" << endl;
    	cout << "|                 |" << endl;
    	cout << "-------------------" << endl;
	}
	else if(card==2){
		cout << "-------------------" << endl;
    	cout << "|                 |" << endl;
    	cout << "| Wild Draw Four  |" << endl;
    	cout << "|                 |" << endl;
    	cout << "-------------------" << endl;
	}
	
    else if(card/100==0){
    color = card / 10; 
    cardNumber = card % 10;

    switch(color) 
    {
        case 5:
            setColor(BLACK, RED);
            cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, RED); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, RED); 
    		cout << "|     " << cardNumber << " Card      |";
    		setColor(WHITE, BLACK); 
        	cout<<endl;

    		setColor(BLACK, RED);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, RED); 
    		cout << "-------------------";
    		setColor(WHITE, BLACK);
    		cout<<endl;
 
            break;
        case 6:
            setColor(BLACK, GREEN);
            cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, GREEN); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, GREEN); 
    		cout << "|     " << cardNumber << " Card      |";
    		setColor(WHITE, BLACK); 
        	cout<<endl;

    		setColor(BLACK, GREEN);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, GREEN); 
    		cout << "-------------------";
    		setColor(WHITE, BLACK);
    		cout<<endl;
			 
            break;
        case 7:
            setColor(BLACK, BLUE);
			cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, BLUE); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, BLUE); 
    		cout << "|     " << cardNumber << " Card      |";
    		setColor(WHITE, BLACK); 
        	cout<<endl;

    		setColor(BLACK, BLUE);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, BLUE); 
    		cout << "-------------------";
    		setColor(WHITE, BLACK);
    		cout<<endl; 
    		
            break;
        case 8:
            setColor(BLACK, YELLOW);
            cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, YELLOW); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, YELLOW); 
    		cout << "|     " << cardNumber << " Card      |";
    		setColor(WHITE, BLACK); 
        	cout<<endl;

    		setColor(BLACK, YELLOW);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, YELLOW); 
    		cout << "-------------------" ;
    		setColor(WHITE, BLACK);
    		cout<<endl;
    		
            break;
        default:
            setColor(BLACK, WHITE);
            break;
    }

 }
 else if(card/100!=0){
 	color=card/100;
 	cardNumber=card%100;
 	switch(color) 
    {
        case 5:
            setColor(BLACK, RED);
			cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, RED); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, RED);
    		
			if(cardNumber==10)
			{
    			cout << "|    Skip Card    |";
    		}
    		else if (cardNumber == 11)
    		{
				cout << "|   Reverse Card  |";								
    		} 
    		else if (cardNumber == 12) 
    		{
    			cout << "|   Draw Two Card |";
    		}
    		setColor(WHITE, BLACK); 
        	cout<<endl;
        	
    		setColor(BLACK, RED);   
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, RED); 
    		cout << "-------------------" ;
    		setColor(WHITE, BLACK);
    		cout<<endl;
    		
            break;
        case 6:
            setColor(BLACK, GREEN);
            cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, GREEN); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, GREEN); 
    		
			if(cardNumber==10)
			{
    			cout << "|    Skip Card    |";
    		}
    		else if (cardNumber == 11)
    		{
				cout << "|   Reverse Card  |";								
    		} 
    		else if (cardNumber == 12) 
    		{
    			cout << "|   Draw Two Card |";
    		}
    		setColor(WHITE, BLACK); 
    		cout<<endl;

    		setColor(BLACK, GREEN);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);										
        	cout<<endl;

    		setColor(BLACK, GREEN); 
    		cout << "-------------------" ;
    		setColor(WHITE, BLACK);
    		cout<<endl;
			 
            break;
        case 7:
            setColor(BLACK, BLUE);
			cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, BLUE); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, BLUE);
    		
			if(cardNumber==10)
			{
    			cout << "|    Skip Card    |";
    		}
    		else if (cardNumber == 11)
    		{
				cout << "|   Reverse Card  |";								
    		} 
    		else if (cardNumber == 12) 
    		{
    			cout << "|   Draw Two Card |";
    		} 
    		
    		setColor(WHITE, BLACK); 
        	cout<<endl;

    		setColor(BLACK, BLUE);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, BLUE); 
    		cout << "-------------------" ;
    		setColor(WHITE, BLACK);
    		cout<<endl; 
			 
            break;
        case 8:
            setColor(BLACK, YELLOW);
            cout << "-------------------";
    		setColor(WHITE, BLACK);  
    		cout<<endl;
    		setColor(BLACK, YELLOW); 
    		cout << "|                 |";
    		setColor(WHITE, BLACK) ;
    		cout<<endl;
    
    		setColor(BLACK, YELLOW);
    		
    		if(cardNumber==10)
			{
    			cout << "|    Skip Card    |";
    		}
    		else if (cardNumber == 11)
    		{
				cout << "|   Reverse Card  |";	
            }								
    		else if (cardNumber == 12) 
    		{
    			cout << "|   Draw Two Card |";
    		} 
    		 
    		setColor(WHITE, BLACK); 
        	cout<<endl;

    		setColor(BLACK, YELLOW);  
    		cout << "|                 |";
    		setColor(WHITE, BLACK);
        	cout<<endl;

    		setColor(BLACK, YELLOW); 
    		cout << "-------------------" ;
    		setColor(WHITE, BLACK);
    		cout<<endl;
            
            break;
        default:
            setColor(BLACK, WHITE);		 
            break;
    }
 }
    
}
//helper functions
int color(int card){
    if(card==1)
    return 7;
    else if(card==2)
    return 7;
    else if(card/100==0){
    int a= card / 10; 
    if(a==5)
    return 4;
    else if(a==6)
    return 2;
    else if(a==7)
    return 1;
    else if(a==8)
    return 6;
    }
    else if(card/100!=0){
 	int b=card/100;
    if(b==5)
    return 4;
    else if(b==6)
    return 2;
    else if(b==7)
    return 1;
    else if(b==8)
    return 6;
    }
    return 7;
}
int cardtype(int card){
    if(card==1)
    return 13;
    else if(card==2)
    return 14;
    else if(card/100==0)
    return card % 10; 
    else if(card/100!=0)
 	return card%100;
    else
    return -1;
}

//Printing board on console function
void PrintBoard(int hand[], int count) {
    int rows;
    if(count<=12)
    rows=1;
    else if(count>=13 && count<=24)
    rows=2;
    else if(count>=25 && count<=36)
    rows=3;
    else if(count>=37 && count<=48)
    rows=4;
    else if(count>=49 && count<=60)
    rows=5;
    else if(count>=61 && count<=72)
    rows=6;
    else if(count>=73 && count<=84)
    rows=7;
    else if(count>=85 && count<=96)
    rows=8;
    else if(count>=97 && count<=108)
    rows=9;
    for(int j=0;j<rows;j++){
        int start,end;
        if(j == 0) {
            start = 0;
            end=12;
        } else if(j == 1) {
            start = 12;
            end=24;
        } else if(j == 2) {
            start = 24;
            end=36;
        } else if(j == 3) {
            start = 36;
           end=48;
        } else if(j == 4) {
            start = 48;
            end=60;
        } else if(j == 5) {
            start = 60;
            end=72;
        } else if(j == 6) {
            start = 72;
            end=84;
        } else if(j == 7) {
            start = 84;
            end=96;
        } else if(j == 8) {
            start = 96;
            end=108;
        }
        if (end > count) 
            end = count; 
    for (int i = start; i < end; i++) {
        int c = color(hand[i]);
        setColor(BLACK, c);
        cout << "------------";
        setColor(WHITE, BLACK);
        cout << "  ";
    }
    cout << endl;

    
    for (int i = start; i < end; i++) {
        int c = color(hand[i]);
        setColor(BLACK, c);
        cout << "|          |";
        setColor(WHITE, BLACK);
        cout << "  ";
    }
    cout << endl;

    
    for (int i = start; i < end; i++) {
        int c = color(hand[i]);
        int cardNumber = cardtype(hand[i]); 
        setColor(BLACK, c);
        cout << "|   " ;
        if(cardNumber>=0 && cardNumber<=9)
        cout<<cardNumber<<" ";
        else if(cardNumber==10)
        cout<<"S"<<" ";
        else if(cardNumber==11)
        cout<<"R"<<" ";
        else if(cardNumber==12)
        cout<<"D2";
        else if(cardNumber==13)
        cout<<"W ";
        else if(cardNumber==14)
        cout<<"W4";
        cout<< "     |";
        setColor(WHITE, BLACK);
        cout << "  ";
    }
    cout << endl;

   
    for (int i = start; i < end; i++) {
        int c = color(hand[i]);
        setColor(BLACK, c);
        cout << "|          |";
        setColor(WHITE, BLACK);
        cout << "  ";
    }
    cout << endl;

    
    for (int i = start; i < end; i++) {
        int c = color(hand[i]);
        setColor(BLACK, c);
        cout << "------------";
        setColor(WHITE, BLACK);
        cout << "  ";
    }
    
    cout << endl << endl;
    }
}
//function to check if a player has won
bool win(int hand1[],int count1, int hand2[],int count2) 
{
    bool flag = true;
    for (int i = 0; i < count1; i++) 
    {
        if (hand1[i] == 0)
            flag = true;
        else
         {
            flag = false;
            break;
         }
    }
    if (flag == true)
        return true;

    bool flag1 = true;
    for (int i = 0; i < count2; i++) 
    {
        if (hand2[i] == 0)
            flag1 = true;
        else 
        {
            flag1 = false;
            break;
        }
    }
    if (flag1 == true)
        return true;

    return false;  
}

//Function for dealing deck cards
void dealCards(int deck[8][15], int hand1[], int hand2[])
{
    int num = 0;
    for (int i = 0; i < 8; i++)
     {
        for (int j = 0; j < 15; j+=2) 
        {
            if(num>=7)
            break;
            else if (deck[i][j] != 0){
                hand1[num] = deck[i][j];
                deck[i][j] = 0;  
                num++;
            }
        }
    }
    num = 0;
    for (int i = 0; i < 8; i++)
     {
        for (int j = 0; j < 15; j++) 
        {
            if(num>=7)
            break;
            else if (deck[i][j] != 0){
                hand2[num] = deck[i][j];
                deck[i][j] = 0;  
                num++;
            }
        }
    }

}

//valid play function
bool isValidPlay(int playercard, int topcard)
{
    if(playercard==1 || playercard==2)
    return true;
    else if(topcard==1 || topcard==2){
        switch(wc){
            case 5:
            if(playercard/100==0 && playercard/10==5)
            return true;
            else if(playercard/100!=0 && playercard/100==5)
                return true;
            break;
            case 6:
            if(playercard/100==0 && playercard/10==6)
            return true;
            else if(playercard/100!=0 && playercard/100==6)
                return true;
            break;
            case 7:
            if(playercard/100==0 && playercard/10==7)
            return true;
            else if(playercard/100!=0 && playercard/100==7)
                return true;
            break;
            case 8:
            if(playercard/100==0 && playercard/10==8)
            return true;
            else if(playercard/100!=0 && playercard/100==8)
                return true;
            break;
        }
    }

    else if (playercard / 100 == 0 && topcard / 100 == 0) 
    {
        if (playercard / 10 == topcard / 10)  
            return true;

        else if (playercard % 10 == topcard % 10)  
            return true;


        else
            return false;
    }
    
    else if (playercard / 100 != 0 && topcard / 100 != 0) 
    {
        if (playercard / 100 == topcard / 100)  
            return true;
        else if (playercard % 100 == topcard % 100)  
            return true;
        else
            return false;
    }
    
    else
    {
        if (playercard / 100 != 0 && topcard / 100 == 0) 
        {
            if (playercard / 100 == topcard / 10)  
                return true;
            
            else
                return false;
        } 
        else if (playercard / 100 == 0 && topcard / 100 != 0) 
        {
            if (playercard / 10 == topcard / 100)  
                return true;
            
            else
                return false;
        }
    }
    return false;  
}

//function to initialize cards of deck 
void initializeDeck(int deck[][15]) 
{
    for (int i = 0; i < 8; i++) 
    {
        for (int j = 0; j < 15; j++)
        {
            deck[i][j] = 0;
        }
    }
    int a = 50;

    for (int i = 0; i < 8; i++)
     {
        for (int j = 0; j < 15; j++) 
        {
            if (j >= 13)
                continue;
            else if (i >= 4 && j == 0)
                continue;

            if (j > 9)
                deck[i][j] = a * 10 + j;
            else
                deck[i][j] = a + j;
        }
        if (a == 80)
            a = 40;
        a += 10;
    }
    for (int i = 0; i < 4; i++)
     {
        for (int j = 13; j < 14; j++)
         {
            deck[i][j] = 1;
        }
    }
    for (int i = 0; i < 4; i++)
     {
        for (int j = 14; j <= 14; j++)
         {
            deck[i][j] = 2;
        }
    }
}

//function for shuffling deck cards
void shuffling(int deck[][15])
 {
    srand(time(0));

    for (int i = 0; i < 108; i++) 
    {
        int a = rand() % 8;
        int c = rand() % 8;
        int d = rand() % 15;
        int b = rand() % 15;
        int temp = deck[a][b];
        deck[a][b] = deck[c][d];
        deck[c][d] = temp;
    }
}

//function for player turn
void playturn(int hand1[], int hand2[], int &topcard) 
{
    int input, input1, playercard;
    int count1 = 7, count2 = 7;  
    bool uno=true,uno1=true;
    cout<<"enter U to call uno before playing your second last card "<<endl;
    while (!win(hand1,count1,hand2,count2))
     {
        cout << "player 1 cards are : "<<endl;
        PrintBoard(hand1, count1);
        cout<<endl<<endl;
        cout << "player 2 cards are : "<<endl;
        PrintBoard(hand2, count2);
        cout << "top card is :\n";
        printcard(topcard);
        cout << endl;
         char draw,skip,et;
        if(TURN==0)
        {
        	st:
        cout<<" player 1 do you want to  draw card enter Y for yes N for no : ";
        cin>>draw;
		while(draw!='Y' && draw!='N' && draw!='E'){
			cout<<"invalid entry : ";
			cin>>draw;
		}
		if(draw=='E'){
			cout<<"do you really want to exit Y for yes and N for no : ";
			cin>>et;
			while(et!='Y'&&et!='N'){
				cout<<"invalid enter again : ";
				cin>>et;
			}
			if(et=='Y')
			exit(0);
			if(et=='N')
			goto st;
		}
        else if(draw=='Y')
        {
            cout << "Drawing a card..." << endl;
            drawcardin(deck, hand1, count1);
            cout << "player 1 cards are : "<<endl;
            PrintBoard(hand1, count1);
            sk:
            cout<<"player 1 do you want to skip enter Y for yes N for no: ";
            cin>>skip;
            while(skip!='Y' && skip!='N' && skip!='E'){
			cout<<"invalid entry : ";
			cin>>skip;
			}
            if(skip=='Y')
            {
                TURN++;
                goto nextturn;
            }
            else if(skip=='E'){
            cout<<"do you really want to exit Y for yes N for no : ";
			cin>>et;
			while(et!='Y'&&et!='N'){
				cout<<"invalid enter again : ";
				cin>>et;
			}
			if(et=='Y')
			exit(0);
			else if(et=='N')
			goto sk;
        	}
        }

        uno=calluno(hand1,count1);
        if(uno==false)
        {
            drawcardin(deck,hand1,count1);
            drawcardin(deck,hand1,count1);
        }

        cout << "enter card for player 1 : ";
        cin >> input;

        while(input<1 || input>count1)
        {
            cout<<"invalid input enter again : ";
            cin>>input;
        }

        playercard = hand1[input - 1];  
        hand1[input - 1] = 0;  

        
        if (isValidPlay(playercard, topcard)) 
        {
            handleSpecialCard(playercard, topcard, hand1, count1, hand2, count2);
            topcard = playercard;  
            updatehand(hand1,count1);
            updatediscardpile(topcard,discardpile);
           	if(win(hand1,count1,hand2,count2)){
            cout<<"player 1 has won the game "<<endl;
            TURN--;
           }
        } 
        else
        {
            
            while(!isValidPlay(playercard,topcard))
            {
            	hand1[input-1]=playercard;
            	cout<<"enter again coz this card is not playable : ";
            	cin>>input;
            	playercard = hand1[input - 1];
            }
        	handleSpecialCard(playercard, topcard, hand1, count1, hand2, count2);
         		hand1[input - 1] = 0;
         		updatehand(hand1,count1); 
         		topcard = playercard;
        		updatediscardpile(topcard,discardpile);
        	if(win(hand1,count1,hand2,count2)){
            	cout<<"player 1 has won the game "<<endl;
            	TURN--;
           	}
        }
        	TURN++;
        }

       else if(TURN==1)
       { 
         nextturn:
         	st1:
        cout<<"player 2 do you want to  draw card enter Y for yes and N for no : ";
        cin>>draw;
        while(draw!='Y' && draw!='N' && draw!='E'){
			cout<<"invalid entry : ";
			cin>>draw;
		}
		if(draw=='E'){
		cout<<"do you really want to exit Y for yes N for no : ";
			cin>>et;
			while(et!='Y'&&et!='N'){
				cout<<"invalid enter again : ";
				cin>>et;
			}
			if(et=='Y')
			exit(0);
			else if(et=='N')
			goto st1;
		}
        else if(draw=='Y')
        {
            cout << "Drawing a card..." << endl;
            drawcardin(deck, hand2, count2);
            cout << "player 2 cards are : "<<endl;
            PrintBoard(hand2, count2);
            sk1:
            cout<<"player 2 do you want to skip enter'Y' for yes 'N' for no: ";
            cin>>skip;
            while(skip!='Y' && skip!='N' && skip!='E'){
			cout<<"invalid entry : ";
			cin>>skip;
			}
            if(skip=='Y'){
                TURN--;
                continue;
            }
            else if(skip=='E'){
            	cout<<"do you really want to exit Y for yes N for no : ";
			cin>>et;
			while(et!='Y'&&et!='N'){
				cout<<"invalid enter again : ";
				cin>>et;
			}
			if(et=='Y')
			exit(0);
			else if(et=='N')
				goto sk1;
			}
        }

        uno1=calluno(hand2,count2);
        if(uno1==false)
        {
            drawcardin(deck,hand2,count2);
            drawcardin(deck,hand2,count2);
        }
        cout << "enter card for player 2 : ";
        cin >> input1;
        while(input1<1 || input1>count2)
        {
            cout<<"invalid input enter again : ";
            cin>>input1;
        }
        playercard = hand2[input1 - 1];  
        hand2[input1 - 1] = 0;  

        
        if (isValidPlay(playercard, topcard)) 
        {
            handleSpecialCard(playercard, topcard, hand1, count1, hand2, count2);
            topcard = playercard;  
            updatediscardpile(topcard,discardpile);
            updatehand(hand2,count2);
            if(win(hand1,count1,hand2,count2)){
            cout<<"player 2 has won the game "<<endl;
            TURN++;
           }
        } 
        else
         {
            while(!isValidPlay(playercard,topcard)){
                hand2[input1-1]=playercard;
            cout<<"enter again coz this card is not playable : ";
            cin>>input1;
            playercard = hand2[input1 - 1];
            }
            hand2[input1 - 1] = 0;
            topcard=playercard;
            handleSpecialCard(playercard, topcard, hand1, count1, hand2, count2);
            updatediscardpile(topcard,discardpile);
         updatehand(hand2,count2); 
         if(win(hand1,count1,hand2,count2)){
            cout<<"player 1 has won the game "<<endl;
            TURN++;
           }
        }
        TURN--;
    	}
    
     cout << "top card is: "<<endl;
     printcard(topcard);
     cout << endl;
    }
     saveLoadGameResult();
	startGame() ;


}
//For game starting
void startGame() 
{

        char input,et;
        stg:
        cout << "_._._._ WELCOME TO THE UNO GAME_._._._" << endl<<endl<<endl;
        cout << "Press 'Y' to Start the game or L to load previous scores or E to exit " << endl;
        cin>>input;
       	if (input== 'Y' || input == 'y')
        {
                return;
        }
        else if(input=='E'){
        	
        	cout<<"do you really want to exit Y for yes N for no : ";
			cin>>et;
			while(et!='Y'&&et!='N'){
				cout<<"invalid enter again : ";
				cin>>et;
			}
			if(et=='Y')
			exit(0);
			else if(et=='N')
			startGame();
		}
        else  if (input== 'l' || input == 'L')
        {
            int a=0,b=0;
            ifstream inputFile("scores.txt");
            if (!inputFile) 
            {
                cout << "Error" << endl;
            }
            inputFile>>a>>b;
            inputFile.close();
            
            cout << "Player 1 Score: "<<a<<endl;
            cout << "Player 2 Score: "<<b<<endl;
            cout<<endl<<endl<<"do you want to exit : ";
            cin>>et;
            
            while(et!='Y'&&et!='N'){
				cout<<"invalid enter again : ";
				cin>>et;
			}
			if(et=='Y')
			exit(0);
			else if(et=='N')
			startGame();
        }
      

}
//Main 
int main() 
{
	ofstream outputFile("scores.txt");
	if(!outputFile)
	{
		cout<<"Error"<<endl;
	}
	outputFile<<0<<" "<<0<<endl;
	outputFile.close();
	
    startGame();
    //hands for players
    int hand1[108] = {0};
    int hand2[108] = {0};
    
    initializeDeck(deck);
    shuffling(deck);
    int topcard;
    
    for(int i=0;i<8;i++){
        for(int j=0;j<15;j++){
            if(deck[i][j]!=0 && deck[i][j]!=1 && deck[i][j]!=2 && deck[i][j]/100==0){
                topcard=deck[i][j];
                deck[i][j]=0;
            }
            break;
        }
    }
    
    dealCards(deck, hand1, hand2);
    playturn(hand1, hand2, topcard);
    cout<<"the game is over "<<endl; 
//	int skipcards[8];
//	int a =0;
//	for(int i=0;i<8;i++){
//		for(int j=0;j<15;j++){
//			if(deck[i][j]%100==10){
//				skipcards[a]=deck[i][j];
//				a++;
//			
//			if(a==7)
//			break;
//			}
//		}
//	}
//	PrintBoard(skipcards,8);
}

