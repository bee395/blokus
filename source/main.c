#include <stdio.h>
#include <string.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>
#include <sftd.h>
#include <time.h>
#include <stdlib.h>
#include "FreeSans_ttf.h"

extern const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
} blokken_img;

int titleScreen[4][20][5]={0};
int titlePlayer[4][4] = {0};
int titleCurrent[4] = {0};
int startscherm[(400/12)*(240/12)] = {0};

//---------------------------------------------------------------------------------
//variables
//---------------------------------------------------------------------------------
char *vormen[]={//laatste cijfer is de breedte van het vormpje
		"11",			//i1
		"112",			//i2
		"11012",		//v3
		"1113",			//i3
		"11112",//5		//o4
		"0101113",//6	//t4
		"11114",		//i4
		"0011113",//8	//l4
		"0111103",		//z4
		"0100101113",	//t5
		"1001001113",	//v5
		"011111004",	//n
		"0011111003",	//z5
		"111115",		//i5
		"1011112",		//u
		"0111101003",	//w
		"1110112",		//p
		"0111100103",	//f
		"0101110103",	//x
		"010011114"		//y
};
int center = (400-20*12)/2;
int totalPlayers = 1;
int optacie = 0;

int tick=0;

//static
int gameStatus = 1;
int field[400] = {0};
int startPosition[4] = {0,399,19,380};
int playerStatus[4];
int playerActive = 0;

char used[4][20];
char currentPiece[32];
char neergelegt[4][21];
int x_as;
int y_as;
int turn;
int stukje;
int rotation = 0;
int flip = 0;
int opgegeven[4]={0};

int frames = 0;

u64 lastTime;

void setupTilteScreen(){
	titleScreen[0][0][0] = 7;//vormpje
	titleScreen[0][0][1] = 5;//x
	titleScreen[0][0][2] = 4;//y
	titleScreen[0][0][3] = 1;//flip
	titleScreen[0][0][4] = 2;//rotate
	
	titleScreen[1][0][0] = 10;
	titleScreen[1][0][1] = 5;
	titleScreen[1][0][2] = 6;
	titleScreen[1][0][3] = 1;
	titleScreen[1][0][4] = 0;
	
	titleScreen[2][0][0] = 5;
	titleScreen[2][0][1] = 6;
	titleScreen[2][0][2] = 5;
	titleScreen[2][0][3] = 1;
	titleScreen[2][0][4] = 1;
	//
	titleScreen[3][0][0] = 13;
	titleScreen[3][0][1] = 9;
	titleScreen[3][0][2] = 4;
	titleScreen[3][0][3] = 1;
	titleScreen[3][0][4] = 1;
	
	titleScreen[0][1][0] = 1;
	titleScreen[0][1][1] = 10;
	titleScreen[0][1][2] = 8;
	titleScreen[0][1][3] = 1;
	titleScreen[0][1][4] = 0;
		
	//
	titleScreen[2][1][0] = 10;
	titleScreen[2][1][1] = 13;
	titleScreen[2][1][2] = 4;
	titleScreen[2][1][3] = 0;
	titleScreen[2][1][4] = 1;
	
	titleScreen[3][1][0] = 1;
	titleScreen[3][1][1] = 13;
	titleScreen[3][1][2] = 5;
	titleScreen[3][1][3] = 1;
	titleScreen[3][1][4] = 1;
	
	titleScreen[1][1][0] = 16;
	titleScreen[1][1][1] = 13;
	titleScreen[1][1][2] = 7;
	titleScreen[1][1][3] = 1;
	titleScreen[1][1][4] = 1;
	//
	titleScreen[3][2][0] = 1;
	titleScreen[3][2][1] = 17;
	titleScreen[3][2][2] = 4;
	titleScreen[3][2][3] = 1;
	titleScreen[3][2][4] = 1;

	titleScreen[0][2][0] = 14;
	titleScreen[0][2][1] = 17;
	titleScreen[0][2][2] = 6;
	titleScreen[0][2][3] = 0;
	titleScreen[0][2][4] = 2;
	
	titleScreen[2][2][0] = 0;
	titleScreen[2][2][1] = 19;
	titleScreen[2][2][2] = 5;
	titleScreen[2][2][3] = 1;
	titleScreen[2][2][4] = 0;

	titleScreen[1][2][0] = 0;
	titleScreen[1][2][1] = 19;
	titleScreen[1][2][2] = 8;
	titleScreen[1][2][3] = 1;
	titleScreen[1][2][4] = 0;
	//
	titleScreen[1][4][0] = 3;
	titleScreen[1][4][1] = 21;
	titleScreen[1][4][2] = 4;
	titleScreen[1][4][3] = 1;
	titleScreen[1][4][4] = 1;
	
	titleScreen[3][3][0] = 2;
	titleScreen[3][3][1] = 21;
	titleScreen[3][3][2] = 7;
	titleScreen[3][3][3] = 1;
	titleScreen[3][3][4] = 2;
	
	titleScreen[2][3][0] = 3;
	titleScreen[2][3][1] = 23;
	titleScreen[2][3][2] = 4;
	titleScreen[2][3][3] = 1;
	titleScreen[2][3][4] = 1;	
	
	titleScreen[0][3][0] = 1;
	titleScreen[0][3][1] = 23;
	titleScreen[0][3][2] = 7;
	titleScreen[0][3][3] = 1;
	titleScreen[0][3][4] = 1;
	//
	titleScreen[2][4][0] = 7;
	titleScreen[2][4][1] = 25;
	titleScreen[2][4][2] = 4;
	titleScreen[2][4][3] = 1;
	titleScreen[2][4][4] = 2;
	
	titleScreen[1][5][0] = 3;
	titleScreen[1][5][1] = 25;
	titleScreen[1][5][2] = 6;
	titleScreen[1][5][3] = 1;
	titleScreen[1][5][4] = 0;

	titleScreen[3][4][0] = 7;
	titleScreen[3][4][1] = 25;
	titleScreen[3][4][2] = 7;
	titleScreen[3][4][3] = 1;
	titleScreen[3][4][4] = 0;
}

