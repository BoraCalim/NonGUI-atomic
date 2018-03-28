#include <stdio.h>
#include <stdlib.h>

int board[8][8] = {{82,78,66,81,75,66,78,82},{80,80,80,80,80,80,80,80},{46,46,46,46,46,46,46,46},{46,46,46,46,46,46,46,46},
	{46,46,46,46,46,46,46,46},{46,46,46,46,46,46,46,46},{112,112,112,112,112,112,112,112},{114,110,98,113,107,98,110,114}};

int whosemove=0, gameended=0;
int move[4];

void movepiece(int line1, int file1, int line2, int file2){
	if(board[line2][file2]==46){
		board[line2][file2]=board[line1][file1];
		board[line1][file1]=46;
	}
	else{
		explosion(line2, file2);
		board[line1][file1]=46;
	}
	whosemove= !(whosemove);
	printboard();
	return;
}

void er(){
	printf("Error; illegal move!\n");
	printboard();
	return;
}

int explosion(int a, int b){
	int i,j;
	board[a][b]=46;
	for(i=-1;i<=1;i++){
		for(j=-1;j<=1;j++)
		{ 
			if(a+i<8 && a+i>=0 && b+j<8 && b+j>=0 && board[a+i][b+j]!=80 && board[a+i][b+j]!=112)
				{
					board[a+i][b+j]=46;
				}
			}
		}
	
	return;
}

void printboard(){
	int i, j;
	for(i=7;i>=0;i--){
		for(j=0;j<=7;j++){
			printf("%c ", board[i][j]);
		}
		printf("\t\t");
		for(j=0;j<=7;j++){
			printf("(%d,%d) ",i,j);
		}
		printf("\n");
	}
}

void inputmoves(){
	scanf("%d %d %d %d",&move[0],&move[1],&move[2],&move[3]);
	if((move[0]<=-1)||(move[0]>=8)||(move[1]<=-1)||(move[1]>=8)||(move[2]<=-1)||(move[2]>=8)||(move[3]<=-1)||(move[3]>=8)){
		er();
		return;
	}
	if(board[move[0]][move[1]]==46){
		er();
		return;
	}
	if(whosemove==1 && (board[move[0]][move[1]]>=66) && ( board[move[0]][move[1]]<=82)){
		er();
		return;
	}
	if(whosemove==0 && (board[move[0]][move[1]]>=98) && (board[move[0]][move[1]]<=114)){
		er();
		return;
	}
	if((board[move[2]][move[3]]!=46) && (whosemove==1 )&& ((board[move[2]][move[3]]>=98) && (board[move[2]][move[3]]<=114))){
		er();
		return;
	}
	if((board[move[2]][move[3]]!=46) && (whosemove==0 )&& ((board[move[2]][move[3]]>=66) && (board[move[2]][move[3]]<=82))){
		er();
		return;
	}
	if((board[move[0]][move[1]]==66)|| (board[move[0]][move[1]]==98) ){
		bishop(move[0],move[1],move[2],move[3]);
	}
	if((board[move[0]][move[1]]==82)|| (board[move[0]][move[1]]==114) ){
		rook(move[0],move[1],move[2],move[3]);
	}
	if((board[move[0]][move[1]]==80)|| (board[move[0]][move[1]]==112) ){
		pawn(move[0],move[1],move[2],move[3]);
	}
	if((board[move[0]][move[1]]==81)|| (board[move[0]][move[1]]==113) ){
		queen(move[0],move[1],move[2],move[3]);
	}
	if((board[move[0]][move[1]]==107)|| (board[move[0]][move[1]]==75) ){
		king(move[0],move[1],move[2],move[3]);
	}
	if((board[move[0]][move[1]]==78)|| (board[move[0]][move[1]]==110) ){
		knight(move[0],move[1],move[2],move[3]);
	}
}


void bishop(int line1, int file1, int line2, int file2){
	int flag=0, i, j;
	int x= ((line2-line1)>0) ? 1: -1, y= ((file2-file1)>0) ? 1: -1; // controlling the increments
	if(abs((line2-line1) )==abs((file2-file1))){
		
		for(i=x, j=y;(!flag) && ((line1+i)!=(line2)) && ((file1+j)!=file2);i+=x, j+=y){
			if(board[line1+i][file1+j]!=46){
				flag=1;
			}
		}if(!flag){
			movepiece(line1,file1,  line2,file2);
		}else{
			er();
			return;
		}
	}else{
		er();
		return;
	}
}