//---------------------------------------------------------------------------------
void copy_string(char d[], char s[]) {
//---------------------------------------------------------------------------------
   int c = 0;
 
   while (s[c] != '\0') {
      d[c] = s[c];
      c++;
   }
   d[c] = '\0';
}

//---------------------------------------------------------------------------------
void prepairGame(){
//---------------------------------------------------------------------------------
	//field[400] = {0};
	x_as = 0;
	y_as = 0;
	turn = 0;
	stukje = 0;
	flip = 1;
	rotation = 0;

	for(int i = 0; i<400; i++){
		field[i]=0;
	}
	for(int p = 0; p<=totalPlayers; p++){
		for(int i = 0; i<20; i++){
			used[p][i]=0;
		}
		opgegeven[p]=0;
	}
	
	playerActive = 0;
	playerStatus[0] = 1;
	playerStatus[1] = 1;
}

//---------------------------------------------------------------------------------
int * getFinalScore(){
//---------------------------------------------------------------------------------
	static int scores[4];
	for(int i = 0; i <= totalPlayers; i++){
		int score = 0;
		for(int k = 0; k <20; k++){
			if(used[i][k] == 0){
				char breedte[32];
				copy_string(breedte, vormen[k]);
				int cool = strlen(breedte)-1;
				for(int p = 0; p <cool; p++){
					if(breedte[p]=='1'){
						score++;
					}
				}
			}
		}
		scores[i] = -score;
		if(neergelegt[i][19]!='\0'){
			scores[i] = scores[i] + 15;
			if(neergelegt[i][19]=='0'){
				scores[i] = scores[i] + 5;
			}
		}
	};
	return scores;
}

//---------------------------------------------------------------------------------
int calculateScore(int fieldLocal[400]){
//---------------------------------------------------------------------------------

	int length = sizeof(vormen) / sizeof(int);
	int totalPoints = 0;
	char breedte[32];
	
	for(int i = 0; i<length; i++){
		copy_string(breedte, vormen[i]);
		
		for(int k = 0; k < strlen(breedte)-1; k++){
			totalPoints++;
		}
	}
	
	for(int i = 0; i<400; i++){
		if(field[i] == playerActive+1){
			totalPoints--;
		}
	}
	
	return totalPoints;
}

//---------------------------------------------------------------------------------
void nextPlayer(){
//---------------------------------------------------------------------------------
	int instap = playerActive;

	do{
		if(playerActive < totalPlayers){
			playerActive++;
		}else{
			turn++;
			playerActive = 0;
		}
	}while(opgegeven[playerActive]==1&&instap!=playerActive);
	
	x_as = 0;
	y_as = 0;
	for(int i = 0; i < 20; i++){//TODO: als alle stukjes zijn neergelegt blijf je maar met het laatste stukje in je hand zitten, als je die probeert te draaien crasht het spel.
		if(used[playerActive][i] == 0 && opgegeven[playerActive]==0){
			stukje = i;
			break;
		}else{
			int teller = 0;
			for(int p = 0; p <= totalPlayers; p++){
				if(opgegeven[p]==1){
					teller++;
				}
			}
			if((turn==20)||(teller==totalPlayers+1)){
				int hoogsteScore = -100;
				int beste = 0;
				for(int k = 0 ; k <= totalPlayers; k++){
					if(getFinalScore()[k]>hoogsteScore){
						hoogsteScore = getFinalScore()[k];
						beste = k;
					}
				}
				for(int k = 0; k < 400; k++){
					field[k] = beste + 1;
				}
			}
		}
	}
	rotation = 0;
}

//---------------------------------------------------------------------------------
void rotate(char breedte[32], int flip, int rotation){
//---------------------------------------------------------------------------------
	int cool = strlen(breedte)-1;		//totalelengte
	int coolp = (breedte[cool] - '0');	//breedte
	char buffer[32];
	//char Scoolp[1];
	char tijdelijk[6] = {'0','1','2','3','4','5'};
	rotation=rotation%4;
	flip=flip%2;
	copy_string(buffer, breedte);
	
	if(flip==0){
		for(int i = 0; i < cool; i++){
			buffer[i] = breedte[coolp - (i%coolp + 1) + i/coolp*coolp];
		}
		copy_string(breedte, buffer);
	}
	
	if(rotation == 0){
		for(int i = 0; i < cool; i++){
			buffer[i] = breedte[i];
		}
	}else if(rotation==1){
		for(int i = 0; i < cool; i++){
			buffer[i] = breedte[coolp-1+i%(cool/coolp)*coolp-i/(cool/coolp)];
		}
		buffer[cool] = tijdelijk[cool/coolp];
	}else if(rotation==2){
		for(int i = 0; i < cool; i++){
			buffer[i] = breedte[cool-i-1];
		}
	}else if(rotation==3){
		for(int i = 0; i < cool; i++){
			buffer[i] = breedte[cool-coolp-1*i%(cool/coolp)*coolp+i/(cool/coolp)];
		}
		buffer[cool] = tijdelijk[cool/coolp];
	}
	copy_string(breedte, buffer);
}

void doMove(int playerActive, int stukje, int rotation, int flip, int x_as, int y_as){
	char breedte[32];
	copy_string(breedte, vormen[stukje]);
	rotate(breedte, flip, rotation);
	
	int cool = strlen(breedte)-1;		//totalelengte
	int coolp = (breedte[cool] - '0');	//breedte
  //if(legalMove(breedte, i%20, i/20)==0){
	if(legalMove(breedte, x_as, y_as)==0){
		for(int i=0; i < cool; i++){
			if(breedte[i]=='1'){
				field[(y_as+i/coolp)*20+x_as+i%coolp] = playerActive+1;
			}
		}
	used[playerActive][stukje]=1;
	neergelegt[playerActive][turn] = stukje + '0';
	nextPlayer();		
	}
}

int spelAfgelopen(){
	//int scores[4];
	//sprintf(scores, getFinalScore());
	int getalletje = 0;
	for(int i = 0; i <= totalPlayers; i++){
		if(opgegeven[i]==1){
			getalletje++;
		}else{
			for(int k = 0; k < 20; k++){
				if(used[i][k]==0){
					break;
				}else{
					if(k==19){
						getalletje++;
					}
				}
			}
		}
	}
	if(getalletje >= 2){
		gameStatus = 2;
		return 1;
	}
	return 0;
}