void rook(int line1, int file1, int line2, int file2){
	int flag, i, x, y;
	x = (line2-line1>0)||(file2-file1>0) ? 1: -1; i=x;
	if((line1==line2) || (file1==file2)){
		if(line1==line2 && file1!=file2){
			for(flag=0;!flag && (file1+i)<file2;i+=x){//geçtiği karelerden biri (ama gittiği kare değil) doluysa çıkıyor
				if(board[line1][file1+i]!=46){
					er();
					return;
				}
			} 
			movepiece(line1,file1,line2,file2);
		} 
		else if(file1==file2 && line1!=line2){
			for(flag=0;!flag && (line1+i)<line2;i+=x){
				if(board[line1+i][file1]!=46){
					er();
					return;
				}	
			}
			movepiece(line1,file1,line2,file2);
		}else{er(); return;
		}
	}else {er(); return;
	}
}

int finished(){
	int flag1=0, flag2=0, i, j;
	for(i=7;i>=0;i--){
		for(j=0;j<=7;j++){
			if(board[i][j]==75){
				flag1=1;
			}
			if(board[i][j]==107){
				flag2=1;
			}
		}
	}
	if(flag1==0 && flag2==0){
		gameended=1;
		winmessage(2);
		return 2;
	}
	else if(flag1==0){
		gameended=1;
		winmessage(-1);
		return -1;
	}else if(flag2==0){
		gameended=1;
		winmessage(1);
		return 1;
	}
	else return 0;
}

int winmessage(int a){
	switch(a){
		case 2: printf("Game ended. Draw.\n"); break;
		case 1: printf("Game ended. White won.\n"); break;
		case -1: printf("Game ended. Black won.\n"); break;
	}
	return a;
}

void pawn(int line1, int file1, int line2, int file2){
	int mode = line2-line1;
	int capt = file2-file1;
	if(file1==file2){
			if ((capt==0 && mode == 2 && board[line1][file1]==80 && line1==1)||(capt==0 && mode == -2 && board[line1][file1]==112 && line1==6)){
			if( board[move[0]+(-(whosemove*2)+1)][move[1]]==46 && board[move[0]+(-(whosemove*2)+1)*2][move[1]]==46 )
				movepiece(line1, file1, line2, file2);
			else {er(); return;
			}
		}else if ((mode==1 &&board[move[2]][move[3]]==46)||(mode==-1 &&board[move[2]][move[3]]==46)) 
				movepiece(line1, file1, line2, file2);
		else if(board[move[2]][move[3]]!=46 && (move[2]-move[0])==(-(whosemove*2)+1))
				movepiece(line1, file1, line2, file2);
		else {
			er();
			return;
		}
	}else if((capt==1||capt==-1) && mode == 1 && board[move[2]][move[3]]!=46){
		movepiece(line1, file1, line2, file2);
	}
	else{er(); return;
	}
	
}

void queen(int line1, int file1, int line2, int file2){
	if((line1==line2) || (file1==file2)){
		if(!(line1==line2 && file1==file2)){
			rook(line1,file1,line2,file2);
		}else{er(); return;
		}
	}else if(abs(file2-file1)==abs(line2-line1)){
		bishop(line1, file1,  line2, file2);
	}else {
		er(); return;
	}
}

void king(int line1, int file1, int line2, int file2){
	int l=abs(line2-line1), f=abs(file2-file1);
	if((l<=1)&&(f<=1)){
		movepiece(line1,file1,line2,file2);
	}
	else{
		er(); return;
	}
}

void knight(int line1, int file1, int line2, int file2){
	int l=abs(line2-line1), f=abs(file2-file1);
	if((l==1 && f==2)||(l==2 && f==1)){
		movepiece(line1,file1,line2,file2);
	}
	else{
		er();
		return;
	}
}

int main() {
	printboard();
	while(!gameended){
		inputmoves();
		finished();
	}	 
	system("PAUSE");
	return 0;
}