//---------------------------------------------------------------------------------
int legalMove(char breedte[32], int x_as, int y_as){//112
//---------------------------------------------------------------------------------

	int aanliggend = 1;
	int cool = strlen(breedte)-1;		//totalelengte
	int coolp = (breedte[cool] - '0');	//breedte
	
	//((x_as+i%coolp)+k%2*2-1)/20)==0) is x_as+k%2*2-1>=0 && (x_as+i%coolp)+k%2*2-1<=19 
	if(x_as >= 0 && y_as >= 0){
		if((x_as+(coolp-1))%20 >= x_as && (y_as+(cool/coolp-1))%20 >= y_as){//voorkomt dat stukje doorloopt op volgende regel
			for(int i=0; i<cool; i++){
				if(breedte[i]=='1'){
					if(field[(y_as+i/coolp)*20+i%coolp+x_as]==0){
						for(int k=0; k<4; k++){
							if(aanliggend!=0){//schuin
								if(turn == 0){
									if((y_as+i/coolp)*20+i%coolp+x_as == startPosition[playerActive]){
										aanliggend = 0;
									}
								}else{
									if(x_as+i%coolp+k%2*2-1>=0 && x_as+i%coolp+k%2*2-1<=19 && y_as+i/coolp+k/2*2-1 >=0 && y_as+i/coolp+k/2*2-1<=19){//werkt iets niet
										if(field[x_as+i%coolp+k%2*2-1+(y_as+i/coolp+k/2*2-1)*20]==playerActive+1)aanliggend = 0;
										//if(field[i/coolp*20+i%coolp+(y_as+k/2*2-1)*20+x_as+k%2*2-1]==playerActive+1)aanliggend = 0;
									}
								}
							}
							if(x_as+i%coolp+k/2*(k%2*2-1) >= 0 && x_as+i%coolp+k/2*(k%2*2-1) <= 19 && y_as+(1-k/2)*(k%2*2-1) >=0 && y_as+(1-k/2)*(k%2*2-1) <=19){//aanliggend
								if(field[x_as+i%coolp+k/2*(k%2*2-1)+(y_as+i/coolp+(1-k/2)*(k%2*2-1))*20] == playerActive+1){
									/*if(playerActive==0){
									char text[1000];
									sprintf(text, "		%d	%d	%d	%d	%d	%d	%s", x_as+i%coolp+k/2*(k%2*2-1)+(y_as+i/coolp+(1-k/2)*(k%2*2-1))*20, x_as+y_as*20+i%coolp+i/coolp*20, k, i, x_as, y_as, breedte);
									//als k = 0 is er een probleem en als je hem 2 vakjes onder een eigen vakje zet. Dan denkt hij dat er een probleem is.
									//als het goed is werkt het weer.
									print(text);
									}*/
					
									return 3;//	waarschijnlijk moeten alle i/coolp van de y_as vervangen worden door (cool/coolp), werkt dus nog niet. 
								}
							}
						}
					}else{
						return 2;
					}
				}
			}
		}
	}
	
	if(aanliggend==0){//
		return 0;
	}
	return 1;
}

int main()
{
	srand(time(NULL));
		
	sf2d_init();
	sf2d_set_clear_color(RGBA8(0x40, 0x40, 0x40, 0xFF));
	sf2d_set_vblank_wait(0);
	sf2d_texture *tex3 = sf2d_create_texture_mem_RGBA8(blokken_img.pixel_data, blokken_img.width, blokken_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);

	// Font loading
	sftd_init();
	sftd_font *font = sftd_load_font_mem(FreeSans_ttf, FreeSans_ttf_size);
	
	u32 kHeld;
	u32 kDown;
	
	setupTilteScreen();//
	prepairGame();

	while (aptMainLoop()) {

		hidScanInput();
		//hidCircleRead(&circle);
		kHeld = hidKeysHeld();
		kDown = hidKeysDown();

		if (kHeld & KEY_START) {
			break;
		}
		if(kDown & KEY_Y){
			prepairGame();
		}
		
		if(gameStatus==1){

			if(playerStatus[playerActive] == 0){
		if((kHeld & KEY_CPAD_UP)||(kDown & KEY_CPAD_UP)){
			if(kDown){
				if(y_as>0){
					y_as--;
					frames = 0;
				}
			}else if(kHeld && (frames % 5 == 0)){
				if(y_as>0){
					y_as--;
					frames = 0;
				}
			}
		}else if((kHeld & KEY_CPAD_DOWN)||(kDown & KEY_CPAD_DOWN)){
			if(kDown){
				if(y_as<19){
					y_as++;
					frames = 0;
				}
			}else if(kHeld && (frames % 5 == 0)){
				if(y_as<19){
					y_as++;
					frames = 0;
				}
			}
		}
		
		if((kHeld & KEY_CPAD_RIGHT)||(kDown & KEY_CPAD_RIGHT)){
			if(kDown){
				if(x_as<19){
					x_as++;
					frames = 0;
				}
			}else if(kHeld && (frames % 5 == 0)){
				if(x_as<19){
					x_as++;
					frames = 0;
				}
			}
		}else if((kHeld & KEY_CPAD_LEFT)||(kDown & KEY_CPAD_LEFT)){
			if(kDown){
				if(x_as>0){
					x_as--;
					frames = 0;
				}
			}else if(kHeld && (frames % 5 == 0)){
				if(x_as>0){
					x_as--;
					frames = 0;
				}
			}
		}if((kDown & KEY_L) && (stukje>0)){//TODO: als alle stukjes zijn neergelegt blijf je maar met het laatste stukje in je hand zitten, als je die probeert te draaien crasht het spel.
			for(int i = stukje-1; i >=0; i--){
				if(used[playerActive][i]==0){
					stukje = i;
					break;
				}
			}
		}else if((kDown & KEY_R) && (stukje<20)){//TODO: als alle stukjes zijn neergelegt blijf je maar met het laatste stukje in je hand zitten, als je die probeert te draaien crasht het spel.
			for(int i = stukje+1; i<20; i++){
				if(used[playerActive][i]==0){
					stukje = i;
					break;
				}
			}
		}
		
		if(kDown & KEY_DLEFT){
			if(rotation > 0){
				rotation--;
			}else{
				rotation = 3;
			}
		}else if(kDown & KEY_DRIGHT){
			if(rotation < 3){
				rotation++;
			}else{
				rotation = 0;
			}
		}else if(kDown & KEY_DUP){
			flip = 1-flip;
		}
		
		if(kDown & KEY_A){
			doMove(playerActive, stukje, rotation, flip, x_as, y_as);
		}
			
		if(kDown & KEY_X){
			opgegeven[playerActive]=1;
			nextPlayer();
		}
			}else{//-----AI-----
				
			u64 timeInSeconds = osGetTime() / 1000;
			srand (timeInSeconds);
			int score[4]={0};
			char besteStukje[32];
			int test = 0;
			
			for(int i = 0; i<400; i++){
				for(int p = 0; p < 20; p++){
					if(used[playerActive][p]!=1){
						char breedte[32];
										
						copy_string(breedte, vormen[p]);
						int cool = strlen(breedte)-1;
						int coolp = (breedte[cool] - '0');
						rotate(breedte, 1, 0);
					
						if(legalMove(breedte, i%20, i/20)==0){
							int Scorenumber = i;
							
							int fieldLocal[400];
							for(int lol = 0; lol< 400; lol++){
								fieldLocal[lol] = field[lol];
							}
							
							for(int k=0; k < cool; k++){
								if(breedte[k]=='1'){
									fieldLocal[(i/20+k/coolp)*20+i%20+k%coolp] = playerActive+1;
								}
							}
							Scorenumber = calculateScore(fieldLocal);
							// && rand()%10==0
							//if(Scorenumber>score[1] && rand()%5 >=1){
							if(Scorenumber > score[3]){

								//highestMove = countPossibleMoves(fieldLocal);
								//highestLeak = countLeaks(fieldLocal);
								
								score[0]=i;
								test=Scorenumber;
								score[1]=p;
							//	score[2]=(int)(breedte - '0');
								copy_string(besteStukje, breedte);
								score[3]=calculateScore(fieldLocal);
							}
						}
					}
				}
			}
			if(test==0){
				opgegeven[playerActive]=1;
				nextPlayer();
			}else{
				doMove(playerActive, score[1], 0, 1, score[0]%20, score[0]/20);
			}
			
			//int coolkp = rand() % sizeof list;
			//int number = score[1];
			//x_as = score[0]%20;
			//y_as = score[0]/20;
			
			//char breedte[32];
			//char source[32];
			//sprintf(source, "%d", besteStukje);
			//copy_string(breedte, besteStukje);
			//copy_string(breedte, source);
			//rotate(breedte, 1, 0);
			//int cool = strlen(breedte)-1;
			//int coolp = (breedte[cool] - '0');
			
			//AI still can't rotate or flip a piece
							
			//used[playerActive][number]=1;
			//rotate(breedte, 0, 0);
			//print(text);
			//print(breedte);
			
			
			//nextPlayer();
			
			/*for(int stop = 0;stop <20;stop++){
				if(used[playerActive][stop]==0 && countPossibleMoves(field)>0){// && countPossibleMoves(field)>0
					break;
				}
				else if(stop==19){
					prepGame();
				}
			}*/
			}
		
		//offset3d = CONFIG_3D_SLIDERSTATE * 30.0f;
		}else if (gameStatus==0){
			if(kDown & KEY_A){
				gameStatus = 1;
			}
		}else if (gameStatus == 2 ){
			
		}
		sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);
			sftd_draw_textf(font, 10, 10, RGBA8(0, 255, 255, 255), 15, "FPS %f", sf2d_get_fps());
			int *score5;
			score5 = getFinalScore();
			for(int i = 0; i<4; i++){
				//
				sftd_draw_textf(font, 10, 30+15*i, RGBA8(255, 255, 255, 255), 15, "Speler %d: %d", i, score5[i]);
			}
			sftd_draw_textf(font, 10, 95, RGBA8(255, 255, 255, 255), 15, "stukje: %d", stukje);
			sftd_draw_textf(font, 10, 110, RGBA8(255, 255, 255, 255), 15, "playerActive: %d", playerActive);
			sftd_draw_textf(font, 10, 125, RGBA8(255, 255, 255, 255), 15, "turn: %d", turn);
			sftd_draw_textf(font, 10, 140, RGBA8(255, 255, 255, 255), 15, "neergelegt: %d", neergelegt[0][turn]- '0');
			for(int i = 0; i<2; i++){
				int b = titleCurrent[2];
				sftd_draw_textf(font, 10, 155+20*i, RGBA8(255, 255, 255, 255), 15, "opgegeven0: %d", opgegeven[i]);
				sftd_draw_textf(font, 160, 155+20*i, RGBA8(255, 255, 255, 255), 15, "opgegeven1: %d", opgegeven[i]);
				
				//titleScreen[i][b][1];
			}
			int b = titleCurrent[2];
			sftd_draw_textf(font, 10, 155+20*3, RGBA8(255, 255, 255, 255), 15, "titlePlayer: %d", b);
				

		sf2d_end_frame();
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		if(gameStatus==1){
			for(int i = 0; i < 400; i++){//field
				sf2d_draw_texture_part(tex3, center + i%20*12, i/20*12, field[i]*12, 0, 12, 12);
			}
			
			char breedte[32];
			copy_string(breedte, vormen[stukje]);
			rotate(breedte, flip, rotation);
			
			int cool = strlen(breedte)-1;
			int coolp = (breedte[cool] - '0');
			
			for(int i=0; i < cool; i++){//piece
				if(breedte[i]=='1'){
					sf2d_draw_texture_part(tex3, center+i%coolp*12+x_as*12, i/coolp*12+y_as*12, playerActive*12+12, 0, 12, 12);
				}
			}
			if(spelAfgelopen()==1){
			}
		}else if (gameStatus==0){
			
			for(int i = 0; i < (400/12)*(240/12); i++){
				sf2d_draw_texture_part(tex3, i%(400/12)*12, i/(400/12)*12, startscherm[i]*12, 0, 12, 12);
			}
			//={10,15,10,0,3};
			for(int i = 0; i < 4; i++){
				int b = titleCurrent[i];
				int vormpje = titleScreen[i][b][0];
				int x = titleScreen[i][b][1];
				int y = titleScreen[i][b][2];
				int flip = titleScreen[i][b][3];
				int rotation = titleScreen[i][b][4];
				
				if(b<19){
				if(tick%20==19&&x!=titlePlayer[i][0]){
					if(x>titlePlayer[i][0]){
						titlePlayer[i][0]++;
						}
						else{
						titlePlayer[i][0]--;
					}
				}
				if(tick%20==9&&y!=titlePlayer[i][1]){
					if(y>titlePlayer[i][1]){
						titlePlayer[i][1]++;
					}else{
						titlePlayer[i][1]--;
					}
				}
				if(x==titlePlayer[i][0]&&y==titlePlayer[i][1]){
					if(tick%20==19&&flip!=titlePlayer[i][2]){
						titlePlayer[i][2]++;
					}
					if(tick%20==9&&rotation!=titlePlayer[i][3]){
						titlePlayer[i][3]++;
					}
				}
				if(x==titlePlayer[i][0]&&y==titlePlayer[i][1]&&flip==titlePlayer[i][2]&&rotation==titlePlayer[i][3]){
					do{
						titleCurrent[i]++;
					}while(titleScreen[i][titleCurrent[i]][1]==0&&titleScreen[i][titleCurrent[i]][2]==0&&titleCurrent[i]<19);
					char breedte[32];
					copy_string(breedte, vormen[vormpje]);
					rotate(breedte, titlePlayer[i][2], titlePlayer[i][3]);
			
					int cool = strlen(breedte)-1;
					int coolp = (breedte[cool] - '0');
					
					for(int k=0; k < cool; k++){//piece
						if(breedte[k]=='1'){
							//sf2d_draw_texture_part(tex3, i%coolp*12+x_as*12, i/coolp*12+y_as*12, 6*12+12, 0, 12, 12);
							startscherm[k%coolp+titlePlayer[i][0]+(k/coolp+titlePlayer[i][1])*(400/12)] = i+1;
						}
					}
					if(i==0){
						titlePlayer[i][0] = 0;
						titlePlayer[i][1] = 0;
					}else if(i==1){
						titlePlayer[i][0] = (400/12)-1;
						titlePlayer[i][1] = 0;
					}else if(i==2){
						titlePlayer[i][0] = 0;
						titlePlayer[i][1] = (240/12-1)-1;
					}else{
						titlePlayer[i][0] = (400/12)-1;
						titlePlayer[i][1] = (240/12-1)-1;
					}
					titlePlayer[i][2] = 0;
					titlePlayer[i][3] = 0;
				}else{
				
					char breedte[32];
					copy_string(breedte, vormen[vormpje]);
					rotate(breedte, titlePlayer[i][2], titlePlayer[i][3]);
			
					int cool = strlen(breedte)-1;
					int coolp = (breedte[cool] - '0');

					for(int k=0; k < cool; k++){//piece
						if(breedte[k]=='1'){
							//sf2d_draw_texture_part(tex3, i%coolp*12+x_as*12, i/coolp*12+y_as*12, 6*12+12, 0, 12, 12);
							sf2d_draw_texture_part(tex3, (k%coolp+titlePlayer[i][0])*12, (k/coolp+titlePlayer[i][1])*12, i*12+12, 0, 12, 12);
						}
					}
				}
			}else{
				if(optacie+1<255){
					optacie = optacie + 1;
				}else{optacie=100;}
				char str[80];
				sprintf(str, "Klik op %c om verder te gaan", 'A');
				int length = sftd_get_text_width(font, 30, str);
				sftd_draw_text(font, (400-length)/2, 110, RGBA8(0, 0, 0, 255), 30, str);
				//sftd_draw_textf(font, (400-length)/2, 140, RGBA8(0, 0, 0, 255), 20, "%d", optacie);
				}
			}

			//stukje, rotaion, flip, x, y,
			tick++;
		}else if(gameStatus == 2){
				int hoogsteScore = -100;
				int beste = 0;
				int gelijk = 0;
				for(int k = 0 ; k <= totalPlayers; k++){
					if(getFinalScore()[k]>hoogsteScore){
						hoogsteScore = getFinalScore()[k];
						beste = k;
					}else if(getFinalScore()[k]>=hoogsteScore){
						beste = k;
						gelijk = 1;
					}
				}
			
				char str[80];
				
				if(gelijk==0){
					sprintf(str, "Speler %d heeft gewonnen!", beste);
					int length = sftd_get_text_width(font, 20, str);
					sftd_draw_textf(font, (400-length)/2, 110, RGBA8(255, 255, 255, 255), 20, "Speler %d heeft gewonnen!", beste);
				}else{
					sprintf(str, "gelijkspel!");
					int length = sftd_get_text_width(font, 20, str);
					sftd_draw_textf(font, (400-length)/2, 110, RGBA8(255, 255, 255, 255), 20, "gelijkspel");
				}
		}
		sf2d_end_frame();
		
		frames = (frames + 1) % 1000;

		sf2d_swapbuffers();
	}
	sf2d_free_texture(tex3);
	sftd_free_font(font);
	sftd_fini();

	sf2d_fini();
	return 0;
}
